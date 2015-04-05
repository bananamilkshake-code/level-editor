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

	Level(const QString &name, QSize size);
	Level(const QString &name, const QString &path);
	virtual ~Level();

	const ElementDesc& select(QPoint position);

	bool isNew() const;
	bool isChanged() const;

	void add(const Element &element, QPoint place);
	void load();
	void saveAs(QString newName, QString newPath);
	void save() const;

signals:
	void elementLoaded(const QString &name, QPoint position);

private:
	std::vector<std::vector<ElementDesc>> elements;

	QString name;
	QString path;

	mutable bool isSaved;

	void init(QSize size);

	QSize getSize() const;
	QString getFullPath() const;
};
