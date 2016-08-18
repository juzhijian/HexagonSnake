#include "hexagon.h"

qint32 Hexagon::shortLen = 0;
qint32 Hexagon::longLen = 0;
QPoint Hexagon::pointUp = QPoint(0, 0);
QPoint Hexagon::pointDown = QPoint(0, 0);
QPoint Hexagon::pointLeftup = QPoint(0, 0);
QPoint Hexagon::pointLeftdown = QPoint(0, 0);
QPoint Hexagon::pointRightup = QPoint(0, 0);
QPoint Hexagon::pointRightdown = QPoint(0, 0);

Hexagon::Hexagon(qint32 len /*= 20*/)
	: sideLen(len)
{
	shortLen = sideLen / 2;
	longLen = sideLen * sin60 / 10000;

	pointUp = QPoint(0, -2 * longLen);
	pointDown = QPoint(0, 2 * longLen);
	pointLeftup = QPoint(-shortLen - sideLen, -longLen);
	pointLeftdown = QPoint(-shortLen - sideLen, longLen);
	pointRightup = QPoint(shortLen + sideLen, -longLen);
	pointRightdown = QPoint(shortLen + sideLen, longLen);
}

Hexagon::Hexagon(const Hexagon &hg)
	:sideLen(hg.sideLen)
{
	for (QVector<QPoint>::const_iterator ite = hg.begin();
		ite != hg.end(); ++ite)
	{
		this->append(*ite);
	}
}

Hexagon::~Hexagon()
{
	this->clear();
}

void Hexagon::initHexagon()
{
	*this << QPoint(0, 0)
		<< QPoint(shortLen, longLen)
		<< QPoint(shortLen + sideLen, longLen)
		<< QPoint(2 * sideLen, 0)
		<< QPoint(shortLen + sideLen, -longLen)
		<< QPoint(shortLen, -longLen);
}


// get the moved hexagon
#if(1)
Hexagon Hexagon::getHexagonUp()
{
	Hexagon hg(this->sideLen);
	hg << this->at(0) + pointUp
		<< this->at(1) + pointUp
		<< this->at(2) + pointUp
		<< this->at(3) + pointUp
		<< this->at(4) + pointUp
		<< this->at(5) + pointUp;
	return hg;
}

Hexagon Hexagon::getHexagonDown()
{
	Hexagon hg(this->sideLen);
	hg << this->at(0) + pointDown
		<< this->at(1) + pointDown
		<< this->at(2) + pointDown
		<< this->at(3) + pointDown
		<< this->at(4) + pointDown
		<< this->at(5) + pointDown;
	return hg;
}

Hexagon	Hexagon::getHexagonLeftup()
{
	Hexagon hg(this->sideLen);
	hg << this->at(0) + pointLeftup 
		<< this->at(1) + pointLeftup
		<< this->at(2) + pointLeftup
		<< this->at(3) + pointLeftup
		<< this->at(4) + pointLeftup
		<< this->at(5) + pointLeftup;
	return hg;
}

Hexagon	Hexagon::getHexagonLeftdown()
{
	Hexagon hg(this->sideLen);
	hg << this->at(0) + pointLeftdown 
		<< this->at(1) + pointLeftdown
		<< this->at(2) + pointLeftdown
		<< this->at(3) + pointLeftdown
		<< this->at(4) + pointLeftdown
		<< this->at(5) + pointLeftdown;
	return hg;
}

Hexagon Hexagon::getHexagonRightup()
{
	Hexagon hg(this->sideLen);
	hg << this->at(0) + pointRightup
		<< this->at(1) + pointRightup
		<< this->at(2) + pointRightup
		<< this->at(3) + pointRightup
		<< this->at(4) + pointRightup
		<< this->at(5) + pointRightup;
	return hg;
}

Hexagon	Hexagon::getHexagonRightdown()
{
	Hexagon hg(this->sideLen);
	hg << this->at(0) + pointRightdown
		<< this->at(1) + pointRightdown
		<< this->at(2) + pointRightdown
		<< this->at(3) + pointRightdown
		<< this->at(4) + pointRightdown
		<< this->at(5) + pointRightdown;
	return hg;
}

