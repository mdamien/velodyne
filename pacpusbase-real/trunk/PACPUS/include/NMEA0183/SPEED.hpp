#if ! defined( SPEED_CLASS_HEADER )

#define SPEED_CLASS_HEADER

#include "qstring.h"
#include "NMEA0183_slim.H"
#include "LATLONG.HPP"
#include "SENTENCE.HPP"
#include "RESPONSE.HPP"

class SPEED : public RESPONSE
{
   public:

      SPEED();
      virtual ~SPEED();

      /*
      ** Data
      */

      double east;
	  double north;
	  double up;

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

      virtual const SPEED& operator = ( const SPEED& source );
};

#endif // SPEED_CLASS_HEADER
