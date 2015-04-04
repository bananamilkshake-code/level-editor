#pragma once

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QString>
#include <QVector>

#include <vector>

#include "element.h"
#include "elementdescription.h"

class Level : public QObject
{
	Q_OBJECT

public:
	static const QSize SIZE;

	Level(const QHash<QString, Element> &elementsDescriptions, const QString &name, QSize size);
	Level(const QHash<QString, Element> &elementsDescriptions, const QString &name, const QString &path);
	virtual ~Level();

	const ElementDesc& select(QPoint position);

	bool isNew() const;
	bool isChanged() const;

	void add(const QString &element, QPoint place);
	void load();
	void save(QString newName, QString newPath);

signals:
	void elementLoaded(const QString &name, QPoint position);

private:
	std::vector<std::vector<ElementDesc>> elements;

	const QHash<QString, Element> &elementsDescriptions;

	QString name;
	QString path;

	bool isSaved;

	void init(QSize size);

	QSize getSize() const;
};
