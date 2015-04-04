#include "elementdescriptionwidget.h"
#include "ui_elementdescriptionwidget.h"

ElementDescriptionWidget::ElementDescriptionWidget(QWidget *parent) :
	QGroupBox(parent),
	ui(new Ui::LevelDescriptionWidget)
{
	ui->setupUi(this);

	this->ui->labelElementName->clear();
}

ElementDescriptionWidget::~ElementDescriptionWidget()
{
	delete ui;
}

void ElementDescriptionWidget::showElement(const ElementDesc &desc)
{
	this->ui->labelElementName->setText(desc.getName());
}
