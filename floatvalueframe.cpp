#include "floatvalueframe.h"
#include "ui_floatvalueframe.h"

#include "floatparameter.h"

FloatValueFrame::FloatValueFrame(QWidget *parent, const FloatParameter *parameter, QString value):
	ValueFrame(parent, parameter, value),
	ui(new Ui::FloatValueFrame)
{
	ui->setupUi(this);

	this->ui->spinValue->setMinimum(parameter->getMin());
	this->ui->spinValue->setMaximum(parameter->getMax());
	this->ui->spinValue->setValue(value.toFloat());

	this->setTitle(parameter->getName());
}

FloatValueFrame::~FloatValueFrame()
{
	delete ui;
}

QString FloatValueFrame::getValue() const
{
	return this->ui->spinValue->text();
}

void FloatValueFrame::on_spinValue_valueChanged(const QString &)
{
	this->onChange();
}
