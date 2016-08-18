#include "snake.h"

/*
 * Snake
 * Input: rect for the move range
		  size for the hexagon side length
		  point for the zero point of head hexagon
 */
Snake::Snake(const QRect& rect, qint32 size, const QPoint& point, QObject *parent /* = 0 */)
	: QObject(parent)
{
	rectMove = rect;

	// init the hexagon
	pHeadHg = new Hexagon(size);
	pHeadHg->initHexagon();
	pHeadHg->move(point);
	listHg.push_front(pHeadHg);

	// init the image
	pImg = new QImage(rectMove.width(), rectMove.height(), QImage::Format_ARGB32_Premultiplied);
	pImg->fill(Qt::transparent);

	// init the painter
	this->ppHg = new QPainter(this->pImg);
	QPen pen;
	pen.setWidth(2);
	pen.setColor(Qt::green);
	this->ppHg->setPen(pen);
	this->ppHg->setBrush(Qt::red);
}

Snake::~Snake()
{

}

bool Snake::moveNext(qint8 dir, QPoint point)
{
	Hexagon *pHexagon;
	pHeadHg = this->listHg.front();
	if (0 == dir)
	{
		pHexagon = new Hexagon(pHeadHg->getHexagonUp());
	}
	else if (1 == dir)
	{
		pHexagon = new Hexagon(pHeadHg->getHexagonDown());
	}
	else if (2 == dir)
	{
		pHexagon = new Hexagon(pHeadHg->getHexagonLeftup());
	}
	else if (3 == dir)
	{
		pHexagon = new Hexagon(pHeadHg->getHexagonLeftdown());
	}
	else if (4 == dir)
	{
		pHexagon = new Hexagon(pHeadHg->getHexagonRightup());
	}
	else if ( 5 == dir)
	{
		pHexagon = new Hexagon(pHeadHg->getHexagonRightdown());
	}

	this->listHg.push_front(pHexagon);
	if (point != pHexagon->getZeroPoint())	// is not food
	{
		this->listHg.pop_back();
	}
	else
	{
		emit(foodGetted());
	}

	this->drawSnake();

	return true;
}

void Snake::drawSnake()
{
	pImg->fill(Qt::transparent);
	for (QLinkedList<Hexagon*>::const_iterator ite = this->listHg.begin();
		ite != this->listHg.end(); ++ite)
	{
		this->ppHg->drawConvexPolygon(**ite);
	}
}

