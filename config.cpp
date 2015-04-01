#include "config.h"

Config::Config():
	elementsDictory("C:\\elements"),
	elementPictureName("pic.png")
{}

Config::~Config()
{}

QString Config::getElementsDictory() const
{
	return elementsDictory;
}

void Config::setElementsDictory(const QString &value)
{
	elementsDictory = value;
}

QString Config::getElementPictureName() const
{
	return elementPictureName;
}

void Config::setElementPictureName(const QString &value)
{
	elementPictureName = value;
}

