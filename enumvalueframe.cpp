#include "enumvalueframe.h"
#include "ui_enumvalueframe.h"

#include "enumparameter.h"

EnumValueFrame::EnumValueFrame(QWidget *parent, const EnumParameter *parameter, QString value):
	ValueFrame(parent, parameter, value),
	ui(new Ui::EnumValueFrame)
{
	ui->setupUi(this);

	this->ui->boxEnumValues->addItems(parameter->getValues());
}

EnumValueFrame::~EnumValueFrame()
{
	delete ui;
}

QString EnumValueFrame::getValue() const
{
	return this->ui->boxEnumValues->currentText();
}
