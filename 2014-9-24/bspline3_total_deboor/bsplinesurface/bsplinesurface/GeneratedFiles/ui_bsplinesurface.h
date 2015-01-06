/********************************************************************************
** Form generated from reading UI file 'bsplinesurface.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BSPLINESURFACE_H
#define UI_BSPLINESURFACE_H

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
#include "subwindow0.h"
#include "subwindow1.h"
#include "subwindow2.h"

QT_BEGIN_NAMESPACE

class Ui_bsplinesurfaceClass
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionExit;
    QAction *actionTile;
    QAction *actionCascade;
    QAction *actionClose;
    QAction *actionCloseAll;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QMdiArea *mdiArea;
    subwindow1 *subwindow_1;
    subwindow2 *subwindow_2;
    subwindow0 *subwindow_0;
    QMenuBar *menuBar;
    QMenu *menuFile_F;
    QMenu *menuWindow_W;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *bsplinesurfaceClass)
    {
        if (bsplinesurfaceClass->objectName().isEmpty())
            bsplinesurfaceClass->setObjectName(QString::fromUtf8("bsplinesurfaceClass"));
        bsplinesurfaceClass->resize(600, 400);
        actionNew = new QAction(bsplinesurfaceClass);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionOpen = new QAction(bsplinesurfaceClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(bsplinesurfaceClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSaveAs = new QAction(bsplinesurfaceClass);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        actionExit = new QAction(bsplinesurfaceClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionTile = new QAction(bsplinesurfaceClass);
        actionTile->setObjectName(QString::fromUtf8("actionTile"));
        actionCascade = new QAction(bsplinesurfaceClass);
        actionCascade->setObjectName(QString::fromUtf8("actionCascade"));
        actionClose = new QAction(bsplinesurfaceClass);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionCloseAll = new QAction(bsplinesurfaceClass);
        actionCloseAll->setObjectName(QString::fromUtf8("actionCloseAll"));
        centralWidget = new QWidget(bsplinesurfaceClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QString::fromUtf8("mdiArea"));
        subwindow_1 = new subwindow1();
        subwindow_1->setObjectName(QString::fromUtf8("subwindow_1"));
        mdiArea->addSubWindow(subwindow_1);
        subwindow_2 = new subwindow2();
        subwindow_2->setObjectName(QString::fromUtf8("subwindow_2"));
        mdiArea->addSubWindow(subwindow_2);
        subwindow_0 = new subwindow0();
        subwindow_0->setObjectName(QString::fromUtf8("subwindow_0"));
        mdiArea->addSubWindow(subwindow_0);

        gridLayout->addWidget(mdiArea, 0, 0, 1, 1);

        bsplinesurfaceClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(bsplinesurfaceClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        menuFile_F = new QMenu(menuBar);
        menuFile_F->setObjectName(QString::fromUtf8("menuFile_F"));
        menuWindow_W = new QMenu(menuBar);
        menuWindow_W->setObjectName(QString::fromUtf8("menuWindow_W"));
        bsplinesurfaceClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(bsplinesurfaceClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        bsplinesurfaceClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(bsplinesurfaceClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        bsplinesurfaceClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile_F->menuAction());
        menuBar->addAction(menuWindow_W->menuAction());
        menuFile_F->addAction(actionNew);
        menuFile_F->addAction(actionOpen);
        menuFile_F->addAction(actionSave);
        menuFile_F->addAction(actionSaveAs);
        menuFile_F->addAction(actionExit);
        menuWindow_W->addAction(actionTile);
        menuWindow_W->addAction(actionCascade);
        menuWindow_W->addAction(actionClose);
        menuWindow_W->addAction(actionCloseAll);

        retranslateUi(bsplinesurfaceClass);
        QObject::connect(actionTile, SIGNAL(triggered()), mdiArea, SLOT(tileSubWindows()));
        QObject::connect(actionCascade, SIGNAL(triggered()), mdiArea, SLOT(cascadeSubWindows()));

        QMetaObject::connectSlotsByName(bsplinesurfaceClass);
    } // setupUi

    void retranslateUi(QMainWindow *bsplinesurfaceClass)
    {
        bsplinesurfaceClass->setWindowTitle(QApplication::translate("bsplinesurfaceClass", "bsplinesurface", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("bsplinesurfaceClass", "New(&N)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionNew->setToolTip(QApplication::translate("bsplinesurfaceClass", "New", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOpen->setText(QApplication::translate("bsplinesurfaceClass", "Open(&O)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("bsplinesurfaceClass", "Open", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSave->setText(QApplication::translate("bsplinesurfaceClass", "Save(&S)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("bsplinesurfaceClass", "Save", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSaveAs->setText(QApplication::translate("bsplinesurfaceClass", "Save As(&A)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSaveAs->setToolTip(QApplication::translate("bsplinesurfaceClass", "Save As", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionExit->setText(QApplication::translate("bsplinesurfaceClass", "Exit(&X)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionExit->setToolTip(QApplication::translate("bsplinesurfaceClass", "Exit", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionTile->setText(QApplication::translate("bsplinesurfaceClass", "Tile(&T)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionTile->setToolTip(QApplication::translate("bsplinesurfaceClass", "Tile", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCascade->setText(QApplication::translate("bsplinesurfaceClass", "Cascade(&C)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCascade->setToolTip(QApplication::translate("bsplinesurfaceClass", "Cascade", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionClose->setText(QApplication::translate("bsplinesurfaceClass", "Close(&O)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionClose->setToolTip(QApplication::translate("bsplinesurfaceClass", "Close", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCloseAll->setText(QApplication::translate("bsplinesurfaceClass", "Close All(&A)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCloseAll->setToolTip(QApplication::translate("bsplinesurfaceClass", "Close All", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        subwindow_1->setWindowTitle(QApplication::translate("bsplinesurfaceClass", "\350\212\202\347\202\271\345\222\214\345\217\202\346\225\260\345\214\226\347\252\227\345\217\243", 0, QApplication::UnicodeUTF8));
        subwindow_2->setWindowTitle(QApplication::translate("bsplinesurfaceClass", "\346\213\237\345\220\210\346\233\262\351\235\242\347\252\227\345\217\243", 0, QApplication::UnicodeUTF8));
        subwindow_0->setWindowTitle(QApplication::translate("bsplinesurfaceClass", "\350\276\223\345\205\245\347\275\221\346\240\274\347\252\227\345\217\243", 0, QApplication::UnicodeUTF8));
        menuFile_F->setTitle(QApplication::translate("bsplinesurfaceClass", "File(&F)", 0, QApplication::UnicodeUTF8));
        menuWindow_W->setTitle(QApplication::translate("bsplinesurfaceClass", "Window(&W)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class bsplinesurfaceClass: public Ui_bsplinesurfaceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BSPLINESURFACE_H
