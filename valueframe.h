#pragma once

#include <QGroupBox>
#include <QPair>
#include <QString>

class Parameter;

// Each parameter needs it's own frame to show data.

class ValueFrame : public QGroupBox
{
	Q_OBJECT

public:
	ValueFrame(QWidget* parent, const Parameter *parameter, QString value);
	virtual ~ValueFrame();

	QPair<QString, QString> getChanged() const;

signals:
	void changed(const QString &parameter, const QString &value);

protected:
	QString value;

	virtual QString getValue() const = 0;

	void onChange();
};
