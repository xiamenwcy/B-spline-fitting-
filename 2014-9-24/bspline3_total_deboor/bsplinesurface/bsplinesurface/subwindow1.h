#ifndef SUBWINDOW1_H
#define SUBWINDOW1_H

#include <QMainWindow>
#include "ui_subwindow1.h"

class subwindow1 : public QMainWindow
{
	Q_OBJECT

public:
	subwindow1(QWidget *parent = 0);
	~subwindow1();

private:
	Ui::subwindow1 ui;
};

#endif // SUBWINDOW1_H
