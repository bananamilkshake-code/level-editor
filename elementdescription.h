#pragma once

#include <QString>

struct ElementDesc
{
private:
	QString name;

public:
	ElementDesc(const QString &name);

	QString getName() const;
};
