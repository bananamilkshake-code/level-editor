#pragma once

#include <QPoint>
#include <QSize>
#include <QString>
#include <QVector>

#include "element.h"

class Level
{
public:
	static const uint8_t WIDTH = 30;
	static const uint8_t HEIGHT = 15;

	Level(const QHash<QString, Element> &elementsDescriptions, QString name, QSize size);
	Level(const QHash<QString, Element> &elementsDescriptions, QString name, QString path);
	~Level();

	bool isNew() const;
	bool isChanged() const;

	void add(const QString &element, QPoint place);
	void save(QString newName, QString newPath);

private:
	struct ElementDesc
	{
	public:
		QString name;

		ElementDesc();
		ElementDesc(const QString &name);
	};

	QVector<QVector<ElementDesc>> elements;

	const QHash<QString, Element> &elementsDescriptions;

	QString name;
	QString path;

	bool isSaved;
};
