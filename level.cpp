#include "level.h"

#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "parameter.h"

const QSize Level::SIZE = QSize(30, 15);

Level::Level(const QString &name, QSize size):
	name(name),
	isSaved(false)
{
	this->init(size);
}

Level::Level(const QString &name, const QString &path):
	name(name),
	path(path),
	isSaved(true)
{}

Level::~Level()
{}

void Level::init(QSize size)
{
	this->elements.clear();

	std::vector<ElementDesc> record;
	record.assign(size.width(), ElementDesc(QString(), QHash<QString, QString>()));
	this->elements.assign(size.height(), record);
}

void Level::setChanged()
{
	this->isSaved = false;

	emit changed();
}

static const QString LEVEL_SIZE = "size";
static const QString LEVEL_ELEMENTS = "elements";

static const QString SIZE_WIDTH = "width";
static const QString SIZE_HEIGHT = "height";

static const QString LEVEL_ELEMENT_NAME = "name";

static const QString LEVEL_ELEMENT_POSITION = "position";

static const QString POSITION_X = "x";
static const QString POSITION_Y = "y";

static const QString LEVEL_ELEMENT_PARAMETERS = "parameters";

static const QString PARAMETER_NAME = "parameter";
static const QString PARAMETER_VALUE = "value";

void Level::load()
{
	QFile file(this->getFullPath());
	file.open(QFile::ReadOnly);
	QJsonDocument document = QJsonDocument::fromJson(file.readAll());
	file.close();

	QJsonObject sizeObject = document.object()[LEVEL_SIZE].toObject();
	QSize size(sizeObject[SIZE_WIDTH].toInt(), sizeObject[SIZE_HEIGHT].toInt());
	this->init(size);

	QJsonArray elementsArray = document.object()[LEVEL_ELEMENTS].toArray();
	for (QJsonValueRef elementRef : elementsArray)
	{
		QJsonObject elementObject = elementRef.toObject();

		QString name = elementObject[LEVEL_ELEMENT_NAME].toString();

		QJsonObject positionObject = elementObject[LEVEL_ELEMENT_POSITION].toObject();
		QPoint position(positionObject[POSITION_X].toInt(), positionObject[POSITION_Y].toInt());

		QHash<QString, QString> parameters;
		QJsonArray parametersArray = elementObject[LEVEL_ELEMENT_PARAMETERS].toArray();
		for (QJsonValueRef parameterRef : parametersArray)
		{
			QJsonObject parameterObject = parameterRef.toObject();

			parameters.insert(parameterObject[PARAMETER_NAME].toString(), parameterObject[PARAMETER_VALUE].toString());
		}

		this->elements[position.y()][position.x()] = ElementDesc(name, parameters);
	}

	qDebug() << "Level " << this->name << " loaded";
}

void Level::saveAs(QString newName, QString newPath)
{
	this->name = newName;
	this->path = newPath;

	this->save();
}

void Level::save() const
{
	QSize size = this->getSize();
	QJsonObject sizeObject;
	sizeObject[SIZE_WIDTH] = size.width();
	sizeObject[SIZE_HEIGHT] = size.height();

	QJsonArray elementsArray;
	for (size_t h = 0; h < this->elements.size(); ++h)
	{
		for (size_t w = 0; w < this->elements[h].size(); ++w)
		{
			const ElementDesc &element = this->elements[h][w];
			if (element.isEmpty())
				continue;

			QJsonObject elementPosition;
			elementPosition.insert(POSITION_X, qint64(w));
			elementPosition.insert(POSITION_Y, qint64(h));

			QJsonArray parametersArray;
			QHashIterator<QString, QString> paramIterator(element.getParams());
			while (paramIterator.hasNext())
			{
				paramIterator.next();

				QJsonObject parameterObject;
				parameterObject.insert(PARAMETER_NAME, paramIterator.key());
				parameterObject.insert(PARAMETER_VALUE, paramIterator.value());
				parametersArray.push_back(parameterObject);
			}

			QJsonObject elementObject;
			elementObject.insert(LEVEL_ELEMENT_NAME, element.getName());
			elementObject.insert(LEVEL_ELEMENT_POSITION, elementPosition);
			elementObject.insert(LEVEL_ELEMENT_PARAMETERS, parametersArray);
			elementsArray.push_back(elementObject);
		}
	}

	QJsonObject data;
	data.insert(LEVEL_SIZE, sizeObject);
	data.insert(LEVEL_ELEMENTS, elementsArray);

	QFile file(this->getFullPath());
	file.open(QFile::WriteOnly);
	file.write(QJsonDocument(data).toJson());
	file.close();

	this->isSaved = true;

	qDebug() << "Level " << this->name << " saved";
}

QString Level::getName() const
{
	return this->name;
}

QSize Level::getSize() const
{
	size_t height = this->elements.size();
	size_t width = (height > 0) ? this->elements[0].size() : 0;

	return QSize(width, height);
}

QString Level::getFullPath() const
{
	return this->path + QDir::separator() + this->name;
}

ElementDesc& Level::select(QPoint position)
{
	return this->elements[position.y()][position.x()];
}

void Level::changeParameter(QPoint position, const QString parameter, const QString &newValue)
{
	this->select(position).setParam(parameter, newValue);

	this->setChanged();
}

bool Level::isNew() const
{
	return this->path.isNull();
}

bool Level::isChanged() const
{
	return !this->isSaved;
}

QString Level::add(const Element &element, QPoint place)
{
	QHash<QString, QString> paramsValues;
	for (auto param : element.getParameters())
	{
		paramsValues[param->getName()] = param->getDefault();
	}

	// Need to know what element was replaced (for limit calculation).
	QString toReplace = this->elements[place.y()][place.x()].getName();

	this->elements[place.y()][place.x()] = ElementDesc(element.getName(), paramsValues);

	this->setChanged();

	return toReplace;
}
