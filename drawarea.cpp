#include "drawarea.h"

#include <QPainter>
#include <QMessageBox>
#include <QMouseEvent>

DrawArea::DrawArea(QWidget * parent):
	QWidget(parent)
{}

DrawArea::~DrawArea()
{}

void DrawArea::paintEvent(QPaintEvent *paintEvent)
{
	QPainter painter(this);
	QImage pixmap("C:\\yellow.png");
	painter.drawImage(0, 20, pixmap);
}

void DrawArea::mousePressEvent(QMouseEvent *eventPress)
{
	QMessageBox box;
	QPoint pos = eventPress->pos();
	box.setText(QString(QString::number(pos.x()) + " " + QString::number(pos.y())));
	box.exec();

	this->update();
}
