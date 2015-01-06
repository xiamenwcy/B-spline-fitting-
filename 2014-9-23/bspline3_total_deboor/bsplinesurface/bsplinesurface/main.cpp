#include "bsplinesurface.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	bsplinesurface w;
	w.show();
	return a.exec();
}
