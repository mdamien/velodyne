#ifndef _SBAS_dataset_H
#define _SBAS_dataset_H

#include "structure_dataset.h"
#include "DataStructures.hpp"
#include "ModelObsExt.hpp"
#include "ECEF2NED.hpp"
#include <string>
#include <fstream>
#include <iostream>


class SBAS_dataset : public structEpochDataSBAS
{
public:

	SBAS_dataset();

	SBAS_dataset(structEpochDataSBAS structCopy){(*this) = structCopy;};

	std::ostream& operator>>(std::ostream& outputStream);

	std::string provideHeader();

	SBAS_dataset& operator<<(gpstk::gnssSatTypeValue gData);

	void setSBASCenter(gpstk::Position SBAScenter);



protected:

	ECEF2NED NEDTransform;

}; 

#endif