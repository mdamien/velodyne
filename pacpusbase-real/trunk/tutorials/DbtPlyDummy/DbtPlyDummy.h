/*********************************************************************
//  created:    2011/04/14
//  filename:   DbtPlyDummy.h
//
//  author:     Gerald Dherbomez
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
//  version:    $Id: $
//
//  purpose:    
*********************************************************************/

#ifndef DBTPLYDUMMY_H
#define DBTPLYDUMMY_H

#include "DbitePlayer/DbtPlyFileManager.h"

// Export macro for DbtPlyDummy DLL for Windows only
#ifdef WIN32
#   ifdef DBTPLYDUMMY_EXPORTS
        // make DLL
#       define DBTPLYDUMMY_API __declspec(dllexport)
#   else
        // use DLL
#       define DBTPLYDUMMY_API __declspec(dllimport)
#   endif
#else
    // On other platforms, simply ignore this 
#   define DBTPLYDUMMY_API 
#endif

namespace pacpus {
    
class ShMem;

struct DBTPLYDUMMY_API Dummy {
    road_time_t time; 
    int dummy; 
}; 

class DBTPLYDUMMY_API DbtPlyDummy
        : public DbtPlyFileManager
{
public:
    DbtPlyDummy(QString name); 
    ~DbtPlyDummy ();

protected:
    void processData(road_time_t t, road_timerange_t tr , void * buf);
    void displayUI();

    virtual ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);
    virtual void startActivity();
    virtual void stopActivity();

private:
    ShMem * shmem_; 
    Dummy data_;
};

} // namespace pacpus

#endif // DBTPLYDUMMY_H
