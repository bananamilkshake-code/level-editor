#pragma once

#include <QString>
#include <QPixmap>

class Parameter;

class Element
{
public:
	typedef QHash<QString, Parameter*> parameters_t;

	static const QString EXTENSION;

	Element(QString name);
	Element(QString name, QPixmap pixmap);
	~Element();

	QString getName() const;
	const QPixmap& getPixmap() const;
	const parameters_t& getParameters() const;

	void load(QString directory);
	void save(QString directory) const;

private:
	QString name;
	QPixmap pixmap;
	parameters_t parameters;

	QString getPath(QString directory) const;
};
