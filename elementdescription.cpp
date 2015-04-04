#include "elementdescription.h"

ElementDesc::ElementDesc(const QString &name):
	name(name)
{}

QString ElementDesc::getName() const
{
	return this->name;
}
