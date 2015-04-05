#pragma once

#include "valueframe.h"

namespace Ui {
class FloatValueFrame;
}

class FloatParameter;

class FloatValueFrame : public ValueFrame
{
	Q_OBJECT

public:
	FloatValueFrame(QWidget *parent, const FloatParameter *parameter, QString value);
	~FloatValueFrame();

	QString getValue() const override;

private slots:
	void on_spinValue_valueChanged(const QString &arg1);

private:
	Ui::FloatValueFrame *ui;
};
