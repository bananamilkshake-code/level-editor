#include "drawarea.h"

#include <QDebug>
#include <QPainter>
#include <QMessageBox>
#include <QMouseEvent>

const QSize DrawArea::ELEMENT_SIZE = QSize(DrawArea::PROPORTION, DrawArea::PROPORTION);

QPixmap DrawArea::eraserPixmap()
{
	QPixmap eraserPixmap(PROPORTION, PROPORTION);
	QPainter painter(&eraserPixmap);
	painter.fillRect(eraserPixmap.rect(), Qt::black);

	return eraserPixmap;
}

DrawArea::DrawArea(QWidget *parent):
	QFrame(parent),
	ERASER(QString(), eraserPixmap()),
	currentElement(&ERASER),
	needDraw(false)
{}

DrawArea::~DrawArea()
{}

void DrawArea::drawElement(const Element &element, QPoint position)
{
	qDebug() << "Printing element " << element.getName();

	QPainter painter(&this->image);
	QPoint imagePosition = position * this->getScale();
	painter.drawPixmap(imagePosition, element.getPixmap());

	this->update();
}

static const QColor BACKGROUND_COLOR = Qt::black;

void DrawArea::prepareForLevel(QSize newProportions)
{
	// Resizing widget to fit loaded level. Setting widget size
	// proportionaly to level size (element will be PROPORTION * PROPORTION
	// sized).

	this->levelProportions = newProportions;

	this->resize(this->levelProportions * PROPORTION);

	// Recreating image and filling it with backgroud colour.

	this->image = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);

	QPainter painter(&this->image);
	painter.fillRect(this->image.rect(), BACKGROUND_COLOR);
}

void DrawArea::setCurrentElement(const Element &element)
{
	this->needDraw = true;

	this->currentElement = &element;
}

void DrawArea::setEraser()
{
	this->setCurrentElement(ERASER);
}

void DrawArea::startSelecting()
{
	this->needDraw = false;
}

void DrawArea::paintEvent(QPaintEvent *)
{
	// Printing image all over the widget.

	QPainter painter(this);
	painter.drawImage(this->rect(), this->image);
}

void DrawArea::mousePressEvent(QMouseEvent *eventPress)
{
	// Calculating selected element position.

	int proportion = this->getScale();
	QPoint position = eventPress->localPos().toPoint();

	qDebug() << "Mouse position " << position;

	// We cannot simply calculate elementPosition as position / proportion: QPoint::operator/
	// will round each value to neares and we will receive incorrect position.
	QPoint elementPosition = QPoint(position.x() / proportion, position.y() / proportion);

	if (this->needDraw)
	{
		this->drawElement(*this->currentElement, elementPosition);

		emit elementPlaced(this->currentElement->getName(), elementPosition);
	}
	else
	{
		emit elementSelected(elementPosition);
	}
}

int DrawArea::getScale() const
{
	// Element proportion (picture size).
	// Currently this method always return PROPORTION as widget size is fixed.
	// This method will be helpfull when we would like to change element size
	// or stretch widget.

	return ceil(this->size().height() / (float) this->levelProportions.height());
}

