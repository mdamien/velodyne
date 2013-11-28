/*==========================================================  (-*- C++ -*-)
 *
 * @file CBSVS.h
 * 
 * @version  $Id: CBSVS.h,v 1.84 2006/02/14 17:38:09 dlabrousse Exp $ 
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBSVS_H__
#define __CBSVS_H__

/*!
  @file CBSVS.h
	CBSVS class definition.
*/

#include "BTypes.h"
#include "BMacros.h"
#include "CBMutex.h"
#include "CBDateTime.h"

#define KB_DEFAULT_MINIMAL_FORMS_PER_NODE  10

class CBStream;
class CBBitStream;
class CBSVS;
class CBSVSMgr;
class CBObjectMgr;
class CBForm;
class CBAtt;
class CBAttAlpha;
class CBAttMeta;

/**
 * @struct TB_FORM_PARAMETERS
 * A structure that represents a unique object identifier.
 */
struct BSVS_EXPORT TB_FORM_PARAMETERS {
  /**
   * @return The Object's class ID
   */
  TBuint32 GetClassID(void) const;
  /**
   * @return The Object's geometric type
   */
  EB_GEOTYPE GetType(void) const;

  const CBSVS       * svs;      //!< The SVS this object belongs to
  const CBObjectMgr * objMgr;   //!< Internal member
  TBuint32            pos;      //!< Internal member
};


#define SVS_MEM_ERROR           ((mStatus & 0x0001) != 0)
#define SVS_IS_3D               ((mStatus & 0x0002) != 0)


/**
 * @class CBSVS
 * The CBSVS class defines a wrapper over the SVS format (Scalable Vector Storage)
 * by providing methods to read, construct and write SVS data.
 * 
 */
class BSVS_EXPORT CBSVS
{
public:

  /**
   * @enum EB_OPEN_STATUS
   * This defines all the possible status that the #Open method can return.
   */
  enum EB_OPEN_STATUS {
    SUCCESS           = 0, //!< SVS file has been successfully open
    ALREADY_OPEN      = 1, //!< A previous call to the #Open method has already been done
    INVALID_STREAM    = 2, //!< The given stream is invalid
    INVALID_FILE      = 3, //!< The given stream object points to an invalid SVS file
    INVALID_VERSION   = 4, //!< You attempt to open a deprecated SVS file.
    INVALID_KEY       = 5, //!< You attempt to open an SVS with an invalid user key
    NOT_ENOUGH_MEMORY = 6, //!< Not enough memory left
    EXPIRED_SVS       = 7, //!< Expired SVS
    NOT_EXPORTABLE    = 8, //!< Non exportable SVS file can not be built in memory. 
    OUT_OF_BOUNDS     = 9  //!< SVS' territory does not intersect one of the specified clipping regions.
  };

  /**
   * Creates an empty CBSVS object.
   */
  CBSVS(void);

  /**
   * Destructor
   */
  virtual ~CBSVS(void);

  /**
	 * Opens an SVS.
   * @param inStream SVS' stream (see #CBStream)
   * @param inUserKey User's key (default \c NULL): SVS will be openned only if this key is the one used for writing SVS (see #WriteToStream)
   * @param inBuildInMemory If \c true, forms will be built in memory, if \c false (default), forms are not built in memory (\e recommended !)
   * @param inDestroyStream If \c true, will destroy \a inStream in destructor (default = \c true)
   * @param inNbClipRegions The number of clipping regions.
   * @param inClipRegions An optional pointer to an array of \a inNbClipRegions clipping regions. If the SVS' territory
   * does not instersect one of the given clipping regions, the method fails and returns the #OUT_OF_BOUNDS error code.
	 * @return Opening status (see #EB_OPEN_STATUS)
   */
  CBSVS::EB_OPEN_STATUS Open(CBStream             * inStream,
                             const TBint8         * inUserKey       = NULL,
                             TBbool                 inBuildInMemory = false,
                             TBbool                 inDestroyStream = true,
                             TBuint32               inNbClipRegions = 0,
                             const TB_2D_LONGRECT * inClipRegions   = NULL);

#ifdef B_MEM_OPTIM
	void ReleaseTrees(void);
#endif

  /**
   * Returns \c true if SVS' geometry is in 3D, \c false otherwise.
	 * @return \c true if SVS' geometry is in 3D, \c false otherwise
   */
  inline TBbool Is3D(void) const { return SVS_IS_3D; }

  /**
   * Sets SVS' geometry to 3D (only if SVS is empty !).
   */
  void Set3D(void);

  /**
   * Returns \c true if SVS is dynamic, \c false otherwise.
	 * @return \c true if SVS is dynamic, \c false otherwise
   */
	inline TBbool IsDynamic(void) const { return mStream == NULL; }

