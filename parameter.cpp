#include "parameter.h"

Parameter::Parameter(QString name):
	name(name)
{}

Parameter::~Parameter()
{}

QString Parameter::getName() const
{
	return name;
}


