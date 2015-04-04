#pragma once

#include <QDialog>
#include <QString>

#include "element.h"

namespace Ui {
class ElementDialog;
}

class ElementDialog : public QDialog
{
	Q_OBJECT

public:
	ElementDialog(QWidget *parent, QString elementsDirectory);
	ElementDialog(QWidget *parent, QString elementsDirectory, const Element &element);
	~ElementDialog();

signals:
	void elementAdded(Element newElement);

private slots:
	void on_buttonBox_accepted();
	void on_buttonImageLoad_clicked();

private:
	Ui::ElementDialog *ui;

	QString elementsDirectory;
};
