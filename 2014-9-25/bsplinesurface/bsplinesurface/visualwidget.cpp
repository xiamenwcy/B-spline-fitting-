#include "visualwidget.h"
#include <math.h>
#include<QPainter>
#include <QToolTip>

visualWidget::visualWidget(QWidget *parent)
	: QWidget(parent)
{
	surface.GenerateKnots(1);
	uknot=new double[mpoints+1];
	vknot=new double[npoints+1];
	double delt1,delt2;
	int i,j;
	delt1=(surface.uknots[M+1]-surface.uknots[p])/(double)mpoints;//定义区间为[u_p,u_(m+1)],均分成mpoints等分
	delt2=(surface.vknots[N+1]-surface.vknots[q])/(double)npoints;//定义区间为[v_q,v_(n+1)],均分成npoints等分

	uknot[0]=surface.uknots[p];
	vknot[0]=surface.vknots[q];

	for(i=1;i<=mpoints;i++)
		uknot[i]=uknot[i-1]+delt1;
	for (j=1;j<=npoints;j++)
		vknot[j]=vknot[j-1]+delt2;
}

visualWidget::~visualWidget()
{
	delete []uknot;
	delete []vknot;
}



void visualWidget::paintEvent(QPaintEvent *event)
{
	int side=qMin(width(),height());
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QTransform transform;
	transform.translate(width()/5,height()/10);
	transform.scale(side/1.2,side/1.2);
	painter.setWorldTransform(transform);
	painter.save();
	painter.setPen(Qt::red);
	QPointF point[4];
	for(int i=1;i<=npoints;i++)
		for(int j=0;j<mpoints;j++)
		{
				point[0]=QPointF(uknot[i-1],vknot[j]);
				point[1]=QPointF(uknot[i],vknot[j]);
				point[2]=QPointF(uknot[i-1],vknot[j+1]);
				point[3]=QPointF(uknot[i-1],vknot[j]);
			    painter.drawPolyline(point,4);

				
				point[0]=QPoint(uknot[i],vknot[j]);
				point[1]=QPoint(uknot[i-1],vknot[j+1]);
				point[2]=QPoint(uknot[i],vknot[j+1]);
				point[3]=QPoint(uknot[i],vknot[j]);
				painter.drawPolyline(point,4);
			  
		}
	
     painter.restore();
	painter.save();
	painter.setPen(Qt::black);
	painter.setPen(Qt::DashLine);
	for(int i=0;i<=N+q+1;i++)
		for(int j=-1;j<M+p;j++)
			painter.drawLine(QPointF(surface.uknots[j+1],surface.vknots[i]),QPointF(surface.uknots[j+2],surface.vknots[i]));
	painter.restore();
}



void visualWidget::mousePressEvent(QMouseEvent* event)
{
	
}

void visualWidget::mouseMoveEvent(QMouseEvent* event)
{
	QString pos=QString("%1,%2").arg(event->pos().x()).arg(event->pos().y());
	QToolTip::showText(event->globalPos(), pos, this);

}

void visualWidget::wheelEvent(QWheelEvent* event)
{
	
}

