#include "element.h"

#include <QDir>
#include <QFile>

const QString Element::EXTENSION = ".element";

Element::Element(QString name):
	Element(name, QPixmap())
{}

Element::Element(QString name, QPixmap pixmap):
	name(name), pixmap(pixmap)
{}

Element::~Element()
{}

QString Element::getName() const
{
	return this->name;
}

const QPixmap& Element::getPixmap() const
{
	return this->pixmap;
}

const Element::parameters_t& Element::getParameters() const
{
	return this->parameters;
}

void Element::load(QString directory)
{
	QFile file(this->getPath(directory));
	file.open(QIODevice::ReadOnly);
	QDataStream in(&file);

	in >> this->pixmap;
}

void Element::save(QString directory) const
{
	QFile file(this->getPath(directory));
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file);

	out << this->pixmap;
}

QString Element::getPath(QString directory) const
{
	return QString(directory + QDir::separator() + this->getName() + EXTENSION);
}

