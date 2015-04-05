#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>
#include <QDebug>
#include <QDirIterator>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QUrl>

#include "elementdialog.h"

const QString MainWindow::LEVEL_FILE_FILTER = "Levels (*.level)";

void MainWindow::extarctNameAndPath(QString source, QString &name, QString &path)
{
	source = QDir::toNativeSeparators(source);
	int lastSeparatorIndex = source.lastIndexOf(QDir::separator());

	path = source.mid(0, lastSeparatorIndex);
	name = source.mid(lastSeparatorIndex + 1, source.size() - lastSeparatorIndex);
}

MainWindow::MainWindow(QWidget *parent):
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	level(nullptr)
{
	this->ui->setupUi(this);

	this->drawArea = new DrawArea(this, Level::SIZE * DrawArea::PROPORTION);

	this->ui->layoutDrawArea->addWidget(this->drawArea);

	this->updateElementsList();

	this->changeMenuState(LevelUnloaded);
	this->changeToolSelection(ActionSelect);

	this->ui->centralWidget->adjustSize();
}

MainWindow::~MainWindow()
{
	delete this->drawArea;

	delete ui;
}

void MainWindow::selectElement(QPoint position)
{
	auto &elementDesc = this->level->select(position);

	qDebug() << "Element selected " << elementDesc.getName();

	this->ui->groupBoxElementDesc->showElement(elementDesc, this->elements);
}

void MainWindow::placeElementOnLevel(const QString &name, QPoint position)
{
	auto element = this->elements.constFind(name);
	this->level->add(element.value(), position);

	this->changeMenuState(LevelChanged);

	this->selectElement(position);
}

void MainWindow::placeLoadedElement(const QString &name, QPoint position)
{
	auto element_iter = this->elements.constFind(name);
	if (element_iter == this->elements.end())
	{
		return;
	}

	qDebug() << "Element with name " << name;

	this->drawArea->setCurrentElement(element_iter.value());
	this->drawArea->setCurrentPosition(position);

	this->drawArea->repaint();
}

void MainWindow::addElement(Element element)
{
	this->elements.insert(element.getName(), element);

	this->ui->listElements->addItem(element.getName());
}

void MainWindow::replaceElement(Element element)
{
	QListWidgetItem *selectedElement = this->ui->listElements->currentItem();
	auto elementIter = this->elements.find(selectedElement->text());

	this->ui->listElements->removeItemWidget(selectedElement);
	this->elements.erase(elementIter);

	this->addElement(element);
}

void MainWindow::on_actionNewLevel_triggered()
{
	if (!this->closeLevel())
		return;

	QString name = QInputDialog::getText(this, "Новый уровень", "Введите имя нового уровня");
	if (name.isEmpty())
		return;

	this->level = new Level(name, Level::SIZE);

	this->changeMenuState(LevelChanged);

	this->bindSlots();
}

void MainWindow::on_actionSaveLevel_triggered()
{
	QString saveName = QFileDialog::getSaveFileName(this, tr("Сохранить"), QString(), LEVEL_FILE_FILTER);
	if (saveName.isEmpty())
		return;

	QString name;
	QString path;

	extarctNameAndPath(saveName, name, path);

	this->level->save(name, path);

	this->changeMenuState(LevelLoaded);
}

void MainWindow::on_actionLoadLevel_triggered()
{
	if (!this->closeLevel())
		return;

	QString url = QFileDialog::getOpenFileName(this, tr("Открыть"), QString(), LEVEL_FILE_FILTER);
	if (url.isEmpty())
		return;

	QString name;
	QString path;

	extarctNameAndPath(url, name, path);

	this->level = new Level(name, path);

	this->bindSlots();

	this->level->load();

	this->changeMenuState(LevelLoaded);
}

void MainWindow::on_actionAddElement_triggered()
{
	ElementDialog dialog(this, this->config.getElementsDictory());

	QObject::connect(&dialog, SIGNAL(elementAdded(Element)), this, SLOT(addElement(Element)));

	dialog.exec();
}

void MainWindow::on_actionChangeElement_triggered()
{
	auto elementIter = this->elements.find(this->ui->listElements->currentItem()->text());

	ElementDialog dialog(this, this->config.getElementsDictory(), elementIter.value());

	QObject::connect(&dialog, SIGNAL(elementAdded(Element)), this, SLOT(replaceElement(Element)));

	dialog.exec();
}

void MainWindow::on_listElements_itemClicked(QListWidgetItem *item)
{
	this->changeToolSelection(ActionPaint);

	auto elementIter = this->elements.find(item->text());
	if (elementIter == this->elements.end())
	{
		qDebug() << "No element with name " << item->text();
		return;
	}

	this->drawArea->setCurrentElement(elementIter.value());
}

void MainWindow::on_buttonEraser_clicked()
{
	this->changeToolSelection(ActionErase);

	this->drawArea->setEraser();
}

void MainWindow::on_buttonSelect_clicked()
{
	this->changeToolSelection(ActionSelect);

	this->drawArea->startSelecting();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (this->closeLevel())
	{
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

bool MainWindow::closeLevel()
{
	if (this->level == nullptr)
		return true;

	bool toClose = true;
	if (this->level->isChanged())
	{
		QMessageBox::StandardButton reply = QMessageBox::question(this, "Изменения", "Имеются не сохраненные изменения. Сохранить?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		switch (reply)
		{
		case QMessageBox::Yes:
			this->on_actionSaveLevel_triggered();
			toClose = true;
			break;
		case QMessageBox::No:
			toClose = true;
			break;
		case QMessageBox::Cancel:
			toClose = false;
			break;
		default:
			return false;
		}
	}

	if (toClose)
		delete this->level;

	return toClose;
}

void MainWindow::bindSlots()
{
	QObject::connect(this->drawArea, SIGNAL(elementPlaced(QString, QPoint)), this, SLOT(placeElementOnLevel(QString, QPoint)));
	QObject::connect(this->drawArea, SIGNAL(elementSelected(QPoint)), this, SLOT(selectElement(QPoint)));

	QObject::connect(this->level, SIGNAL(elementLoaded(QString, QPoint)), this, SLOT(placeLoadedElement(QString, QPoint)));
}

void MainWindow::changeMenuState(MenuState state)
{
	this->drawArea->setEnabled(LevelUnloaded != state);
	this->ui->actionSaveLevel->setEnabled(LevelChanged == state);
}

void MainWindow::changeToolSelection(ToolSelection toolSelection)
{
	this->ui->actionChangeElement->setEnabled(ActionPaint == toolSelection);
	this->ui->listElements->setItemSelected(this->ui->listElements->currentItem(), ActionPaint == toolSelection);
	this->ui->buttonSelect->setDown(ActionSelect == toolSelection);
	this->ui->buttonEraser->setDown(ActionErase == toolSelection);
}

void MainWindow::loadElement(const QString &elementName)
{
	Element newElement(elementName);
	newElement.load(this->config.getElementsDictory());

	this->addElement(std::move(newElement));
}

void MainWindow::updateElementsList()
{
	QDir directory(this->config.getElementsDictory());
	auto elements = directory.entryList(QStringList("[A-Za-z]*"), QDir::Filter::Dirs);
	for (QString elementName : elements)
	{
		elementName = elementName.mid(0, elementName.lastIndexOf('.'));
		this->loadElement(elementName);
	}
}
