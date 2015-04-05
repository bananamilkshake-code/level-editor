#include "floatparameter.h"

FloatParameter::FloatParameter(QString name, float min, float max):
	Parameter(name),
	min(min),
	max(max)
{}

FloatParameter::~FloatParameter()
{}

float FloatParameter::getMin() const
{
	return min;
}

float FloatParameter::getMax() const
{
	return max;
}

Parameter::Type FloatParameter::getType() const
{
	return Parameter::TypeFloat;
}
