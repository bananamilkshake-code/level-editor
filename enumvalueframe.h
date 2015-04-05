#pragma once

#include "valueframe.h"

namespace Ui {
class EnumValueFrame;
}

class EnumParameter;

class EnumValueFrame : public ValueFrame
{
	Q_OBJECT

public:
	explicit EnumValueFrame(QWidget *parent, const EnumParameter *parameter, QString value);
	~EnumValueFrame();

private slots:
	void on_boxEnumValues_currentIndexChanged(const QString &arg1);

private:
	Ui::EnumValueFrame *ui;

	QString getValue() const override;
};
