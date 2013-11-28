/*==========================================================  (-*- C++ -*-)
 *
 * @file CBGraphicChart.h
 * 
 * @version  $Id: CBGraphicChart.h,v 1.38 2006/03/09 14:38:43 wkunkel Exp $ 
 * 
 * @author  William Kunkel
 *
 * @copyright  (c) 2002-2003 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef _CBGRAPHIC_CHART_H_
#define _CBGRAPHIC_CHART_H_

/*!
  @file CBGraphicChart.h
	CBGraphicChart class definition.
*/

#if defined(_WIN32_WCE) && !defined(_BDISABLE_XML_SUPPORT)
#  define _BDISABLE_XML_SUPPORT
#endif

#include "BTypes.h"
#include "CBImage.h"

// Forward declarations
class CBChartImp;
class CBVector;

/**
 * @struct TB_IMAGE
 * The TB_IMAGE structure instructs the graphic chart where 
 * and how an image must be inserted.
 * TB_IMAGE data types are used to display geo-referenced images 
 * such as satelite raster images.
 */
struct BRND_EXPORT TB_IMAGE {
  /**
   * \enum EB_POSITION
   * Defines the relative position of the image compared to the insertion point.
   */
  enum EB_POSITION { 
    TOPLEFT=0, //!< The insertion point will be the upper-left corner of the image (in screen coordinates).
    CENTER     //!< The insertion point will be the center of the image.
  };
  TB_2D_LONGPOINT mPoint; //!< Insertion point in real coordinates of the image.
  CBImage       * mImage; //!< The Image.
  EB_POSITION     mPos;   //!< The position of the image compared to the insertion point.
};


/**
 * \enum EB_CHART_VERSION
 * Enumeration that is used to handle versioning of Graphic charts.
 * @since v1.5 Creation.
 */
typedef enum {
  CHART_V1_0   = 10,  //!< Graphic Chart Version 1.0  [ Deprecated ]
  CHART_V1_1   = 11,  //!< Graphic Chart Version 1.1
  CHART_V1_2   = 12,  //!< Graphic Chart Version 1.2
  CHART_V1_3   = 13,  //!< Graphic Chart Version 1.3
  CHART_V1_4   = 14,  //!< Graphic Chart Version 1.4
  CHART_V_LAST = 14   //!< Latest Graphic Chart Version
} EB_CHART_VERSION;


/**
 * @class CBGraphicChart
 * The CBGraphicChart class is intented to be used in conjonction with a #CBView object
 * in order to parameterize all rendering operations. A Graphic Chart can be seen like a style sheet
 * which informs the graphic engine how to display SVS geometric forms (color, style, text font, etc...)
 * depending on criteria such as the class from which an object belongs and/or the current scale factor. 
 *
 * A graphic chart is made up of a series of styles and properties which can be either related to a class 
 * of object or to a particular type of geometric forms. 
 *
 * @note In this version, only a small part of the graphic chart properties can be modified at run-time 
 * (see #SetClassProperties and #SetStyleProperties methods).
 *
 * In addition, a graphic chart provides the following features :
 * - Zoom configuration : The graphic chart can also act on the way of zooming in a view. Two modes are
 * possible. The first is called 'continuous zoom' (or free zoom) and the second 'stepped zoom'. In this last mode, 
 * you can specify a set of predefined zoom levels from which the end user can not leave.
 * - Raster images insertion : The graphic chart allows you to display geo-referenced raster images on background.
 * These images are attached to a specific zoom level and a geographical point (see #TB_IMAGE). This implies that 
 * the current zoom mode must be set to 'stepped'.
 * 
 * SVS Graphic Chart data can be described either by an XML document or a platform independent binary 
 * file (".cht" extension). Here the XML vocabulary used to define a graphic chart \ref xmlchartpage.
 * @note On PDA platforms, only binary graphic charts are supported.
 * 
 * @note Multithreading support : no thread-safe support is provided.
 *
 */
