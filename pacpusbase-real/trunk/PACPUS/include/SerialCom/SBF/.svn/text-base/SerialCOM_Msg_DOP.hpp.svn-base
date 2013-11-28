/*! 
\class SerialCOM_Msg_DOP
\brief Dilution Of Precision block
\author Clement Fouque
\version 1.0
\date Dec. 2008
\bug None
\warning None

This block contains both Dilution of Precision (DOP) values and SBAS protection levels. The DOP values result from a trace of the unit position variance-covariance matrices:

In these equations, the matrix Q is the inverse of the unweighed design matrix used for the computation of the position. The term “unweighed” implies that the DOP factor only addresses the effect of the geometric factors on the quality of the position. 

The DOP values can be used to interpret the current constellation geometry. This is an important parameter for the quality of the position fix: the DOP parameter is the propagation factor of the pseudorange variance. For example, if an error of 5 metres is present in the pseudorange, it will propagate into the horizontal plane with a factor expressed by the HDOP. Hence a low DOP value indicates that the satellites used for the position fix result in a low multiplication of the systematic ranging errors. A threshold value of six (6) for the PDOP is generally considered as the maximum value allowed for an acceptable position computation. 

The horizontal and vertical protection levels (HPL and VPL) indicate the integrity of the computed
horizontal and vertical position components, provided SBAS information has been used (see the SetSBASCorrections command). The probability that the error in the position components exceeds the protection levels will be less than or equal to 10-7 per hour (see DO 229 [2]). This is guaranteed by the SBAS provider. Currently, EGNOS and WAAS do not advise to use the system for integrity-critical applications.

Note that the receiver assumes a beta Class 3 classification for the receiver noise component.


<b>Output rate:</b>  if enabled, this block is generated each time a new position fix is available, i.e. at a nominal rate specified by the SetPVTInterval and SetOutputDecimation commands.

 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_DOP_Plrx_H
#define _SerialCOM_Msg_DOP_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_DOP : public SerialCOM_Msg , public SbfDataXDOP
   {

      public : 

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_DOP();

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

	//! return the size of the structure SbfDataXDOP
         int getSizeOfStruct(){return sizeof(SbfDataXDOP);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);
        
         //! Display Data to stdout;
         virtual void stdoutDisplay();
	
   };

};

#endif
