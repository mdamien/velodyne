/*! 
\class SerialCOM_Msg_PosCovCartesian
\brief Position Covariance matrix in Cartesian frame
\author C. Fouque
\version 1.0
\date Dec. 2008
\bug None
\warning None

This block contains the elements of the symmetric variance-covariance matrix of the positi
expressed relative to the Cartesian axes of the WGS-84 ellipsoid:

This variance-covariance matrix contains an indication of the accuracy of the estimated parameters (see diagonal elements) and the correlation between these estimates (see off-diagonal elements). The position variance results from the propagation of all pseudorange variances using the observation geometry. The PolaRx implements a stochastic error model for individual pseudorange measurements which is based on the following input parameters:
   • C/N0;
   • satellite elevation;
   • pseudorange type;
   • URA of the broadcast ephemeris;
   • ionospheric model.

In special cases all or some components of the variance-covariance matrix are undefined and set their Do-Not-Use value:
    • 2D position fix: all components of the variance-covariance matrix are undefined and set their Do-Not-Use value.
    • Base mode: all components, except the clock bias variance, of the variance-covariance matrix are undefined and set to their Do-Not-Use value.
    • RTK mode (float or fix): all covariances between the position and clock bias are undefined and set to their Do-Not-Use value.

Please use the following equation to compute the correlation factor between, say, x and y estimates:
                                               rxy = sxy / sqrt( sx^2 + sy^2 )

This factor ranges from zero (0), which indicates no correlation, to one (1), which indicates maximal
correlation.

<b>Output rate:</b> if enabled, this block is generated together with the corresponding PVTCartesian
block.

 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_PosCovCartesian_Plrx_H
#define _SerialCOM_Msg_PosCovCartesian_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_PosCovCartesian : public SerialCOM_Msg , public SbfDataPosCovCartesian
   {

      public : 

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_PosCovCartesian();

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

	//! return the size of the structure SbfDataPosCovCartesian
         int getSizeOfStruct(){return sizeof(SbfDataPosCovCartesian);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);
        
         //! Display Data to stdout;
         virtual void stdoutDisplay();
	
   };

};


#endif