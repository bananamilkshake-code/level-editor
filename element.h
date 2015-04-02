#pragma once

#include <QString>
#include <QPixmap>

class Element
{
public:
	Element(QString name, QPixmap pixmap);
	~Element();

	QString getName() const;
	QPixmap getPixmap() const;
private:
	QString name;
	QPixmap pixmap;
};
