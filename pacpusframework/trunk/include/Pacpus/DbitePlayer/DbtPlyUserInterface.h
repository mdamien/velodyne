// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Gerald Dherbomez <firstname.surname@utc.fr>
/// @date    April, 2007
/// @version $Id: DbtPlyUserInterface.h 91 2013-05-19 10:32:48Z gdherbom $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief DbitePlayer graphical user interface.
///
/// Detailed description.

#ifndef DEF_PACPUS_DBTPLYUSERINTERFACE_H
#define DEF_PACPUS_DBTPLYUSERINTERFACE_H

#include <QWidget>

#include <Pacpus/kernel/ComponentBase.h>
#include <Pacpus/kernel/ComponentFactory.h>
#include <Pacpus/DbitePlayer/DbitePlayerConfig.h>
#include <Pacpus/DbitePlayer/DbtPlyFileManager.h>
#include <Pacpus/DbitePlayer/DbtPlyEngine.h>

class QButtonGroup;
class QCheckBox;
class QCloseEvent;
class QGroupBox;
class QLabel;
class QLayout;
class QPushButton;
class QSlider;
class QTableWidget;

namespace pacpus {
    
class DbtPlyEngine;
class DbtPlyEngineState;

class DBITE_PLAYER_API DbtPlyUserInterface
        : public QWidget
        , public ComponentBase
{
    Q_OBJECT

public:
    /// Constructor.
    ///
    /// @param name component name
    /// @see ComponentBase::ComponentBase(QString)
    DbtPlyUserInterface(QString name);

    /// Destructor.
    ~DbtPlyUserInterface();

    /// @returns time slider value
    int getTime();

    /// sets time slider value to 0
    void resetTime();

public Q_SLOTS:
    /// Slot.
    /// Refreshes the state of the player.
    void displayStateSlot(DbtPlyEngineState * state, float speed);

    /// Slot.
    /// Displays the max and min times.
    void displayMinMaxTime(road_time_t min, road_time_t max);

    /// Slot.
    /// Displays the current time of the player.
    void displayTime(road_time_t time);

private:
    /// Configures the component.
    virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

    /// Starts component activity.
    virtual void startActivity();

    /// Stops component activity.
    virtual void stopActivity();

    void closeEvent(QCloseEvent * e);

    void connectButtons();
    void connectDisplay();
    void connectSlider();
    QLayout * createMainLayout();
    QGroupBox * createControlGroupBox();
    QGroupBox * createComponentListGroupBox();
    void updateComponentList();
    
private:
    DbtPlyEngine * mEngine;

    QWidget * wTel_ ;
    QButtonGroup * butGroup;
    QPushButton * playBut ;
    QPushButton * pauseBut ;
    QPushButton * stopBut ;
    QPushButton * speedUpBut ;
    QPushButton * speedDownBut ;
    QLabel * lab;
    QCheckBox * rev;
    QSlider * timeSlider;
    QLabel * timeMinTitle;
    QLabel * timeMinValue;
    QLabel * timeMaxTitle;
    QLabel * timeMaxValue;
    QLabel * timeCurTitle;
    QLabel * timeCurValue;

    QTableWidget * componentTableWidget;

    // current max time
    road_time_t tMax_;
    // current min time
    road_time_t tMin_;
    // current absolute time
    road_time_t absTime_;
    // current relative time
    int relTime_;
};

} // namespace pacpus

#endif // DEF_PACPUS_DBTPLYUSERINTERFACE_H
