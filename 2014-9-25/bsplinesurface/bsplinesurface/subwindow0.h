#ifndef SUBWINDOW0_H
#define SUBWINDOW0_H

#include <QMainWindow>
#include "ui_subwindow0.h"
#include <QtGui/QFileDialog>
#include <QtCore/QString>


class subwindow0 : public QMainWindow
{
	Q_OBJECT

public:
	subwindow0(QWidget *parent = 0);
	~subwindow0();

private:
	Ui::subwindow0 ui;
public slots:
	void newFile(); 
	void  open(); 
    bool save();
	bool saveAs();

};

#endif // SUBWINDOW0_H
