#include "elementdescription.h"

ElementDesc::ElementDesc(const QString &name):
	name(name)
{}

QString ElementDesc::getName() const
{
	return this->name;
}

const QHash<QString, QString> ElementDesc::getParams() const
{
	return this->params;
}
