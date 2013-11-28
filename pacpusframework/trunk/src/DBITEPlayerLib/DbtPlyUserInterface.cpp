// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @author  Gerald Dherbomez <firstname.surname@utc.fr>
/// @version $Id: DbtPlyUserInterface.cpp 91 2013-05-19 10:32:48Z gdherbom $

#include <Pacpus/DbitePlayer/DbtPlyUserInterface.h>

#include <Pacpus/kernel/ComponentManager.h>
#include <Pacpus/kernel/Log.h>

#include <cassert>
#include <cmath> // fabs
#include <qapplication.h>   // quit()
#include <qboxlayout.h>
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qslider.h>
#include <qtablewidget.h>

namespace pacpus {

class DbtPlyEngineState;

DECLARE_STATIC_LOGGER("pacpus.core.DbtPlyUserInterface");

//static ComponentFactory<DbtPlyUserInterface> factory("DbtPlyUserInterface");

////////////////////////////////////////////////////////////////////////////////
DbtPlyUserInterface::DbtPlyUserInterface(QString name)
    : ComponentBase(name)
    , componentTableWidget(NULL)
    , mEngine(NULL)
{
    relTime_ = absTime_ = tMin_ = tMax_ = 0;

    setLayout(createMainLayout());

    show();
}

////////////////////////////////////////////////////////////////////////////////
DbtPlyUserInterface::~DbtPlyUserInterface()
{  
}

////////////////////////////////////////////////////////////////////////////////
ComponentBase::COMPONENT_CONFIGURATION DbtPlyUserInterface::configureComponent(XmlComponentConfig /*config*/)
{
    ComponentManager * mgr = ComponentManager::getInstance();
    mEngine = dynamic_cast<DbtPlyEngine *>(mgr->getComponent("dbiteEngine"));
    if (NULL == mEngine) {
        LOG_FATAL("cannot get a pointer of the 'dbiteEngine' component");
        return CONFIGURED_FAILED;
    }

    connectButtons();
    connectDisplay();
    connectSlider();

    updateComponentList();

    return ComponentBase::CONFIGURED_OK;
}

////////////////////////////////////////////////////////////////////////////////
/// Starts activity.
void DbtPlyUserInterface::startActivity()
{ 
}

////////////////////////////////////////////////////////////////////////////////
/// Stops activity.
void DbtPlyUserInterface::stopActivity()
{ 
}

////////////////////////////////////////////////////////////////////////////////
/// Overloaded.
/// Invoked on close event.
void DbtPlyUserInterface::closeEvent(QCloseEvent * /*event*/)
{
    qApp->quit();
}

void DbtPlyUserInterface::displayStateSlot(DbtPlyEngineState * state, float speed)
{
    LOG_DEBUG("displayStateSlot, state = " << state->toString() << ", speed = " << speed);

    QString speedString;
    if (fabs(speed) >= 1) {
        speedString = speedString.setNum((int)speed);
    } else {
        speedString = "1/" + speedString.setNum((int)(1.0 / speed));
    }

    QString stateAndSpeedText;
    stateAndSpeedText = state->toString() + " - speed : " + speedString;

    lab->setText(stateAndSpeedText);
    lab->adjustSize();
}

void DbtPlyUserInterface::displayMinMaxTime(road_time_t min, road_time_t max)
{
    timeMinValue->setText(QString::number(min));
    tMin_ = min;
    timeMaxValue->setText(QString::number(max));
    tMax_ = max;
    timeSlider->setMaximum(tMax_-tMin_);
}

void DbtPlyUserInterface::displayTime(road_time_t time)
{
    absTime_ = time;
    if ((time - tMin_ - relTime_) > 40000 )
    {
        // refresh at 25Hz rate
        relTime_ = (int)(time - tMin_);
        timeCurValue->setText(QString::number(relTime_/1e6) + " - " + QString::number(absTime_));
        timeSlider->setValue(relTime_);
    }
}

int DbtPlyUserInterface::getTime()
{
    return timeSlider->value();
}

void DbtPlyUserInterface::resetTime()
{
    timeSlider->setValue(0);
}

QLayout * DbtPlyUserInterface::createMainLayout()
{
    QGroupBox * mainGroupBox = createControlGroupBox();
    QGroupBox * componentListGroupBox = createComponentListGroupBox();

    QGridLayout * generalLayout = new QGridLayout(this);
    generalLayout->addWidget(mainGroupBox, /* row = */ 0, /* column = */ 0, /* rowSpan = */ 1, /* columnSpan = */ 3);
    generalLayout->addWidget(componentListGroupBox, /* row = */ 1, /* column = */ 0, /* rowSpan = */ 1, /* columnSpan = */ 1);

    return generalLayout;
}

QGroupBox * DbtPlyUserInterface::createControlGroupBox()
{
    const int kButtonWidthInPixels = 20;
    const int kButtonHeightInPixels = 20;

    QGridLayout * mainLayout = new QGridLayout(this);

    butGroup = new QButtonGroup (this );
    playBut = new QPushButton ("|>", this);
    playBut->resize(kButtonWidthInPixels, kButtonHeightInPixels);
    butGroup->addButton(playBut,1);
    mainLayout->addWidget(playBut,0,0);

    pauseBut = new QPushButton ("||", this);
    pauseBut->resize(kButtonWidthInPixels, kButtonHeightInPixels);
    butGroup->addButton(pauseBut,2);
    mainLayout->addWidget(pauseBut,0,1);

    stopBut = new QPushButton ("O", this);
    stopBut->resize(kButtonWidthInPixels, kButtonHeightInPixels);
    butGroup->addButton(stopBut,3);
    mainLayout->addWidget(stopBut,0,2);

    speedUpBut = new QPushButton ("+", this);
    speedUpBut->resize(kButtonWidthInPixels, kButtonHeightInPixels);
    butGroup->addButton(speedUpBut,4);
    mainLayout->addWidget(speedUpBut,1,0);

    speedDownBut = new QPushButton ("-", this);
    speedDownBut->resize(kButtonWidthInPixels, kButtonHeightInPixels);
    butGroup->addButton(speedDownBut,5);
    mainLayout->addWidget(speedDownBut,1,1);

    rev = new QCheckBox(tr("Reverse"), this);
    mainLayout->addWidget(rev,1,2);

    mainLayout->columnMinimumWidth(1);

    lab = new QLabel (this);
    lab->setText(tr("Player State"));
    lab->adjustSize();
    mainLayout->addWidget(lab,2,0,1,3);

    timeMinTitle = new QLabel(this);
    timeMinTitle->setText(tr("Min time"));
    timeMinTitle->adjustSize();
    mainLayout->addWidget(timeMinTitle,3,0);

    timeMinValue = new QLabel(this);
    timeMinValue->setText("0");
    timeMinValue->adjustSize();
    timeMinValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    mainLayout->addWidget(timeMinValue,3,1,1,2);

    timeMaxTitle = new QLabel(this);
    timeMaxTitle->setText(tr("Max time"));
    timeMaxTitle->adjustSize();
    mainLayout->addWidget(timeMaxTitle,4,0);

    timeMaxValue = new QLabel(this);
    timeMaxValue->setText("0");
    timeMaxValue->adjustSize();
    timeMaxValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    mainLayout->addWidget(timeMaxValue,4,1,1,2);

    timeCurTitle = new QLabel(this);
    timeCurTitle->setText(tr("Current time"));
    timeCurTitle->adjustSize();
    mainLayout->addWidget(timeCurTitle,5,0);

    timeCurValue = new QLabel(this);
    timeCurValue->setText("0 - 0");
    timeCurValue->adjustSize();
    timeCurValue->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    mainLayout->addWidget(timeCurValue,5,1,1,2);

    timeSlider = new QSlider(Qt::Horizontal, this);
    timeSlider->setMinimum(0);
    timeSlider->adjustSize();
    mainLayout->addWidget(timeSlider, /* row = */ 6, /* column = */ 0, /* rowSpan = */ 1, /* columnSpan = */ 3);

    QGroupBox * mainGroupBox = new QGroupBox(tr("Control"));
    mainGroupBox->setLayout(mainLayout);

    return mainGroupBox;
}

QGroupBox * DbtPlyUserInterface::createComponentListGroupBox()
{
    QGroupBox * componentListGroupBox = new QGroupBox(tr("Component list"));

    QBoxLayout * componentListLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    componentListGroupBox->setLayout(componentListLayout);

    componentTableWidget = new QTableWidget(this);
    componentListLayout->addWidget(componentTableWidget);

    return componentListGroupBox;
}

void DbtPlyUserInterface::updateComponentList()
{
    ComponentManager * mgr = ComponentManager::getInstance();
    QStringList componentNames = mgr->getAllComponentsName();

    componentTableWidget->setRowCount(componentNames.size());
    componentTableWidget->setColumnCount(2);
    QStringList labels;
    labels << tr("Name") << tr("State") << tr("Details");
    componentTableWidget->setHorizontalHeaderLabels(labels);

    int idx = 0;
    for (QStringList::const_iterator it = componentNames.constBegin(), itend = componentNames.constEnd(); it != itend; ++it, ++idx) {
        QString componentName = *it;
        LOG_DEBUG("adding to component list: " << componentName);
        componentTableWidget->setItem(idx, 0, new QTableWidgetItem(componentName));

        ComponentBase * component = mgr->getComponent(componentName);
        if (component) {
            COMPONENT_STATE state = component->getState();

            QString stateString;
            switch (state) {
            case STOPPED:
                stateString = tr("Stopped");
                break;
            case NOT_MONITORED:
                stateString = tr("Not monitored");
                break;
            case MONITOR_OK:
                stateString = tr("Monitor OK");
                break;
            case MONITOR_NOK:
                stateString = tr("Monitor wrong");
                break;

            default:
                stateString = tr("UNKNOWN");
                break;
            }
            componentTableWidget->setItem(idx, 1, new QTableWidgetItem(stateString));

            // TODO: ADD component type and some detailed information (e.g. parameters)
            //QString componentInfo = component->getDetails();
            //componentTableWidget->setItem(idx, 2, new QTableWidgetItem(componentInfo));
        }
    }
}

void DbtPlyUserInterface::connectButtons()
{
    connect(playBut, SIGNAL(clicked()),
        mEngine, SLOT(playEvent()));
    connect(pauseBut, SIGNAL(clicked()),
        mEngine, SLOT(pauseEvent()));
    connect(stopBut, SIGNAL(clicked()),
        mEngine, SLOT(stopEvent()));
    connect(speedUpBut, SIGNAL(clicked()),
        mEngine, SLOT(speedUpEvent()));
    connect(speedDownBut, SIGNAL(clicked()),
        mEngine, SLOT(speedDownEvent()));
}

void DbtPlyUserInterface::connectDisplay()
{
    connect(mEngine, SIGNAL(displayStateSig(DbtPlyEngineState *, float)),
        this, SLOT(displayStateSlot(DbtPlyEngineState *, float)));

    connect (mEngine, SIGNAL(timeMinMax(road_time_t, road_time_t)),
        this, SLOT(displayMinMaxTime(road_time_t , road_time_t)));
    connect (mEngine, SIGNAL(curReplayTime(road_time_t)),
        this, SLOT(displayTime(road_time_t)));
    connect (rev, SIGNAL(toggled(bool)),
        mEngine, SLOT(changeDirection(bool)));
}

void DbtPlyUserInterface::connectSlider()
{
    connect (timeSlider, SIGNAL(sliderPressed()),
        mEngine, SLOT(pauseEvent()));
    connect (timeSlider, SIGNAL(sliderReleased()),
        mEngine, SLOT(playEvent()));
}

} // namespace pacpus
