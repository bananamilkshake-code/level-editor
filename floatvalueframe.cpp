#include "floatvalueframe.h"
#include "ui_floatvalueframe.h"

#include "floatparameter.h"

FloatValueFrame::FloatValueFrame(QWidget *parent, const FloatParameter *parameter, QString value):
	ValueFrame(parent, parameter, value)
{
	ui->setupUi(this);

	this->ui->spinValue->setMinimum(parameter->getMin());
	this->ui->spinValue->setMaximum(parameter->getMax());
	this->ui->spinValue->setValue(value.toFloat());
}

FloatValueFrame::~FloatValueFrame()
{
	delete ui;
}

QString FloatValueFrame::getValue() const
{
	return this->ui->spinValue->text();
}
