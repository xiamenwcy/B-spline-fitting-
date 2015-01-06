#ifndef SUBWINDOW0_H
#define SUBWINDOW0_H

#include <QMainWindow>
#include "ui_subwindow0.h"



class subwindow0 : public QMainWindow
{
	Q_OBJECT

public:
	subwindow0(QWidget *parent = 0);
	~subwindow0();

public:
	Ui::subwindow0 ui;

};

#endif // SUBWINDOW0_H
