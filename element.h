#pragma once

#include <QString>
#include <QPixmap>

class Element
{
public:
	static const QString EXTENSION;

	Element(QString name);
	Element(QString name, QPixmap pixmap);
	~Element();

	QString getName() const;
	const QPixmap& getPixmap() const;

	void load(QString directory);
	void save(QString directory) const;

private:
	QString name;
	QPixmap pixmap;

	QString getPath(QString directory) const;
};
