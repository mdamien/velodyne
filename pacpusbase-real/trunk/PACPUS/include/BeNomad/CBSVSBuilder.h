/*==========================================================  (-*- C++ -*-)
 *
 * @file CBSVSBuilder.h
 * 
 * @version  $Id: CBSVSBuilder.h,v 1.13 2005/08/20 16:32:56 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBSVS_BUILDER_H__
#define __CBSVS_BUILDER_H__

/*!
 * @file CBSVSBuilder.h
 * CBSVSHeader class definition.
 */

#include "BTypes.h"
#include "CBSVS.h"
#include "CBDateTime.h"

class CBSVSHeader;
class CBStream;
class CBFormAbstract;
class CBFormPoint2D;
class CBFormPoint3D;
class CBFormRect2D;
class CBFormRect3D;
class CBForm2D;
class CBForm3D;


/**
 * @class CBSVSBuilder
 * The CBSVSBuilder class defines a generic wrapper for building SVS Files from scratch.
 * This class provides a set of method to construct either 2D or 3D geometric forms   
 * with or without attached attributes.
 *
 * @note If you plan to create geometric objets with string or meta attributes, you should
 * keep in mind the following rules :
 * 
 *  - Adding a NULL String or Meta attribute (e.g #TB_ATTTYPE) is strictly forbidden,
 *  - Adding a #EB_ATTTYPE_ALPHA or #EB_ATTTYPE_META attribute requires that the corresponding
 * data must be <b>new</b> allocated (not malloc). 
 *  - Adding a #EB_ATTTYPE_ALPHA or #EB_ATTTYPE_META attribute means that you lost the ownership
 * of the attribute's data (This also means that a string or a meta attribute's value can not be shared
 * by more than one #TB_ATTRIBUTE structure).
 *  - Adding a #EB_ATTTYPE_USER_ALPHA or #EB_ATTTYPE_USER_META requires that you maintain the attribute's value
 * in memory until the call of the #Dump method.
 */
class BSVS_EXPORT CBSVSBuilder
{
public:

  /**
   * Constructs a generic SVSBuilder.
   * @param inSVSHeader An optional SVS Header.
   * @param inDestroyHeader Indicates whether the given SVS header must be 
   * destroy by this CBSVSBuilder instance.
   * @param in3D \c true if SVS' geometry must be in 3D.
   */
  CBSVSBuilder(CBSVSHeader * inSVSHeader = NULL, 
               TBbool        inDestroyHeader=true,
               TBbool        in3D = false);

  /**
   * Destructor.
   */
  virtual ~CBSVSBuilder(void);

  /**
   * Accessor to the underlying #CBSVS object.
   * @return the underlying #CBSVS object.
   */
  const CBSVS * GetSVS(void) const { return mSVS; }

  /**
   * Adds a new abstract object in the specified class.
   * @param inClassID The class identifier.
   * @param inAtts An array of attributes.
   * @param inNbAtts The number of attributes in the array.
   * @return A valid CBFormAbstract object or \c null if an error occurred.
   */
  const CBFormAbstract * AddAbstract(TBuint32             inClassID, 
                                     const TB_ATTRIBUTE * inAtts,
                                     TBuint16             inNbAtts);

  /**
   * Adds a new 2D point in the specified class.
   * @param inClassID The class identifier.
   * @param inPt The coordinates of the 2D point.
   * @param inAtts An optional array of attributes.
   * @param inNbAtts The number of attributes in the array.
   * @return A valid CBFormPoint2D object or \c null if an error occurred.
   */
  const CBFormPoint2D * AddPoint(TBuint32                inClassID, 
                                 const TB_2D_LONGPOINT & inPt, 
                                 const TB_ATTRIBUTE    * inAtts   = NULL,
                                 TBuint16                inNbAtts = 0);
  
  /**
   * Adds a new 3D point in the specified class.
   * @param inClassID The class identifier.
   * @param inPt The coordinates of the 3D point.
   * @param inAtts An optional array of attributes.
   * @param inNbAtts The number of attributes in the array.
   * @return A valid CBFormPoint3D object or \c null if an error occurred.
   */
  const CBFormPoint3D * AddPoint(TBuint32                inClassID, 
                                 const TB_3D_LONGPOINT & inPt, 
                                 const TB_ATTRIBUTE    * inAtts   = NULL,
                                 TBuint16                inNbAtts = 0);

  /**
   * Adds a new 2D line in the specified class.
   * @param inClassID The class identifier.
   * @param inPt1 The first coordinates of the 2D line.
   * @param inPt2 The second coordinates of the 2D line.
   * @param inAtts An optional array of attributes.
   * @param inNbAtts The number of attributes in the array.
   * @return A valid CBForm2D object or \c null if an error occurred.
   */
  const CBForm2D * AddLine(TBuint32                inClassID, 
                           const TB_2D_LONGPOINT & inPt1, 
                           const TB_2D_LONGPOINT & inPt2, 
                           const TB_ATTRIBUTE *    inAtts   = NULL,
                           TBuint16                inNbAtts = 0);
  
