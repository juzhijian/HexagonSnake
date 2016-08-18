#ifndef GAMESET_H
#define GAMESET_H

#include <QDialog>
#include "ui_GameSet.h"

class GameSet : public QDialog
{
	Q_OBJECT

public:
	GameSet(QWidget *parent = 0);
	~GameSet();

private:
	Ui::GameSet ui;
};

#endif // GAMESET_H
