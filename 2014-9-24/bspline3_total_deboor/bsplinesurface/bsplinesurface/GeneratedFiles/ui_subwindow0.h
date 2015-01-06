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
#include "viewer0.h"

QT_BEGIN_NAMESPACE

class Ui_subwindow0
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    viewer0 *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFile_F;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *subwindow0)
    {
        if (subwindow0->objectName().isEmpty())
            subwindow0->setObjectName(QString::fromUtf8("subwindow0"));
        subwindow0->resize(800, 600);
        actionNew = new QAction(subwindow0);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/images/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
        actionOpen = new QAction(subwindow0);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionSave = new QAction(subwindow0);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionSaveAs = new QAction(subwindow0);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/images/saveAs.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveAs->setIcon(icon3);
        centralwidget = new viewer0(subwindow0);
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
        menuFile_F->addAction(actionNew);
        menuFile_F->addAction(actionOpen);
        menuFile_F->addAction(actionSave);
        menuFile_F->addAction(actionSaveAs);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionSave);
        toolBar->addAction(actionSaveAs);

        retranslateUi(subwindow0);
        QObject::connect(actionOpen, SIGNAL(triggered()), subwindow0, SLOT(open()));

        QMetaObject::connectSlotsByName(subwindow0);
    } // setupUi

    void retranslateUi(QMainWindow *subwindow0)
    {
        subwindow0->setWindowTitle(QApplication::translate("subwindow0", "subwindow0", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("subwindow0", "New(&N)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionNew->setToolTip(QApplication::translate("subwindow0", "\346\226\260\345\273\272\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionNew->setShortcut(QApplication::translate("subwindow0", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("subwindow0", "Open(&O)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("subwindow0", "Open", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOpen->setShortcut(QApplication::translate("subwindow0", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("subwindow0", "Save(&S)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("subwindow0", "Save", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSave->setShortcut(QApplication::translate("subwindow0", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionSaveAs->setText(QApplication::translate("subwindow0", "SaveAs(&A)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSaveAs->setToolTip(QApplication::translate("subwindow0", "SaveAs", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSaveAs->setShortcut(QApplication::translate("subwindow0", "Ctrl+A", 0, QApplication::UnicodeUTF8));
        menuFile_F->setTitle(QApplication::translate("subwindow0", "File(&F)", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("subwindow0", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class subwindow0: public Ui_subwindow0 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBWINDOW0_H
