/*!
\class SerialCOM_Msg_RAIMStatistics
\brief RAIM Statistics computed by the receiver
\author C. Fouque
\version 1.0
\date Dec. 2008
\bug none
\warning None

The output of the RAIM algorithm contains integrity information, which can be used in user applications. First, the RAIM algorithm generates its own integrity flag, which can be used by a user as a receiver-level indication of positional integrity. If the internal integrity test is successful, a user has an opportunity to introduce a more stringent application-specific integrity criterion by using External Reliability Levels (XERL). The positional solution is deemed as passed an application-level integrity test if the XERLs are within user-defined (and application-dependent) alarm limits. This comparison (and the definition of alarm limits as well) takes place in a user application and is outside  of the receiver scope.

Output rate: if enabled, this block is output at a rate defined by the SetPVTInterval and
SetOutputDecimation commands. If there are no satellites available for an epoch (due to signal
obstruction for example), the N field is set to 0.


 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_RAIMStatistics_Plrx_H
#define _SerialCOM_Msg_RAIMStatistics_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_RAIMStatistics : public SerialCOM_Msg , public SbfDataRAIMStatistics
   {

      public :

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_RAIMStatistics();

         /*! \brief Copy constructor*/
	//SerialCOM_Msg_RXM_SBAS (const SerialCOM_Msg_RXM_SBAS &source);

	/*! \brief reset internal variables of the message after an error or the end of a
         *  message */
         /*! For more information see SerialCOM_Msg::reset*/
         void reset();

	/*! \brief Read the core of the message to check if the object is able to handle this
         *  message*/
         /*! For more information see SerialCOM_Msg::identify*/
         int identify(vector<unsigned char> *pbuffer);

         /*! \brief extracts the data of the message contained in the buffer vector*/
         /*! For more information see SerialCOM_Msg::formatData*/
         int formatData(vector<unsigned char> *pbuffer);

         int fromStructFile(void *buf);

	//! return the size of the structure SbfDataRAIMStatistics
         int getSizeOfStruct(){return sizeof(SbfDataRAIMStatistics);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);

         //! Display Data to stdout;
         virtual void stdoutDisplay();

   };

};


#endif