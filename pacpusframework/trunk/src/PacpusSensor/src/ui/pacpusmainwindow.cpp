// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @author  Gerald Dherbomez <firstname.surname@utc.fr>
/// @version    $Id: pacpusmainwindow.cpp 91 2013-05-19 10:32:48Z gdherbom $

#include "pacpusmainwindow.h"

#include <iostream>
#include <qapplication.h>
#include <qgroupbox.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qstringlist.h>

#include <Pacpus/kernel/ComponentBase.h>
#include <Pacpus/kernel/Log.h>

namespace pacpus {

DECLARE_STATIC_LOGGER("pacpus.core.PacpusMainWindow");

//////////////////////////////////////////////////////////////////////////
PacpusMainWindow::PacpusMainWindow(QWidget * parent)
    : QDialog(parent)
{
    setupUi(this);

    componentManager_ = ComponentManager::getInstance();

    // create the box that will display the components and add it to the main layout of the window
    componentContainer_ = new QGroupBox( "Components" );
    gridLayout->addWidget(componentContainer_);

    // create the own vertical layout of the components list
    layoutBox_ = new QVBoxLayout;
    //create the logical container of the components
    componentGroup_ = new QButtonGroup;
    componentGroup_->setExclusive (false);

    // insert the checkbox corresponding to the components
    QStringList l = componentManager_->getAllComponentsName();
    for (QStringList::Iterator it = l.begin(); it != l.end(); ++it) {
        ComponentCheckBox * chkBox = new ComponentCheckBox( *it, componentContainer_ );
        layoutBox_->addWidget(chkBox);
        componentGroup_->addButton(chkBox);
        QObject::connect(chkBox, SIGNAL(activate(QString)),(QDialog*)this, SLOT(startComponent(QString)) );
        QObject::connect(chkBox, SIGNAL(deactivate(QString)),(QDialog*)this, SLOT(stopComponent(QString)) );
    }
    componentContainer_->setLayout(layoutBox_);

    connect(&monitoringTimer_, SIGNAL(timeout()), this, SLOT(monitoring()));
    monitoringTimer_.start(1000);

    nbActiveComponent_ = 0;
}

//////////////////////////////////////////////////////////////////////////
PacpusMainWindow::~PacpusMainWindow()
{
    monitoringTimer_.stop();
}

//////////////////////////////////////////////////////////////////////////
void PacpusMainWindow::startAcquisition()
{
    for (int i = 0; i < componentGroup_->buttons().size(); ++i) {
        componentGroup_->buttons().at(i)->setChecked(true);
    }
}

//////////////////////////////////////////////////////////////////////////
void PacpusMainWindow::stopAcquisition()
{
    for (int i = 0; i < componentGroup_->buttons().size(); ++i) {
        componentGroup_->buttons().at(i)->setChecked(false);
    }
}

//////////////////////////////////////////////////////////////////////////
void PacpusMainWindow::startComponent(QString component)
{
    componentManager_->start(component);
    ++nbActiveComponent_;
    if (nbActiveComponent_ == componentGroup_->buttons().size()) {
        buttonStop->setEnabled(true);
        buttonStart->setEnabled(false);
    } else {
        buttonStop->setEnabled(true);
        buttonStart->setEnabled(true);
    }
    /*if (!isRunning()) {
        continue_=true;
        start();
    }*/
    //monitoringTimer_.start(100);
}

//////////////////////////////////////////////////////////////////////////
void PacpusMainWindow::stopComponent(QString component)
{
    --nbActiveComponent_;
    componentManager_->stop(component);
    if (nbActiveComponent_ == 0) {
        //msleep(200);
        continue_ = false;
        buttonStop->setEnabled(false);
        buttonStart->setEnabled(true);
    } else {
        buttonStop->setEnabled(true);
        buttonStart->setEnabled(true);
    }
}

//////////////////////////////////////////////////////////////////////////
// Parallel loop of the graphical interface 
// Monitor the component and display their state in the checkbox with the 
// following color code: 
//      state           color       box
//      --------------------------------------
//      stopped         white       unchecked
//      not monitored   gray        checked
//      monitor ok      green       checked 
//      monitor nok     red         checked
//////////////////////////////////////////////////////////////////////////

/// @todo Voir si besoin de faire un thread : un timer est peut être suffisant ?? 
void PacpusMainWindow::monitoring()
{
    /*
    qDebug ("Component monitoring thread running");
    while (continue_)
    {
    msleep(100); */
    // Scan the states of each component and apply the corresponding color to the checkbox

    //QPalette  palet = buttonStop->palette();
    //palet.setColor(QPalette::Button,Qt::red);
    //buttonStop->setPalette(palet);

    for (int i = 0; i < componentGroup_->buttons().size(); ++i) {
        QString componentName = componentGroup_->buttons().at(i)->text();
        ComponentBase::COMPONENT_STATE state = componentManager_->getComponent(componentName)->getState();
        QAbstractButton * b = componentGroup_->buttons()[i];
        QPalette palette = b->palette();

        switch(state) {
        case ComponentBase::STOPPED :
            palette.setColor(QPalette::Base, Qt::white);
            b->setPalette(palette);
            //qDebug() << "STOPPED";
            break;

        case ComponentBase::NOT_MONITORED :
            palette.setColor(QPalette::Base, Qt::gray);
            b->setPalette(palette);
            //qDebug() << "NOT_MONITORED";
            break;

        case ComponentBase::MONITOR_OK :
            palette.setColor(QPalette::Base, Qt::green);
            b->setPalette(palette);
            //qDebug() << "MONITOR_OK";
            break;

        case ComponentBase::MONITOR_NOK :
            palette.setColor(QPalette::Base, Qt::red);
            b->setPalette(palette);
            //qDebug() << "MONITOR_NOK";
            break;

        default:
            std::cerr << "Unkown state " << state << " of component: " << componentName.toStdString() << "\n";
        }
        //componentGroup_->buttons().at(i)->setPalette(palette);
    }
    repaint();
    /*}
    qDebug ("Component monitoring thread stopped"); */
}

} // namespace pacpus
