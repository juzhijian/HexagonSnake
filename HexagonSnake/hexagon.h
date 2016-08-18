#ifndef HEXAGON_H
#define HEXAGON_H

#include <QPolygon>
#include <QVector>

class Hexagon : public QPolygon
{
public:
	explicit Hexagon(qint32 len = 20);
	Hexagon(const Hexagon &);						// no explicit
	~Hexagon();

	void			initHexagon();			// construct a regular hexagon

	// for paint
#if(0)
	QPolygon		getPolygonDown(qint32 n = 1){ return this->translated(0, n * 2 * longLen); }
	QPolygon		getPolygonRightup(){ return this->translated(shortLen + sideLen, -longLen); }
	QPolygon		getPolygonRightdown(){ return this->translated(shortLen + sideLen, longLen); }
#endif
	
	// for move and paint
	Hexagon			getHexagonUp();
	Hexagon			getHexagonDown();
	Hexagon			getHexagonLeftup();
	Hexagon			getHexagonLeftdown();
	Hexagon			getHexagonRightup();
	Hexagon			getHexagonRightdown();
#if(1)
	Hexagon			getHexagonDown(qint32);
	Hexagon			getHexagonRight(qint32, bool);
#endif

	void			moveToUp();
	void			moveToDown();
	void			moveToLeftup();
	void			moveToLeftdown();
	void			moveToRightup();
	void			moveToRightdown();

	const QPoint&	getZeroPoint(){ return this->at(0); }
	const qint32&	getShortLen() { return shortLen; }
	const qint32&	getLongLen() { return longLen; }
	void			move(qint32, qint32);		// use the most left corner as the zero point
	void			move(QPoint);
    

private:
	const qint32		sideLen;

	const static qint32	sin60 = 8660;			// sin60/10000
	const static qint32	cos60 = 5000;			// cos60/10000
	static qint32	shortLen;
	static qint32	longLen;
	static QPoint	pointUp;
	static QPoint	pointDown;
	static QPoint	pointLeftup;
	static QPoint	pointLeftdown;
	static QPoint	pointRightup;
	static QPoint	pointRightdown;
};

#endif // HEXAGON_H