  /**
   * \internal
   */
  inline CBDateTime GetExpDateTime(void) const { return mExpDateTime; }

  /**
   * \internal
   */
  inline CBSVSMgr * GetSVSMgr(void) const { return mSVSMgr; }

  /**
   * \internal
   */
  inline TBuint32 GetNbObjectMgr(void) const { return mNbObjectMgr; }

  /**
   * \internal
   */
	inline TBbool MemOk(void) const { return SVS_MEM_ERROR; }

  /**
   * Returns SVS' territory.
	 * @return SVS' territory
   */
  inline const TB_LONGRECT& GetTerritory(void) const { return mTerritory; }

  /**
   * @since v1.5
   * Retrieves SVS' territory for a specific classID and geometric type
	 * @param inClassID The specific classID
	 * @param inType The specific geometric type
	 * @param outTerritory The corresponding territory
	 * @return \c false if \a inClassID with geometric type \a inType was not found or if \a inType is #EB_GEOTYPE_ABSTRACT, \c true otherwise
   */
  TBbool GetTerritory(TBuint32     inClassID,
                      EB_GEOTYPE   inType,
                      TB_LONGRECT& outTerritory) const;

  /**
   * Sets SVS' exportability.
	 * @param exportable If \c true, SVS is exportable, if \c false SVS is not exportable.
   * @note This can be done only on empty SVS
   */
  void SetExportability(TBbool exportable);

  /**
   * Returns \c true if SVS is exportable, \c false otherwise.
	 * @return \c true if SVS is exportable, \c false otherwise
   */
  TBbool Exportable(void) const;

  /**
   * \internal 
   */
  TBuint32 GetObjMgrIndex(const CBObjectMgr * inObjMgr) const;

  /**
   * Returns total number of classes in SVS.
	 * @return Total number of classes in SVS.
   */
  TBuint32 GetNbClasses(void) const;

  /**
   * Returns total number of forms in SVS.
	 * @return Total number of forms in SVS
   */
  TBuint32 GetNbForms(void) const;
	
  /**
   * Returns total number of geometric forms in SVS
	 * (all forms which geometric type is not #EB_GEOTYPE_ABSTRACT)
	 * @return Total number of geometric forms in SVS
   */
  TBuint32 GetNbGeoForms(void) const;

  /**
   * \internal 
   * SHOULD NOT BE USED !!
   */
  const CBStream * GetStream(TBbool inLoadData = true) const;

  /**
   * \internal 
   * MUST NOT BE USED !!
	 */
  void ReleaseStream(void) const;

  /**
   * \internal 
   * SHOULD NOT BE USED !!
	 */
  inline void SetSVSMgr (CBSVSMgr * inSVSMgr) { mSVSMgr = inSVSMgr; }

  /**
   * Adds a new object to SVS in the specified class ID \a inClassID.
	 * @param inObject New Object to add (see #TB_EXTERN_OBJECT).
	 * @param inClassID The Class ID in which object will be added.
	 */
  CBForm * AddObject(const TB_EXTERN_OBJECT& inObject, TBuint32 inClassID);

  /**
   * Adds a new object to SVS in the specified class ID \a inClassID.
	 * @param inForm New Object to add (see #CBForm).
	 * @param inClassID The Class ID in which object will be added.
	 */
  TBbool AddObject(CBForm * inForm, TBuint32 inClassID);

  /**
   * Returns SVS object identified by \a inFormParameters (see #TB_FORM_PARAMETERS).
	 * @param inFormParameters Form's parameters
	 * @param inCopy If \c true (default) and forms are built in memory, returns a copy of SVS object
	 * @param inPrivateArg A private argument (MUST be NULL).
   * @return SVS object identified by \a inFormParameters
	 */
  CBForm * ExtractForm(const TB_FORM_PARAMETERS& inFormParameters, TBbool inCopy = true, TBany inPrivateArg = NULL) const;

  /**
   * \internal
	 */
  CBForm * ExtractForm(TBuint32  inFrmPos, TBuint32& outClassID, TBany inPrivateArg = NULL) const;

  /**
   * Removes \a inForm from the specified SVS's class.
	 * @param inForm SVS object to remove
	 * @param inClassID Class ID of \a inForm's object.
	 * @param inDestroy If \c true, \a inForm will be destroyed
	 * @return \c true if \a inForm has been found, \c false otherwise
	 */
  TBbool RemoveObject(CBForm * inForm, TBuint32 inClassID, TBbool inDestroy = true);

