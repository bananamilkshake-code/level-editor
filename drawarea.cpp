#include "drawarea.h"

#include <QPainter>
#include <QMessageBox>
#include <QMouseEvent>

DrawArea::DrawArea(QWidget * parent):
	QWidget(parent)
{
	this->setAttribute(Qt::WA_OpaquePaintEvent, true);
}

DrawArea::~DrawArea()
{}

void DrawArea::setCurrentPixmap(const QPixmap &pixmap)
{
	this->currentPixmap = pixmap;
}

void DrawArea::paintEvent(QPaintEvent *paintEvent)
{
	QPainter painter(this);
	QPoint imagePosition = this->cursorPosition * PROPORTION;
	painter.drawPixmap(imagePosition.x(), imagePosition.y(), this->currentPixmap);
}

void DrawArea::mousePressEvent(QMouseEvent *eventPress)
{
	QPoint pos = eventPress->pos();

	this->cursorPosition = pos / PROPORTION;

	this->update();
}
