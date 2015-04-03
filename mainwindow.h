#pragma once

#include <QMainWindow>
#include <QLayout>

#include "config.h"
#include "drawarea.h"
#include "level.h"
#include "element.h"

class QListWidgetItem;

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

public slots:
	void placeElementOnLevel(const QString &name, QPoint position);
	void placeLoadedElement(const QString &name, QPoint position);

private slots:
	void on_actionNewLevel_triggered();
	void on_actionSaveLevel_triggered();
	void on_actionLoadLevel_triggered();

	void on_listElements_itemClicked(QListWidgetItem *item);

	void on_buttonEraser_clicked();

private:
	enum MenuState
	{
		LevelUnloaded,
		LevelLoaded,
		LevelChanged
	};

	static const QString LEVEL_FILE_FILTER;

	static void extarctNameAndPath(QString source, QString &name, QString &path);

	Config config;

	Ui::MainWindow *ui;

	DrawArea *drawArea;

	Level *level;

	QHash<QString, Element> elements;

	void bindSlots();
	void closeLevel();
	void loadElement(const QString &elementName);
	void setMenuActionsState(MenuState state);
	void updateElementsList();
};
