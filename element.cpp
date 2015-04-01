#include "element.h"

Element::Element(QString name, QPixmap pixmap):
	name(name), pixmap(pixmap)
{}

Element::~Element()
{}

QString Element::getName() const
{
	return this->name;
}

QPixmap Element::getPixmap() const
{
	return this->pixmap;
}

