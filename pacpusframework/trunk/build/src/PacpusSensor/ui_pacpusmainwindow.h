/********************************************************************************
** Form generated from reading UI file 'pacpusmainwindow.ui'
**
** Created: Tue Oct 1 15:57:47 2013
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PACPUSMAINWINDOW_H
#define UI_PACPUSMAINWINDOW_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PacpusMainWindow
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout1;
    QPushButton *buttonStop;
    QPushButton *buttonStart;

    void setupUi(QWidget *PacpusMainWindow)
    {
        if (PacpusMainWindow->objectName().isEmpty())
            PacpusMainWindow->setObjectName(QString::fromUtf8("PacpusMainWindow"));
        PacpusMainWindow->resize(120, 78);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PacpusMainWindow->sizePolicy().hasHeightForWidth());
        PacpusMainWindow->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(PacpusMainWindow);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout1 = new QGridLayout();
        gridLayout1->setSpacing(6);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        buttonStop = new QPushButton(PacpusMainWindow);
        buttonStop->setObjectName(QString::fromUtf8("buttonStop"));
        buttonStop->setEnabled(false);

        gridLayout1->addWidget(buttonStop, 2, 0, 1, 1);

        buttonStart = new QPushButton(PacpusMainWindow);
        buttonStart->setObjectName(QString::fromUtf8("buttonStart"));

        gridLayout1->addWidget(buttonStart, 0, 0, 2, 1);


        gridLayout->addLayout(gridLayout1, 0, 0, 1, 1);


        retranslateUi(PacpusMainWindow);
        QObject::connect(buttonStart, SIGNAL(clicked()), PacpusMainWindow, SLOT(startAcquisition()));
        QObject::connect(buttonStop, SIGNAL(clicked()), PacpusMainWindow, SLOT(stopAcquisition()));

        QMetaObject::connectSlotsByName(PacpusMainWindow);
    } // setupUi

    void retranslateUi(QWidget *PacpusMainWindow)
    {
        PacpusMainWindow->setWindowTitle(QApplication::translate("PacpusMainWindow", "Pacpus", 0, QApplication::UnicodeUTF8));
        buttonStop->setText(QApplication::translate("PacpusMainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        buttonStart->setText(QApplication::translate("PacpusMainWindow", "Start", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PacpusMainWindow: public Ui_PacpusMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PACPUSMAINWINDOW_H
