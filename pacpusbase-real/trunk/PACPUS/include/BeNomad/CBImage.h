/*==========================================================  (-*- C++ -*-)
 *
 * @file CBImage.h
 * 
 * @version  $Id: CBImage.h,v 1.11 2005/06/01 12:07:22 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBIMAGE_H_
#define _CBIMAGE_H_

/*!
  @file CBImage.h
	CBImage class definition.
*/

#if defined(_BWIN32_API_SUPPORT)    
#  include <windows.h>
#endif

#include "BTypes.h"

// Forward declaration
class CBImageImp;

/**
 * @class CBImage
 * The CBImage class defines a generic interface for loading and painting images.
 * @note Currently only BMP and DIB files are supported.
 */
class BRND_EXPORT CBImage
{
public:

  /**
   * \enum EB_OPTIM
   * An enumeration that specifies how images have to be handled.
   */
  enum EB_OPTIM {
    USE_NATIVE_API = 0,   //!< Specifies that images will be handled with the native graphic API (i.e GDI on Windows platforms)
    DEFAULT_OPTIM  = 1,   //!< Optimize for minimal memory use. 
    SPEED_OPTIM    = 2,   //!< Optimize speed drawing (but uses more memory than other options).
    //OPTIM_FOR_16BPP = 16, //!< Specifies an optimization for 16bpp off-screen
    //OPTIM_FOR_24BPP = 24, //!< Specifies an optimization for 24bpp off-screen
    //OPTIM_FOR_32BPP = 32  //!< Specifies an optimization for 32bpp off-screen
  };

  /**
   * Default constructor.
   * Constructs an empty image.
   * @param inImgOptim The image optimization to use (See #EB_OPTIM)
   */
  CBImage(EB_OPTIM inImgOptim = USE_NATIVE_API);

  /**
   * Copy constructor.
   * Constructs a shared copy of the given image.
   */
  CBImage(const CBImage & inSource);

  /**
   * Assignment operator
   * Makes a shared copy of the given image.
   */
  CBImage & operator=(const CBImage & inOther);

  /**
   * Destructor
   */
  ~CBImage(void);

  /**
   * Returns \c true if the image is not empty.
   * @return \c true if the image is not empty, \c false otherwise.
   */
  TBbool IsNull(void) const { return (mImp == NULL); }

  /**
   * Returns the type of optimization used to construct this image.
   * @return the type of optimization used to construct this image.
   * @note If this method returns \c false, you can not use all platform specific Paint method.
   */
  const EB_OPTIM & GetOptimization(void) const { return mOptim; }

  /**
   * Returns the name (full path) of the associated image file.
   * @return the name (full path) of the associated image file or \c null if this image is empty.
   */
  const TBchar * GetFileName(void) const;

  /**
   * Loads an image from the file specified by \a inFileName.
   * If \a inFormat is \c null, this method checks the file extension to determine its type.
   * @param inFileName The full path of the image to load.
   * @param inFormat The image format to take into account (i.e "bmp")
   * @return \c true if the image is not empty.
   */
  TBbool Load(const TBchar * inFileName, const TBchar * inFormat = NULL);

  /**
   * Loads an image from the file specified by \a inFileName.
   * If \a inFormat is \c null, this method checks the file extension to determine its type.
   * @param inFileName The full path of the image to load.
   * @param inFormat The image format to take into account (i.e "bmp")
   * @param inImgOptim The image optimization to use (See #EB_OPTIM)
   * @return \c true if the image is not empty.
   */
  TBbool Load(const TBchar * inFileName, const TBchar * inFormat, EB_OPTIM inImgOptim);
  
  /**
   * Unloads the current image such that it becomes empty.
   * @return \c true if this image was successfully unloaded.
   * @note Unloaded an empty image returns \c false.
   */
  TBbool UnLoad(void);

  /**
   * Returns the size of the image.
   * @param outWidth The width in pixels of the image.
   * @param outHeight The height in pixels of the image.
   * @return \c false if the image contains no data or if an error occurs, \c true otherwise.
   */
  TBbool GetSize(TBuint32 & outWidth, TBuint32 & outHeight) const;

  /**
   * @name Image transparency
   */
  //@{
  /**
   * Returns the color (RGB 24bits value) used to make a transparency effect. The value
   * 0xFFFFFFFF means that there is no transpanrency.
   * @return The color (RGB 24bits value) used to make a transparency effect. 
   */
  TBuint32 GetTransparentColor (void) const;
 
  /**
   * Sets the color (RGB 24bits value) used to make a transparency effect. The value
   * 0xFFFFFFFF means that there is no transpanrency.
   * @param inTranspClr The color mask used to make a transparency effect. 
   */
  void SetTransparentColor (TBuint32 inTranspClr);
 
  /**
   * Returns \c true if the image is transparent, \c false otherwise.
   * @return \c true if the image is transparent, \c false otherwise.
   */
  TBbool IsTransparent(void) const;

  //@}
#if defined(_BWIN32_API_SUPPORT) 
  /**
   * @name Windows specific
   */
  //@{
  /**
   * Loads a DIB resource from the specified resource ID \a inResourceId.
   * @param inResourceId The ID of the DIB resource to load.
   * @param inMod Handle to the module whose executable file contains the resource.    
   * @return \c true if the method succeeds, \c false otherwise.
   */ 
  TBbool LoadDIBResource(UINT inResourceId, HMODULE inMod=NULL);

   /**
   * Loads a DIB resource from the specified resource name \a inResourceName.
   * @param inResourceName The name of the DIB resource to load.
   * @param inMod Handle to the module whose executable file contains the resource.    
   * @return \c true if the method succeeds, \c false otherwise.
   */ 
  TBbool LoadDIBResource(const TBchar * inResourceName, HMODULE inMod=NULL);

  /**
   * Paints the current image into the given device context using 
   * SetDIBBitsToDevice or StretchDIBits GDI function.
   * @param inDC Handle to destination device context.
   * @param inDCRect Device context region to paint to(optional).
   * @param inDIBRect DIB region to paint from (optional).
   * @return \c true if the method succeeds, \c false otherwise.
   * @note If you provide regions with different width or height, the image will be stretched.
   */
  TBbool Paint (HDC inDC, RECT * inDCRect=NULL, RECT * inDIBRect=NULL) const;  
  //@}
#endif

  /**
   * \internal 
   * @return The internal image implementation.
   */
  inline CBImageImp * GetImageImp(void) { return mImp; }

private:

  CBImageImp * mImp;
  EB_OPTIM     mOptim;
};

#endif /* _CBIMAGE_H_ */
