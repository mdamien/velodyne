/*==========================================================  (-*- C++ -*-)
 *
 * @file CBSVSMgr.h
 * 
 * @version  $Id: CBSVSMgr.h,v 1.50 2006/02/08 10:16:14 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBSVS_MGR_H_
#define _CBSVS_MGR_H_

/*!
  @file CBSVSMgr.h
	CBSVSMgr class definition.
*/

#include "CBObserver.h"
#include "CBSVS.h"
#include "CBHashMap.h"

#if defined (_BMT_SAFE)
#  include "CBMutex.h"
#endif

// forward declarations
class CBSVS;
class CBSVSCache;
class CBSVSValidator;
class CBClipZone;

/**
 * @class CBSVSMgr
 *
 * @brief A class that allows you to manage transparently a set of SVS files
 * or dynamic SVS objects.
 * In addition, the CBSVSMgr class includes an efficient memory cache to
 * handle a large amount of svs data.
 */
class BSVS_EXPORT CBSVSMgr : public CBSubject
{
public:

  /** 
   * @enum EB_MEM_TYPE
   * Defines the type of memory cache to use.
   */
  enum EB_MEM_TYPE { 
    RAM = 0, //!< RAM Memory
    VM       //!< Virtual Memory
  };

  /**
   * Creates a new CBSVSMgr object with a maximum memory cache of \c inCacheSize Mbytes.
   * Depending on the \c inMemType argument, the memory can reside either in RAM or in VM
   * (Virtual Memory). In most cases you should select VM if the total size of svs data is 
   * greater than the cache size.
   * @param inMemType The type of memory to use (see #EB_MEM_TYPE).
   * @param inCacheSize The maximum size of the memory cache
   * @param inSVSValidator A #CBSVSValidator object that is used by the #Open method to
   * determine if SVS files are compatible together (i.e same projection, scale, ...). If
   * null, no check is performed. 
   **/
  CBSVSMgr(EB_MEM_TYPE      inMemType, 
           TBuint16         inCacheSize    = 16,
           CBSVSValidator * inSVSValidator = NULL);

  /**
   * Destructor
   * Close all loaded SVS files and destroy this SVS manager.
   **/
  ~CBSVSMgr(void);  

  //
#ifdef _DEBUG
  void PrintCacheInfo(void) const;
#endif
  //

  /**
   * Returns the number of #CBSVS objects handled by this manager.
   * @return The number of #CBSVS objects handled by this manager.
   */
  inline TBuint32 GetCount(void) const { return mSVSPool.GetCount(); }

  /**
   * Returns only the number of dynamic #CBSVS objects handled by this manager.
   * @note A dynamic SVS is a #CBSVS object with no stream attached (all geometric forms
   * are stored in memory).
   * @return The number of dynamic #CBSVS objects handled by this SVS manager.
   */
  inline TBuint32 GetDynCount(void) const { return mDynCount; }

  /**
   * Returns all the CBSVS objects handled by this manager.
   * @return A vector of pointer to #CBSVS objects.
   */
  inline const CBVector& GetSVSPool(void) const { return mSVSPool; }
 
  /**
   * Returns the currently attached CBSVSValidator object if any.
   * @return A pointer to a CBSVSValidator object or null.
   */
  inline const CBSVSValidator * GetValidator(void) const { return mValidator; }
 
  /**
   * Returns the union in 2D of all opened SVS' territories
   * @return The union in 2D of all opened SVS' territories.
   */
  inline const TB_2D_LONGRECT & GetGlobal2DTerritory(void) const { return mGlobalTerritory; }

  /**   
   * Checks whether the given SVS file has already been loaded.
   * @return \c true if the specified SVS file has already been loaded, \c false otherwise.
   * @since v1.5 : Creation
   */
  TBbool Contains(const TBchar * inFileName) const;


  /**   
   * Returns the CBSVS instance associated to given SVS file.
   * @return A valid CBSVS pointer if the specified SVS file is managed, \c NULL otherwise.
   * @since v1.5.1 : Creation
   */
  const CBSVS * GetSVS(const TBchar * inFileName) const;


  /**
   * Returns the full path name of the file associated with the given #CBSVS object.
   * @note Only non dynamic #CBSVS objects have a file name.
   * @param inSVS The #CBSVS object of which we want to find the file name.
   * @param outFileName Contains the associated file name. 
   * @return \c false if an error occurs (#GetLastError() returns #NOT_FOUND), \c true otherwise.
   */
  TBbool GetFileName(const CBSVS * inSVS, const TBchar *& outFileName);

