/*==========================================================  (-*- C++ -*-)
 *
 * @file CBSVSCursor.h
 * 
 * @version  $Id: CBSVSCursor.h,v 1.4 2005/04/06 13:49:07 dlabrousse Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBSVS_CURSOR_H__
#define __CBSVS_CURSOR_H__

/*!
 * @file CBSVSCursor.h
 * CBSVSCursor class definition.
 */

#include "BTypes.h"
#include "CBClipZone.h"
#include "CBForm.h"

// Forward declarations
class CBSVS;
class CBSVSMgr;
class CBCursor;
class CBForm;

/**
 * \typedef BCursorSVSFilterCbk
 * Defines the template of an SVS Filter Callback which is called each time
 * the cursor is about to parse a new SVS. Implementations of this user defined
 * callback should return \c false to skip one or more particular CBSVS objects.
 */
typedef TBbool (*BCursorSVSFilterCbk) (TBany inUserData, const CBSVS * inSVS);  

/**
 * \typedef BCursorClassFilterCbk
 * Defines the template of an SVS Class Callback which is called each time
 * the cursor is about to parse a new geometric class. Implementations of this 
 * user defined callback should return \c false to skip one or more particular 
 * geometric classes.
 */
typedef TBbool (*BCursorClassFilterCbk) (TBany inUserData, const TBuint32 inClassID, const EB_GEOTYPE inType);


/**
 * @class CBSVSCursor
 * Defines a cursor which provides you a way of parsing SVS' objects like an iterator does.
 * This class allows you to parse the whole content of one or more SVS files or to restrict
 * the research to particular SVS files or classes of objects via the use of filter callbacks
 * (see #SetFilterCallbacks). In addition, the research may be restricted to a specific area
 * defined by a polygon (see #SetClipZone).
 *
 * @note Multithreading support : The CBSVSCursor class is compatible with multithreaded 
 * applications but not thread-safe ! This means that two or more CBSVSCursor objects 
 * can be run simultaneously in separate threads but multiple threads should not invoke 
 * methods of a CBSVSCursor object at the same time. To enable multithreading support you 
 * should compile with the macro _BMT_SAFE defined and link against the suitable library or DLL.
 *
 */
class BSVS_EXPORT CBSVSCursor
{
public:
  
  /**
   * Constructs a new SVS Cursor which acts as an iterator on the content of 
   * the given \a inSVS.   
   * @param inSVS The SVS to explore.
   */
  CBSVSCursor(CBSVS * inSVS);

  /**
   * Constructs a new SVS Cursor which acts as an iterator on the content of 
   * a pool of SVS files. The cusror does not parse each SVS file in a sequential way 
   * but simultaneously by ascending Class IDs and geometric type order.
   *
   * @note Working with a pool means that this cursor will be automaticaly 
   * notified whenever the pool undergoes a change (i.e. SVS addition or deletion)
   * @param inSVSMgr The pool of SVS files to explore. 
   */
  CBSVSCursor(CBSVSMgr * inSVSMgr);
    
  /**
   * Destructor
   */
  virtual ~CBSVSCursor(void);

  /**
   * @struct TB_FILTER_CALLBACKS
   * A stucture that contains optional used defined callbacks and related data 
   * which allows you to specify filters on SVS files and/or classes of objects.
   */
  struct TB_FILTER_CALLBACKS {
    BCursorSVSFilterCbk   mSVSCbk;           //!< SVS Filter callback
    TBany                 mSVSCbkUserData;   //!< SVS Filter user data
    BCursorClassFilterCbk mClassCbk;         //!< SVS Class callback
    TBany                 mClassCbkUserData; //!< SVS Class user data
  };

  /**
   * Assigns user defined filter callbacks (and data) to this cursor.
   * @param inFilterCbk A pointer to an #CBSVSCursor::TB_FILTER_CALLBACKS  
   * structure that contains user defined callbacks and data or NULL to 
   * remove any filter callbacks.
   * @return \c false if you call this method while iterating over SVS' objects. 
   */
  TBbool SetFilterCallbacks(const TB_FILTER_CALLBACKS * inFilterCbk = NULL);

  /**
   * Tells the cursor to parse only geometric objects which intersect 
   * with the given clipping zone.
   * @note Geometry of the objects will not be clipped !
   * @param inClipZone The clipping zone.   
   * @return \c false if you call this method while iterating over SVS' objects. 
   */
  TBbool SetClipZone(const CBClipZone & inClipZone);
	
	/**
   * Removes geometric clipping 
   * @return \c false if you call this method while iterating over SVS' objects. 
   */
  TBbool UnsetClipZone(void);
	
  /**
   * Returns the current clipping zone.
   * @return The current clipping zone.
   * @since v1.5
   */
  const CBClipZone & GetClipZone(void) const;

  /**
   * Tests if the SVS Cursor has found one more element.
   * @return \c true if there is one more element, \c false otherwise.
   * @warning Never use the 'break' statement to exit from a \c 'while' or  \c 'for' 
   * iteration in which the Next method is used. Instead, you shoud use the 
   * #Stop method as follow :
   * \code
   *  CBSVSCursor cursor(svsMgr);
   *  while (cusor.Next()) {
   *    ....
   *    if (end) {
   *      cursor.Stop();
   *      continue;
   *    }
   *  }
   * \endcode
   */
  TBbool Next(void);

  /** 
   * Tells the cursor to stop its process.
   * @note You MUST call once again the #Next method.
   */ 
  void Stop(void);

  /**
   * Resets the cursor.
   * @return \c false if you call this method while iterating over SVS' objects.
   * @deprecated This method does nothing ! 
   */
  TBbool Reset(void);

  /** 
   * Returns the current SVS in use.
   * @return The current SVS in use.
   * @since v1.5
   */
  const CBSVS * GetSVS(void) const;

  /** 
   * Returns the Class ID of the current Form.
   * @return The Class ID of the current Form.
   */
  inline TBuint32 GetClassID(void) const { return mClassID; }

  /**
   * Returns the type of the current Form.
   * @return The type of the current Form.
   */
  inline EB_GEOTYPE GetType(void) const { return mGeoType; }

  /**
   * Returns the current geometric or abstract Form for read-only access.
   * @return The current geometric or abstract Form for read-only access.
   */
  inline const CBForm * GetForm(void) const { return mForm; }

  /**
   * Returns the bounding rectangle of the current Form.
   * @return The bounding rectangle of the current Form.
   * @since v1.5
   */
  const TB_LONGRECT & GetBoundingRect(void) const;

private:
  // Disable default and copy ctor
  CBSVSCursor(void);
  CBSVSCursor(const CBSVSCursor&);
  CBSVSCursor& operator=(const CBSVSCursor&);

private:
  TBuint16            mFlags;
  EB_GEOTYPE          mGeoType;
  TBuint32            mClassID;
  CBCursor          * mCursor;
  const CBForm      * mForm;
  mutable TB_LONGRECT mRect;
};

#endif /* __CBSVS_CURSOR_H__ */
