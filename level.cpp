#include "level.h"

Level::ElementDesc::ElementDesc():
	ElementDesc(QString())
{}

Level::ElementDesc::ElementDesc(const QString &name):
	name(name)
{}

Level::Level(const QHash<QString, Element> &elementsDescriptions, QString name, QSize size):
	elementsDescriptions(elementsDescriptions),
	name(name),
	path(QString()),
	isSaved(false)
{}

Level::Level(const QHash<QString, Element> &elementsDescriptions, QString name, QString path):
	elementsDescriptions(elementsDescriptions),
	name(name),
	path(path),
	isSaved(true)
{}

Level::~Level()
{}

bool Level::isNew() const
{
	return this->path.isNull();
}

bool Level::isChanged() const
{
	return !this->isSaved;
}

void Level::add(const QString &element, QPoint place)
{
	this->elements[place.x()][place.y()] = ElementDesc(element);

	this->isSaved = false;
}

void Level::save(QString newName, QString newPath)
{
	this->name = newName;
	this->path = newPath;

	this->isSaved = true;
}
