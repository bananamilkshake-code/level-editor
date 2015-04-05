#pragma once

#include <QHash>
#include <QString>

struct ElementDesc
{
public:
	ElementDesc(const QString &name, QHash<QString, QString> params);

	void setParam(QString name, QString value);

	QString getName() const;
	const QHash<QString, QString> getParams() const;

	bool isEmpty() const;

private:
	QString name;
	QHash<QString, QString> params;
};
