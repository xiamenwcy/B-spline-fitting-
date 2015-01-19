
#include "mainwindow.h"
#include <QtGui/QApplication>
#include <iostream>


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	std::cout<<"B-spline fitting begin ..."<<std::endl;
	std::cout.precision(10);
	std::cout << std::scientific;
	mainwindow w; 
	w.show();
	return app.exec();
}
