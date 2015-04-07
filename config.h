#pragma once

#include <QString>

// In future this class can be used to load configuration
// infogmation from file.

class Config
{
public:
	Config();
	~Config();

	QString getElementsDictory() const;
	void setElementsDictory(const QString &value);

	void update();

private:
	QString elementsDictory;
};

