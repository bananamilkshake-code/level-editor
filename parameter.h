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

	Parameter(QString name);
	~Parameter();

	QString getName() const;

	virtual Type getType() const = 0;

private:
	QString name;
};
