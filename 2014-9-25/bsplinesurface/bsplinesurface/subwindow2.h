#ifndef SUBWINDOW2_H
#define SUBWINDOW2_H

#include <QMainWindow>
#include "ui_subwindow2.h"

class subwindow2 : public QMainWindow
{
	Q_OBJECT

public:
	subwindow2(QWidget *parent = 0);
	~subwindow2();

private:
	Ui::subwindow2 ui;
};

#endif // SUBWINDOW2_H
