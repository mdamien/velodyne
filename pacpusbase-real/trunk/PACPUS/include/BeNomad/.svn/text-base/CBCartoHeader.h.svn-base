/*==========================================================  (-*- C++ -*-)
 *
 * @file CBCartoHeader.h
 * 
 * @version  $Id: CBCartoHeader.h,v 1.18 2006/02/15 16:11:10 dlabrousse Exp $ 
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2006 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBCARTOHEADER_H__
#define __CBCARTOHEADER_H__

/*!
 * @file CBCartoHeader.h
 * CBCartoHeader class definition.
 */

#include "CBSVSHeader.h"

#include "BCartoConst.h"


/**
 * @enum EB_SVS_TYPE
 * This enum defines the type of Cartographic SVS file.  
 */
enum EB_SVS_TYPE {
  EB_SVS_UNDEFINED_CLASSIFICATION = 0, //!< A Cartographic SVS file that contains a user defined classification
  EB_SVS_CARTO_CLASSIFICATION     = 1, //!< A Cartographic SVS that follows the predefined cartographic classification (See BCartoConst.h)
  EB_SVS_TYPE_MAX                 = 2  //!< An invalid value
};


/**
 * @enum EB_SOURCE_FORMAT
 * This enum defines all the possible source format of an SVS file.
 */
enum EB_SOURCE_FORMAT {
  EB_SOURCE_UNDEFINED = 0, //!< Undefined source format
  EB_SOURCE_DXF       = 1, //!< DXF format
  EB_SOURCE_GDF_3_0   = 2, //!< GDF 3.0 format
  EB_SOURCE_GDF_4_0   = 3, //!< GDF 4.0 format
  EB_SOURCE_SHP       = 4, //!< Shapefile format
  EB_SOURCE_MAX       = 5  //!< An invalid value
};


class CBSVS;

/**
 * @class CBCartoHeader
 *
 * This class reads general information contained in an SVS header.
 *
 * The SVS header is an object class of type #EB_GEOTYPE_ABSTRACT and of class ID 0
 * which contains general information on the SVS such as :
 * - the type of cartographic classification used,
 * - the format in which the data comes from, 
 * - the coordinate system of the geometry,
 * - the scale of the geometry,
 * - the encoding used for textual attributes.
 */
class BSVS_EXPORT CBCartoHeader : public CBSVSHeader
{
public:

  /**
   * Constructs a Cartographic SVS Header that contains undefined values
   * (undefined classification, source and coordinate system).
   */
  CBCartoHeader(void);

  /**
   * Constructs a Cartographic SVS Header.
   * @param inType The type of cartographic SVS file (see #EB_SVS_TYPE).
   * @param inFormat The format in which the data comes from (see #EB_SOURCE_FORMAT).
   * @param inCoord The coordinate system of the geometry (see #EB_COORD).
   * @param inScale The scale of the geometry.  
   * @param inEncoding The encoding of textual attributes.
   * @deprecated See second constructor.
   */
  CBCartoHeader(EB_SVS_TYPE      inType,
                EB_SOURCE_FORMAT inFormat   = EB_SOURCE_UNDEFINED,                
                EB_COORD         inCoord    = EB_COORD_UNDEFINED,
                TBuint32         inScale    = 1,
                EB_ENCODING      inEncoding = EB_ENCODING_ISO_8859_1);     

  /**
   * Constructs a Cartographic SVS Header.
   * @param inType The type of cartographic SVS file (see #EB_SVS_TYPE).
   * @param inCoordSystem The compplete coordinate system of the geometry (see #EB_COORD_SYSTEM).
   * @param inScale The scale of the geometry.  
   * @param inFormat The format in which the data comes from (see #EB_SOURCE_FORMAT).
   * @param inEncoding The encoding of textual attributes.
   * @since v1.8.0 Creation
   */
  CBCartoHeader(EB_SVS_TYPE             inType,
                const TB_COORD_SYSTEM & inCoordSystem,
                TBuint32                inScale    = 1,
                EB_SOURCE_FORMAT        inFormat   = EB_SOURCE_UNDEFINED,                
                EB_ENCODING             inEncoding = EB_ENCODING_ISO_8859_1);   

  /**
   * Copy constructor
   */
  CBCartoHeader(const CBCartoHeader & inSource);

  /**
   * Assignment operator.
   */
  CBCartoHeader & operator=(const CBCartoHeader & inOther);

  /**
   * Destructor.
   */
  ~CBCartoHeader(void) {};

  /**
   * Returns the type of SVS file.
   * @return The type of SVS file.
   */
  inline EB_SVS_TYPE GetSVSType(void) const { return mSVSType; }

