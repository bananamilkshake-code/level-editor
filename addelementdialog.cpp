#include "addelementdialog.h"
#include "ui_addelementdialog.h"

#include <QDir>
#include <QFileDialog>
#include <QString>

#include "config.h"

AddElementDialog::AddElementDialog(QWidget *parent, QString elementsDirectory):
	QDialog(parent),
	ui(new Ui::AddElementDialog),
	elementsDirectory(elementsDirectory)
{
	ui->setupUi(this);

	this->ui->labelPicturePath->clear();
	this->ui->labelPicturePreview->clear();

	this->adjustSize();
}

AddElementDialog::~AddElementDialog()
{}

void AddElementDialog::on_buttonBox_accepted()
{
	QString name = this->ui->lineName->text();
	QPixmap pixmap(*this->ui->labelPicturePreview->pixmap());

	Element element(name, pixmap);
	element.save(this->elementsDirectory);

	emit elementAdded(element);
}

void AddElementDialog::on_buttonImageLoad_clicked()
{
	QFileDialog dialog(this, "Изображение элемента");

	if (!dialog.exec())
		return;

	QString imagePath = dialog.selectedFiles()[0];

	this->ui->labelPicturePath->setText(imagePath);

	QPixmap preview(imagePath);

	this->ui->labelPicturePreview->setPixmap(preview);
}
