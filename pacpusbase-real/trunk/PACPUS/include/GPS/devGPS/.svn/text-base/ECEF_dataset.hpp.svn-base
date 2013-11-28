#ifndef _ECEF_dataset_H
#define _ECEF_dataset_H

#include "structure_dataset.h"
#include "DataStructures.hpp"
#include "ModelObsExt.hpp"
#include "ECEF2NED.hpp"
#include <string>
#include <fstream>
#include <iostream>


class ECEF_dataset : public structEpochDataECEF
{
public:

	ECEF_dataset();

	ECEF_dataset(structEpochDataECEF structCopy){(*this) = structCopy;};

	std::ostream& operator>>(std::ostream& outputStream);

	std::string provideHeader();

	ECEF_dataset& operator<<(gpstk::gnssSatTypeValue gData);

}; 

#endif