class BRND_EXPORT CBGraphicChart 
{
public:

#if defined(_BFREETYPE_SUPPORT)
  /**
   * A static method that must be called in your main program (before any 
   * CBGraphicChart instanciation) in order to initialize the underlying 
   * FreeType2 library.
   * @since 1.5.1 Creation
   */
  static TBbool LoadFontMapping(const TBchar * inFilename);
  
  /**
   * A static method that must be called at your main program termination
   * to cleanup all font resources.
   * @since 1.5.1 Creation
   */
  static void CleanupFontMapping(void);
#endif

  /**
   * Creates a default Graphic Chart.
   * This defines a default representation for all closed and open geometric forms.
   */
  CBGraphicChart(void);

  /**
   * Destructor
   */
  ~CBGraphicChart (void);

  /**
   * \enum EB_ZOOM_MODE
   * Defines the two possible ways of zooming in a view.
   */
  enum EB_ZOOM_MODE{
    CONTINUOUS = 0, //!< Defines the continuous mode or "free mode"
    STEPPED    = 1  //!< Defines the stepped mode (a set of predefined and authorized zoom levels)
  };

  /**
   * Returns the version of the graphic chart.
   * @return The version of the graphic chart.
   * @since v1.5 Creation
   */
  EB_CHART_VERSION GetVersion(void) const;


  /**
   * Specifies a new base directory for loading images.
   * @param inBaseDir New base directory for images (bitmaps) referenced by the graphic chart.
   * @note The \c NULL value can be used to remove a previous base directory.
   * @since v1.5.1
   */
  void SetBaseDir(const TBchar * inBaseDir);

  /**
   * Returns the internal name of the graphic chart.
   * @return The internal name of the graphic chart or \c null.
   */
  const TBint8 * GetName(void) const;
  
  /**
   * Sets the internal name of the graphic chart.
   * @param inName The new internal name of the graphic chart or \c null.
   */
  void SetName(const TBint8 * inName);

  /**
   * @name Zoom related methods
   */
  //@{
  /**
   * Returns the current zoom mode.
   * @return The current zoom mode.
   */
  CBGraphicChart::EB_ZOOM_MODE GetZoomMode(void) const;
  
  /**
   * Sets the current zoom mode.
   * @param inZoomMode The new current zoom mode.
   * @note Changing the current zoom mode does not affect the set of predefined 
   * zoom levels (if any).
   */
  void SetZoomMode(CBGraphicChart::EB_ZOOM_MODE inZoomMode);

  /**
   * Returns the number of zoom levels defined in the graphic chart.
   * @return The number of zoom levels defined in the graphic chart.
   */
  TBuint16 GetZoomLevels(void) const;

  /**
   * Returns the scale factor associated with the specified zoom level.
   * @param inZoomIndex Specifies the zoom level.
   * @return The scale factor.
   * @note This assumes that \a inZoomIndex < GetZoomLevels()
   */
  TBfloat GetZoomScale(TBuint16 inZoomIndex) const;

  /**
   * Inserts a new zoom level with the specified scale factor \a inScale.
   * @param inScale The scale factor of this new zoom level.
   * @param outZoomIndex Returns the index of the new inserted zoom level.
   * @return \c false if there is already a zoom level with this scale factor, \c true otherwise.
   * @note Zoom levels are automatically sorted according to their scale factors.
   */
  TBbool InsertZoomScale(TBfloat inScale, TBuint16 & outZoomIndex);
  
  /**
   * Changes the scale factor of an existing zoom level.
   * @param inZoomIndex The zoom level index.
   * @param inScale The new scale factor.
   * @return The new index of the changed zoom level.
   * @note Zoom levels are automatically sorted according to their scale factors.
   */
  TBuint16 SetZoomScale(TBuint16 inZoomIndex, TBfloat inScale);

  /**
   * Removes and destroys the specified zoom level.
   * @param inZoomIndex The index of the zoom level to remove.
   * @note This assumes that \a inZoomIndex < GetZoomLevels()
   */
  void RemoveZoomScale (TBuint16 inZoomIndex);
  //@}
 
