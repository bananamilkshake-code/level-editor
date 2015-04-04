#pragma once

#include <QDialog>
#include <QString>

#include "element.h"

namespace Ui {
class AddElementDialog;
}

class AddElementDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AddElementDialog(QWidget *parent, QString elementsDirectory);
	~AddElementDialog();

signals:
	void elementAdded(Element newElement);

private slots:
	void on_buttonBox_accepted();
	void on_buttonImageLoad_clicked();

private:
	Ui::AddElementDialog *ui;

	QString elementsDirectory;
};
