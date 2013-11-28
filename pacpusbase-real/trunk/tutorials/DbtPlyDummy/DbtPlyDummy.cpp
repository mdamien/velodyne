/*********************************************************************
//  created:    2011/04/14
//  filename:   DbtPlydummy.cpp
//
//  author:     Gerald Dherbomez
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
//  version:    $Id: DbtPlyDummy.cpp 1203 2012-08-02 11:58:15Z morasjul $
//
//  purpose:    
*********************************************************************/

#include "DbtPlyDummy.h"
#include "PacpusTools/ShMem.h"

namespace pacpus {

//////////////////////////////////////////////////////////////////////////
/// Constructs the component factory
static ComponentFactory<DbtPlyDummy> sFactory("DbtPlyDummy"); 

//////////////////////////////////////////////////////////////////////////
/// Constructor
DbtPlyDummy::DbtPlyDummy(QString name)
    : DbtPlyFileManager(name)
{
    shmem_ = new ShMem("DbtPlyDummy", sizeof(Dummy)); 
}

//////////////////////////////////////////////////////////////////////////
/// Destructor
DbtPlyDummy::~DbtPlyDummy()
{
    delete shmem_; 
}

//////////////////////////////////////////////////////////////////////////
/// Configures the component
ComponentBase::COMPONENT_CONFIGURATION DbtPlyDummy::configureComponent(XmlComponentConfig config)
{
    DbtPlyFileManager::configureComponent(config);
    return ComponentBase::CONFIGURED_OK;
}

//////////////////////////////////////////////////////////////////////////
/// Starts the component
void DbtPlyDummy::startActivity()
{
    DbtPlyFileManager::startActivity();
}

//////////////////////////////////////////////////////////////////////////
/// Stops the component 
void DbtPlyDummy::stopActivity()
{
    DbtPlyFileManager::stopActivity();
}

//////////////////////////////////////////////////////////////////////////
/// Processes the data
void DbtPlyDummy::processData(road_time_t t, road_timerange_t /*tr*/ , void * buf)
{
    // no data available
    if (buf == NULL)
        return; 

    data_.time = t;
    data_.dummy = *(int*)(buf);  

    printf("Dummy: new data sent to shared memory, data value=%d time=%lld\n", data_.dummy, data_.time);
    shmem_->write(&data_, sizeof(Dummy)); 

}

//////////////////////////////////////////////////////////////////////////
/// Displays user interface
void DbtPlyDummy::displayUI()
{
    printf (" No graphical interface implemented\n");
}

} // namespace pacpus
