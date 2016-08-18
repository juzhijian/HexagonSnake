#include "HexagonSnake.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HexagonSnake w;
	w.show();
	return a.exec();
}
