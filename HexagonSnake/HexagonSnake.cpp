#include "HexagonSnake.h"

HexagonSnake::HexagonSnake(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// windows setting
	//this->setMinimumSize(800, 600);
	this->resize(800, 600);
    this->setWindowIcon(QIcon(":/HS/Resources/icon256.png"));
	strProPath = QApplication::applicationDirPath();

	// program setting
	loadDefaultSettings();
	/*
	if (!loadSettings())
	{
	loadDefaultSettings();
	}
	*/

	// ctrl setiing
	createCtrl();

	initMapAndSnake();

}

HexagonSnake::~HexagonSnake()
{

}


void HexagonSnake::createCtrl()
{
	bPause = false;

	// widget for pause ui
	uiPauseWidget = new QWidget(this);
	uiPauseWidget->resize(this->size());
	uiPauseWidget->setStyleSheet("background-color: rgba(150,150,150,190);"
								 "border-width: 2px;"
								 "border-style: solid;"
								 "border-color: rgb(0,200,0);"
								 "color: yellow;"
								 "font-family: Courier New;"
								 "font-size: 36px;"
								 "font-weight: bold;");
	uiPauseWidget->setHidden(true);
	
	// pause label
	uiLblShow = new QLabel(tr("Pause"), this);
	uiLblShow->setStyleSheet("color: rgba(30,30,30,200);"
							 "font-size: 70px;");

	// return to game label
	uiLblReturn = new QLabel(tr("Return to Game"), this);

	// setting label
	uiLblSetting = new QLabel(tr("Setting"), this);

	// exti label
	uiLblExit = new QLabel(tr("Exit"), this);

	// pause widget layout 
	QHBoxLayout	*uiHLayoutWidget = new QHBoxLayout(uiPauseWidget);
	QGridLayout *uiVLayoutWidget = new QGridLayout(uiPauseWidget);
	uiVLayoutWidget->addWidget(uiLblReturn);
	uiVLayoutWidget->addWidget(uiLblSetting);
	uiVLayoutWidget->addWidget(uiLblExit);
	uiHLayoutWidget->addWidget(uiLblShow);
	uiHLayoutWidget->addLayout(uiVLayoutWidget);

	// label list
	listUiLbl.append(uiLblReturn);
	listUiLbl.append(uiLblSetting);
	listUiLbl.append(uiLblExit);

	// connection
	connect(this,&HexagonSnake::pauseSelected,
		[=](int index){
		switch (index)
		{
		case 0:
			mapTimerId = QObject::startTimer(mapTimerInt);
			uiPauseWidget->hide();
			bPause = !bPause;
			break;
		case 1:
			this->changeSettings();
			break;
		case 2:
			if (QMessageBox::Yes ==
				QMessageBox::question(this, tr("Quesiton"), tr("Are you sure?")))
			{
				QApplication::exit();
			}
			break;
		default:
			break;
		}
	});
}

bool HexagonSnake::loadSettings()
{
	QSettings	s("settings.ini", QSettings::IniFormat);
	s.setIniCodec("utf-8");

	keyMoveUp = Qt::Key(s.value("KeyBoard/moveUp").toInt());
	keyMoveDown = Qt::Key(s.value("KeyBoard/moveDown").toInt());
	keyMoveLeftup = Qt::Key(s.value("KeyBoard/moveLeftup").toInt());
	keyMoveLeftdown = Qt::Key(s.value("KeyBoard/moveLeftdown").toInt());
	keyMoveRightup = Qt::Key(s.value("KeyBoard/moveRightup").toInt());
	keyMoveRightdown = Qt::Key(s.value("KeyBoard/moveRightdown").toInt());
	keyPause = Qt::Key(s.value("KeyBoard/pause").toInt());

	return true;
}

void HexagonSnake::loadDefaultSettings()
{
	// snake and map
	nSideSize = 25;
	nMapW = SNAKE_MAP_WIDTH;
	nMapH = SNAKE_MAP_HEIGHT;

	// key
	keyMoveUp = Qt::Key_E;
	keyMoveDown = Qt::Key_D;
	keyMoveLeftup = Qt::Key_W;
	keyMoveLeftdown = Qt::Key_S;
	keyMoveRightup = Qt::Key_R;
	keyMoveRightdown = Qt::Key_F;
	mapKey2Int.insert(keyMoveUp, 0);
	mapKey2Int.insert(keyMoveDown, 1);
	mapKey2Int.insert(keyMoveLeftup, 2);
	mapKey2Int.insert(keyMoveLeftdown, 3);
	mapKey2Int.insert(keyMoveRightup, 4);
	mapKey2Int.insert(keyMoveRightdown, 5);

	keyPause = Qt::Key_Space;

	// style
	strLblSelected = QString("color:blue;\
							   background-color: rgb(250,250,250);");
	strLblNotSelected = QString("color: yellow;\
							       background-color: rgba(150,150,150,190);");

#if(1)
	QSettings setting("settings.ini", QSettings::IniFormat);
	setting.setIniCodec("utf-8");

	setting.beginGroup("SnakeAndMap");
	setting.setValue("sideSize", nSideSize);
	setting.setValue("mapWidth", nMapW);
	setting.setValue("mapHeight", nMapH);
	setting.endGroup();

	setting.beginGroup("KeyBoard");
	setting.setValue("moveUp", keyMoveUp);
	setting.setValue("moveDown", keyMoveDown);
	setting.setValue("moveLeftup", keyMoveLeftup);
	setting.setValue("moveLeftdown", keyMoveLeftdown);
	setting.setValue("moveRightup", keyMoveRightup);
	setting.setValue("moveRightdown", keyMoveRightdown);
	setting.setValue("pause", keyPause);
	setting.endGroup();

	setting.beginGroup("StyleSheet");
	setting.setValue("labelSelected", strLblNotSelected);
	setting.setValue("labelNotSelected", strLblNotSelected);
	setting.endGroup();

#endif

}

