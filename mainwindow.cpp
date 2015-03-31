#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent):
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	this->ui->setupUi(this);

	this->drawArea = new DrawArea(this);

	this->ui->verticalLayout->addWidget(this->drawArea);

	this->updateElementsList();
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

void MainWindow::updateElementsList()
{

}
