#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPixmap>
#include <QDirIterator>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent):
	QMainWindow(parent),
	ui(new Ui::MainWindow)
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
}

MainWindow::~MainWindow()
{
	delete this->drawArea;
	delete ui;
}

void MainWindow::onActionNewLevelTriggered()
{}

void MainWindow::onActionSaveTriggered()
{}

void MainWindow::onActionLoadTriggered()
{}

void MainWindow::onActionAddItemTriggered()
{}

void MainWindow::on_listElements_clicked(const QModelIndex &index)
{
	const Element &selectedElement = this->elements[index.row()];

	this->drawArea->setCurrentPixmap(selectedElement.getPixmap());
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

	this->elements.push_back(Element(elementName, pixmap));

	this->ui->listElements->addItem(elementName);
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
