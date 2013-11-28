/*********************************************************************
//  created:    2008/07/09 - 10:12
//  filename:   DataExport2Txt.h
//
//  author:     Gerald Dherbomez
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
//  version:    $Id: $
//
//  purpose:    Export dbt structure into ASCII files (CSV format)
*********************************************************************/


#include "AlascaDataModule.h"


class DataExport2Txt : public AlascaDataModule
{
public:
  DataExport2Txt(QString name);
  ~DataExport2Txt();
  void compute(GlobalAlascaData data);
  void setImage(QImage*){};
  void setWheelSpeed(TimestampedStructWheelSpeed);
  void setRadar(const DONNEE_RADAR &data_radar);


protected:
  virtual void startActivity(){};
  virtual void stopActivity(){};
  virtual ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config) { return ComponentBase::CONFIGURED_OK; };

private:
  // A pointer on the 3D viewer component
  DONNEE_RADAR dataRadar_;
  StructWheelSpeed dataSpeed_;
  FILE *speedTxtFile;
};