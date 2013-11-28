/*********************************************************************
//  created:    2011/04/26
//  filename:   DummyComponent.cpp
//
//  author:     Gerald Dherbomez
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
//  version:    $Id: DummyComponent.cpp 1182 2012-07-05 16:42:32Z kurdejma $
//
//  purpose:    Tuto 3
*********************************************************************/

#include "DummyComponent.h"

#include "kernel/ComponentFactory.h"
#include "kernel/DbiteFileTypes.h"
#include "kernel/Log.h"

using namespace pacpus;
using namespace std;

DECLARE_STATIC_LOGGER("pacpus.base.DummyComponent");

/// Component factory for DummyComponent
static ComponentFactory<DummyComponent> sFactory("DummyComponent");

/// Constructor
DummyComponent::DummyComponent(QString name)
    : ComponentBase(name)
{
}

/// Destructor
DummyComponent::~DummyComponent()
{
}

/// Configures the component
ComponentBase::COMPONENT_CONFIGURATION DummyComponent::configureComponent(XmlComponentConfig config)
{
    period_ = config.getProperty("period").toInt();

    return ComponentBase::CONFIGURED_OK;
}

/// Starts the component
void DummyComponent::startActivity()
{
    // create the DBT file
    dbtFile_.open("dummy.dbt", WriteMode, FILE_DBT_UNKNOWN, sizeof(Dummy));
    data_.dummy = 0;

    // create and launch the timer
    connect(&timer_, SIGNAL(timeout()), this, SLOT(acquire()));
    timer_.start(period_);

    LOG_INFO("Start the timer with a period of " << period_ << " [msec]");
}

/// Stops the component 
void DummyComponent::stopActivity()
{
    timer_.disconnect();
    timer_.stop();

    dbtFile_.close(); 
}

/// Activity triggered on the timer
void DummyComponent::acquire()
{
    // acquire data
    data_.time = road_time();
    data_.dummy++;

    // record data in DBT file
    dbtFile_.writeRecord(data_.time, 0, (const char *) &data_, sizeof(Dummy)); 

    // Just inform the user with a point in the terminal
    LOG_DEBUG("record written");
}
