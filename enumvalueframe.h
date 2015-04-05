#pragma once

#include "valueframe.h"

namespace Ui {
class EnumValueFrame;
}

class EnumParameter;

class EnumValueFrame : public ValueFrame
{
	Q_OBJECT

public:
	explicit EnumValueFrame(QWidget *parent, const EnumParameter *parameter, QString value);
	~EnumValueFrame();

private:
	Ui::EnumValueFrame *ui;

	QString getValue() const override;
};