  /**
   * Loads data from the given SVS file and constructs a non dynamic #CBSVS object.
   * @param inFileName The full path name of the SVS file to open.
   * @param outSVS  The created #CBSVS object.
   * @param inUserKey User's key (default \c NULL): SVS will be openned only if this key is the one used for writing SVS (see #CBSVS::WriteToStream)
   * @param inNbClipRegions The number of clipping regions.
   * @param inClipRegions An optional pointer to an array of \a inNbClipRegions clipping regions. If the SVS' territory
   * does not instersect one of the given clipping regions, the method fails.
   * @return \c false if an error occurs, true otherwise. Call the #GetLastError method
   * in order to obtain detail on the error.
   * @note The error can take one of the following values :
   *      - #INVALID_FILENAME
   *      - #ALREADY_EXISTS
   *      - #CANT_OPEN_FILE
   *      - #SVS_VALIDATION_FAILED
   *      - #INVALID_USER_KEY
   *      - #NOT_ENOUGH_MEMORY (On WinCE platform)
   *      - #EXPIRED_SVS 
   *      - #OUT_OF_BOUNDS
   *      - #NONE
   */
  TBbool Open(const TBchar         * inFileName,
              CBSVS               *& outSVS,
              const TBint8         * inUserKey       = NULL,
              TBuint32               inNbClipRegions = 0,
              const TB_2D_LONGRECT * inClipRegions   = NULL);

  /**   
   * Loads data from a series of SVS files.
   * @note The loading process will be stopped on the first error encountered.
   * @param inFileNames Array of full path name of the SVS files to open.
   * @param nbFiles Number of SVS files to open.
   * @param outErrorFileIdx If the SVS manager fails to open an SVS file, this argument will return its index.
   * @param inUserKey User's key (default \c NULL): SVS will be openned only if this key is the one used for writing SVS (see #CBSVS::WriteToStream)
   * @param inNbClipRegions The number of clipping regions.
   * @param inClipRegions An optional pointer to an array of \a inNbClipRegions clipping regions. If the SVS' territory
   * does not instersect one of the given clipping regions, the method fails.
   * @return \c false if an error occurs, true otherwise. Call the #GetLastError method
   * in order to obtain detail on the error.
   * @note The error can take one of the following values :
   *      - #INVALID_FILENAME
   *      - #ALREADY_EXISTS
   *      - #CANT_OPEN_FILE
   *      - #SVS_VALIDATION_FAILED
   *      - #INVALID_USER_KEY
   *      - #NOT_ENOUGH_MEMORY (On WinCE platform)
   *      - #EXPIRED_SVS 
   *      - #OUT_OF_BOUNDS
   *      - #NONE
   * @since v1.5 : Creation
   */

  TBbool Open(const TBchar        ** inFileNames,
              TBuint32               nbFiles,
              TBuint32             & outErrorFileIdx,
              const TBint8         * inUserKey       = NULL,
              TBuint32               inNbClipRegions = 0,
              const TB_2D_LONGRECT * inClipRegions   = NULL);


  /**
   * Adds a new dynamic #CBSVS object in the SVS manager.
   * @param inSVS The #CBSVS object to add.
   * @param inOwner  \c true if you want to transfert the ownership of \c inSVS to the manager.
   * if \c false you will have to destroy this object yourself.
   * @return \c false if an error occurs (#GetLastError() may return #NOT_DYNAMIC_SVS, #ALREADY_EXISTS or #ALREADY_MANAGED), true otherwise. 
   */
  TBbool Add(CBSVS * inSVS, TBbool inOwner = true);

  /**
   * Closes and removes a non dynamic #CBSVS object from the SVS manager.
   * @param inFileName The name of the SVS file to close.
   * @return \c true if success, false otherwise. (#GetLastError() returns #NOT_FOUND). 
   */
  TBbool Close(const TBchar * inFileName);

  /**
   * Removes a dynamic #CBSVS object from the SVS manager.
   * @warning If the given #CBSVS was added with \c inOwner=true then it will be 
   * automaticaly deleted and \c ioSVS will be set to \c null.
   * @param ioSVS The CBSVS object to remove from the SVS manager.
   * @return \c true if success, false otherwise. (#GetLastError() may return #NOT_DYNAMIC_SVS, #NOT_FOUND or #ALREADY_MANAGED). 
   */
  TBbool Remove(CBSVS *& ioSVS);
  