#if(1)
Hexagon Hexagon::getHexagonDown(qint32 n = 1)
{
	Hexagon hg(this->sideLen);
	QPoint point(0, n * 2 * longLen);
	hg << this->at(0) + point
		<< this->at(1) + point
		<< this->at(2) + point
		<< this->at(3) + point
		<< this->at(4) + point
		<< this->at(5) + point;
	return hg;
}

/*
 * getHexagonRight
 * Input: n is the steps of movement
 *		  ud is the flag fo first move direction, true for up and false for down
 * Output: Hexagon
 */
Hexagon	Hexagon::getHexagonRight(qint32 n, bool ud = true)
{
	Hexagon hg(this->sideLen);
	qint32 x = n / 2;
	QPoint point(x * 2 * sideLen, 0);

	// move even times to right
	hg << this->at(0) + point
		<< this->at(1) + point
		<< this->at(2) + point
		<< this->at(3) + point
		<< this->at(4) + point
		<< this->at(5) + point;

	if (n & 1)
	{
		if (ud)					// move right up
		{
			hg.moveToRightup();
		}
		else					// move right down
		{
			hg.moveToRightdown();
		}
	};

	return hg;
}

#endif

#endif

// the movement of hexagon
#if(1)
void Hexagon::moveToUp()
{
    QVector<QPoint>::iterator ite = this->begin();
    *(ite++) +=pointUp;
    *(ite++) +=pointUp;
    *(ite++) +=pointUp;
    *(ite++) +=pointUp;
    *(ite++) +=pointUp;
    *(ite++) +=pointUp;
}

void Hexagon::moveToDown()
{
    QVector<QPoint>::iterator ite = this->begin();
    *(ite++) +=pointDown;
    *(ite++) +=pointDown;
    *(ite++) +=pointDown;
    *(ite++) +=pointDown;
    *(ite++) +=pointDown;
    *(ite++) +=pointDown;
}

void Hexagon::moveToLeftup()
{
    QVector<QPoint>::iterator ite = this->begin();
    *(ite++) +=pointLeftup;
    *(ite++) +=pointLeftup;
    *(ite++) +=pointLeftup;
    *(ite++) +=pointLeftup;
    *(ite++) +=pointLeftup;
    *(ite++) +=pointLeftup;
}

void Hexagon::moveToLeftdown()
{
    QVector<QPoint>::iterator ite = this->begin();
    *(ite++) +=pointLeftdown;
    *(ite++) +=pointLeftdown;
    *(ite++) +=pointLeftdown;
    *(ite++) +=pointLeftdown;
    *(ite++) +=pointLeftdown;
    *(ite++) +=pointLeftdown;  
}

void Hexagon::moveToRightup()
{
    QVector<QPoint>::iterator ite = this->begin();
    *(ite++) +=pointRightup;
    *(ite++) +=pointRightup;
    *(ite++) +=pointRightup;
    *(ite++) +=pointRightup;
    *(ite++) +=pointRightup;
    *(ite++) +=pointRightup;
}

void Hexagon::moveToRightdown()
{
    QVector<QPoint>::iterator ite = this->begin();
    *(ite++) +=pointRightdown;
    *(ite++) +=pointRightdown;
    *(ite++) +=pointRightdown;
    *(ite++) +=pointRightdown;
    *(ite++) +=pointRightdown;
    *(ite++) +=pointRightdown; 
}

void Hexagon::move(qint32 dx, qint32 dy)
{    
    QPoint point(dx,dy);
    QVector<QPoint>::iterator ite = this->begin();
	*(ite++) +=point;
	*(ite++) +=point;
	*(ite++) +=point;
	*(ite++) +=point;
	*(ite++) +=point;
	*(ite++) +=point; 
}

void Hexagon::move(QPoint point)
{
    QVector<QPoint>::iterator ite = this->begin();
    *(ite++) +=point;
    *(ite++) +=point;
    *(ite++) +=point;
    *(ite++) +=point;
    *(ite++) +=point;
    *(ite++) +=point; 
}

#endif
