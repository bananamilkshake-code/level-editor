#pragma once

#include <QString>

class Parameter
{
public:
	enum Type
	{
		TypeFloat,
		TypeEnum
	};

	explicit Parameter(QString name);
	virtual ~Parameter();

	QString getName() const;

	virtual Type getType() const = 0;

private:
	QString name;
};
