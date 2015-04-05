#include "valueframe.h"

#include "parameter.h"

ValueFrame::ValueFrame(QWidget* parent, const Parameter *parameter, QString value):
	QGroupBox(parameter->getName(), parent),
	value(value)
{}

ValueFrame::~ValueFrame()
{}

QPair<QString, QString> ValueFrame::getChanged() const
{
	return QPair<QString, QString>(this->title(), this->getValue());
}

void ValueFrame::onChange()
{
	emit changed(this->title(), this->getValue());
}
