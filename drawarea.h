#pragma once

#include <QWidget>

class DrawArea : public QWidget
{
	Q_OBJECT
public:
	DrawArea(QWidget * parent = 0);
	~DrawArea();

protected:
	void paintEvent(QPaintEvent *paintEvent);
	void mousePressEvent(QMouseEvent *eventPress);
};
