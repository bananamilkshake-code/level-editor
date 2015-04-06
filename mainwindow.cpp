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

	this->ui->drawArea->prepareForLevel(Level::SIZE);

	this->updateElementsList();

	this->changeMenuState(LevelUnloaded);
	this->changeToolSelection(ActionSelect);

	this->ui->centralWidget->adjustSize();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::levelChanged()
{
	this->changeMenuState(LevelChanged);
}

void MainWindow::selectElement(QPoint position) const
{
	ElementDesc &elementDesc = this->level->select(position);

	this->information(QString("Element selected %1").arg(elementDesc.getName()));

	this->ui->groupBoxElementDesc->showElement(elementDesc, position, this->elements);
}

void MainWindow::changeParameter(QPoint position, const QString parameter, const QString newValue)
{
	this->information(QString("Parameter %1 for element on position (%2, %3) changed to %4").arg(parameter , QString::number(position.x()), QString::number(position.y()), newValue));

	this->level->changeParameter(position, parameter, newValue);
}

void MainWindow::placeElementOnLevel(const QString &elementName, QPoint position)
{
	auto element = this->elements.find(elementName);

	QString replacedElement = this->level->add(element.value(), position);

	this->elementUsed(elementName);
	this->elementUnused(replacedElement);

	this->selectElement(position);
}

