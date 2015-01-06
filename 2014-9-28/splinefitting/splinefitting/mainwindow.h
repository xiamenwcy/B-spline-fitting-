#pragma once

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMdiArea>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <QtCore/QString>
#include <QtGui/QLabel>
#include <QtGui/QFileDialog>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Geometry/VectorT.hh>
#include <iostream>
#include "MeshSubWindow.h"
#include "KnotSubWindow.h"
#include "FitSubWindow.h"
#include <QtCore/QTextCodec>




//QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));//支持中文

class QMdiArea;
class QMenu;
class QAction;
class QMdiSubWindow;
class QActionGroup;



class mainwindow:public  QMainWindow
{
	Q_OBJECT
public:
	mainwindow(void);
	~mainwindow(void);

private slots:
		void newFile();
		void open();
		//bool save();
		//bool saveAs();
		//bool savePara();
		//bool save_global_costs();
		void openRecentFile();
		//void set_window_visible(bool bVisible);
		//void set_boundary_condition(bool bBoundary);
		void meshwindow_close();
		void knotswindow_close();
		void fitwindow_close();
		/*void set_triangulation_type();
		void set_triangulation_type(bool tv);
		void surface_sampling();
		void add_knots();
		void mesh_parametrization();
		void surface_fitting();
		void mesh_fitting();
		void set_output(bool bo);
		void set_sa_type();
		void set_ann(bool av);
		void set_knot_input(bool ki);
		void save_knots();*/
signals:
       void updateMeshWindow(CSurfaceData *surfacedata);

protected:

	typedef OpenMesh::TriMesh_ArrayKernelT<>  Mesh;

private:
	void createActions();
	void createMenus();
	void updateRecentFileActions();
	QString strippedName(const QString &fullFileName);

	enum { MaxRecentFiles = 5 };
	QAction *recentFileActions[MaxRecentFiles];
	QAction *separatorAction;

	QMenu *fileMenu;
	QMenu *samplingMenu;
	QMenu *fittingMenu;
	QMenu *surfaceMenu;
	QMenu *meshMenu;
	QMenu *optionsMenu;
	QMenu *triangulationMenu;
	QMenu *saMenu;
	QMenu *windowMenu;
	QMenu *helpMenu;
	QMenu *testMenu;
	QMenu *saveMenu;
	QAction *testAction;
	QAction *newAction;
	QAction *openAction;
	QAction *saveAction;
	QAction *saveCurvatureAction;
	QAction *saveDensityAction;
	QAction *saveFitAction;
	QAction *saveErrorAction;
	QAction *saveCEAction;
	QAction *saveCMAction;
	QAction *saveparaAction;
	QAction *samplingAction_1;
	QAction *samplingAction_2;
	QAction *samplingAction_3;
	QAction *knotsAction;
	QAction *surfacefittingAction;
	QAction *parametrizationAction;
	QAction *matrixoutputAction;
	QAction *meshfittingAction;
	QAction *boundaryAction;
	QActionGroup *triangulationActionGroup;
	QAction *delaunayAction;
	QAction *mean_errorAction;
	QAction *sco_Action;
	QAction *variance_ddtAction;
	QAction *local_ddtAction;
	QAction *annAction;
	QAction *onestepAction;
	QAction *saAction;
	QAction *lopAction;
	QAction *combinationAction;
	QActionGroup *saActionGroup;
	QActionGroup *windowActionGroup;
	QAction *pointsAction;
	QAction *meshAction;
	QAction *fittingAction;
	QAction *exitAction;
	QAction *aboutAction;
	QAction *aboutQtAction;
	QAction *outputAction;
	QAction *saveGCAction;
	QAction *knotInputAction;
	QAction *saveKnotsAction;

	QMdiArea *mdi;
	MeshSubWindow *meshwindow;
	KnotSubWindow *knotswindow;
	FitSubWindow  *fitwindow;
	CSurfaceData *surfacedata;
	QMdiSubWindow* mesh;//初始网格窗口
	QMdiSubWindow* knots;//初始节点窗口
	QMdiSubWindow* fitting;//拟合网格窗口
};
