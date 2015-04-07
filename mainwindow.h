#pragma once

#include <QMainWindow>
#include <QLayout>

#include "config.h"
#include "drawarea.h"
#include "level.h"
#include "element.h"

class QCloseEvent;
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
	void levelChanged();
	void selectElement(QPoint position) const;
	void changeParameter(QPoint position, const QString parameter, const QString newValue);
	void placeElementOnLevel(const QString &elementName, QPoint position);
	void placeLoadedElement(const QString &name, QPoint position);
	void addElement(Element element);
	void replaceElement(Element element);

private slots:
	void on_actionNewLevel_triggered();
	void on_actionSaveLevel_triggered();
	void on_actionSaveAs_triggered();
	void on_actionLoadLevel_triggered();
	void on_actionAddElement_triggered();
	void on_actionChangeElement_triggered();
	void on_actionUploadElements_triggered();

	void on_listElements_itemClicked(QListWidgetItem *item);

	void on_buttonEraser_clicked();
	void on_buttonSelect_clicked();

protected:
	void closeEvent(QCloseEvent *event) override;

private:
	enum MenuState
	{
		LevelUnloaded,
		LevelLoaded,
		LevelChanged,
	};

	enum ToolSelection
	{
		ActionErase,
		ActionPaint,
		ActionSelect,
	};

	static const QString LEVEL_FILE_FILTER;

	static void extarctNameAndPath(QString source, QString &name, QString &path);

	Config config;

	Ui::MainWindow *ui;

	Level *level;

	QHash<QString, Element> elements;

	bool closeLevel();

	void adjustLayout();
	void bindSlots();
	void changeMenuState(MenuState state);
	void changeToolSelection(ToolSelection toolSelection);
	void elementUsed(const QString &elementName);
	void elementUnused(const QString &elementName);
	void loadElement(const QString &elementName);
	void printLevel();
	void resetElementsUsage();
	void updateElementsList();

	QListWidgetItem* findElementItem(const QString &elementName);
};
