#pragma once

#include <QFrame>

#include "element.h"

class DrawArea : public QFrame
{
	Q_OBJECT
public:
	static const uint8_t PROPORTION = 30;

	DrawArea(QWidget * parent, QSize size);
	~DrawArea();

	void setCurrentElement(const Element &element);
	void setCurrentPosition(const QPoint &position);
	void setEraser();
	void startSelecting();

signals:
	void elementPlaced(const QString &element, QPoint point);
	void elementSelected(QPoint point);

protected:
	void paintEvent(QPaintEvent *) override;

	void mousePressEvent(QMouseEvent *eventPress) override;

private:
	const Element ERASER;

	QPoint cursorPosition;

	const Element *currentElement;

	bool needDraw;

	static QPixmap eraserPixmap();
};
