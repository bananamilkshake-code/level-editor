#pragma once

#include <QWidget>

class DrawArea : public QWidget
{
	Q_OBJECT
public:
	static const uint8_t PROPORTION = 30;

	DrawArea(QWidget * parent = 0);
	~DrawArea();

	void setCurrentPixmap(const QPixmap &pixmap);

protected:
	void paintEvent(QPaintEvent *paintEvent);
	void mousePressEvent(QMouseEvent *eventPress);

private:
	QPoint cursorPosition;

	QPixmap currentPixmap;
};
