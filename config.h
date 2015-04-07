#pragma once

#include <QString>

// In future this class can be used to load configuration
// infogmation from file.

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