  /**
   * @name Raster images Management
   */
  //@{
  /**
   * Returns all the raster images attached to the specified zoom level.
   * You can also use the returned vector to add or remove images.
   * @param inZoomIndex The zoom level index.
   * @return A vector of TB_IMAGE structures.
   * @warning The returned vector must not be deleted by the caller !
   */
  CBVector * GetImages(TBuint16 inZoomIndex) const;
  //@}


  /**
   * @name Class & Style Properties
   */
  //@{
  /**
   * \enum EB_PROP_MASK
   * A set of bit flags that indicate the properties to get or set.
   */
  enum EB_PROP_MASK {
    MIN_SCALE  = 1, //!< Specifies the minimum scale validity property. 
    MAX_SCALE  = 2, //!< Specifies the maximum scale validity property. 
    VISIBILITY = 4, //!< Specifies the visibility property.
    NAME       = 8  //!< Specifies the name property related to a class of objects.
  };

  /**
   * @struct TB_CLASS_PROPERTIES
   * This structure defines the properties available at a class level. 
   * These parameters can be considered as global for all styles defined within a class.
   * (See #GetClassProperties and #SetClassProperties methods).
   */
  struct TB_CLASS_PROPERTIES {
    TBfloat        mMinScale;   //!< Minimum scale factor that determines the class visibility (0.f indicates that there is no minimum scale).
    TBfloat        mMaxScale;   //!< Maximum scale factor that determines the class visibility (0.f indicates that there is no maximum scale).
    TBbool         mVisibility; //!< The global visibility flag used to show or hide all elements of a class.
    const TBint8 * mName;       //!< The name of the class (if any).
    TBuint8        mMask;       //!< Array of flags that indicate which properties are to be retrieved or modified (See #EB_PROP_MASK).
  };

  /**
   * This method allows you to retrieve class properties according to the specified bit flags 
   * (see TB_CLASS_PROPERTIES.mMask) and Class ID.
   * @param inClassID The class identifier.
   * @param ioClassProp Specifies the properties to get (See CBGraphicChart::TB_CLASS_PROPERTIES).
   * @return \c false if the specified class does not exist, \c true otherwise.
   */
  TBbool GetClassProperties(TBuint32 inClassID, TB_CLASS_PROPERTIES & ioClassProp) const;
 
  /**
   * This method allows you to set class properties according to the specified bit flags 
   * (see TB_CLASS_PROPERTIES.mMask) and Class ID.
   * @param inClassID The class identifier.
   * @param inClassProp Specifies the properties to set (See CBGraphicChart::TB_CLASS_PROPERTIES)
   * @return \c false if the specified class does not exist, \c true otherwise.
   */
  TBbool SetClassProperties(TBuint32 inClassID, const TB_CLASS_PROPERTIES & inClassProp);   

  /**
   * @struct TB_STYLE_PROPERTIES
   * This structure defines the properties related to a style definition associated with a 
   * specific type of geometric forms.
   * (See #GetStyleProperties and #SetStyleProperties methods).
   * @note This structure is implemented as a single linked-list because several styles 
   * might be defined depending on the scale range validity.
   */
  struct TB_STYLE_PROPERTIES {
    TB_STYLE_PROPERTIES(void);
    ~TB_STYLE_PROPERTIES(void);
    TBfloat               mMinScale;   //!< Minimum scale from which this style is valid (0.f indicates there is no minimum scale).
    TBfloat               mMaxScale;   //!< Maximum scale under which this style is valid (0.f indicates there is no maximum scale).
    TB_STYLE_PROPERTIES * mNext;       //!< The next style properties (if any) or \c null.
    TBbool                mVisibility; //!< The visibility flag.
    TBuint8               mMask;       //!< Array of flags that indicate which properties are to be retrieved or modified (See #EB_PROP_MASK).
  };
  
  /**
   * This method allows you to retrieve style properties according to the specified bit flags 
   * (see TB_STYLE_PROPERTIES.mMask)
   * @param inClassID The class identifier.
   * @param inGeoType The type of geometric forms.
   * @param ioStyleProp Specifies the properties to get (See CBGraphicChart::TB_STYLE_PROPERTIES).
   * @return \c false if the specified style does not exist, \c true otherwise.
   */
  TBbool GetStyleProperties(TBuint32              inClassID, 
                            EB_GEOTYPE            inGeoType, 
                            TB_STYLE_PROPERTIES & ioStyleProp) const;

