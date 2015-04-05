#pragma once

#include "parameter.h"

class FloatParameter : public Parameter
{
public:
	FloatParameter(QString name, float min, float max);
	~FloatParameter();

	Type getType() const override;
	QString getDefault() const override;

	float getMin() const;
	float getMax() const;

private:
	float min;
	float max;
};
