#include "level.h"

#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "parameter.h"

const QSize Level::SIZE = QSize(20, 15);

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
	std::vector<ElementDesc> record;
	record.assign(size.width(), ElementDesc(QString(), QHash<QString, QString>()));
	this->elements.assign(size.height(), record);
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

		emit elementLoaded(name, position);
	}

	qDebug() << "Level " + this->name + " loaded";
}

void Level::saveAs(QString newName, QString newPath)
{
	this->name = newName;
	this->path = newPath;

	this->save();
}

void Level::save() const
{
	QFile file(this->getFullPath());
	QDataStream stream(&file);
	stream.device()->open(QIODevice::WriteOnly);

	QSize size = this->getSize();

	stream << size.width() << size.height();

	for (int h = 0; h < size.height(); ++h)
	{
		for (int w = 0; w < size.width(); ++w)
		{
			stream << this->elements[h][w].getName();
		}
	}

	this->isSaved = true;

	qDebug() << "Level " + this->name + " saved";

	stream.device()->close();
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

const ElementDesc& Level::select(QPoint position)
{
	return this->elements[position.y()][position.x()];
}

bool Level::isNew() const
{
	return this->path.isNull();
}

bool Level::isChanged() const
{
	return !this->isSaved;
}

void Level::add(const Element &element, QPoint place)
{
	QHash<QString, QString> paramsValues;
	for (auto param : element.getParameters())
	{
		paramsValues[param->getName()] = param->getDefault();
	}

	this->elements[place.y()][place.x()] = ElementDesc(element.getName(), paramsValues);

	this->isSaved = false;
}
