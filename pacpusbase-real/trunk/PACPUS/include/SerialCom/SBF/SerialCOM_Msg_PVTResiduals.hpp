/*!
\class SerialCOM_Msg_PVTResiduals
\brief PVT residuals statitics for each SV
\author C. Fouque
\version 1.0
\date Dec. 2008
\bug none

\warning None

This block contains the residuals of the range and range-rate (Doppler) measurements with respect to the computed position. A residual is the difference between the measured and the expected range or range-rate between the receiver and the satellite, taking into account all modelled errors such as ionospheric delays, tropospheric delays, satellite clock etc. As such, the residuals can be seen as a measure of all the unmodelled errors in the range and the range-rate (multipath, receiver noise, etc).

This block can be used to monitor the quality of the position fix. Under normal circumstances, the residuals should lie within the a-priori variance of the range and range-rate.

<b>Output rate:</b> if enabled, this block is generated at a nominal rate specified by the SetPVTInterval and SetOutputDecimation commands.

 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_PVTResiduals_Plrx_H
#define _SerialCOM_Msg_PVTResiduals_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_PVTResiduals : public SerialCOM_Msg , public SbfDataPVTResiduals
   {

      public :

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_PVTResiduals();

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

	//! return the size of the structure SbfDataPVTResiduals
         int getSizeOfStruct(){return sizeof(SbfDataPVTResiduals);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);

         //! Display Data to stdout;
         virtual void stdoutDisplay();

   };

};


#endif