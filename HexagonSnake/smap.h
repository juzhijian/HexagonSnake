#ifndef SMAP_H
#define SMAP_H

#include "hexagon.h"
#include "snake.h"

#include <QObject>
#include <QPolygon>
#include <QImage>
#include <QPainter>
#include <QVector>
#include <QMap>

class Smap : public QObject
{
	Q_OBJECT

public:
	Smap(const QRect&rect, qint32 size, QObject *parent = 0);
	~Smap();

	void				setBackground(QColor clr);
	void				setBrushColor(QColor clr);
	void				setPenColor(QColor clr);

	const QImage&		getMap(){ return *pImg; }
	const QPoint&		getLeftupPoint(){ return this->pointHgLeftup; }
	const QPoint&		getVecHgPoint(qint32 index) { return vecHgPoint.at(index); }
	qint32				getHgPointNum(){ return this->vecHgPoint.size(); }

private:
	QPoint		pointHgLeftup;				// the left up point of hexagon
	QVector<QPoint>		vecHgPoint;			// the points of all the hexagon 

	QImage		*pImg;
	QPainter	*ppMap;
	QPen		pen;
	QBrush		brush;
};

#endif // SMAP_H
