#pragma once

#include <QString>

class Config
{
public:
	static const QString ELEMENT_PICTURE_NAME;

	Config();
	~Config();

	QString getElementsDictory() const;
	void setElementsDictory(const QString &value);

	void update();

private:
	QString elementsDictory;
};

