#include "elementdescriptionwidget.h"
#include "ui_elementdescriptionwidget.h"

#include "element.h"
#include "enumparameter.h"
#include "enumvalueframe.h"
#include "floatparameter.h"
#include "floatvalueframe.h"
#include "parameter.h"

ElementDescriptionWidget::ElementDescriptionWidget(QWidget *parent):
	QGroupBox(parent),
	ui(new Ui::LevelDescriptionWidget)
{
	ui->setupUi(this);

	this->ui->labelElementName->clear();
	this->ui->labelPositionValue->clear();
}

ElementDescriptionWidget::~ElementDescriptionWidget()
{
	this->freeValuesFrames();

	delete ui;
}

void ElementDescriptionWidget::showElement(const ElementDesc &desc, const QHash<QString, Element> &elements)
{
	this->ui->labelElementName->setText(desc.getName());

	this->freeValuesFrames();

	auto elementDesc = elements.constFind(desc.getName()).value();

	auto params = desc.getParams();
	QHashIterator<QString, QString> paramIter(params);
	while (paramIter.hasNext())
	{
		paramIter.next();

		const Parameter *paramDesc = elementDesc.getParameters().constFind(paramIter.key()).value();

		this->showParameter(paramDesc, paramIter.value());
	}
}

void ElementDescriptionWidget::freeValuesFrames()
{
	for (auto frame : this->valuesFrames)
	{
		this->ui->layoutParams->removeWidget(frame);
		delete frame;
	}

	this->valuesFrames.clear();
}

void ElementDescriptionWidget::showParameter(const Parameter *paramDesc, QString value)
{
	ValueFrame *parameterFrame = nullptr;

	switch (paramDesc->getType())
	{
	case Parameter::TypeEnum:
		parameterFrame = new EnumValueFrame(this, dynamic_cast<const EnumParameter*>(paramDesc), value);
		break;
	case Parameter::TypeFloat:
		parameterFrame = new FloatValueFrame(this, dynamic_cast<const FloatParameter*>(paramDesc), value);
		break;
	}

	this->ui->layoutParams->addWidget(parameterFrame);

	this->valuesFrames.insert(parameterFrame);
}
