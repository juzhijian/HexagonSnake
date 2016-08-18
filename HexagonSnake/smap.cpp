#include "smap.h"

/*
 * Smap 
 * Input: rect for the map showing range
		  size for the hexagon side length
 */
Smap::Smap(const QRect&rect,qint32 size, QObject *parent /* = 0 */)
	: QObject(parent)
{
	// init the image
	qint32 w = rect.width();
	qint32 h = rect.height();
	this->pImg = new QImage(w, h, QImage::Format_ARGB32_Premultiplied);
	this->pImg->fill(Qt::black);

	// init the painter
	this->ppMap = new QPainter(this->pImg);

	pen.setColor(Qt::gray);
	pen.setWidth(2);
	brush.setColor(Qt::darkCyan);
	brush.setStyle(Qt::SolidPattern);
	this->ppMap->setPen(pen);
	this->ppMap->setBrush(brush);

	// init the hexagon
	Hexagon hexagon(size);
	hexagon.initHexagon();
	hexagon.move(hexagon.getShortLen(), hexagon.getLongLen());
	this->pointHgLeftup = hexagon.getZeroPoint();

	int numW = 2 * w / (3*size);
	int numH = h / (2*hexagon.getLongLen());
	if (3*size*numW / 2 + hexagon.getShortLen() > w)
	{
		--numW;
	}
	bool ud = false;
	for (int i = 0; i < numW; i++)
	{
        Hexagon	tmp(hexagon);
		for (int j = 0; j < numH; j++)
		{
			ppMap->drawConvexPolygon(tmp);
			this->vecHgPoint.append(tmp.getZeroPoint());
            tmp.moveToDown();
		}
		
		if (ud)
		{
			hexagon.moveToRightup();
			numH++;
		}
		else
		{
			hexagon.moveToRightdown();
			numH--;
		}
		ud = !ud;
	}
}

Smap::~Smap()
{

}



