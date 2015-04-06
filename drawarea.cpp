#include "drawarea.h"

#include <QDebug>
#include <QPainter>
#include <QMessageBox>
#include <QMouseEvent>

const QSize DrawArea::ELEMENT_SIZE = QSize(DrawArea::PROPORTION, DrawArea::PROPORTION);

QPixmap DrawArea::eraserPixmap()
{
	QPixmap eraserPixmap(PROPORTION, PROPORTION);
	QPainter painter(&eraserPixmap);
	painter.fillRect(eraserPixmap.rect(), Qt::black);

	return eraserPixmap;
}

DrawArea::DrawArea(QWidget *parent):
	QFrame(parent),
	ERASER(QString(), eraserPixmap()),
	currentElement(&ERASER),
	needDraw(false)
{}

DrawArea::~DrawArea()
{}

void DrawArea::drawElement(const Element &element, QPoint position)
{
	emit information("Printing element " + element.getName());

	QPainter painter(&this->image);
	QPoint imagePosition = position * this->getScale();
	painter.drawPixmap(imagePosition, element.getPixmap());

	this->update();
}

void DrawArea::setCurrentElement(const Element &element)
{
	this->needDraw = true;

	this->currentElement = &element;
}

void DrawArea::setEraser()
{
	this->setCurrentElement(ERASER);
}

static const QColor BACKGROUND_COLOR = Qt::black;

void DrawArea::prepareForLevel(QSize newProportions)
{
	this->levelProportions = newProportions;

	this->resize(this->levelProportions * PROPORTION);

	this->image = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);

	QPainter painter(&this->image);
	painter.fillRect(this->image.rect(), BACKGROUND_COLOR);
}

void DrawArea::startSelecting()
{
	this->needDraw = false;
}

void DrawArea::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawImage(this->rect(), this->image);
}

void DrawArea::mousePressEvent(QMouseEvent *eventPress)
{
	int proportion = this->getScale();
	QPoint position = eventPress->localPos().toPoint();

	emit information(QString("Mouse position (%1, %2)").arg(QString::number(position.x()), QString::number(position.y())));

	QPoint elementPosition = QPoint(position.x() / proportion, position.y() / proportion);

	if (this->needDraw)
	{
		this->drawElement(*this->currentElement, elementPosition);

		emit elementPlaced(this->currentElement->getName(), elementPosition);
	}
	else
	{
		emit elementSelected(elementPosition);
	}
}

int DrawArea::getScale() const
{
	return ceil(this->size().height() / (float) this->levelProportions.height());
}

