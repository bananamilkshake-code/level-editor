#include "drawarea.h"

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

DrawArea::DrawArea(QWidget * parent):
	QWidget(parent), ERASER("Empty", eraserPixmap()), currentElement(&ERASER)
{
	this->setAttribute(Qt::WA_OpaquePaintEvent, true);
}

DrawArea::~DrawArea()
{}

void DrawArea::setCurrentElement(const Element &element)
{
	this->currentElement = &element;
}

void DrawArea::setEraser()
{
	this->currentElement = &ERASER;
}

void DrawArea::paintEvent(QPaintEvent *paintEvent)
{
	QPainter painter(this);
	QPoint imagePosition = this->cursorPosition * PROPORTION;
	painter.drawPixmap(imagePosition.x(), imagePosition.y(), this->currentElement->getPixmap());
}

void DrawArea::mousePressEvent(QMouseEvent *eventPress)
{
	QPoint pos = eventPress->pos();

	this->cursorPosition = pos / PROPORTION;

	this->update();

	if (this->currentElement == &ERASER)
	{
		emit elementErased(this->cursorPosition);
	}
	else
	{
		emit elementPlaced(this->currentElement->getName(), this->cursorPosition);
	}
}