  /**
   * Adds a new 3D line in the specified class.
   * @param inClassID The class identifier.
   * @param inPt1 The first coordinates of the 3D line.
   * @param inPt2 The second coordinates of the 3D line.
   * @param inAtts An optional array of attributes.
   * @param inNbAtts The number of attributes in the array.
   * @return A valid CBForm3D object or \c null if an error occurred.
   */
  const CBForm3D * AddLine(TBuint32                inClassID, 
                           const TB_3D_LONGPOINT & inPt1, 
                           const TB_3D_LONGPOINT & inPt2, 
                           const TB_ATTRIBUTE *    inAtts   = NULL,
                           TBuint16                inNbAtts = 0);
  
  /**
   * Adds a new 2D polyline in the specified class.
   * @param inClassID The class identifier.
   * @param inPts The coordinates of the 2D polyline.
   * @param inNbPts The number of 2D points that define this polyline.
   * @param inAtts An optional array of attributes.
   * @param inNbAtts The number of attributes in the array.
   * @return A valid CBForm2D object or \c null if an error occurred.
   * @note At least two points are required.
   */
  const CBForm2D * AddPolyline(TBuint32                inClassID, 
                               const TB_2D_LONGPOINT * inPts, 
                               TBuint32                inNbPts,
                               const TB_ATTRIBUTE    * inAtts   = NULL,
                               TBuint16                inNbAtts = 0);

  /**
   * Adds a new 3D polyline in the specified class.
   * @param inClassID The class identifier.
   * @param inPts The coordinates of the 3D polyline.
   * @param inNbPts The number of 3D points that define this polyline.
   * @param inAtts An optional array of attributes.
   * @param inNbAtts The number of attributes in the array.
   * @return A valid CBForm3D object or \c null if an error occurred.
   * @note At least two points are required.
   */
  const CBForm3D * AddPolyline(TBuint32                inClassID, 
                               const TB_3D_LONGPOINT * inPts, 
                               TBuint32                inNbPts,
                               const TB_ATTRIBUTE    * inAtts   = NULL,
                               TBuint16                inNbAtts = 0);

  /**   
   * Adds a new 2D rectangle in the specified class.
   * @param inClassID The class identifier.
   * @param inRect The coordinates of the 2D rectangle.   
   * @param inAtts An optional array of attributes.
   * @param inNbAtts The number of attributes in the array.
   * @return A valid CBFormRect2D object or \c null if an error occurred.   
   * @since v1.5 Creation
   */
  const CBFormRect2D * AddRectangle(TBuint32                inClassID, 
                                    const TB_2D_LONGRECT  & inRect,                               
                                    const TB_ATTRIBUTE    * inAtts   = NULL,
                                    TBuint16                inNbAtts = 0);
  /**   
   * Adds a new 3D rectangle in the specified class.
   * @param inClassID The class identifier.
   * @param inRect The coordinates of the 3D rectangle.  
   * @param inAtts An optional array of attributes.
   * @param inNbAtts The number of attributes in the array.
   * @return A valid CBFormRect3D object or \c null if an error occurred.   
   * @since v1.5 Creation
   */
  const CBFormRect3D * AddRectangle(TBuint32                inClassID, 
                                    const TB_3D_LONGRECT  & inRect,                               
                                    const TB_ATTRIBUTE    * inAtts   = NULL,
                                    TBuint16                inNbAtts = 0);

  /**   
   * Adds a new 2D ellipse in the specified class.
   * @param inClassID The class identifier.
   * @param inRect The coordinates of the 2D rectangle that defines the ellipse.    
   * @param inAtts An optional array of attributes.
   * @param inNbAtts The number of attributes in the array.
   * @return A valid CBFormRect2D object or \c null if an error occurred.   
   * @since v1.5
   */
  const CBFormRect2D * AddEllipse(TBuint32                inClassID, 
                                  const TB_2D_LONGRECT  & inRect,                               
                                  const TB_ATTRIBUTE    * inAtts   = NULL,
                                  TBuint16                inNbAtts = 0);
  /**   
   * Adds a new 3D ellipse in the specified class.
   * @param inClassID The class identifier.
   * @param inRect The coordinates of the 3D rectangle that defines the ellipse.  
   * @param inAtts An optional array of attributes.
   * @param inNbAtts The number of attributes in the array.
   * @return A valid CBFormRect3D object or \c null if an error occurred.   
   * @since v1.5
   */
  const CBFormRect3D * AddEllipse(TBuint32                inClassID, 
                                  const TB_3D_LONGRECT  & inRect,                               
                                  const TB_ATTRIBUTE    * inAtts   = NULL,
                                  TBuint16                inNbAtts = 0);

