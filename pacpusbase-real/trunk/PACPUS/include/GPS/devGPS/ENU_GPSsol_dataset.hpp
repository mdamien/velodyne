#ifndef _ENU_GPSsol_dataset_H
#define _ENU_GPSsol_dataset_H

#include "structure_dataset.h"
#include "DataStructures.hpp"
#include "ModelObsExt.hpp"
#include "ECEF2NED.hpp"
#include <string>
#include <fstream>
#include <iostream>


class ENU_GPSsol_dataset : public structEpochGPSsolENU
{
public:

	ENU_GPSsol_dataset();

	ENU_GPSsol_dataset(structEpochGPSsolENU structCopy){(*this) = structCopy;};

	std::ostream& operator>>(std::ostream& outputStream);

	std::string provideHeader();

	void storeSolutionECEF(gpstk::Vector<double> &sol, double sow);

	void setENUCenter(gpstk::Position ENUcenter);



protected:

	ECEF2NED NEDTransform;

}; 

#endif