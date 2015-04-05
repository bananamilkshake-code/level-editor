#pragma once

#include <QGroupBox>
#include <QPair>

class Parameter;

class ValueFrame : public QGroupBox
{
public:
	ValueFrame(QWidget* parent, const Parameter *parameter, QString value);
	virtual ~ValueFrame();

	QPair<QString, QString> getChanged() const;

protected:
	QString value;

	virtual QString getValue() const = 0;
};
