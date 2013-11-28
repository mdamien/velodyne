/*********************************************************************
//  created:    2012/08/01
//  filename:   DbtHeaderFix.h
//
//  author:     Gerald Dherbomez
//              Copyright Heudiasyc UMR UTC/CNRS 7253
// 
//  version:    $Id: $
//
//  purpose:    
*********************************************************************/

#ifndef DbtHeaderFix_H
#define DbtHeaderFix_H

#include <qtimer.h>
#include <QString>

#include "kernel/ComponentBase.h"
#include "kernel/DbiteFile.h"
#include "kernel/road_time.h"

class DbtHeaderFix
        : public QObject
        , public ComponentBase
{
    Q_OBJECT

public:
    DbtHeaderFix(QString name);
    ~DbtHeaderFix();

protected:
    virtual ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);
    virtual void startActivity();
    virtual void stopActivity();

public Q_SLOTS:
  

private:
  bool readDbiteFile(road_time_t & tmin, road_time_t & tmax, int32_t & nbRecords);

  pacpus::DbiteFile dbtFileIn_;
  pacpus::DbiteFile dbtFileOut_;

  hdfile_header_t headerIn_; 

  QString dbtFileName_;

  road_time_t newTmin, newTmax; 
  int32_t newNbRecords;

};

#endif // DbtHeaderFix_H
