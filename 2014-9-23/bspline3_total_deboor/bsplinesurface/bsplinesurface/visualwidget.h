#ifndef VISUALWIDGET_H
#define VISUALWIDGET_H

#include <QWidget>
#include <Qpainter>
#include <QMouseEvent>
#include "BSplineView.h"

class visualWidget : public QWidget
{
	Q_OBJECT

public:
	visualWidget(QWidget *parent);
	~visualWidget();
	
protected:
	void paintEvent(QPaintEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);

public:
	   double *uknot;
	   double *vknot;
	   CBSplineSurfaceView surface;
	
};

#endif // VISUALWIDGET_H
