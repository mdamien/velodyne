// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license
/// @author  Gerald Dherbomez <firstname.surname@utc.fr>
/// @version $Id: ComponentBase.cpp 91 2013-05-19 10:32:48Z gdherbom $

#include <Pacpus/kernel/ComponentBase.h>
#include <Pacpus/kernel/ComponentManager.h>
#include <Pacpus/kernel/Log.h>

using namespace pacpus;

DECLARE_STATIC_LOGGER("pacpus.core.ComponentBase");

ComponentBase::ComponentBase(const QString& name)
  : componentName(name)
  , recording(true)
  , THREAD_ALIVE(true)
  , mIsActive(false)
  , mgr(NULL)
  , componentState_(NOT_MONITORED)
{
    LOG_TRACE("constructor");
    // Get a pointer on the instance of ComponentManager.
    mgr = ComponentManager::getInstance();
    LOG_INFO("component " << componentName << " was created");
}

ComponentBase::~ComponentBase()
{  
    LOG_TRACE("destructor");
}

int ComponentBase::startComponent()
{
    if (mIsActive)
      return false;
      
    mIsActive = true;
    startActivity();
    
    return true;
}

int ComponentBase::stopComponent()
{
    if (!mIsActive)
      return false;

    mIsActive = false;
    stopActivity();
    
    return true;
}

void ComponentBase::setState(const COMPONENT_STATE state)
{
    componentState_ = state;
}

// FIXME: this should be const.
ComponentBase::COMPONENT_STATE ComponentBase::getState()
{
    COMPONENT_STATE state = componentState_;
    if (ComponentBase::NOT_MONITORED != componentState_) {
        componentState_ = ComponentBase::MONITOR_NOK;
    }
    return state;
}

bool ComponentBase::isConfigured() const
{
    return configuration_ == CONFIGURED_OK;
}
