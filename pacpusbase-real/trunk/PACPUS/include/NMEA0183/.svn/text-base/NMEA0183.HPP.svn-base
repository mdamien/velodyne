#if ! defined( NMEA_0183_CLASS_HEADER )

#define NMEA_0183_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** Internet: sam_blackburn@pobox.com
**
** You can use it any way you like as long as you don't try to sell it.
**
** Copyright, 1996, Samuel R. Blackburn
**
** $Workfile: nmea0183.hpp $
** $Revision: 5 $
** $Modtime: 10/10/98 3:03p $
*/

/*
** General Purpose Classes
*/

#include "NMEA0183/Sentence.hpp"
#include "NMEA0183/Response.hpp"
#include "NMEA0183/LatLong.hpp"
#include "NMEA0183/LoranTD.hpp"
#include "NMEA0183/Manufact.hpp"
#include "NMEA0183/MList.hpp"
#include "NMEA0183/OmegaPar.hpp"
#include "NMEA0183/DeccaLOP.hpp"
#include "NMEA0183/RatioPls.hpp"
#include "NMEA0183/RadarDat.hpp"
#include "NMEA0183/SatDat.hpp"
#include "NMEA0183/FreqMode.hpp"
#include "NMEA0183/WayptLoc.hpp" // Sentence Not Recommended For New Designs

/*
** Response Classes
*/

#include "NMEA0183/AAM.hpp"
#include "NMEA0183/ALM.hpp"
#include "NMEA0183/APB.hpp"
#include "NMEA0183/ASD.hpp"
#include "NMEA0183/BEC.hpp"
#include "NMEA0183/BOD.hpp"
#include "NMEA0183/BWC.hpp"
#include "NMEA0183/BWR.hpp"
#include "NMEA0183/BWW.hpp"
#include "NMEA0183/DBT.hpp"
#include "NMEA0183/DCN.hpp"
#include "NMEA0183/DPT.hpp"
#include "NMEA0183/FSI.hpp"
#include "NMEA0183/GDA.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/GDF.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/GDP.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/GGA.hpp"
#include "NMEA0183/GLA.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/GLC.hpp"
#include "NMEA0183/GLF.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/GLL.hpp"
#include "NMEA0183/GLP.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/GOA.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/GOF.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/GOP.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/GSA.hpp"
#include "NMEA0183/GST.hpp" // ajouté par moi
#include "NMEA0183/GSV.hpp"
#include "NMEA0183/GTD.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/GXA.hpp"
#include "NMEA0183/GXF.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/GXP.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/HCC.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/HDG.hpp"
#include "NMEA0183/HDM.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/HDT.hpp"
#include "NMEA0183/HSC.hpp"
#include "NMEA0183/IMA.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/LCD.hpp"
#include "NMEA0183/MHU.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/MTA.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/MTW.hpp"
#include "NMEA0183/MWV.hpp"
#include "NMEA0183/OLN.hpp"
#include "NMEA0183/OSD.hpp"
#include "NMEA0183/P.hpp"
#include "NMEA0183/RMA.hpp"
#include "NMEA0183/RMB.hpp"
#include "NMEA0183/RMC.hpp"
#include "NMEA0183/ROT.hpp"
#include "NMEA0183/RPM.hpp"
#include "NMEA0183/RSA.hpp"
#include "NMEA0183/RSD.hpp"
#include "NMEA0183/RTE.hpp"
#include "NMEA0183/SFI.hpp"
#include "NMEA0183/STN.hpp"
#include "NMEA0183/TEP.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/TRF.hpp"
#include "NMEA0183/TTM.hpp"
#include "NMEA0183/VBW.hpp"
#include "NMEA0183/VDR.hpp"
#include "NMEA0183/VHW.hpp"
#include "NMEA0183/VLW.hpp"
#include "NMEA0183/VPW.hpp"
#include "NMEA0183/VTG.hpp"
#include "NMEA0183/VWE.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/WCV.hpp"
#include "NMEA0183/WDC.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/WDR.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/WNC.hpp"
#include "NMEA0183/WPL.hpp"
#include "NMEA0183/XDR.hpp"
#include "NMEA0183/XTE.hpp"
#include "NMEA0183/XTR.hpp"
#include "NMEA0183/ZDA.hpp"
#include "NMEA0183/ZFI.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/ZFO.hpp" 
#include "NMEA0183/ZLZ.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/ZPI.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/ZTA.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/ZTE.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/ZTG.hpp"
#include "NMEA0183/ZTI.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/ZWP.hpp" // Sentence Not Recommended For New Designs
#include "NMEA0183/ZZU.hpp" // Sentence Not Recommended For New Designs


