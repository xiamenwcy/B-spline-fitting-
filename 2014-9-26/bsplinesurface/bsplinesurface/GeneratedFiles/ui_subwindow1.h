/********************************************************************************
** Form generated from reading UI file 'subwindow1.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBWINDOW1_H
#define UI_SUBWINDOW1_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include "visualwidget.h"

QT_BEGIN_NAMESPACE

class Ui_subwindow1
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionExit;
    QAction *actionMeshparameterization;
    QAction *actionMeshdomain;
    QAction *actionClear;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    visualWidget *widget;
    QMenuBar *menuBar;
    QMenu *menuFile_F;
    QMenu *menuMesh_M;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *subwindow1)
    {
        if (subwindow1->objectName().isEmpty())
            subwindow1->setObjectName(QString::fromUtf8("subwindow1"));
        subwindow1->resize(573, 512);
        actionNew = new QAction(subwindow1);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionOpen = new QAction(subwindow1);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(subwindow1);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSaveAs = new QAction(subwindow1);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        actionExit = new QAction(subwindow1);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionMeshparameterization = new QAction(subwindow1);
        actionMeshparameterization->setObjectName(QString::fromUtf8("actionMeshparameterization"));
        actionMeshdomain = new QAction(subwindow1);
        actionMeshdomain->setObjectName(QString::fromUtf8("actionMeshdomain"));
        actionClear = new QAction(subwindow1);
        actionClear->setObjectName(QString::fromUtf8("actionClear"));
        centralWidget = new QWidget(subwindow1);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget = new visualWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        subwindow1->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(subwindow1);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 573, 23));
        menuFile_F = new QMenu(menuBar);
        menuFile_F->setObjectName(QString::fromUtf8("menuFile_F"));
        menuMesh_M = new QMenu(menuBar);
        menuMesh_M->setObjectName(QString::fromUtf8("menuMesh_M"));
        subwindow1->setMenuBar(menuBar);
        mainToolBar = new QToolBar(subwindow1);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        subwindow1->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(subwindow1);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        subwindow1->setStatusBar(statusBar);

        menuBar->addAction(menuFile_F->menuAction());
        menuBar->addAction(menuMesh_M->menuAction());
        menuFile_F->addAction(actionNew);
        menuFile_F->addAction(actionOpen);
        menuFile_F->addAction(actionSave);
        menuFile_F->addAction(actionSaveAs);
        menuFile_F->addAction(actionExit);
        menuMesh_M->addAction(actionMeshparameterization);
        menuMesh_M->addAction(actionMeshdomain);
        menuMesh_M->addAction(actionClear);

        retranslateUi(subwindow1);

        QMetaObject::connectSlotsByName(subwindow1);
    } // setupUi

    void retranslateUi(QMainWindow *subwindow1)
    {
        subwindow1->setWindowTitle(QApplication::translate("subwindow1", "subwindow1", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("subwindow1", "New(&N)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionNew->setToolTip(QApplication::translate("subwindow1", "New", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOpen->setText(QApplication::translate("subwindow1", "Open(&O)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("subwindow1", "Open", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSave->setText(QApplication::translate("subwindow1", "Save(&S)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("subwindow1", "Save", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSaveAs->setText(QApplication::translate("subwindow1", "Save As(&A)", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("subwindow1", "Exit(&X)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionExit->setToolTip(QApplication::translate("subwindow1", "Exit", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionMeshparameterization->setText(QApplication::translate("subwindow1", "Mesh parameterization(&P)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionMeshparameterization->setToolTip(QApplication::translate("subwindow1", "Mesh parameterization", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionMeshdomain->setText(QApplication::translate("subwindow1", "Mesh  domain(&D)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionMeshdomain->setToolTip(QApplication::translate("subwindow1", "Mesh  domain", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionClear->setText(QApplication::translate("subwindow1", "Clear(&C)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionClear->setToolTip(QApplication::translate("subwindow1", "Clear", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        menuFile_F->setTitle(QApplication::translate("subwindow1", "File(&F)", 0, QApplication::UnicodeUTF8));
        menuMesh_M->setTitle(QApplication::translate("subwindow1", "Mesh(&M)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class subwindow1: public Ui_subwindow1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBWINDOW1_H
