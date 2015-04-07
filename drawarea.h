#pragma once

#include <QFrame>

#include "element.h"

class DrawArea : public QFrame
{
	Q_OBJECT
public:
	static const uint8_t PROPORTION = 30;
	static const QSize ELEMENT_SIZE;

	// This element is used to replace existing element.
	// It equivalent to empty element.
	const Element ERASER;

	DrawArea(QWidget *parent = 0);
	~DrawArea();

	void drawElement(const Element &element, QPoint position);
	void prepareForLevel(QSize newProportions);
	void setCurrentElement(const Element &element);
	void setEraser();
	void startSelecting();

signals:
	void elementPlaced(const QString &element, QPoint point);
	void elementSelected(QPoint point);
	void information(const QString &text);

protected:
	void paintEvent(QPaintEvent *) override;
	void mousePressEvent(QMouseEvent *eventPress) override;

private:

	// Element to draw.
	const Element *currentElement;

	QSize levelProportions;

	// Element drawing executs on paintEvent() method. But this method
	// erasing all drawed data from widget. To prevent it we will use
	// image as paint device. This image will be redrawed on widget on
	// paintEvent method call.
	QImage image;

	// Flag to drawing state. If it is true, pressing on area will cause
	// current element drawing. If not element will be selected.
	bool needDraw;

	// QPixmap cannot be created before application starts. This
	// method is used to create ERASER field on DrawArea construction.
	static QPixmap eraserPixmap();

	int getScale() const;
};
