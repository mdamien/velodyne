#ifndef GPSTK_RINEXSBASHEADER_HPP
#define GPSTK_RINEXSBASHEADER_HPP


#include "FFStream.hpp"
#include "RinexSBASBase.hpp"

namespace gpstk
{
   /** @addtogroup RinexSBAS */
   //@{

      /**
       * This class models the RINEX SBAS header for a RINEX SBAS file.
       *
       * \sa rinex_SBAS_test.cpp and rinex_SBAS_read_write.cpp for examples.
       * \sa gpstk::RinexSBASData and gpstk::RinexSBASStream classes.
       */
   class RinexSBASHeader : public RinexSBASBase
   {
   public:
         /// Constructor
      RinexSBASHeader(void) : valid(0), version(2.1) {}
      
         /// Destructor
      virtual ~RinexSBASHeader() {}

         /// RinexSBASHeader is a "header" so this function always returns true.
      virtual bool isHeader(void) const {return true;}

         /// This function dumps the contents of the header.
      virtual void dump(std::ostream& s) const;

         /// Tell me, Am I valid?
      unsigned long valid;

         /// These are validity bits used in checking the RINEX SBAS header.
      enum validBits
      {
         versionValid = 0x01,        ///< Set if the RINEX version is valid.
         runByValid = 0x02,          ///< Set if the Run-by value is valid.
         commentValid = 0x04,        ///< Set if the comments are valid. Very subjective
         ionAlphaValid = 0x08,       ///< Set if the Ion Alpha value is valid.
         ionBetaValid = 0x010,       ///< Set if the Ion Beta value is valid.
         deltaUTCValid = 0x020,      ///< Set if the Delta UTC value is valid.
         leapSecondsValid = 0x040,   ///< Set if the Leap Seconds value is valid.
         endValid = 0x080000000,           ///< Set if the end value is valid.

            /// This bitset checks that all required header items are available
            /// for a Rinex 2.0 version file
         allValid20 = 0x080000003,
            /// This bitset checks that all required header items are available
            /// for a Rinex 2.1 version file
         allValid21 = 0x080000003,
            /// This bitset checks that all required header items are available
            /// for a Rinex 2.11 version file
         allValid211 = 0x080000003
      };

         /** @name HeaderValues
          */
         //@{
      double version;           ///< RINEX Version

      std::string fileType;            
      std::string fileProgram;
      std::string fileAgency;
      std::string date;
      std::vector<std::string> commentList;
      long UTCRefTime;
      long UTCRefWeek;
      long leapSeconds;
         //@}

         /** @name FormattingStd::Strings
          */
         //@{
      static const std::string versionString; //"RINEX VERSION / TYPE"
      static const std::string runByString; //"PGM / RUN BY / DATE"
      static const std::string commentString; // "COMMENT"
      static const std::string endOfHeader;  //"END OF HEADER"
      static const std::string rcvString; // "COMMENT"
         //@}

   protected:
         /// Writes a correctly formatted record from this data to stream \a s.
      virtual void reallyPutRecord(FFStream& s) const
         throw(std::exception, FFStreamError, 
               gpstk::StringUtils::StringException);

         /**
          * This function reads the RINEX SBAS header from the given FFStream.
          * If an error is encountered in reading from the stream, the stream
          * is reset to its original position and its fail-bit is set.
          * @throws StringException when a StringUtils function fails
          * @throws FFStreamError when exceptions(failbit) is set and
          *  a read or formatting error occurs.  This also resets the
          *  stream to its pre-read position.
          */
      virtual void reallyGetRecord(FFStream& s) 
         throw(std::exception, FFStreamError, 
               gpstk::StringUtils::StringException);
   }; // class RinexSBASHeader

   //@}

} // namespace

#endif
