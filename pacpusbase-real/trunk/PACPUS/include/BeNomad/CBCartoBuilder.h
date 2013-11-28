/*==========================================================  (-*- C++ -*-)
 *
 * @file CBCartoBuilder.h
 * 
 * @version  $Id: CBCartoBuilder.h,v 1.11 2006/03/07 14:31:26 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBCARTO_BUILDER_H__
#define __CBCARTO_BUILDER_H__

/*!
 * @file CBCartoBuilder.h
 * CBCartoBuilder class definition.
 */

#include "CBSVSBuilder.h"
#include "CBCartoHeader.h"

/**
 * @class CBCartoBuilder
 * The CBCartoBuilder class is a specialization of the generic CBSVSBuilder class  
 * intended to build cartographic SVS files.
 * @since 1.7.0 Added character encoding support.
 */
class BSVS_EXPORT CBCartoBuilder : public CBSVSBuilder
{
public:

  /**
   * Constructs an SVSBuilder intented to build a cartographic SVS file.
   * @param inType The type of cartographic SVS file (see #EB_SVS_TYPE).
   * @param inFormat The format in which the data comes from (see #CBCartoHeader::EB_SOURCE_FORMAT).
   * @param inCoord The coordinate system of the geometry (see #CBCartoHeader::EB_COORD).
   * @param inScale The scale of the geometry.  
   * @param in3D \c true if SVS' geometry must be in 3D.
   * @param inEncoding The character encoding for string attributes (default is ISO-8859-1 for 
   * backward compatibility, UTF-8 otherwise).
   */
  CBCartoBuilder(EB_SVS_TYPE      inType     = EB_SVS_UNDEFINED_CLASSIFICATION,
                 EB_SOURCE_FORMAT inFormat   = EB_SOURCE_UNDEFINED,                 
                 EB_COORD         inCoord    = EB_COORD_UNDEFINED,
                 TBuint32         inScale    = 1,
                 TBbool           in3D       = false,
                 EB_ENCODING      inEncoding = EB_ENCODING_ISO_8859_1);

   /**
    * Constructs an SVSBuilder intented to build a cartographic SVS file.
    * @param inType The type of cartographic SVS file (see #EB_SVS_TYPE).
    * @param inCoordSystem The complete coordinate system of the geometry (see #EB_COORD_SYSTEM).
    * @param inScale The scale of the geometry.  
    * @param in3D \c true if SVS' geometry must be in 3D.
    * @param inFormat The format in which the data comes from (see #CBCartoHeader::EB_SOURCE_FORMAT).
    * @param inEncoding The character encoding for string attributes (default is ISO-8859-1 for 
    * backward compatibility, UTF-8 otherwise).
    * @since v1.8.0 Creation
    */
  CBCartoBuilder(EB_SVS_TYPE             inType,
                 const TB_COORD_SYSTEM & inCoordSystem,
                 TBuint32                inScale    = 1,
                 TBbool                  in3D       = false,
                 EB_SOURCE_FORMAT        inFormat   = EB_SOURCE_UNDEFINED,
                 EB_ENCODING             inEncoding = EB_ENCODING_ISO_8859_1);
  

  /**
   * Destructor.
   */
  ~CBCartoBuilder(void) {}

  /**
   * Returns the character encoding for input string attributes.         
   * @since 1.7.0 Creation.
   */
  inline EB_ENCODING GetEncoding(void) const { return mEncoding; }

  /**
   * Creates a (multiple) polygon corresponding to a corridor around an array of 2D points
   * in the specified class.
   * @param inClassID The class identifier.
   * @param inPts Array of 2D points that define a polyline.
   * @param inNbPts Number of 2D points in array.
   * @param inDistance Corridor's width.
   * @param inAtts An optional array of attributes.
   * @param inNbAtts The number of attributes in the array.
   * @return A valid CBForm2D object or \c null if an error occurred.
   * @note At least one point is required.
   */
  const CBForm2D * AddZone(TBuint32                inClassID, 
                           const TB_2D_LONGPOINT * inPts, 
                           TBuint32                inNbPts,
                           TBuint16                inDistance,                
                           const TB_ATTRIBUTE    * inAtts   = NULL,
                           TBuint16                inNbAtts = 0);

protected:
  // Disable copy
  CBCartoBuilder(const CBCartoBuilder&);
  CBCartoBuilder& operator=(const CBCartoBuilder&);

private:
  EB_ENCODING mEncoding;
};

#endif /* __CBCARTO_BUILDER_H__ */
