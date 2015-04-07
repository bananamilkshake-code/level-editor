#include "config.h"

#include <QCoreApplication>
#include <QDir>

Config::Config():
	elementsDictory("elements")
{}

Config::~Config()
{}

QString Config::getElementsDictory() const
{
	return (QCoreApplication::applicationDirPath() + QDir::separator() + elementsDictory);
}

void Config::setElementsDictory(const QString &value)
{
	elementsDictory = value;
}

void Config::update()
{}
