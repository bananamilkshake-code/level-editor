#include "element.h"

#include <QDir>
#include <QFile>
#include <QHash>
#include <QJsonDocument>
#include <QVariantMap>
#include <QJsonArray>
#include <QJsonObject>

#include "floatparameter.h"
#include "enumparameter.h"

const QString Element::EXTENSION = ".element";
const char* Element::PICTURE_FORMAT = "PNG";

const QHash<Element::Data, QString> Element::DATA_FILES =
{
	{Element::Picture, "pic.png"},
	{Element::Params, "params.json"}
};

Element::Element(QString name):
	Element(name, QPixmap())
{}

Element::Element(QString name, QPixmap pixmap):
	name(name), pixmap(pixmap)
{}

Element::~Element()
{}

QString Element::getName() const
{
	return this->name;
}

const QPixmap& Element::getPixmap() const
{
	return this->pixmap;
}

const Element::parameters_t& Element::getParameters() const
{
	return this->parameters;
}

void Element::load(QString directory)
{
	QString picFile = this->getPathOf(directory, Picture);
	this->pixmap.load(picFile, PICTURE_FORMAT);

	this->loadParams(directory);
}

void Element::save(QString elementsDirectory) const
{
	QDir directory(elementsDirectory);
	directory.mkdir(this->getName());

	QString picFile = this->getPathOf(elementsDirectory, Picture);
	this->pixmap.save(picFile, PICTURE_FORMAT);
}

static const QString PARAMETERS_SERIALISATION = "parameters";

static const QString NAME_SERIALISATION = "name";
static const QString TYPE_SERIALISATION = "type";
static const QString DESC_SERIALISATION = "desc";

static const QString FLOAT_TYPE = "float";
static const QString ENUM_TYPE = "enum";

static const QString FLOAT_DESC_MIN = "min";
static const QString FLOAT_DESC_MAX = "max";

static const QString ENUM_DESC_VALUES = "values";

void Element::loadParams(QString directory)
{
	QString filePath = this->getPathOf(directory, Params);
	QFile file(filePath);
	file.open(QFile::ReadOnly);
	QJsonDocument document = QJsonDocument::fromJson(file.readAll());
	file.close();

	QJsonArray parametersArray = document.object()[PARAMETERS_SERIALISATION].toArray();
	for (QJsonValueRef parameterObjectRef : parametersArray)
	{
		QJsonObject parameterObject = parameterObjectRef.toObject();

		QString name = parameterObject[NAME_SERIALISATION].toString();
		QString type = parameterObject[TYPE_SERIALISATION].toString();
		QJsonObject desc = parameterObject[DESC_SERIALISATION].toObject();

		std::shared_ptr<Parameter> parameter;

		if (type == FLOAT_TYPE)
		{
			float min = desc[FLOAT_DESC_MIN].toDouble();
			float max = desc[FLOAT_DESC_MAX].toDouble();

			parameter = std::make_shared<FloatParameter>(name, min, max);
		}
		else if (type == ENUM_TYPE)
		{
			QStringList values;
			foreach (QVariant value, desc[ENUM_DESC_VALUES].toArray())
			{
				values.push_back(value.toString());
			}

			parameter = std::make_shared<EnumParameter>(name, values);
		}

		this->parameters[name] = parameter;
	}
}

void Element::saveParams(QString directory) const
{
	QJsonDocument document;

	QString filePath = this->getPathOf(directory, Params);
	QFile file(filePath);
	file.open(QFile::WriteOnly);
	file.write(document.toBinaryData());
	file.close();
}

QString Element::getPath(QString directory) const
{
	return QString(directory + QDir::separator() + this->getName());
}

QString Element::getPathOf(QString directory, Data data) const
{
	return this->getPath(directory) + QDir::separator() + DATA_FILES.constFind(data).value();
}

