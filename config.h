#pragma once

#include <QString>

class Config
{
public:
	Config();
	~Config();

	QString getElementsDictory() const;
	void setElementsDictory(const QString &value);

	QString getElementPictureName() const;
	void setElementPictureName(const QString &value);

private:
	QString elementsDictory;
	QString elementPictureName;
};

