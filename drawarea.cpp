#include "drawarea.h"

#include <QDebug>
#include <QPainter>
#include <QMessageBox>
#include <QMouseEvent>

QPixmap DrawArea::eraserPixmap()
{
	QPixmap eraserPixmap(PROPORTION, PROPORTION);
	QPainter painter(&eraserPixmap);
	painter.fillRect(eraserPixmap.rect(), Qt::black);

	return eraserPixmap;
}

DrawArea::DrawArea(QWidget *parent, QSize size):
	QFrame(parent),
	ERASER(QString(), eraserPixmap()),
	currentElement(&ERASER),
	levelProportions(size),
	needDraw(false)
{
	this->resize(size);

	this->setAttribute(Qt::WA_OpaquePaintEvent, true);
}

DrawArea::~DrawArea()
{}

void DrawArea::setCurrentElement(const Element &element)
{
	this->needDraw = true;

	this->currentElement = &element;
}

void DrawArea::setCurrentPosition(const QPoint &position)
{
	this->cursorPosition = position;
}

void DrawArea::setEraser()
{
	this->setCurrentElement(ERASER);
}

void DrawArea::setProportions(QSize newProportions)
{
	this->levelProportions = newProportions;
}

void DrawArea::startSelecting()
{
	this->needDraw = false;
}

void DrawArea::paintEvent(QPaintEvent *)
{
	if (!this->needDraw)
		return;

	int proportion = this->getScale();
	QPoint imagePosition = this->cursorPosition * proportion;

	qDebug() << "Image position " << imagePosition.x() << " " << imagePosition.y();

	QPainter painter(this);
	painter.drawPixmap(imagePosition.x(), imagePosition.y(), this->currentElement->getPixmap());
}

void DrawArea::mousePressEvent(QMouseEvent *eventPress)
{
	int proportion = this->getScale();
	QPoint position = eventPress->localPos().toPoint();

	qDebug() << "Mouse position " << position.x() << " " << position.y();

	this->setCurrentPosition(QPoint(position.x() / proportion, position.y() / proportion));

	if (this->needDraw)
	{
		this->update();
		emit elementPlaced(this->currentElement->getName(), this->cursorPosition);
	}
	else
	{
		emit elementSelected(this->cursorPosition);
	}
}

int DrawArea::getScale() const
{
	return ceil(this->size().height() / (float) this->levelProportions.height());
}

