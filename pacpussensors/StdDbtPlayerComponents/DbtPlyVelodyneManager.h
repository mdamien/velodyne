/*********************************************************************
// created:    2010/04/15
//
// author:     Gerald Dherbomez
// 
// version:    $Id: $
//
// purpose:    Dbite Player Velodyne Manager definition
*********************************************************************/

#ifndef DBTPLYVELODYNEMANAGER_H
#define DBTPLYVELODYNEMANAGER_H

#include <qobject.h>

#include "DbitePlayer/DbtPlyFileManager.h"
#include "PacpusTools/ShMem.h"
#include "../VelodyneComponent/structure_velodyne.h"

// Export macro for DbtPlyVelodyne DLL for Windows only
#ifdef WIN32
#   ifdef DBTPLYVELODYNE_EXPORTS
        // make DLL
#       define DBTPLYVELODYNE_API __declspec(dllexport)
#   else
        // use DLL
#       define DBTPLYVELODYNE_API __declspec(dllimport)
#   endif
#else
    // On other platforms, simply ignore this 
#   define DBTPLYVELODYNE_API 
#endif

namespace pacpus {

class DBTPLYVELODYNE_API DbtPlyVelodyneManager
        : public DbtPlyFileManager
{
    Q_OBJECT

public:
    DbtPlyVelodyneManager(QString name);
    virtual ~DbtPlyVelodyneManager();

    void displayUI();

protected:
    void processData(road_time_t, road_timerange_t, void * dataBuffer);
    virtual void startActivity();
    virtual void stopActivity();

private:
    ShMem * shMem_;

    VelodynePolarData sphericData_;

    road_time_t tic_;
    void tic();
    void toc(const char * text);
};

} // namespace pacpus

#endif // DBTPLYVELODYNEMANAGER_H
