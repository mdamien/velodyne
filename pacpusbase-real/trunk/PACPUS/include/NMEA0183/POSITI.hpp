#if ! defined( POSITI_CLASS_HEADER )

#define POSITI_CLASS_HEADER

#include "qstring.h"
#include "NMEA0183_slim.H"
#include "LATLONG.HPP"
#include "SENTENCE.HPP"
#include "RESPONSE.HPP"

class POSITI : public RESPONSE
{
   public:

      POSITI();
      virtual ~POSITI();

      /*
      ** Data
      */
      double latitude;
      double longitude;
      double altitude;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual QString PlainEnglish( void ) const;
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const POSITI& operator = ( const POSITI& source );
};

#endif // POSITI_CLASS_HEADER