  /**
   * Adds a new 2D polygon in the specified class.
   * @param inClassID The class identifier.
   * @param inPts The coordinates of the 2D polygon.
   * @param inNbPts The number of 2D points that define this polygon.
   * @param inAtts An optional array of attributes.
   * @param inNbAtts The number of attributes in the array.
   * @return A valid CBForm2D object or \c null if an error occurred.
   * @note At least three points are required.
   */
  const CBForm2D * AddPolygon(TBuint32                inClassID, 
                              const TB_2D_LONGPOINT * inPts, 
                              TBuint32                inNbPts,
                              const TB_ATTRIBUTE    * inAtts   = NULL,
                              TBuint16                inNbAtts = 0);

  /**
   * Adds a new 3D polygon in the specified class.
   * @param inClassID The class identifier.
   * @param inPts The coordinates of the 3D polygon.
   * @param inNbPts The number of 3D points that define this polygon.
   * @param inAtts An optional array of attributes.
   * @param inNbAtts The number of attributes in the array.
   * @return A valid CBForm3D object or \c null if an error occurred. 
   * @note At least three points are required.
   */
  const CBForm3D * AddPolygon(TBuint32                inClassID, 
                              const TB_3D_LONGPOINT * inPts, 
                              TBuint32                inNbPts,
                              const TB_ATTRIBUTE    * inAtts   = NULL,
                              TBuint16                inNbAtts = 0);

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
  virtual const CBForm2D * AddZone(TBuint32                inClassID, 
                                   const TB_2D_LONGPOINT * inPts, 
                                   TBuint32                inNbPts,
                                   TBuint16                inDistance,                
                                   const TB_ATTRIBUTE    * inAtts   = NULL,
                                   TBuint16                inNbAtts = 0);

  /**
   * Adds the specified generic form \a inForm and its attribut(s) in the specified class.
   * @param inClassID The class identifier.
   * @param inForm The generic form to add.      
   * @return The generic added form or \c null if an error occurred.
   * @note The \a inForm argument must not belong to an existing SVS or be added twice 
   * (The \a inForm ownership is transfered to the SVS Builder if this method succeeds).
   */
  const CBForm * AddForm (TBuint32 inClassID, CBForm * inForm);
  
  /**
   * Duplicates the object's geometry referenced by the \a inFormParam argument
   * in the specified class.
   * @param inClassID The class identifier.
   * @param inFormParam A unique object identifier.
   * @param inCopyAtt Indicates if existing attributes must be copied from the object source.
   * @param inAtts An optional array of new or additional attributes.
   * @param inNbAtts The number of new attributes in the array.
   * @return The copied form or \c null if an error occurred. 
   */
  const CBForm * CopyFrom(TBuint32                   inClassID, 
                          const TB_FORM_PARAMETERS & inFormParam,
                          TBbool                     inCopyAtt = true,
                          const TB_ATTRIBUTE       * inAtts    = NULL,
                          TBuint16                   inNbAtts  = 0);

  /**
   * Removes and destroys all SVS Forms (of any types) from the specified class \a Class ID.
   * @param inClassID Class ID of objects to remove.
   * @return \c false if the specified Class ID does not exist, \c true otherwise.
   */
  TBbool Remove(TBuint32 inClassID);

  /**
   * Removes and destroys all objects (of type \a inType) from the specified class \a Class ID.
   * @param inClassID Class ID of objects to remove.
	 * @param inType Geometric type of objects to remove (see #EB_GEOTYPE).
   * @return \c false if the specified Class ID does not exist or if there is no object 
   * of type \a inType contained in this class, \c true otherwise.
   */
  TBbool Remove(TBuint32 inClassID, EB_GEOTYPE inType);

  /** 
   * Removes an SVS Form which was previously added.
   * @param inForm The SVS Form to remove.
   * @param inClassID Class ID of \a inForm's object.
   * @param inDestroy If \c true, \a inForm will be destroyed
   * @return \c true if \a inForm has been found, \c false otherwise
   */
  TBbool Remove(const CBForm * inForm, TBuint32 inClassID, TBbool inDestroy = true);

  /**
   * Dump the whole content of the SVS data into the specified output stream.
	 * @warning : after dump, it is not possible to add new geometric objects or to re-use created forms !
   * @param inStream The output stream.
   * @param inUserKey The optional user's key for data protection.
   * @param inExpTime An optional expiration date and time (SVS cannot be openned after this date).
   * @return \c false if no object has been added or if an error occurred, \c true otherwise.    
   */
  TBbool Dump(CBStream         * inStream, 
              const TBint8     * inUserKey = NULL, 
              const CBDateTime & inExpTime = (time_t) 0);

protected:  

  // Disable copy
  CBSVSBuilder(const CBSVSBuilder&);
  CBSVSBuilder& operator=(const CBSVSBuilder&);

  TBbool SetAttributes(TB_EXTERN_OBJECT   & ioObj,
                       const TB_ATTRIBUTE * inAtts, 
                       TBuint16             inNbAtts);
protected:

  TBbool        mDestroyHeader;
  TBint8      * mEmptyStr;
  CBSVS       * mSVS;
  CBSVSHeader * mSVSHeader;
};

#endif /* __CBSVS_BUILDER_H__ */
