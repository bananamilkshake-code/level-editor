#pragma once

#include <QMainWindow>
#include <QLayout>

#include "config.h"
#include "drawarea.h"
#include "level.h"
#include "element.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void onActionNewLevelTriggered();
	void onActionSaveTriggered();
	void onActionLoadTriggered();

	void onActionAddItemTriggered();

	void on_listElements_clicked(const QModelIndex &index);

private:
	Config config;

	Ui::MainWindow *ui;

	DrawArea *drawArea;

	QList<Element> elements;

	void loadElement(const QString &elementName);
	void updateElementsList();
};
