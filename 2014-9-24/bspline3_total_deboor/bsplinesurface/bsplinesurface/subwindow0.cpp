#include "subwindow0.h"

subwindow0::subwindow0(QWidget *parent)
: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(newFile())); 
}

subwindow0::~subwindow0()
{

}
void subwindow0::newFile()
{

}
void subwindow0::open()
{
	//begin painting
ui.centralwidget->flag=true;

}
bool subwindow0::save()
{
return true;
}
bool  subwindow0::saveAs()
{
	return true;

}