class NMEA0183
{
   private:

      SENTENCE m_Sentence;

      void m_Initialize( void );

   protected:

      QVector<RESPONSE*> m_ResponseTable;

      void m_SetContainerPointers( void );
      void m_SortResponseTable( void );

   public:

      NMEA0183();
      virtual ~NMEA0183();

      /*
      ** NMEA 0183 Sentences we understand
      */

      AAM Aam;
      ALM Alm;
      APB Apb;
      ASD Asd;
      BEC Bec;
      BOD Bod;
      BWC Bwc;
      BWR Bwr;
      BWW Bww;
      DBT Dbt;
      DCN Dcn;
      DPT Dpt;
      FSI Fsi;
      GDA Gda; // Sentence Not Recommended For New Designs
      GDF Gdf; // Sentence Not Recommended For New Designs
      GDP Gdp; // Sentence Not Recommended For New Designs
      GGA Gga;
      GLA Gla; // Sentence Not Recommended For New Designs
      GLC Glc;
      GLF Glf; // Sentence Not Recommended For New Designs
      GLL Gll;
      GLP Glp; // Sentence Not Recommended For New Designs
      GOA Goa; // Sentence Not Recommended For New Designs
      GOF Gof; // Sentence Not Recommended For New Designs
      GOP Gop; // Sentence Not Recommended For New Designs
      GSA Gsa;
	  GST Gst; // ajouté par moi
      GSV Gsv;
      GTD Gtd; // Sentence Not Recommended For New Designs
      GXA Gxa;
      GXF Gxf; // Sentence Not Recommended For New Designs
      GXP Gxp; // Sentence Not Recommended For New Designs
      HCC Hcc; // Sentence Not Recommended For New Designs
      HDG Hdg;
      HDM Hdm; // Sentence Not Recommended For New Designs
      HDT Hdt;
      HSC Hsc;
      IMA Ima; // Sentence Not Recommended For New Designs
      LCD Lcd;
      MHU Mhu; // Sentence Not Recommended For New Designs
      MTA Mta; // Sentence Not Recommended For New Designs
      MTW Mtw;
      MWV Mwv;
      OLN Oln;
      OSD Osd;
      P   Proprietary;
      RMA Rma;
      RMB Rmb;
      RMC Rmc;
      ROT Rot;
      RPM Rpm;
      RSA Rsa;
      RSD Rsd;
      RTE Rte;
      SFI Sfi;
	  STN Stn;
      TEP Tep; // Sentence Not Recommended For New Designs
      TRF Trf;
      TTM Ttm;
      VBW Vbw;
      VDR Vdr;
      VHW Vhw;
      VLW Vlw;
      VPW Vpw;
      VTG Vtg;
      VWE Vwe; // Sentence Not Recommended For New Designs
      WCV Wcv;
      WDC Wdc; // Sentence Not Recommended For New Designs
      WDR Wdr; // Sentence Not Recommended For New Designs
      WNC Wnc;
      WPL Wpl;
	  XDR Xdr;
	  XTE Xte;
      XTR Xtr;
      ZDA Zda;
      ZFI Zfi; // Sentence Not Recommended For New Designs
      ZFO Zfo;
      ZLZ Zlz; // Sentence Not Recommended For New Designs
      ZPI Zpi; // Sentence Not Recommended For New Designs
      ZTA Zta; // Sentence Not Recommended For New Designs
      ZTE Zte; // Sentence Not Recommended For New Designs
      ZTI Zti; // Sentence Not Recommended For New Designs
      ZTG Ztg;
      ZWP Zwp; // Sentence Not Recommended For New Designs
      ZZU Zzu; // Sentence Not Recommended For New Designs


      QString ErrorMessage; // Filled when Parse returns FALSE
      QString LastSentenceIDParsed; // ID of the lst sentence successfully parsed
      QString LastSentenceIDReceived; // ID of the last sentence received, may not have parsed successfully
      QString PlainText; // A human-readable string of text that explains what just happened

      QString TalkerID;
      QString ExpandedTalkerID;

      virtual BOOL IsGood( void ) const;
      virtual BOOL Parse( void );
      //virtual void Serialize( CArchive& archive );

      NMEA0183& operator << ( const char *source );
      NMEA0183& operator >> ( QString& destination );
};

#endif // NMEA_0183_CLASS_HEADER
