#include "valueframe.h"

#include "parameter.h"

ValueFrame::ValueFrame(QWidget* parent, const Parameter *parameter, QString value):
	QGroupBox(parent),
	value(value)
{
	this->setTitle(parameter->getName());
}

ValueFrame::~ValueFrame()
{}


QPair<QString, QString> ValueFrame::getChanged() const
{
	return QPair<QString, QString>(this->title(), this->getValue());
}
