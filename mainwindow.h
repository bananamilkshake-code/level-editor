#pragma once

#include <QMainWindow>

#include "drawarea.h"

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

private:
	Ui::MainWindow *ui;

	DrawArea *drawArea;

	void updateElementsList();
};
