#pragma once

#include <QGroupBox>
#include <QPoint>
#include <QSet>

#include "element.h"
#include "elementdescription.h"

namespace Ui {
class LevelDescriptionWidget;
}

class ValueFrame;

class ElementDescriptionWidget : public QGroupBox
{
	Q_OBJECT

public:
	explicit ElementDescriptionWidget(QWidget *parent = 0);
	~ElementDescriptionWidget();

	void showElement(const ElementDesc &desc, QPoint position, const QHash<QString, Element> &elements);

private:
	Ui::LevelDescriptionWidget *ui;

	QSet<ValueFrame*> valuesFrames;

	void freeValuesFrames();
	void showParameter(const std::shared_ptr<Parameter> &paramDesc, QString value);
};
