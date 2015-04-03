#pragma once

#include <QWidget>

#include "element.h"

class DrawArea : public QWidget
{
	Q_OBJECT
public:
	static const uint8_t PROPORTION = 30;

	DrawArea(QWidget * parent = 0);
	~DrawArea();

	void setCurrentElement(const Element &element);
	void setCurrentPosition(const QPoint &position);
	void setEraser();

signals:
	void elementPlaced(const QString &element, QPoint point);

protected:
	void paintEvent(QPaintEvent *paintEvent);
	void mousePressEvent(QMouseEvent *eventPress);

private:
	const Element ERASER;

	QPoint cursorPosition;

	const Element *currentElement;

	static QPixmap eraserPixmap();
};
