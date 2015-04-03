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
	QWidget(parent), ERASER(QString(), eraserPixmap()), currentElement(&ERASER)
{
	this->setAttribute(Qt::WA_OpaquePaintEvent, true);
}

DrawArea::~DrawArea()
{}

void DrawArea::setCurrentElement(const Element &element)
{
	this->currentElement = &element;
}

void DrawArea::setCurrentPosition(const QPoint &position)
{
	this->cursorPosition = position;
}

void DrawArea::setEraser()
{
	this->currentElement = &ERASER;
}

void DrawArea::paintEvent(QPaintEvent *paintEvent)
{
	QPoint imagePosition = this->cursorPosition * PROPORTION;

	QPainter painter(this);
	painter.drawPixmap(imagePosition.x(), imagePosition.y(), this->currentElement->getPixmap());
}

void DrawArea::mousePressEvent(QMouseEvent *eventPress)
{
	this->setCurrentPosition(eventPress->pos() / PROPORTION);

	this->update();

	emit elementPlaced(this->currentElement->getName(), this->cursorPosition);
}
