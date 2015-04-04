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

DrawArea::DrawArea(QWidget *parent):
	QFrame(parent),
	ERASER(QString(), eraserPixmap()),
	currentElement(&ERASER),
	needDraw(false)
{
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

void DrawArea::startSelecting()
{
	this->needDraw = false;
}

void DrawArea::paintEvent(QPaintEvent *)
{
	if (!this->needDraw)
		return;

	QPoint imagePosition = this->cursorPosition * PROPORTION;

	QPainter painter(this);
	painter.drawPixmap(imagePosition.x(), imagePosition.y(), this->currentElement->getPixmap());
}

void DrawArea::mousePressEvent(QMouseEvent *eventPress)
{
	this->setCurrentPosition(eventPress->pos() / PROPORTION);

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