void MainWindow::placeLoadedElement(const QString &name, QPoint position)
{
	auto element_iter = this->elements.constFind(name);
	if (element_iter == this->elements.end())
	{
		return;
	}

	this->information("Element with name " + name);

	this->ui->drawArea->drawElement(element_iter.value(), position);
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

void MainWindow::information(const QString &text) const
{
	qDebug() << text;
}

static const QString LEVEL_STANDART_NAME = "newlevel";

void MainWindow::on_actionNewLevel_triggered()
{
	if (!this->closeLevel())
		return;

	this->level = new Level(LEVEL_STANDART_NAME, Level::SIZE);

	this->ui->drawArea->prepareForLevel(Level::SIZE);

	this->levelChanged();
	this->bindSlots();
}

void MainWindow::on_actionSaveLevel_triggered()
{
	if (this->level->isNew())
	{
		this->on_actionSaveAs_triggered();
		return;
	}

	this->level->save();

	this->changeMenuState(LevelLoaded);
}

void MainWindow::on_actionSaveAs_triggered()
{
	QString saveName = QFileDialog::getSaveFileName(this, tr("Сохранить"), QString(), LEVEL_FILE_FILTER);
	if (saveName.isEmpty())
		return;

	QString name;
	QString path;
	extarctNameAndPath(saveName, name, path);

	this->level->saveAs(name, path);

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

	this->printLevel();
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

void MainWindow::on_actionUploadElements_triggered()
{
	this->elements.clear();
	this->ui->listElements->clear();

	this->updateElementsList();
}

void MainWindow::on_listElements_itemClicked(QListWidgetItem *item)
{
	this->changeToolSelection(ActionPaint);

	auto elementIter = this->elements.find(item->text());
	if (elementIter == this->elements.end())
	{
		this->information("No element with name " + item->text());
		return;
	}

	if (elementIter.value().isUsedLast())
	{
		this->on_buttonSelect_clicked();
	}
	else
	{
		this->ui->drawArea->setCurrentElement(elementIter.value());
	}
}

void MainWindow::on_buttonEraser_clicked()
{
	this->changeToolSelection(ActionErase);

	this->ui->drawArea->setEraser();
}

void MainWindow::on_buttonSelect_clicked()
{
	this->changeToolSelection(ActionSelect);

	this->ui->drawArea->startSelecting();
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
	QObject::connect(this->ui->drawArea, SIGNAL(elementPlaced(QString, QPoint)), this, SLOT(placeElementOnLevel(QString, QPoint)));
	QObject::connect(this->ui->drawArea, SIGNAL(elementSelected(QPoint)), this, SLOT(selectElement(QPoint)));
	QObject::connect(this->ui->drawArea, SIGNAL(information(QString)), this, SLOT(information(QString)));

	QObject::connect(this->level, SIGNAL(changed()), this, SLOT(levelChanged()));
	QObject::connect(this->level, SIGNAL(information(QString)), this, SLOT(information(QString)));

	QObject::connect(this->ui->groupBoxElementDesc, SIGNAL(parameterChanged(QPoint,QString,QString)), this, SLOT(changeParameter(QPoint,QString,QString)));
}

void MainWindow::changeMenuState(MenuState state)
{
	this->ui->drawArea->setEnabled(LevelUnloaded != state);
	this->ui->actionSaveLevel->setEnabled(LevelChanged == state);
	this->ui->actionSaveAs->setEnabled(LevelChanged == state);
}

void MainWindow::changeToolSelection(ToolSelection toolSelection)
{
	this->ui->actionChangeElement->setEnabled(ActionPaint == toolSelection);
	this->ui->listElements->setItemSelected(this->ui->listElements->currentItem(), ActionPaint == toolSelection);
	this->ui->buttonSelect->setDown(ActionSelect == toolSelection);
	this->ui->buttonEraser->setDown(ActionErase == toolSelection);
}

static const QColor COLOR_ITEM_UNAVAILABLE = Qt::red;
static const QColor COLOR_ITEM_AVAILABLE = Qt::black;

void MainWindow::elementUsed(const QString &elementName, bool boundToZero)
{
	auto elementIter = this->elements.find(elementName);
	if (elementIter == this->elements.end() || !elementIter.value().usedLast(boundToZero))
		return;

	this->information("Element " + elementName + " comes to it's limit");

	this->findElementItem(elementName)->setTextColor(COLOR_ITEM_UNAVAILABLE);

	this->on_buttonSelect_clicked();
}

void MainWindow::elementUnused(const QString &elementName)
{
	auto elementIter = this->elements.find(elementName);
	if (elementIter == this->elements.end() || !elementIter.value().releaseOne())
		return;

	this->information("Element " + elementName + " must be unlocked");

	this->findElementItem(elementName)->setTextColor(COLOR_ITEM_AVAILABLE);
}

void MainWindow::loadElement(const QString &elementName)
{
	Element newElement(elementName);

	newElement.load(this->config.getElementsDictory());

	this->addElement(std::move(newElement));
}

void MainWindow::printLevel()
{
	this->resetElementsUsage();

	this->ui->drawArea->prepareForLevel(this->level->getSize());

	QSize levelSize = this->level->getSize();
	for (int x = 0; x < levelSize.width(); ++x)
	{
		for (int y = 0; y < levelSize.height(); ++y)
		{
			QPoint position(x, y);
			auto element = this->level->select(position);
			if (element.isEmpty())
				continue;

			auto elementIter = this->elements.constFind(element.getName());
			if (elementIter == this->elements.end())
			{
				this->information("No element with name " + element.getName() + " to print");
				continue;
			}

			this->elementUsed(element.getName(), false);

			this->ui->drawArea->drawElement(elementIter.value(), position);
		}
	}
}

void MainWindow::resetElementsUsage()
{
	for (auto elementIter = this->elements.begin(); elementIter != this->elements.end(); ++elementIter)
	{
		elementIter.value().resetLimit();
	}
}

void MainWindow::updateElementsList()
{
	this->elements.insert(QString(), this->ui->drawArea->ERASER);

	QDir directory(this->config.getElementsDictory());
	auto elements = directory.entryList(QStringList("[A-Za-z]*"), QDir::Filter::Dirs);
	for (QString elementName : elements)
	{
		this->loadElement(elementName);
	}
}

QListWidgetItem* MainWindow::findElementItem(const QString &elementName)
{
	for (int itemId = 0; itemId < this->ui->listElements->count(); ++itemId)
	{
		QListWidgetItem *currentItem = this->ui->listElements->item(itemId);
		if (currentItem->text() == elementName)
			return currentItem;
	}

	return nullptr;
}
