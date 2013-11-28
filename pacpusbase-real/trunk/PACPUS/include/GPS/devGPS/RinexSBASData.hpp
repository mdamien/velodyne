#ifndef RINEXSBASDATA_HPP
#define RINEXSBASDATA_HPP

#include <list>

#include "StringUtils.hpp"
#include "DayTime.hpp"
#include "FFStream.hpp"
#include "RinexSBASBase.hpp"
#include "RinexSBASStream.hpp"

namespace gpstk
{
   /** @addtogroup RinexSBAS */
   //@{

      /**
       * This class models a RINEX SBAS record.
       *
       * \sa rinex_SBAS_test.cpp and rinex_SBAS_read_write.cpp for examples.
       * \sa gpstk::RinexSBASHeader and gpstk::RinexSBASStream classes.
       */
   class RinexSBASData : public RinexSBASBase
   {
   public:
         /**
          * Constructor
          * @warning CHECK THE PRNID TO SEE IF THIS DATA IS
          *  VALID BEFORE USING!!
          */

         /// Initializes the SBAS data with an EngEphemeris
      RinexSBASData(unsigned char *buffer, int *svid, int *MsgType, gpstk::DayTime *time);

         /// destructor
      virtual ~RinexSBASData() {}

         // The next four lines is our common interface
         /// RinexSBASData is "data" so this function always returns true.
      virtual bool isData(void) const {return true;}

         /**
          * A debug output function.
          * Prints the PRN id and the IODC for this record.
          */
      virtual void dump(std::ostream& s) const;


         /** @name Epochdata
          */
         //@{


   private:
         /// Parses string \a currentLine to obtain PRN id and epoch.
      void getPRNEpoch(const std::string& currentLine)
         throw(gpstk::StringUtils::StringException, FFStreamError);

         /// Reads line 1 of the SBAS Data record
      void getSBASFirtPart(const std::string& currentLine)
         throw(gpstk::StringUtils::StringException, FFStreamError);

         /// Reads line 2 of the SBAS Data record
      void getSBASSecondPart(const std::string& currentLine)
         throw(gpstk::StringUtils::StringException, FFStreamError);



         /// generates a line to be output to a file for the PRN/epoch line
      std::string putPRNEpoch(void) const
         throw(gpstk::StringUtils::StringException);

         /// Writes line 7 of the SBAS Data record
      std::string putSBASFirstPart(void) const
         throw(gpstk::StringUtils::StringException);

         /// Writes line 7 of the SBAS Data record
      std::string putSBASSecondPart(void) const
         throw(gpstk::StringUtils::StringException);

   protected:
         /// Outputs the record to the FFStream \a s.
      virtual void reallyPutRecord(FFStream& s) const
         throw(std::exception, FFStreamError,
               gpstk::StringUtils::StringException);

         /**
          * This function retrieves a RINEX SBAS record from the given FFStream.
          * If an error is encountered in reading from the stream, the stream
          * is returned to its original position and its fail-bit is set.
          * @throws StringException when a StringUtils function fails
          * @throws FFStreamError when exceptions(failbit) is set and
          *  a read or formatting error occurs.  This also resets the
          *  stream to its pre-read position.
          */
      virtual void reallyGetRecord(FFStream& s)
         throw(std::exception, FFStreamError,
               gpstk::StringUtils::StringException);

	  /* !\brief Personnal version of gpstk::stringutils::x2int becuase there is a bug wiht
		the convertion of 0x00*/
	  unsigned int x2int(const std::string& s) throw(gpstk::StringUtils::StringException);


		unsigned char *dataBlock; //taille 32
		int *svid;
		int *MsgType;


		  DayTime *time;        ///< Time according to the record.
		  long HOWtime;        ///< Time of subframe 1-3 (sec of week)
		  short weeknum;       ///< GPS full week number that corresponds
                           ///< to the HOWtime of SF1

   };  // class RinexSBASData

   //@}

} // namespace


#endif
