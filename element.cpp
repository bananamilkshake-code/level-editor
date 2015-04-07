#include "element.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QHash>
#include <QJsonDocument>
#include <QVariantMap>
#include <QJsonArray>
#include <QJsonObject>

#include "floatparameter.h"
#include "enumparameter.h"
#include "drawarea.h"

const QString Element::EXTENSION = ".element";
const char* Element::PICTURE_FORMAT = "PNG";

const QHash<Element::Data, QString> Element::DATA_FILES =
{
	{Element::Params, "params.json"}
};

Element::Element(QString name):
	Element(name, QPixmap())
{}

Element::Element(QString name, QPixmap pixmap):
	name(name), pixmap(pixmap), limit(0), left(0)
{}

Element::~Element()
{}

bool Element::usedLast()
{
	// Element was placed and needs to decrease left value.

	if (!this->isLimited())
	{
		return false;
	}

	this->left -= 1;

	return this->isUsedLast();
}

bool Element::releaseOne()
{
	if (!this->isLimited())
	{
		return false;
	}

	this->left = std::min(this->limit, this->left + 1);

	return (this->left > 0);
}

void Element::resetLimit()
{
	this->left = this->limit;
}

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

static const QString PARAMETERS_SERIALISATION = "parameters";
static const QString PARAMETER_PICTURE = "picture";
static const QString PARAMETER_LIMIT = "limit";

static const QString NAME_SERIALISATION = "name";
static const QString TYPE_SERIALISATION = "type";
static const QString DESC_SERIALISATION = "desc";

static const QString FLOAT_TYPE = "float";
static const QString ENUM_TYPE = "enum";

static const QString FLOAT_DESC_MIN = "min";
static const QString FLOAT_DESC_MAX = "max";

static const QString ENUM_DESC_VALUES = "values";

void Element::load(QString directory)
{
	QString filePath = this->getPathOf(directory, Params);
	QFile file(filePath);
	file.open(QFile::ReadOnly);
	QJsonDocument document = QJsonDocument::fromJson(file.readAll());
	file.close();

	QJsonObject elementObject = document.object();
	QJsonArray parametersArray = elementObject[PARAMETERS_SERIALISATION].toArray();
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

	QString picturePath = this->getPath(directory) + QDir::separator() + elementObject[PARAMETER_PICTURE].toString();

	qDebug() << "Picture path for " << this->name << " element is " << picturePath;

	// Loaded pictures must be scaled to one size.
	this->pixmap = QPixmap(picturePath).scaled(DrawArea::ELEMENT_SIZE);

	if (this->pixmap.isNull())
		qDebug() << "No picture \"" << picturePath << "\" for " << this->getName() << " element";

	this->limit = elementObject[PARAMETER_LIMIT].toInt();

	this->resetLimit();
}

void Element::save(QString) const
{}

bool Element::isLimited() const
{
	return this->limit > 0;
}

bool Element::isUsedLast() const
{
	return this->isLimited() && (this->left <= 0);
}

int Element::getLimit() const
{
	return this->limit;
}

QString Element::getPath(QString directory) const
{
	return QString(directory + QDir::separator() + this->getName());
}

QString Element::getPathOf(QString directory, Data data) const
{
	return this->getPath(directory) + QDir::separator() + DATA_FILES.constFind(data).value();
}

