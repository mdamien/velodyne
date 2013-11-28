#ifndef _PRNMask_H
#define _PRNMask_H

#include "SatID.hpp"
#include "structure/structureSBAS.h"
#include "Exception.hpp"
#include <map>

namespace SBAS
{
	class PRNMask
	{
	public:

		PRNMask();

		void addMT1(const SBAS::structPRNMaskAssignement* data);

		inline short getIODP() const
		{
			return IODP;};

		gpstk::SatID getSatIDFromMask(unsigned char satMask) /*throw(gpstk::InvalidRequest)*/;

	protected:

		short IODP;

		std::map<unsigned char,gpstk::SatID> mapPRNMask;
	};

}
#endif
