#pragma once

#include <QFrame>

#include "element.h"

class DrawArea : public QFrame
{
	Q_OBJECT
public:
	static const uint8_t PROPORTION = 30;

	DrawArea(QWidget *parent = 0);
	~DrawArea();

	void drawElement(const Element &element, QPoint position);
	void setCurrentElement(const Element &element);
	void setEraser();
	void prepareForLevel(QSize newProportions);
	void startSelecting();

signals:
	void elementPlaced(const QString &element, QPoint point);
	void elementSelected(QPoint point);

protected:
	void paintEvent(QPaintEvent *) override;

	void mousePressEvent(QMouseEvent *eventPress) override;

private:
	const Element ERASER;

	const Element *currentElement;

	QSize levelProportions;
	QImage image;

	bool needDraw;

	static QPixmap eraserPixmap();

	int getScale() const;
};
