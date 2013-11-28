#ifndef GPSTK_RINEXSBASBASE_HPP
#define GPSTK_RINEXSBASBASE_HPP


#include "FFData.hpp"

namespace gpstk
{
   /** @defgroup RinexSBAS RINEX SBAS files */
   //@{

  /**
   * This class serves no purpose other than to make readable diagrams.
   */
   class RinexSBASBase : public FFData
   {
   public:
         /// in deference to our coding standards, this is declared virtual
      virtual ~RinexSBASBase() {}
   };

   //@}

}

#endif
