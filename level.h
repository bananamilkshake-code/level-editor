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

	ElementDesc& select(QPoint position);
	void changeParameter(QPoint position, const QString parameter, const QString &newValue);

	bool isNew() const;
	bool isChanged() const;

	void add(const Element &element, QPoint place);
	void load();
	void saveAs(QString newName, QString newPath);
	void save() const;

signals:
	void changed();
	void elementLoaded(const QString &name, QPoint position);

private:
	std::vector<std::vector<ElementDesc>> elements;

	QString name;
	QString path;

	mutable bool isSaved;

	void init(QSize size);
	void setChanged();

	QSize getSize() const;
	QString getFullPath() const;
};
