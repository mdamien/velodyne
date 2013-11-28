/*********************************************************************
//  created:    2012/08/01
//  filename:   DbtHeaderFix.cpp
//
//  author:     Gerald Dherbomez
//              Copyright Heudiasyc UMR UTC/CNRS 7253
// 
//  version:    $Id: DbtHeaderFix.cpp 1182 2012-07-05 16:42:32Z kurdejma $
//
//  purpose:    
*********************************************************************/

#include "DbtHeaderFix.h"

#include "kernel/ComponentFactory.h"
#include "kernel/DbiteFileTypes.h"
#include "kernel/Log.h"

#include <iostream>
#include <limits>

#include <QMessageBox>
#include <QString>

using namespace pacpus;
using namespace std;

DECLARE_STATIC_LOGGER("pacpus.base.DbtHeaderFix");

/// Component factory for DbtHeaderFix
static ComponentFactory<DbtHeaderFix> sFactory("DbtHeaderFix");

/// Constructor
DbtHeaderFix::DbtHeaderFix(QString name)
    : ComponentBase(name)
{
}

/// Destructor
DbtHeaderFix::~DbtHeaderFix()
{
}

/// Configures the component
ComponentBase::COMPONENT_CONFIGURATION DbtHeaderFix::configureComponent(XmlComponentConfig config)
{
    dbtFileName_ = config.getProperty("dbt");

    return ComponentBase::CONFIGURED_OK;
}

/// Starts the component
void DbtHeaderFix::startActivity()
{
  // create the DBT file
  dbtFileIn_.open(dbtFileName_.toStdString(), ReadMode);

  headerIn_.DataOffset = dbtFileIn_.getDataOffset();
  headerIn_.DataSize = dbtFileIn_.getRecordSize();
  headerIn_.FileSize = dbtFileIn_.getFileSize();
  headerIn_.NbRecords = dbtFileIn_.getRecordCount();
  headerIn_.TimeMin = dbtFileIn_.getTimeMin();
  headerIn_.TimeMax = dbtFileIn_.getTimeMax();
  headerIn_.Type = dbtFileIn_.getType();
  headerIn_.VersionNumber = dbtFileIn_.getVersion();
  
  QMessageBox msgBox;
  QString userMsg = "This is the actual header of the DBT file:\n" + QString::fromStdString((std::string)dbtFileIn_);
   msgBox.setText(userMsg);
   msgBox.setInformativeText("Press OK to continue.");
   msgBox.setStandardButtons(QMessageBox::Ok);
   msgBox.setDefaultButton(QMessageBox::Ok);
   int ret = msgBox.exec();
  
   if (!readDbiteFile(newTmin, newTmax, newNbRecords))
      LOG_ERROR("failed to read infos in Dbite file");
   dbtFileIn_.close(); 

   dbtFileOut_.open(dbtFileName_.toStdString(), WriteMode);

   userMsg = "The header of DBT File will be modified, this header:\n"
     + QString::fromStdString((std::string)dbtFileOut_) 
     + "\nwill be updated with these informations:\nTmin = " + QString::number(newTmin) 
     + "\nTmax = " + QString::number(newTmax) 
     + "\nNbRecord = " + QString::number(newNbRecords);
   msgBox.setText(userMsg);
   msgBox.setInformativeText("Do you want to save your changes?");
   msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
   msgBox.setDefaultButton(QMessageBox::Cancel);
   ret = msgBox.exec();

   switch (ret) {
   case QMessageBox::Save:
       // Save was clicked
        dbtFileOut_.setTimeMin(newTmin); 
   dbtFileOut_.setTimeMax(newTmax);
   dbtFileOut_.setRecordCount(newNbRecords);
     
       break;
   case QMessageBox::Discard:
       // Don't Save was clicked
       break;
   case QMessageBox::Cancel:
       // Cancel was clicked
       break;
   default:
       // should never be reached
       break;
 }
dbtFileOut_.close();

}

/// Stops the component 
void DbtHeaderFix::stopActivity()
{
}


bool DbtHeaderFix::readDbiteFile(road_time_t & tmin, road_time_t & tmax, int32_t & nbRecords)
{
  tmin = std::numeric_limits<road_time_t>::max();
  tmax = 0;
  nbRecords = 0;

  road_time_t time;
  road_timerange_t tr;

  for (;;) {
    if (!dbtFileIn_.readRecord(time, tr)) {
      break; 
    }
    if (time < tmin) tmin = time;
    if (time > tmax) tmax = time;
    nbRecords++;
  }

  return true;
}