  /**
   * Returns the source format from which the SVS data comes.
   * @return The source format from which the SVS data comes.
   */
  inline EB_SOURCE_FORMAT GetSource(void) const { return mSourceFormat; }
  
  /**
   * Returns the coordinate system of the geometry.
   * @return The coordinate system of the geometry.
   * @deprecated See #GetCoordSystem to get the full coordinate system definition.
   */
  inline EB_COORD GetCoord(void) const { return mCoord.coordType; }
  
  /**
   * Returns the complete coordinate system definition of the geometry.
   * @return the complete coordinate system definition of the geometry.
   * @since v1.8.0 Creation
   */
  inline const TB_COORD_SYSTEM & GetCoordSystem(void) const { return mCoord; }
  
  /**
   * Returns the encoding of textual attributes.
   * @return The encoding of textual attributes.
   */
  inline EB_ENCODING GetEncoding(void) const { return mEncoding; }
  
  /**
   * Returns the scale of the geometry.
   * @return The scale of the geometry.
   */
  inline TBuint32 GetScale(void) const { return mScale; }

  /**
   * Sets the type of SVS file.
   * @param inType The type of SVS file.
   */
  void SetSVSType(EB_SVS_TYPE inType);
  
  /**
   * Sets the source format from which the SVS data comes.
   * @param inSource The source format from which the SVS data comes.
   */
  void SetSource(EB_SOURCE_FORMAT inSource);
  
  /**
   * Sets the coordinate system of the geometry.
   * @param inCoord The coordinate system of the geometry.
   * @deprecated See #SetCoordSystem replacement.
   */
  void SetCoord(EB_COORD inCoord);
  
  /**
   * Sets the complete coordinate system definition.
   * @param inCoordSystem The coordinate system definition of the geometry.
   * @since v1.8.0 Creation
   */
  void SetCoordSystem(const TB_COORD_SYSTEM & inCoordSystem);

  /**
   * Sets the encoding of textual attributes.
   * @param inCharSet The encoding of textual attributes.
   */
  void SetEncoding(EB_ENCODING inEncoding);
  
  /**
   * Sets the scale of the geometry.
   * @param inScale The scale of the geometry.
   */
  void SetScale(TBuint32 inScale);

  /**
   * Returns \c true if this SVS header is a Cartographic SVS Header.
   * @return \c true if this SVS header is a Cartographic SVS Header.
   */
  TBbool IsValid(void) const { return (mSVSType         != EB_SVS_TYPE_MAX) &&                                       
                                      (mSourceFormat    != EB_SOURCE_MAX)   && 
                                      (mCoord.coordType != EB_COORD_MAX)    &&
                                      (mCoord.ellipsoid != EB_ELLIPSOID_MAX); }

  /**
   * Populates this class with all the header information coming from the given SVS.
   * @param inSVS The SVS which contains cartographic header information to extract.
   * @return \c true if this header contains header information, \c false otherwise.
   */
  TBbool Get(CBSVS * inSVS);

  /**
   * Assigns cartographic header information to the given SVS (Older header information will be erased).
   * @param inSVS The SVS which must contain cartographic header information.
   * @return \c false if an error occurs, \c true otherwise.
   */
  TBbool Set(CBSVS * inSVS);
  
  /**
   * Resets all information from this SVS Header such that it becomes empty and invalid.
   */
  void Reset(void);
  
  /**
   * Equality operator which determines whether two CBCartoHeader object are equal.
   */
  friend TBbool operator==(const CBCartoHeader& inH1, const CBCartoHeader& inH2) 
  {
    return (inH1.mSVSType         == inH2.mSVSType          &&
            inH1.mEncoding        == inH2.mEncoding         &&
            inH1.mCoord.coordType == inH2.mCoord.coordType  &&
            inH1.mCoord.ellipsoid == inH2.mCoord.ellipsoid  &&
            inH1.mScale           == inH2.mScale);
  }

  /**
   * Returns the default ellipsoid which is associated to the given type of coordinate system.
   * This helper method is provided for backward compatibility with SVS files that do not contain
   * the ellipsoid parameter in their header.
   * @return the default ellipsoid which is associated to the given type of coordinate system.
   * @since v1.8.0 Creation
   */
  static EB_ELLIPSOID GetDefaultEllipsoid(EB_COORD inCoord);
  
private:

  EB_SVS_TYPE      mSVSType;
  EB_SOURCE_FORMAT mSourceFormat;
  EB_ENCODING      mEncoding;
  TB_COORD_SYSTEM  mCoord;  
  TBuint32         mScale;
  TBbool           mBuildAbstracts;
};

#endif // __CBCARTOHEADER_H__
