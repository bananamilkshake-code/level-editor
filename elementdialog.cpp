#include "elementdialog.h"
#include "ui_elementdialog.h"

#include <QDir>
#include <QFileDialog>
#include <QString>

#include "config.h"
#include "drawarea.h"

ElementDialog::ElementDialog(QWidget *parent, QString elementsDirectory):
	QDialog(parent),
	ui(new Ui::ElementDialog),
	elementsDirectory(elementsDirectory)
{
	ui->setupUi(this);

	this->ui->labelPicturePath->clear();
	this->ui->labelPicturePreview->clear();

	this->adjustSize();
}

ElementDialog::ElementDialog(QWidget *parent, QString elementsDirectory, const Element &element):
	ElementDialog(parent, elementsDirectory)
{
	this->ui->lineName->setText(element.getName());
	this->ui->labelPicturePreview->setPixmap(element.getPixmap());
}

ElementDialog::~ElementDialog()
{}

void ElementDialog::on_buttonBox_accepted()
{
	QString name = this->ui->lineName->text();
	QPixmap pixmap(*this->ui->labelPicturePreview->pixmap());

	Element element(name, pixmap);
	element.save(this->elementsDirectory);

	emit elementAdded(element);
}

void ElementDialog::on_buttonImageLoad_clicked()
{
	QFileDialog dialog(this, "Изображение элемента");

	if (!dialog.exec())
		return;

	QString imagePath = dialog.selectedFiles()[0];

	this->ui->labelPicturePath->setText(imagePath);

	QPixmap preview(imagePath);
	this->ui->labelPicturePreview->setPixmap(preview.scaled(DrawArea::PROPORTION, DrawArea::PROPORTION));
}
