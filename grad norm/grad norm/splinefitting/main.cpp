

#include <QApplication>
#include <QtGui>
#include "mainwindow.h"
#include <iostream>
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setApplicationName("B-spline fitting");
	std::cout.precision(10);
	std::cout << std::scientific;
	std::cout<<"B-spline fitting begin ..."<<std::endl;
	mainwindow w; 
	w.show();
	return app.exec();
}