  /**
   * Removes and destroys all objects (of type \a inType) from the specified class \a Class ID.
	 * @param inClassID Class ID of objects to remove.
	 * @param inType Geometric type of objects to remove (see #EB_GEOTYPE).
   * @return \c false if the specified Class ID does not exist or if there is no object 
   * of type \a inType contained in this class, \c true otherwise.
	 */
  TBbool RemoveClass(TBuint32 inClassID, EB_GEOTYPE inType);

  /**
   * Removes and destroys all objects (of any types) from the specified class \a Class ID.
	 * @param inClassID Class ID of objects to remove.
   * @return \c false if the specified Class ID does not exist, \c true otherwise.
	 */
  TBbool RemoveClass(TBuint32 inClassID);

  /**
   * \internal
	 */
  void Settle(TBuint32 inMinimalFormsPerNode = KB_DEFAULT_MINIMAL_FORMS_PER_NODE);

  /**
   * \internal
	 */
  TBbool PostSettle(TBuint32 inClassID, EB_GEOTYPE inType);

  /**
   * \internal
	 */
  //TBbool Save(const TBchar * inFileName);

  /**
   * Writes SVS in stream \a outStream (see #CBStream).
	 * @param outStream Stream to write SVS in
   * @param inUserKey User's key (default \c NULL): key used for data protection: it will be required for openning SVS (see #Open).
   * @param inExpTime Sets an expiration date and time for this SVS (see #CBDateTime). SVS cannot be openned after this date.
   * @return \c false if there is no object in SVS, \c true otherwise.
	 */
  TBbool WriteToStream(CBStream        * outStream,
                       const TBint8    * inUserKey = NULL,
                       const CBDateTime& inExpTime = (time_t) 0);

  /**
   * \internal
	 */
  TBbool FindObjectMgr(TBuint32 inClassID, EB_GEOTYPE inType, TBuint32 & outIndex) const;

  /**
   * \internal
	 */
  TBbool FindObjectMgr(TBuint32 inFrmPos, TBuint32 & outIndex) const;

  /**
   * \internal
	 */
  inline CBObjectMgr * GetObjectMgr(TBuint32 inIndex) const
  {
    return inIndex < mNbObjectMgr ? mObjectMgr[inIndex] : NULL;
  }
  
  inline TBuint32 GetMaxAlphaLen(void) const { return mMaxAlphaLen; }
  inline TBuint32 GetMaxMetaLen (void) const { return mMaxMetaLen;  }

protected:

  TBbool IsSettled (void) const;

  CBAtt * CreateAlphaAtt(TBuint16  inCode, EB_GEOTYPE inType, TBbool notify);
  CBAtt * CreateMetaAtt (TBuint16  inCode, EB_GEOTYPE inType, TBbool notify);

  inline const CBObjectMgr * const * GetObjectMgr(void) const { return mObjectMgr; }

#if defined(_BMT_SAFE)  
  CBObjectMgr * const * GetSafeObjMgrCopy(TBuint32 & outNbObjMgr);
#endif

private:

  void SettleAttributes(void);

  CBAttAlpha * FindAlphaAtt(TBuint16 inCode, EB_GEOTYPE inType, TBuint32&  outIdx) const;
  CBAttMeta  * FindMetaAtt (TBuint16 inCode, EB_GEOTYPE inType, TBuint32&  outIdx) const;
  
  TBbool SetObjectMgr(TBuint32 inClassID,  EB_GEOTYPE inType, TBuint32 & outIndex);

  void SetTerritory(void);

  void WriteAlphaAttToStream (CBBitStream * inBitStream);
  void WriteMetaAttToStream  (CBBitStream * inBitStream);

  TBbool ReadAlphaAttFromStream(CBBitStream * inBitStream, TBbool inBuildInMemory);
  TBbool ReadMetaAttFromStream (CBBitStream * inBitStream, TBbool inBuildInMemory);

  // Disable copy
  CBSVS (const CBSVS &);
  CBSVS & operator=(const CBSVS &);

private:

  TBuint16       mStatus;
  TBuint16       mFlags;
  CBDateTime     mExpDateTime;
  TBuint32       mNbAlphaAtt;
  TBuint32       mNbMetaAtt;
  TBuint32       mMaxAlphaLen;
  TBuint32       mMaxMetaLen;
  TBuint32       mNbObjectMgr;
  CBSVSMgr     * mSVSMgr;
  CBStream     * mStream;
  CBAttAlpha  ** mAlphaAtt;
  CBAttMeta   ** mMetaAtt;
  CBObjectMgr ** mObjectMgr;
  TBany          mPrivate;
  TBany          mPrivate2;
  TB_LONGRECT    mTerritory;
#if defined(_BMT_SAFE)
  mutable CBMutex mMutex;
#endif

  friend class CBObjectMgr;
  friend class CBSVSMgr;
  friend class CBCursor;
  friend class CBGraph;
};

#endif //  __CBSVS_H__
