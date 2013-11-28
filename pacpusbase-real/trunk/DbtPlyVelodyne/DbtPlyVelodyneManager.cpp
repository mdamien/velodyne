/*********************************************************************
// created:    2010/04/15 
//
// author:     Gerald Dherbomez
// 
// version:    $Id:  $
//
// purpose:    Dbite Player Velodyne Manager implementation
*********************************************************************/

#include "DbtPlyVelodyneManager.h"

#include "kernel/ComponentFactory.h"
#include "kernel/ComponentManager.h"
#include "kernel/Log.h"

#include <iostream>
#include <string>

namespace pacpus {

using namespace std;

DECLARE_STATIC_LOGGER("pacpus.base.DbtPlyVelodyneManager");

static ComponentFactory<DbtPlyVelodyneManager> sFactory("DbtPlyVelodyneManager");

static const string kVelodyneMemoryName = "VELODYNE";

/// Constructor.
DbtPlyVelodyneManager::DbtPlyVelodyneManager(QString name)
    : DbtPlyFileManager (name)
    , shMem_(NULL)
{
    LOG_TRACE("constructor");
}

/// Destructor.
DbtPlyVelodyneManager::~DbtPlyVelodyneManager()
{ 
    LOG_TRACE("destructor");
}

void DbtPlyVelodyneManager::processData(road_time_t /*time*/, road_timerange_t /*timeRange*/, void * buffer)
{
    if (NULL == buffer) {
        LOG_WARN("processing data: NULL buffer");
		return;
    }

    if (mVerbose) {
        VelodynePolarData & vpd = *(VelodynePolarData *)buffer;
        cout << "[VELODYNE]:\t"
             << "#range=" << vpd.range << "\n"
                ;
    }

    memcpy(&sphericData_, buffer, sizeof(VelodynePolarData) );
    shMem_->write(&sphericData_, sizeof(VelodynePolarData) );
}

void DbtPlyVelodyneManager::startActivity()
{
    LOG_TRACE("starting activity...");

    shMem_ = new ShMem(kVelodyneMemoryName.c_str(), sizeof(VelodynePolarData));
    if (!shMem_) {
        LOG_FATAL("cannot create Velodyne shared memory");
    }
	DbtPlyFileManager::startActivity();
    LOG_TRACE("started activity");
}

void DbtPlyVelodyneManager::stopActivity()
{
    LOG_TRACE("stopping activity...");

    DbtPlyFileManager::stopActivity();
    delete shMem_;  // it is ok to delete a NULL pointer
    shMem_ = NULL;
    LOG_TRACE("stopped activity");
}

void DbtPlyVelodyneManager::displayUI()
{
}

void DbtPlyVelodyneManager::tic()
{
    tic_ = road_time();
}

void DbtPlyVelodyneManager::toc(const char * text)
{
    LOG_INFO("duration = " << (int)(road_time() - tic_) << " : " << text);
}

} // namespace pacpus
