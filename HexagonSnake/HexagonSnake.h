#ifndef HEXAGONSNAKE_H
#define HEXAGONSNAKE_H

#include "common.h"
#include "snake.h"
#include "smap.h"
#include "hexagon.h"
#include "GameSet.h"

#include <QtWidgets/QMainWindow>
#include "ui_HexagonSnake.h"

#include <QPaintEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimerEvent>
#include <QTime>
#include <QSettings>
#include <QString>
#include <QPainter>
#include <QImage>
#include <QPen>
#include <QBrush>
#include <QMessageBox>
#include <QLabel>
#include <QMap>
#include <QList>

class HexagonSnake : public QMainWindow
{
	Q_OBJECT

public:
	HexagonSnake(QWidget *parent = 0);
	~HexagonSnake();

	void	createCtrl();

	bool	loadSettings();
	void	loadDefaultSettings();
	void	changeSettings();

	void	initMapAndSnake();
	void	drawMapAndSnake();

	void	createNewFood();

protected:
	void paintEvent(QPaintEvent *);
	void timerEvent(QTimerEvent *);
	void keyPressEvent(QKeyEvent *);
	void keyReleaseEvent(QKeyEvent *);
	//void mousePressEvent(QMouseEvent *); 

signals:
	void pauseSelected(int id);

private:
	Ui::HexagonSnakeClass ui;

	// snake map
	Smap		*pSmap;
	QImage		*pMapImg;
	QRect		mapRect;						// the rect range of snake area and map area
	qint32		nSideSize;						// the basic step size
	qint32		nMapW;
	qint32		nMapH;
	qint32		mapTimerId;						// timer id
	qint32		mapTimerInt;					// timer interval

	// snake
	Snake		*pSnake;
	Qt::Key		keyCurDir;						// the current move direction

	// food
	Hexagon		*pFoodHg;
	qint32		nFoodAllNum;					// all the num of food can be place
	QPoint		pointFoodHg;
	QRadialGradient brushStyle;
	QPen		penFood;

	// path
	QString		strProPath;

	// key
	QMap<Qt::Key, qint8>	mapKey2Int;
	Qt::Key		keyMoveUp;
	Qt::Key		keyMoveDown;
	Qt::Key		keyMoveLeftup;
	Qt::Key		keyMoveLeftdown;
	Qt::Key		keyMoveRightup;
	Qt::Key		keyMoveRightdown;
	Qt::Key		keyPause;

	// pause menu
	bool		bPause;
	QString		strLblSelected;
	QString		strLblNotSelected;
	QList<QLabel*> listUiLbl;
	int			nCurLabel;
	QLabel		*uiLblReturn;
	QLabel		*uiLblSetting;
	QLabel		*uiLblExit;
	QLabel		*uiLblShow;
	QWidget		*uiPauseWidget;
};

#endif // HEXAGONSNAKE_H
