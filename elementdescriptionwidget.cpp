#include "elementdescriptionwidget.h"
#include "ui_elementdescriptionwidget.h"

#include "element.h"
#include "enumparameter.h"
#include "enumvalueframe.h"
#include "floatparameter.h"
#include "floatvalueframe.h"
#include "parameter.h"
#include "valueframe.h"

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

void ElementDescriptionWidget::showElement(const ElementDesc &desc, QPoint position, const QHash<QString, Element> &elements)
{
	this->position = position;

	this->ui->labelElementName->setText(desc.getName());
	this->ui->labelPositionValue->setText(QString("%1 x; %2 y").arg(QString::number(position.x()), QString::number(position.y())));

	this->freeValuesFrames();

	if (!elements.contains(desc.getName()))
		return;

	auto elementDesc = elements.constFind(desc.getName()).value();

	auto params = desc.getParams();
	QHashIterator<QString, QString> paramIter(params);
	while (paramIter.hasNext())
	{
		paramIter.next();

		const std::shared_ptr<Parameter> &paramDesc = elementDesc.getParameters().constFind(paramIter.key()).value();

		this->showParameter(paramDesc, paramIter.value());
	}
}

void ElementDescriptionWidget::onChange(const QString &parameter, const QString &value)
{
	emit parameterChanged(this->getPosition(), parameter, value);
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

void ElementDescriptionWidget::showParameter(const std::shared_ptr<Parameter> &paramDesc, QString value)
{
	ValueFrame *parameterFrame = nullptr;

	switch (paramDesc->getType())
	{
	case Parameter::TypeEnum:
		parameterFrame = new EnumValueFrame(this, dynamic_cast<const EnumParameter*>(paramDesc.get()), value);
		break;
	case Parameter::TypeFloat:
		parameterFrame = new FloatValueFrame(this, dynamic_cast<const FloatParameter*>(paramDesc.get()), value);
		break;
	}

	this->ui->layoutParams->addWidget(parameterFrame);

	QObject::connect(parameterFrame, SIGNAL(changed(QString,QString)), this, SLOT(onChange(QString,QString)));

	this->valuesFrames.insert(parameterFrame);
}

QPoint ElementDescriptionWidget::getPosition() const
{
	return this->position;
}
