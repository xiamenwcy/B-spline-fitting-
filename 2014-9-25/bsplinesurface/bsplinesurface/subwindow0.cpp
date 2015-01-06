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
QString filename;
filename=QFileDialog::getOpenFileName(this,"open a file","C:/Users/asus/Desktop/bspline3_total_deboor/bsplinesurface/bsplinesurface/model","objectfile(*.obj  *.off  *.stl)") ;  
if (filename!=NULL)   //如果成功的执行
{
	std::string s = filename.toStdString();//qstring转string
	ui.centralwidget->mesh_.clear();
	ui.centralwidget->open_mesh(s);
	ui.centralwidget->flag=true;
	Vec center2;
	center2.setValue(ui.centralwidget->center1[0],ui.centralwidget->center1[1],ui.centralwidget->center1[2]);
	/*ui.centralwidget->camera()->setSceneCenter(center2);
	ui.centralwidget->camera()->setSceneRadius(ui.centralwidget->radius);*/
}

}
bool subwindow0::save()
{
return true;
}
bool  subwindow0::saveAs()
{
	return true;

}