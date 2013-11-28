#ifndef GPSTK_RINEXSBASSTREAM_HPP
#define GPSTK_RINEXSBASSTREAM_HPP


#include "FFTextStream.hpp"
#include "RinexSBASHeader.hpp"

namespace gpstk
{
   /** @addtogroup RinexSBAS */
   //@{

      /**
       * This class performs file i/o on a RINEX SBAS file.
       *
       * \sa rinex_SBAS_test.cpp and rinex_SBAS_read_write.cpp for examples.
       * \sa gpstk::RinexSBASHeader and gpstk::RinexSBASData classes.
       */
   class RinexSBASStream : public FFTextStream
   {
   public:
         /// Default constructor
      RinexSBASStream()
            : headerRead(false)
         {}
      
         /** Constructor 
          * Opens a file named \a fn using ios::openmode \a mode.
          */
      RinexSBASStream(const char* fn, std::ios::openmode mode=std::ios::in)
            : FFTextStream(fn, mode), headerRead(false) {}
      
         /// Destructor
      virtual ~RinexSBASStream() {}
      
         /// overrides open to reset the header
      virtual void open(const char* fn, std::ios::openmode mode)
         { 
            FFTextStream::open(fn, mode); 
            headerRead = false; 
            header = RinexSBASHeader();
         }

         /// RINEX SBAS header for this file.
      RinexSBASHeader header;
     
         /// Flag showing whether or not the header has been read.
      bool headerRead;
   };

   //@}

}

#endif
