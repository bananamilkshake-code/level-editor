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

void DrawArea::paintEvent(QPaintEvent *paintEvent)
{
	QPainter painter(this);
	QImage pixmap("C:\\yellow.png");
	QPoint imagePosition = this->cursorPosition * PROPORTION;
	painter.drawImage(imagePosition.x(), imagePosition.y(), pixmap);
}

void DrawArea::mousePressEvent(QMouseEvent *eventPress)
{
	QMessageBox box;
	QPoint pos = eventPress->pos();

	this->cursorPosition = pos / PROPORTION;

	this->update();
}
