#pragma once

#include <QHash>
#include <QString>

struct ElementDesc
{
public:
	ElementDesc(const QString &name);

	QString getName() const;
	const QHash<QString, QString> getParams() const;

private:
	QString name;
	QHash<QString, QString> params;
};