  /**
   * This method allows you to set style properties according to the specified bit flags 
   * (see TB_STYLE_PROPERTIES.mMask)
   * @param inClassID The class identifier.
   * @param inGeoType The type of geometric forms.
   * @param inStyleProp Specifies the properties to set (See CBGraphicChart::TB_STYLE_PROPERTIES).
   * @return \c false if the specified style does not exist, \c true otherwise.
   */
  TBbool SetStyleProperties(TBuint32                    inClassID, 
                            EB_GEOTYPE                  inGeoType, 
                            const TB_STYLE_PROPERTIES & inStyleProp);   

  //@}

  /**
   * @name SVS Graphic Chart IO methods
   */
  //@{

#if !defined(_BDISABLE_XML_SUPPORT)
  /**
   * Constructs a SVS graphic chart from an XML file descrition 
   * @param inXMLFileName The name of the XML file to load.
   * @param inStrictMode If \c true, this method returns immediately if an error occurs   
   * while loading an external reference (i.e image not found). In this case, the current
   * style definition is skipped and the process continues.
   * @param inImgOptim The image optimization to use (See #CBImage::EB_OPTIM)
   * @return \c true if the XML chart description was successfully loaded, \c false otherwise.
   * In case of error, you can call the #GetLastError method to obtain more details.
   */
  TBbool LoadXMLDescription(const TBchar * inXMLFileName, TBbool inStrictMode = true, CBImage::EB_OPTIM inImgOptim = CBImage::DEFAULT_OPTIM);

  /**
   * Saves the content of the current SVS graphic chart as an XML file descrition. 
   * @param inXMLFileName The name of the destination file.
   * @param inVersion The graphic chart version.
   * @return \c true if the XML chart description was successfully saved, \c false otherwise.
   * In case of error, you can call the #GetLastError method to obtain more details.
   */
  TBbool SaveAsXML(const TBchar * inXMLFileName, EB_CHART_VERSION inVersion = CHART_V_LAST);
#endif

  /**
   * Constructs a SVS graphic chart from a binary file descrition 
   * @param inFileName The name of the binary file to load (extension '.cht')
   * @param inStrictMode If \c true, this method returns immediately if an error occurs
   * while loading an external reference (i.e image not found). In this case, the current
   * style definition is skipped and the process continues.
   * @param inImgOptim The image optimization to use (See #CBImage::EB_OPTIM)
   * @return \c true if the binary chart description was successfully loaded, \c false otherwise.
   * In case of error, you can call the #GetLastError method to obtain more details.
   */
  TBbool LoadBinaryDescription(const TBchar * inFileName, TBbool inStrictMode = true, CBImage::EB_OPTIM inImgOptim = CBImage::DEFAULT_OPTIM);

#if !defined(_WIN32_WCE)
  /**
   * Saves the content of the current SVS graphic chart as a binary file descrition. 
   * @param inFileName The name of the destination file.
   * @param inVersion The graphic chart version.
   * @return \c true if the binary chart description was successfully saved, \c false otherwise.
   * In case of error, you can call the #GetLastError method to obtain more details.
   */
  TBbool SaveAsBinary(const TBchar * inFileName, EB_CHART_VERSION inVersion = CHART_V_LAST);
#endif

  /**
   * Returns the last error message resulting from an IO operation.
   * @return The last error message resulting from an IO operation.
   */
  const TBint8 * GetLastError(void) const;
  //@}

  /**
   * \internal
   */
  inline CBChartImp * GetChartImp(void) const { return mChartImp; }

  static EB_GEOTYPE     StringToGeoType(const TBint8 * inFormTypeStr);
  static const TBint8 * GeoTypeToString(EB_GEOTYPE inType);

protected:

  // Disable copy
  CBGraphicChart (const CBGraphicChart&);
  CBGraphicChart & operator=(const CBGraphicChart&);

private:

  CBChartImp * mChartImp;
};



#endif /* _CBGRAPHIC_CHART_H_ */
