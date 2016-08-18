#ifndef SNAKE_H
#define SNAKE_H

#include "hexagon.h"

#include <QObject>
#include <QLinkedList>
#include <QImage>
#include <QPainter>
#include <QPoint>

class Snake : public QObject
{
	Q_OBJECT

public:
	Snake(const QRect& rect, qint32 size, const QPoint& point, QObject *parent = 0);
	~Snake();

	bool			moveNext(qint8 dir, QPoint point);
	void			drawSnake();

	void			setBrushColor();
	void			setPenColor();

	const QImage&	getSnake(){ return *pImg; }

signals:
	void			foodGetted();

private:
	Hexagon		*pHeadHg;
	QLinkedList<Hexagon*>	listHg;

	QPainter	*ppHg;
	QImage		*pImg;
	QRect		rectMove;
};

#endif // SNAKE_H
