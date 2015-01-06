/********************************************************************************
** Form generated from reading UI file 'subwindow0.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBWINDOW0_H
#define UI_SUBWINDOW0_H

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
#include "MeshViewer.h"

QT_BEGIN_NAMESPACE

class Ui_subwindow0
{
public:
    MeshViewer *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFile_F;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *subwindow0)
    {
        if (subwindow0->objectName().isEmpty())
            subwindow0->setObjectName(QString::fromUtf8("subwindow0"));
        subwindow0->resize(800, 600);
        centralwidget = new MeshViewer(subwindow0);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        subwindow0->setCentralWidget(centralwidget);
        menubar = new QMenuBar(subwindow0);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menuFile_F = new QMenu(menubar);
        menuFile_F->setObjectName(QString::fromUtf8("menuFile_F"));
        subwindow0->setMenuBar(menubar);
        toolBar = new QToolBar(subwindow0);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        subwindow0->addToolBar(Qt::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(subwindow0);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        subwindow0->setStatusBar(statusBar);

        menubar->addAction(menuFile_F->menuAction());

        retranslateUi(subwindow0);

        QMetaObject::connectSlotsByName(subwindow0);
    } // setupUi

    void retranslateUi(QMainWindow *subwindow0)
    {
        subwindow0->setWindowTitle(QApplication::translate("subwindow0", "subwindow0", 0, QApplication::UnicodeUTF8));
        menuFile_F->setTitle(QApplication::translate("subwindow0", "File(&F)", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("subwindow0", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class subwindow0: public Ui_subwindow0 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBWINDOW0_H
