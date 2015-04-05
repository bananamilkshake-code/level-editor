#include "enumparameter.h"

EnumParameter::EnumParameter(QString name, QStringList values):
	Parameter(name),
	values(values)
{}

EnumParameter::~EnumParameter()
{}

Parameter::Type EnumParameter::getType() const
{
	return Parameter::TypeEnum;
}

const QStringList& EnumParameter::getValues() const
{
	return this->values;
}
