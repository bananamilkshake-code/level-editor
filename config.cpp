#include "config.h"

const QString Config::ELEMENT_PICTURE_NAME = "pic.png";

Config::Config():
	elementsDictory("C:\\elements")
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

void Config::update()
{

}
