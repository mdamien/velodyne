#ifndef __POLARXGPSTKSOLVER__
#define __POLARXGPSTKSOLVER__

#include <QtCore>
#include "structure/structure_septentrio.h"
#include "GPSTK_Nav.hpp"
#include "polarxObs.hpp"
// #include "basicGPSSolver.hpp"
#include "basicDopplerSolver.hpp"
#include "GPSEphemerisStore.hpp"
#include "ModelObsExt.hpp"

class polarxGPSTKsolver
{
   public:
      //! Constructeur de classe
         polarxGPSTKsolver() ;

         //! Destructeur de classe
         ~polarxGPSTKsolver() ;

         //! Ajoute les données de Navigation
         void addNavigationData( SbfDataGPSRaw * NavData );

         //! Ajoute les observables
         void addObservationData( SbfDataMeasEpoch * NavData );
         void addObservationData( SbfDataShortMeasEpoch * NavData );
         void addObservationData( SbfDataGenMeasEpoch * NavData );
//          template <typename T> void addObservationData( T ObsData ) ;

         //! calcul de la solution de Navigation:
         int computeNavigationSolution();

         // Accesseur
         void setElevationThd( int Th )   { pNav->setElevationThd(Th);  }
         void setCN0Thd( int Th )         { pNav->setCNOThd(Th);        }
         void EphDump()                   { pNav->getEphStore().dump(std::cout,1) ; }
         int NbMeas()                     { return nbMeas ; }
         int NbEph()                      { return nbEph ; }
         gpstk::Position getReceiverPosition() ;
         Vector<double> getReceiverVelocity();
         Vector<double> getReceiverClock();
         gpstk::gnssSatTypeValue getGnssSatValue() { return preparedRAW ; }

   private:

   //! NbEph : Nombre d'ephemerides stockée dans la structure de navigation
      int nbEph ;
      int nbMeas ;

      //! Solveur GPS CA seul
      basicGPSSolver * pBasicGPSSolver;

      //! Solveur GPS CA+Doppler
      basicDopplerSolver * pBasicDopplerSolver ;

      //! Conteneur des données d'observation:
      polarxObs * pObs;
      gpstk::gnssSatTypeValue preparedRAW ;

      //! Conteneur des données de Navigation
      GPSTK_Nav * pNav;

      //! Solution de navigation:
      Vector<double> curSolution;
      Vector<double> curDopplersol;


};

#endif
