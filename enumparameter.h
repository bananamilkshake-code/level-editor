#pragma once

#include <QStringList>

#include "parameter.h"

class EnumParameter : public Parameter
{
public:
	EnumParameter(QString name, QStringList values);
	~EnumParameter();

	Type getType() const override;

	const QStringList& getValues() const;

public:
	QStringList values;
};
