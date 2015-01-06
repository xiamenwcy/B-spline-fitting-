/********************************************************************************
** Form generated from reading UI file 'subwindow2.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBWINDOW2_H
#define UI_SUBWINDOW2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "interface.h"

QT_BEGIN_NAMESPACE

class Ui_subwindow2
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionExit;
    QAction *actionMeshSmooth;
    QAction *actionMeshClear;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    Viewer *widget;
    QMenuBar *menuBar;
    QMenu *menuFile_F;
    QMenu *menuMesh_M;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *subwindow2)
    {
        if (subwindow2->objectName().isEmpty())
            subwindow2->setObjectName(QString::fromUtf8("subwindow2"));
        subwindow2->resize(647, 505);
        actionNew = new QAction(subwindow2);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionOpen = new QAction(subwindow2);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(subwindow2);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSaveAs = new QAction(subwindow2);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        actionExit = new QAction(subwindow2);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionMeshSmooth = new QAction(subwindow2);
        actionMeshSmooth->setObjectName(QString::fromUtf8("actionMeshSmooth"));
        actionMeshClear = new QAction(subwindow2);
        actionMeshClear->setObjectName(QString::fromUtf8("actionMeshClear"));
        centralWidget = new QWidget(subwindow2);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new Viewer(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout->addWidget(widget);

        subwindow2->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(subwindow2);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 647, 23));
        menuFile_F = new QMenu(menuBar);
        menuFile_F->setObjectName(QString::fromUtf8("menuFile_F"));
        menuMesh_M = new QMenu(menuBar);
        menuMesh_M->setObjectName(QString::fromUtf8("menuMesh_M"));
        subwindow2->setMenuBar(menuBar);
        mainToolBar = new QToolBar(subwindow2);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        subwindow2->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(subwindow2);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        subwindow2->setStatusBar(statusBar);

        menuBar->addAction(menuFile_F->menuAction());
        menuBar->addAction(menuMesh_M->menuAction());
        menuFile_F->addAction(actionNew);
        menuFile_F->addAction(actionOpen);
        menuFile_F->addAction(actionSave);
        menuFile_F->addAction(actionSaveAs);
        menuFile_F->addAction(actionExit);
        menuMesh_M->addAction(actionMeshSmooth);
        menuMesh_M->addAction(actionMeshClear);

        retranslateUi(subwindow2);

        QMetaObject::connectSlotsByName(subwindow2);
    } // setupUi

    void retranslateUi(QMainWindow *subwindow2)
    {
        subwindow2->setWindowTitle(QApplication::translate("subwindow2", "subwindow2", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("subwindow2", "New(&N)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionNew->setToolTip(QApplication::translate("subwindow2", "New", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOpen->setText(QApplication::translate("subwindow2", "Open(&O)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("subwindow2", "Open", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSave->setText(QApplication::translate("subwindow2", "Save(&S)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("subwindow2", "Save", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSaveAs->setText(QApplication::translate("subwindow2", "Save As(&A)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSaveAs->setToolTip(QApplication::translate("subwindow2", "Save As", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionExit->setText(QApplication::translate("subwindow2", "Exit(&X)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionExit->setToolTip(QApplication::translate("subwindow2", "Exit", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionMeshSmooth->setText(QApplication::translate("subwindow2", "Mesh  Smooth(&S)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionMeshSmooth->setToolTip(QApplication::translate("subwindow2", "Mesh  Smooth", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionMeshClear->setText(QApplication::translate("subwindow2", "Mesh  Clear(&C)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionMeshClear->setToolTip(QApplication::translate("subwindow2", "Mesh  Clear", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        menuFile_F->setTitle(QApplication::translate("subwindow2", "File(&F)", 0, QApplication::UnicodeUTF8));
        menuMesh_M->setTitle(QApplication::translate("subwindow2", "Mesh(&M)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class subwindow2: public Ui_subwindow2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBWINDOW2_H