  /**
   * Depending on the \c inExceptDynamic flag, this method closes either all #CBSVS objects
   * or all non dynamic #CBSVS objects.
   * @param inExceptDynamic If \c true, closes all non dynamic #CBSVS objects.
   */
  void CloseAll (TBbool inExceptDynamic = false);

  /**
   * @enum EB_ERROR
   * This enum defines all the possible errors 
   */
  enum EB_ERROR {
    NONE = 0,               //!< No error. 
    INVALID_FILENAME,       //!< The given SVS file name is invalid.
    CANT_OPEN_FILE,         //!< The SVS Manager can not open the given SVS file.
    ALREADY_EXISTS,         //!< The given SVS file has already been loaded.
    INVALID_SVS_FILE,       //!< The given file is not in the SVS format.
    INVALID_SVS_VERSION,    //!< The given SVS file is deprecated.
    INVALID_USER_KEY,       //!< The given SVS file's user key does nor correspond to given user key.
    SVS_VALIDATION_FAILED,  //!< The SVS Manager reject the given SVS file due to validation failure (see #GetValidationError)
    NOT_FOUND,              //!< The given SVS or file name can not be found.
    NOT_DYNAMIC_SVS,        //!< You attempt to #Add a non dynamic CBSVS object in the manager.
    NOT_ENOUGH_MEMORY,      //!< Not enough memory to open this SVS File 
    ALREADY_MANAGED,        //!< The given CBSVS object is handled by another SVS Manager. 
    EXPIRED_SVS,            //!< Expired SVS
    OUT_OF_BOUNDS           //!< SVS' territory does not intersect one of the specified clipping regions.
  };

   /**
   * This methods allows you to retrieve the last generated error code 
   * @return A value among the following ones #EB_ERROR
   */
  inline EB_ERROR GetLastError (void) const { return mErr; }

  /**
   * @brief Returns the last validation error.
   * In case where the #GetLastError returns #SVS_VALIDATION_FAILED, this method allows you to
   * obtain the corresponding error description.
   * @return A string description of the validation error.
   */
  const TBchar * GetValidationError(void) const;

  /**
   * @since v1.5
   * Returns all the SVS which intersect the specified clipping area.
   * @param inClipZone The clipping area.
   * @param outSVS A new vector of CBSVS * or NULL if that no SVS file intersects the clipping area.
   * (It's up to the caller to delete the returned vector).
   * @return \c true if there is at least one SVS file that intersects the clipping area, \c false otherwise.
   */
  //bool GetSVSFromClipZone(const CBClipZone& inClipZone, CBVector *& outSVS);

  //void Save(const TBint8 * inFileName = NULL);
  inline TBuint32 GetMaxAlphaLen (void) const { return mMaxAlphaLen; }
  inline TBuint32 GetMaxMetaLen  (void) const { return mMaxMetaLen;  }

  enum EB_EVENT {
    ADDED,
    REMOVED,
    MULTI_ADDED,
    MULTI_REMOVED,
    ALL_REMOVED
  };

private:

  TBbool LoadData    (const CBSVS * inSVS);
  TBbool ReleaseData (const CBSVS * inSVS);

  //void AddSVS   (CBSVS * inSVS);
  //void RemoveSVS(CBSVS * inSVS);

private:  
  CBVector         mSVSPool;
  CBVector         mSVSInfos;
  CBHashMap        mSVSMap;
  CBSVSCache     * mSVSCache;
  CBSVSValidator * mValidator;
  //CBSVS          * mExtractSVS;
  //CBCursor       * mCursor;
#if defined (_BMT_SAFE)
  mutable CBMutex  mMutex;
#endif
  TBuint32         mMaxAlphaLen;
  TBuint32         mMaxMetaLen;
  TBuint32         mDynCount;
  EB_ERROR         mErr;
  TB_2D_LONGRECT   mGlobalTerritory;

private:

  // Disable default ctor
  CBSVSMgr (void);
  // Disable copy
  CBSVSMgr (const CBSVSMgr &);
  CBSVSMgr & operator=(const CBSVSMgr &);

  void UpdateGlobalTerritory(CBSVS * inSVS);

  void UpdateLengths(void);

  friend class CBSVS;
  friend class CBCursor;
};


#endif /* _CBSVS_MGR_H_ */
