#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDirIterator>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QUrl>

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

	this->drawArea = new DrawArea(this);
	this->drawArea->setGeometry(0,
				    this->ui->menuBar->height(),
				    Level::WIDTH * DrawArea::PROPORTION,
				    Level::HEIGHT * DrawArea::PROPORTION);

	this->ui->listElements->setGeometry(this->drawArea->geometry().width(),
					    0,
					    this->ui->listElements->width(),
					    this->drawArea->height());


	this->updateElementsList();

	this->setFixedSize(this->size());

	this->setMenuActionsState(LevelUnloaded);
}

MainWindow::~MainWindow()
{
	if (this->level)
		delete this->level;

	delete this->drawArea;

	delete ui;
}

void MainWindow::placeElementOnLevel(const QString &name, QPoint position)
{
	this->level->add(name, position);

	this->setMenuActionsState(LevelChanged);
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

void MainWindow::on_actionNewLevel_triggered()
{
	this->closeLevel();

	QString name = QInputDialog::getText(this, "Новый уровень", "Введите имя нового уровня");

	this->level = new Level(this->elements, name, QSize(Level::WIDTH, Level::HEIGHT));

	this->setMenuActionsState(LevelChanged);

	this->bindSlots();
}

void MainWindow::on_actionSaveLevel_triggered()
{
	QString saveName = QFileDialog::getSaveFileName(this, tr("Сохранить"), QString(), LEVEL_FILE_FILTER);
	QString name;
	QString path;

	extarctNameAndPath(saveName, name, path);

	this->level->save(name, path);

	this->setMenuActionsState(LevelLoaded);
}

void MainWindow::on_actionLoadLevel_triggered()
{
	this->closeLevel();

	QString url = QFileDialog::getOpenFileName(this, tr("Открыть"), QString(), LEVEL_FILE_FILTER);
	QString name;
	QString path;

	extarctNameAndPath(url, name, path);

	this->level = new Level(this->elements, name, path);

	this->bindSlots();

	this->level->load();

	this->setMenuActionsState(LevelLoaded);
}

void MainWindow::on_listElements_itemClicked(QListWidgetItem *item)
{
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
	this->drawArea->setEraser();
}

void MainWindow::bindSlots()
{
	QObject::connect(this->drawArea, SIGNAL(elementPlaced(QString, QPoint)), this, SLOT(placeElementOnLevel(QString, QPoint)));
	QObject::connect(this->level, SIGNAL(elementLoaded(QString, QPoint)), this, SLOT(placeLoadedElement(QString, QPoint)));
}

void MainWindow::closeLevel()
{
	if (this->level == nullptr)
		return;

	if (this->level->isChanged())
	{
		QMessageBox::StandardButton reply = QMessageBox::question(this, "Изменения", "Имеются не сохраненные изменения. Сохранить?", QMessageBox::Yes | QMessageBox::No);
		switch (reply)
		{
		case QMessageBox::Yes:
				this->on_actionSaveLevel_triggered();
			break;
		case QMessageBox::No:
		default:
			break;
		}
	}

	delete this->level;
}

void MainWindow::loadElement(const QString &elementName)
{
	QString pathToLevel = this->config.getElementsDictory() + QDir::separator() + elementName;
	QPixmap pixmap(pathToLevel + QDir::separator() + this->config.getElementPictureName());
	if (pixmap.isNull())
	{
		qDebug() << "Pixmap for element " << elementName << " not found.";
		return;
	}

	this->elements.insert(elementName, Element(elementName, pixmap));

	this->ui->listElements->addItem(elementName);

	this->setMenuActionsState(LevelLoaded);
}

void MainWindow::setMenuActionsState(MenuState state)
{
	switch (state)
	{
	case LevelUnloaded:
		this->ui->actionSaveLevel->setEnabled(false);
		break;
	case LevelLoaded:
		this->ui->actionSaveLevel->setEnabled(false);
		break;
	case LevelChanged:
		this->ui->actionSaveLevel->setEnabled(true);
		break;
	}
}

void MainWindow::updateElementsList()
{
	QDir directory(this->config.getElementsDictory());
	auto elementsDirectory = directory.entryList(QStringList("[A-Za-z]*"));
	for (auto elementName : elementsDirectory)
	{
		this->loadElement(elementName);
	}
}