void HexagonSnake::changeSettings()
{
	GameSet	set(this);
	if (QDialog::Accepted == set.exec())
	{

	}
	else
	{

	}

}

void HexagonSnake::initMapAndSnake()
{
	// create showing image area
	pMapImg = new QImage(nMapW, nMapH, QImage::Format_ARGB32_Premultiplied);

	// create the Smap instance
	mapRect.setLeft(20);
	mapRect.setTop(20);
	mapRect.setWidth(760);
	mapRect.setHeight(560);
	pSmap = new Smap(mapRect,nSideSize,this);

	// create the Snake instance
	pSnake = new Snake(mapRect,nSideSize, pSmap->getLeftupPoint(), this);
	keyCurDir = keyMoveDown;
	
	connect(pSnake, &Snake::foodGetted, 
		[=]{
		delete pFoodHg;
		createNewFood();
	});

	// create the food
	nFoodAllNum = pSmap->getHgPointNum();
	penFood.setColor(Qt::yellow);
	penFood.setWidth(2);
	brushStyle = QRadialGradient();
	brushStyle.setColorAt(0, Qt::yellow);
	brushStyle.setColorAt(1, Qt::darkMagenta);
	brushStyle.setSpread(QGradient::ReflectSpread);
	createNewFood();

	// draw the map and snake
	drawMapAndSnake();

	// set the timer event
	mapTimerInt = 350;
	mapTimerId = QObject::startTimer(mapTimerInt);
}

void HexagonSnake::drawMapAndSnake()
{
	pMapImg->fill(QColor(0, 0, 0));

	QPainter pp(pMapImg);
	
	// draw map
	pp.drawImage(mapRect.left(),mapRect.top(), pSmap->getMap());

	// draw snake
	pSnake->moveNext(mapKey2Int.value(keyCurDir),pointFoodHg);
	pp.drawImage(mapRect.left(), mapRect.top(), pSnake->getSnake());

	// draw food
	pp.setPen(penFood);
	pp.setBrush(brushStyle);
	pp.drawConvexPolygon(*pFoodHg);
}

void HexagonSnake::createNewFood()
{
	qsrand(QTime::currentTime().minute()+QTime::currentTime().second()*1000);
	int index = qrand() % nFoodAllNum;
			// get the num between [a,b): (qrand() % (b-a)) + a

	pFoodHg = new Hexagon(nSideSize);
	pFoodHg->initHexagon();
	pointFoodHg = pSmap->getVecHgPoint(index);
	pFoodHg->move(QPoint(mapRect.left(),mapRect.top()) + pointFoodHg);
}

/*******************************************************************/

void HexagonSnake::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    
	QPainter painter(this);
	//painter.setViewport(0, 0, 800, 600);			
	// 实际显示区域，即物理坐标：给painter绘制的区域，默认为this->geometry()，会随窗口的改变而改变
	//painter.setWindow(0, 0, 300, 200);				
	// 绘图区域，即逻辑坐标：即将 800x600 的显示区域映射成 300x200 绘图区域
	//painter.fillRect(0, 0, 150, 100, Qt::green);
	// 绘制一个“绘图区域”的1/4大小的矩形，当改变窗口大小，矩形仍为窗口大小的1/4
	painter.setWindow(0, 0, this->nMapW, this->nMapH);
	painter.drawImage(0, 0, *pMapImg);
}

void HexagonSnake::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e)
    
    //if(e->timerId() == mapTimerId)
    //{
		drawMapAndSnake();
		update();
    //}
}

void HexagonSnake::keyPressEvent(QKeyEvent *e)
{
	int key = e->key();
    
    if(!this->bPause)
    {
		if (keyMoveUp == key
			|| keyMoveDown == key
			|| keyMoveLeftup == key
			|| keyMoveLeftdown == key
			|| keyMoveRightup == key
			|| keyMoveRightdown == key)
		{
			keyCurDir = Qt::Key(key);
		}
		else if (keyPause == key)
		{
			QObject::killTimer(mapTimerId);
			uiLblReturn->setStyleSheet(strLblSelected);
			uiLblSetting->setStyleSheet(strLblNotSelected);
			uiLblExit->setStyleSheet(strLblNotSelected);
			uiPauseWidget->show();
			nCurLabel = 0;
			bPause = !bPause;
		}
    }
    else
    {
        if (keyPause == key)
		{
			mapTimerId = QObject::startTimer(mapTimerInt);
			uiPauseWidget->hide();
			bPause = !bPause;
		}
		else if (Qt::Key_Up == key)
		{
			listUiLbl.at(nCurLabel)->setStyleSheet(strLblNotSelected);
			if (0 == nCurLabel)
			{
				nCurLabel = listUiLbl.size() - 1;
			}
			else
			{
				--nCurLabel;
			}
			listUiLbl.at(nCurLabel)->setStyleSheet(strLblSelected);
		}
		else if (Qt::Key_Down == key)
		{
			listUiLbl.at(nCurLabel)->setStyleSheet(strLblNotSelected);
			if (listUiLbl.size() - 1 == nCurLabel)
			{
				nCurLabel = 0;
			}
			else
			{
				++nCurLabel;
			}
			listUiLbl.at(nCurLabel)->setStyleSheet(strLblSelected);

		}
		else if (Qt::Key_Return == key)
		{
			emit(pauseSelected(nCurLabel));
			/*
			this->changeSettings();
			QApplication::exit();
			*/
		}
    }
}

void HexagonSnake::keyReleaseEvent(QKeyEvent *e)
{
	Q_UNUSED(e)
}
