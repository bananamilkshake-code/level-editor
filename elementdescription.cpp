#include "elementdescription.h"

ElementDesc::ElementDesc(const QString &name, QHash<QString, QString> params):
	name(name),
	params(params)
{}

void ElementDesc::setParam(QString name, QString value)
{
	this->params[name] = value;
}

QString ElementDesc::getName() const
{
	return this->name;
}

const QHash<QString, QString> ElementDesc::getParams() const
{
	return this->params;
}

bool ElementDesc::isEmpty() const
{
	// If this is eraser.
	return this->name.isNull();
}
