#pragma once

#include <QGroupBox>

#include "elementdescription.h"

namespace Ui {
class LevelDescriptionWidget;
}

class ElementDescriptionWidget : public QGroupBox
{
	Q_OBJECT

public:
	explicit ElementDescriptionWidget(QWidget *parent = 0);
	~ElementDescriptionWidget();

	void showElement(const ElementDesc &desc);

private:
	Ui::LevelDescriptionWidget *ui;
};
