#ifndef BSPLINESURFACE_H
#define BSPLINESURFACE_H

#include <QtGui/QMainWindow>
#include "ui_bsplinesurface.h"

class bsplinesurface : public QMainWindow
{
	Q_OBJECT

public:
	bsplinesurface(QWidget *parent = 0, Qt::WFlags flags = 0);
	~bsplinesurface();

private:
	Ui::bsplinesurfaceClass ui;
};

#endif // BSPLINESURFACE_H
