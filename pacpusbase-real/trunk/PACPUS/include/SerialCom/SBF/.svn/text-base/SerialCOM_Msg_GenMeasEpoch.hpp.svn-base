/*!
\class SerialCOM_Msg_GenMeasEpoch
\brief Generic Measurement Epoch frame
\author C. Fouque
\version 1.0
\date Dec. 2008
\bug None
\warning None

This block contains code phase, carrier phase, Doppler observations, and measurement quality indicators for all tracked satellites for a particular epoch.

Compared to the (Short)MeasEpoch, the GenMeasEpoch is much more flexible in terms of size and contents. Its size is significantly smaller than that of the MeasEpoch block with the same contents. This is also the only block able to contain L2C data.

The reasoning behind the GenMeasEpoch block is as follows. For each tracked code (C/A, P1, P2, L2C), the same set of basic measurements are produced:
    o the pseudorange;
    o the carrier phase (not for the P1 code);
    o the Doppler (not for the P1 code);
    o the C/N0;
    o the lock-time.

Each sub-block of the GenMeasEpoch block contains one such measurement set. For instance, a CA-only channel will generate one sub-block, and a CA-P1-P2 channel will produce three sub-blocks: one for the CA measurements, one for P1 and one for P2.

To decrease the block size, all the measurements from a logical channel are referenced to the CA measurements from the main antenna (or from one of the auxiliary antennas if the main-antenna signal is blocked). For instance, the L2 Doppler is not much different from the L1 Doppler (scaled to the L2 frequency), such that the difference is encoded, instead of the entire value.

This is done by using two types of sub-blocks: the measurement set coming from the CA tracking on one of the antennas is encoded in a long type-1 sub-block, as entire values. The other measurement sets are encoded in shorter type-2 sub-blocks, containing only the differences with the CA measurements, whenever applicable. Every logical channel produces one type-1 sub-block, followed or not by a number of type-2 sub-blocks, depending on the available data.

Every type-1 sub-block contains a field called “N_Type2”, which gives the number of type-2 sub-blocks that are dependent on it. These dependent type-2 blocks immediately follow the type-1 block.

The first sub-block is always of type 1. The total number of type-1 sub-blocks in the GenMeasEpoch block is given by the field called “N”.

Decoding is done as follows:
     1. Decode the first sub-block. This is always a type-1 sub-block. Get the N_Type2 field from this sub-block.
     2. If N_Type2 is not 0, decode the N_Type2 following sub-blocks. These are type-2 sub-blocks.
     3. Go back to 1 till the N type-1 sub-blocks have been decoded.

Output rate: if enabled, this block is output at a rate defined by the SetMeasInterval and SetOutputDecimation commands. If there are no measurements available for an epoch (due to signal obstruction for example), the N field is set to 0.


 */

#pragma warning( once : 4290 )
#pragma warning( once : 4274 )

#ifndef _SerialCOM_Msg_GenMeasEpoch_Plrx_H
#define _SerialCOM_Msg_GenMeasEpoch_Plrx_H

#include <vector>
#include "SerialCOM_Msg.hpp"
#include "SerialCOM_Protocol.hpp"
#include "structure_septentrio.h"

namespace Plrx
{

   class SerialCOM_Msg_GenMeasEpoch : public SerialCOM_Msg , public SbfDataGenMeasEpoch
   {

      public :

         /*! \brief Constructor. Intitialise the member variables*/
         SerialCOM_Msg_GenMeasEpoch();

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

	//! return the size of the structure SbfDataGenMeasEpoch
         int getSizeOfStruct(){return sizeof(SbfDataGenMeasEpoch);};

	//! write the Data of the message in the DByte file
         virtual int writeDByte(road_time_t currentRoadtime, road_timerange_t currentTimerange);

         //! Display Data to stdout;
         virtual void stdoutDisplay();

   };

};


#endif