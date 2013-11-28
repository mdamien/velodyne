#ifndef _ENU_dataset_H
#define _ENU_dataset_H

#include "structure_dataset.h"
#include "DataStructures.hpp"
#include "ModelObsExt.hpp"
#include "ECEF2NED.hpp"
#include <string>
#include <fstream>
#include <iostream>


class ENU_dataset : public structEpochDataENU
{
public:

	ENU_dataset();

	ENU_dataset(structEpochDataENU structCopy){(*this) = structCopy;};

	std::ostream& operator>>(std::ostream& outputStream);

	std::string provideHeader();

	ENU_dataset& operator<<(gpstk::gnssSatTypeValue gData);

	void setENUCenter(gpstk::Position ENUcenter);



protected:

	ECEF2NED NEDTransform;

}; 

#endif