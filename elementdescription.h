#pragma once

#include <QHash>
#include <QString>


// Keeps information about drawed element.
struct ElementDesc
{
public:
	ElementDesc(const QString &name, QHash<QString, QString> params);

	void setParam(QString name, QString value);

	QString getName() const;
	const QHash<QString, QString> getParams() const;

	bool isEmpty() const;

private:
	// Element name.
	QString name;

	// Parameters' values.
	QHash<QString, QString> params;
};
