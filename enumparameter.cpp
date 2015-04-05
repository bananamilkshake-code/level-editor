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

QString EnumParameter::getDefault() const
{
	return this->getValues()[0];
}

const QStringList& EnumParameter::getValues() const
{
	return this->values;
}
