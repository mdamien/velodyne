/*==========================================================  (-*- C++ -*-)
 *
 * @file BTypes.h
 * 
 * @version  $Id: BTypes.h,v 1.58 2006/06/19 11:02:08 wkunkel Exp $
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2005 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

/*!
  @file BTypes.h
	Definition of types, structures, unions and enums used in SDK.
*/

#ifndef __BTYPES_H__
#define __BTYPES_H__

#include "BPlatforms.h"

#ifndef NULL
# define NULL    0
#endif

typedef void *         TBany;
typedef bool           TBbool;
typedef char           TBint8;
typedef unsigned char  TBuint8;
typedef short          TBint16;
typedef unsigned short TBuint16;
typedef long           TBint32;
typedef unsigned long  TBuint32;
typedef float          TBfloat;
typedef double         TBdouble;

#if defined(_WIN32)
typedef          __int64 TBint64;
typedef unsigned __int64 TBuint64;
#else
typedef          long long TBint64;
typedef unsigned long long TBuint64;
#endif

#if defined(_WIN32)
#  include <TCHAR.h>
  /**
   * \typedef TBchar
   * The TBchar type can used to describe ANSI, MBCS, or Unicode strings (i.e Win32 TCHAR type).
   */
   typedef _TCHAR  TBchar;
   typedef wchar_t TBwchar;
#else /* !_WIN32 */
#  include <wchar.h>
   typedef wchar_t TBwchar;
#  if defined(_UNICODE)
     typedef TBwchar TBchar;
     #define __T(x)  L ## x
#  else /* !_UNICODE */
     typedef TBint8 TBchar;
     #define __T(x)  x
#  endif 
   // Generic text macros to be used with string literals and character constants
#  define _T(x)       __T(x)
#  define _TEXT(x)    __T(x)
#endif


#define KB_SDK_VERSION_MAJOR      0x01      //!< The major version number of the SDK
#define KB_SDK_VERSION_MINOR      0x0A      //!< The minor version number of the SDK
#define KB_SDK_VERSION_REVISION   0x00      //!< The revision version number of the SDK
#define KB_SDK_VERSION_DOTTED     "1.10.0";  //!< The version string like "1.2.3"

/**
 * The version number of the SDK (stored on 3 bytes).
 */
#define KB_SDK_VERSION_NUMBER  ((KB_SDK_VERSION_MAJOR << 16) | (KB_SDK_VERSION_MINOR << 8) | KB_SDK_VERSION_REVISION)

/**
 * \internal 
 */
extern "C" BSVS_EXPORT TBbool BCheckSDKVersion(int inVersion);
extern "C" BSVS_EXPORT int    BGetSDKVersion(void);

/**
 * An helper Macro that checks whether the SIV SDK version in use is compatible with
 * the version the software has been compiled against (Only the major and minor
 * version numbers are compared to).
 */
#define B_CHECK_SDK_VERSION BCheckSDKVersion(KB_SDK_VERSION_NUMBER)

/**
 * An helper Macro that returns the full version number of the SDK.
 */
#define B_SDK_VERSION BGetSDKVersion()

/**
 * \internal
 * @struct TB_2D_BITSIZE
 */
typedef struct {
  TBuint8 x;       //!< Number of bits for \c x component
  TBuint8 y;       //!< Number of bits for \c y component
} TB_2D_BITSIZE;

/**
 * \internal
 * @struct TB_3D_BITSIZE
 */
typedef struct {
  TBuint8 x;       //!< Number of bits for \c x component
  TBuint8 y;       //!< Number of bits for \c y component
  TBuint8 z;       //!< Number of bits for \c z component
} TB_3D_BITSIZE;

/**
 * \internal
 * @union TB_BITSIZE
 */
typedef union {
  TB_2D_BITSIZE s2;   //!< Number of bits for 2D point or vector
  TB_3D_BITSIZE s3;   //!< Number of bits for 3D point or vector
} TB_BITSIZE;

/**
 * \internal
 * @union TB_32
 * A union that represents a 32 bits integer signed or unsigned.
 */
typedef union {
  TBint32  s;   //!< Signed 32 bits integer
  TBuint32 u;   //!< unsigned 32 bits integer
} TB_32;

/**
 * @struct TB_2D_POINT
 * A structure that represents \e screen coordinates of a 2D point.
 */
typedef struct {
  TBint16       x;  //!< \c x coordinate
  TBint16       y;  //!< \c y coordinate
} TB_2D_POINT;

/**
 * @struct TB_2D_LONGPOINT
 * A structure that represents coordinates of a 2D point.
 */
typedef struct {
  TBint32       x;  //!< \c x coordinate
  TBint32       y;  //!< \c y coordinate
} TB_2D_LONGPOINT;

/**
 * @struct TB_2D_DBLPOINT
 * A structure that represents coordinates of a 2D point in double precision.
 * @since 1.8.0 Creation
 */
typedef struct {
  TBdouble      x;  //!< \c x coordinate in double precision.
  TBdouble      y;  //!< \c y coordinate in double precision.
} TB_2D_DBLPOINT;

/**
 * @struct TB_3D_DBLPOINT
 * A structure that represents coordinates of a 3D point in double precision.
 * @since 1.8.0 Creation
 */
typedef struct {
  TBdouble      x;  //!< \c x coordinate in double precision.
  TBdouble      y;  //!< \c y coordinate in double precision.
  TBdouble      z;  //!< \c z coordinate in double precision.
} TB_3D_DBLPOINT;

/**
 * @struct TB_3D_LONGPOINT
 * A structure that represents coordinates of a 3D point.
 */
typedef struct {
  TBint32       x;    //!< \c x coordinate
  TBint32       y;    //!< \c y coordinate
  TBint32       z;    //!< \c z coordinate
} TB_3D_LONGPOINT;

/**
 * @union TB_LONGPOINT
 * A union that represents coordinates of a 2D or 3D point.
 */
typedef union {
  TB_2D_LONGPOINT p2;   //!< 2D point
  TB_3D_LONGPOINT p3;   //!< 3D point
} TB_LONGPOINT;

/**
 * \internal
 * @struct TB_RENDERPOINT
 * A structure that represents a render point : 2D coordinates + index of this point in a polygon or a polyline.
 */
typedef struct {
  TBuint32         index;
  TB_2D_LONGPOINT  p;
} TB_RENDERPOINT;

/**
 * \internal
 * @enum EB_ORDER
 * An enum that defines an order of an attribute or a point in CBCursor callbacks.
 */
typedef enum {
  EB_FIRST_FIRST = 0x1,
  EB_FIRST       = 0x2,
  EB_PROCESS     = 0x4,
  EB_LAST        = 0x8,
  EB_LAST_LAST   = 0x10
} EB_ORDER;


/**
 * @struct TB_2D_SIZE
 * A structure that represents the width and height of a rectangle. 
 */
typedef struct {
  TBint32   w;    //!< Specifies the rectangle's width. 
  TBint32   h;    //!< Specifies the rectangle's height. 
} TB_2D_SIZE;


/**
 * @struct TB_2D_RECT
 * A structure that represents \e screen coordinates of a 2D rectangle with horizontal and vertical sides.
 */
typedef struct {
  TB_2D_POINT     min;  //<! Coordinates of rectangle's corner with minimal values in \c x and \c y
  TB_2D_POINT     max;  //<! Coordinates of rectangle's corner with maximal values in \c x and \c y
} TB_2D_RECT;

/**
 * @struct TB_2D_LONGRECT
 * A structure that represents coordinates of a 2D rectangle with horizontal and vertical sides.
 */
typedef struct {
  TB_2D_LONGPOINT min;  //<! Coordinates of rectangle's corner with minimal values in \c x and \c y
  TB_2D_LONGPOINT max;  //<! Coordinates of rectangle's corner with maximal values in \c x and \c y
} TB_2D_LONGRECT;

/**
 * @struct TB_3D_LONGRECT
 * A structure that represents coordinates of a 3D rectangle with horizontal and vertical sides.
 */
typedef struct {
  TB_3D_LONGPOINT min;  //<! Coordinates of rectangle's corner with minimal values in \c x, \c y and \c z
  TB_3D_LONGPOINT max;  //<! Coordinates of rectangle's corner with maximal values in \c x, \c y and \c z
} TB_3D_LONGRECT;

/**
 * @union TB_LONGRECT
 * A union that represents coordinates of a 2D or 3D rectangle with horizontal and vertical sides.
 */
typedef union {
  TB_2D_LONGRECT  rect2;   //<! 2D rectangle
  TB_3D_LONGRECT  rect3;   //<! 3D rectangle
} TB_LONGRECT; 

/**
 * @struct TB_2D_DELTAPOINT
 * A structure that represents coordinates of a 2D vector.
 */
typedef struct {
  TBint16   dx;    //!< \c x component
  TBint16   dy;    //!< \c y component
} TB_2D_DELTAPOINT;

/**
 * @struct TB_2D_FORM
 * A structure that represents geometry of a 2D polyline (type #EB_GEOTYPE_OPEN) or
 * a 2D polygon (type #EB_GEOTYPE_CLOSED).
 * Polylines and polygons are described by an initial point and an array of vectors.
 * @note For polygons, last vector (between last point and first point) is implicit.
 */
typedef struct {
  TB_2D_LONGPOINT    initPoint;   //!< Initial point
  TBuint32           nbIntPoints; //!< Number of vectors
  TB_2D_DELTAPOINT * intPoints;   //!< Array of vectors
} TB_2D_FORM;

/**
 * @struct TB_3D_DELTAPOINT
 * A structure that represents coordinates of a 3D vector.
 */
typedef struct {
  TBint16   dx;    //!< \c x component
  TBint16   dy;    //!< \c y component
  TBint16   dz;    //!< \c z component
} TB_3D_DELTAPOINT;

/**
 * @struct TB_3D_FORM
 * A structure that represents geometry of a 3D polyline (type #EB_GEOTYPE_OPEN) or
 * a 3D polygon (type #EB_GEOTYPE_CLOSED).
 * Polylines and polygons are described by an initial point and an array of vectors.
 * @note For polygons, last vector (between last point and first point) is implicit.
 */
typedef struct {
  TB_3D_LONGPOINT    initPoint;   //!< Initial point
  TBuint32           nbIntPoints; //!< Number of vectors
  TB_3D_DELTAPOINT * intPoints;   //!< Array of vectors
} TB_3D_FORM;

/**
 * @struct TB_2D_ARC
 * A structure that represents geometry of a 2D elliptic arc (type #EB_GEOTYPE_ARC).
 */
typedef struct {
  TBint16          sAngle; //!< Start angle in 16th of degrees, origin at 3 o'clock
  TBint16          dAngle; //!< Delta angle in 16th of degrees (trigonometric orientation)
  TB_2D_LONGRECT   rect;   //!< Bounding rectangle
} TB_2D_ARC;

/**
 * @struct TB_3D_ARC
 * A structure that represents geometry of a 3D elliptic arc (type #EB_GEOTYPE_ARC).
 */
typedef struct {
  TBint16          sAngle; //!< Start angle in 16th of degrees, origin at 3 o'clock
  TBint16          dAngle; //!< Delta angle in 16th of degrees (trigonometric orientation)
  TB_3D_LONGRECT   rect;   //!< Bounding rectangle
} TB_3D_ARC;

/**
 * @struct TB_2D_CIRCLE
 * A structure that represents geometry of a circle. <b> not yet implemented </b>
 */
typedef struct {
  TBuint32         radius; //!< Circle's radius
  TB_2D_LONGPOINT  center; //!< Circle's center
} TB_2D_CIRCLE;

/**
 * @struct TB_3D_CIRCLE
 * A structure that represents geometry of a sphere. <b> not yet implemented </b>
 */
typedef struct {
  TBuint32         radius; //!< Sphere's radius
  TB_3D_LONGPOINT  center; //!< Sphere's center
} TB_3D_CIRCLE;

/**
 * @typedef EB_ATTTYPE
 * A type that is used for describing an attribute type.
 * Possible values are :
 * \arg #EB_ATTTYPE_KEY
 * \arg #EB_ATTTYPE_LABEL
 * \arg #EB_ATTTYPE_SIGNED
 * \arg #EB_ATTTYPE_UNSIGNED
 * \arg #EB_ATTTYPE_FLOAT
 * \arg #EB_ATTTYPE_ALPHA
 * \arg #EB_ATTTYPE_META
 * \arg #EB_ATTTYPE_USER_ALPHA
 * \arg #EB_ATTTYPE_USER_META
 * \arg #EB_ATTTYPE_USER_ANY
 */
typedef TBuint16 EB_ATTTYPE;
#define EB_ATTTYPE_KEY        0  //!< Defines a numerical key which may be used for a key/label relation (field \c uVal of #TB_ATTTYPE)
#define EB_ATTTYPE_LABEL      1  //!< Defines a numerical label which may be used for a key/label relation (field \c uVal of #TB_ATTTYPE)
#define EB_ATTTYPE_SIGNED     2  //!< Defines a 32 bits signed integer (field \c sVal of #TB_ATTTYPE)
#define EB_ATTTYPE_UNSIGNED   3  //!< Defines a 32 bits unsigned integer (field \c uVal of #TB_ATTTYPE)
#define EB_ATTTYPE_FLOAT      4  //!< Defines a float value (field \c fVal of #TB_ATTTYPE)
#define EB_ATTTYPE_ALPHA      5  //!< Defines a string (field \c cVal of #TB_ATTTYPE)
#define EB_ATTTYPE_META       6  //!< Defines a meta attribute, see #TB_META_ATT (field \c mVal of #TB_ATTTYPE)
#define EB_ATTTYPE_USER_ALPHA 7  //!< Defines a user's string : it is up to user to destroy string (field \c cVal of #TB_ATTTYPE)
#define EB_ATTTYPE_USER_META  8  //!< Defines a meta attribute (see structure #TB_META_ATT) : it is up to user to destroy structure (field \c mVal of #TB_ATTTYPE)
#define EB_ATTTYPE_USER_ANY   9  //!< Defines a pointer on anything : user is owner of pointed value. This type of attribute cannot be saved in an SVS file. (field \c aVal of #TB_ATTTYPE)

/**
 * @struct TB_META_ATT
 * A structure that represents #EB_ATTTYPE_META or #EB_ATTTYPE_USER_META attribute.
 * The field \c data is a pointer on a so called meta data which can be of any type or structure.
 * The field \c size is the size in bytes of meta data.
 */
typedef struct {
  TBuint32 size;  //!< Size in bytes of meta data
  TBany    data;  //!< Pointer on meta data
} TB_META_ATT;

/**
 * @union TB_ATTTYPE
 * A union that defines all possible types or structure an SVS object's attribute
 * can be defined by.
 */
typedef union {
  TBuint32      uVal;  //!< #EB_ATTTYPE_KEY or #EB_ATTTYPE_LABEL or #EB_ATTTYPE_UNSIGNED
  TBint32       sVal;  //!< #EB_ATTTYPE_SIGNED
  TBfloat       fVal;  //!< #EB_ATTTYPE_FLOAT
  TBint8 *      cVal;  //!< #EB_ATTTYPE_ALPHA or #EB_ATTTYPE_USER_ALPHA
  TB_META_ATT * mVal;  //!< #EB_ATTTYPE_META or #EB_ATTTYPE_USER_META
  TBany         aVal;  //!< #EB_ATTTYPE_USER_ANY
} TB_ATTTYPE;

/**
 * @struct TB_ATTRIBUTE
 * A structure that represents an SVS object's semantic definition.
 * An SVS object is composed of a set of attributes. Each attribute
 * is defined by its type (see #EB_ATTTYPE), its value and its numerical code.\n
 * An attributes code must be used as a definition of attribute's 'meaning' :\n
 * Two attributes with same code have same signification. For example, a code may
 * be reserved for defining objects' names.
 * @note Attributes codes and types are related : two attributes of same code \e must have same type !
 * However, each class of an SVS has his own attributes' definition, so this restriction
 * applies only for attributes of a same class.
 */
typedef struct TB_ATTRIBUTE {
  EB_ATTTYPE type;   //!< Attribute's type (see #EB_ATTTYPE)
  TBuint16   code;   //!< Attribute's code
  TB_ATTTYPE u;      //!< Attribute's value (see #TB_ATTTYPE)
} TB_ATTRIBUTE;

typedef struct TB_GEOMETRY TB_GEOMETRY;


#if defined (_WIN32)
  // undef Windows macros defined in DLGS.H
# undef   frm2
# undef   frm3
#endif

/**
 * @union TB_GEOTYPE
 * A union that defines all possible structures an SVS object's geometry
 * can be defined by.
 */
typedef union {
  TB_2D_LONGPOINT * pnt2;   //!< 2D point (type #EB_GEOTYPE_POINT)
  TB_3D_LONGPOINT * pnt3;   //!< 3D point (type #EB_GEOTYPE_POINT)
  TB_2D_FORM *      frm2;   //!< 2D closed (type #EB_GEOTYPE_CLOSED) or 2D open form (type #EB_GEOTYPE_OPEN)
  TB_3D_FORM *      frm3;   //!< 3D closed (type #EB_GEOTYPE_CLOSED) or 3D open form (type #EB_GEOTYPE_OPEN)
  TB_2D_ARC *       arc2;   //!< 2D elliptic arc (type #EB_GEOTYPE_ARC)
  TB_3D_ARC *       arc3;   //!< 3D elliptic arc (type #EB_GEOTYPE_ARC)
  TB_2D_CIRCLE *    cir2;   //!< Circle (type #EB_GEOTYPE_CIRCLE <b> Not yet implemented </b>)
  TB_3D_CIRCLE *    cir3;   //!< Sphere (type #EB_GEOTYPE_CIRCLE <b> Not yet implemented </b>)
  TB_2D_LONGRECT *  rec2;   //!< 2D rectangle (type #EB_GEOTYPE_RECTANGLE) or ellipse (type #EB_GEOTYPE_ELLIPSE)
  TB_3D_LONGRECT *  rec3;   //!< 3D rectangle (type #EB_GEOTYPE_RECTANGLE) or ellipsoide (type #EB_GEOTYPE_ELLIPSE)
  TB_GEOMETRY *     geo;    //!< 2D or 3D complex (type #EB_GEOTYPE_COMPLEX)
} TB_GEOTYPE;

/**
 * @typedef EB_GEOTYPE
 * A type that is used for describing a geometric type.
 * Possible values are :
 * \arg #EB_GEOTYPE_ABSTRACT
 * \arg #EB_GEOTYPE_CLOSED
 * \arg #EB_GEOTYPE_RECTANGLE <b> Not yet implemented </b>
 * \arg #EB_GEOTYPE_ELLIPSE
 * \arg #EB_GEOTYPE_CIRCLE <b> Not yet implemented </b>
 * \arg #EB_GEOTYPE_COMPLEX
 * \arg #EB_GEOTYPE_OPEN
 * \arg #EB_GEOTYPE_ARC
 * \arg #EB_GEOTYPE_POINT
 * \arg #EB_GEOTYPE_MAX  (for internal use)
 */
typedef TBuint16 EB_GEOTYPE;
#define EB_GEOTYPE_ABSTRACT  0  //!< No geometry
#define EB_GEOTYPE_CLOSED    1  //!< Defines a (possibly multi) polygon (field \c frm2 or \c frm3 of #TB_GEOTYPE)
#define EB_GEOTYPE_RECTANGLE 2  //!< Defines a (possibly multi) rectangle (field \c rec2 or \c rec3 of #TB_GEOTYPE).
#define EB_GEOTYPE_ELLIPSE   3  //!< Defines a (possibly multi) ellipse (field \c rec2 or \c rec3 of #TB_GEOTYPE
#define EB_GEOTYPE_CIRCLE    4  //!< Defines a (possibly multi) circle (field \c cir2 or \c cir3 of #TB_GEOTYPE). <b> Not yet implemented </b>
#define EB_GEOTYPE_COMPLEX   5  //!< Defines a complex : any combination of all other geometric types (field \c geo of #TB_GEOTYPE)
#define EB_GEOTYPE_OPEN      6  //!< Defines a (possibly multi) polyline (field \c frm2 or \c frm3 of #TB_GEOTYPE)
#define EB_GEOTYPE_ARC       7  //!< Defines a (possibly multi) elliptic arc (field \c arc2 or \c arc3 of #TB_GEOTYPE)
#define EB_GEOTYPE_POINT     8  //!< Defines a (possibly multi) point (field \c pnt2 or \c pnt3 of #TB_GEOTYPE)
#define EB_GEOTYPE_MAX       9  //!< Internal use

/**
 * @struct TB_GEOMETRY
 * A structure that represents an SVS object's geometric definition.
 */
typedef struct TB_GEOMETRY {  
  EB_GEOTYPE type;     //!< Geometric type
  TBuint16   nbForm;   //!< Number of geometric entities
  TB_GEOTYPE g;        //!< Geometric definition (see #TB_GEOTYPE)	
} TB_GEOMETRY;

/**
 * @struct TB_EXTERN_OBJECT
 * A structure that represents an SVS object with geometric and semantic definition
 */
typedef struct TB_EXTERN_OBJECT {
  TBuint16       nbAtt;   //!< Number of attributes
  TB_ATTRIBUTE * att;     //!< Array of attributes (see #TB_ATTRIBUTE)
  TB_GEOMETRY    geo;     //!< Geometry (see #TB_GEOMETRY)
} TB_EXTERN_OBJECT;


/** 
 * \mainpage SVS (Scalable Vector Storage)
 *
 * An SVS file contains the <b>geometric</b> and <b>semantic</b> description of a set of vector objects.
 *
 * \section svsclasses SVS Classes
 * 
 * Each geometric or abstract object in an SVS file belongs to a class. A class is defined by 
 * an numerical value (Class ID) and a geometric type (every object in a same class has a unique 
 * geometric type - see \ref geodef). Objects classes are sorted by increasing Class IDs and by 
 * geometric type which defines an order for parsing objects in a SVS. If several SVS are 
 * simultaneously parsed, objects of smaller Class IDs will be parsed before objects of greater 
 * Class IDs independently of which SVS they belong to. 
 * Inside a same class, objects are ordered by decreasing size.
 * @note The rendering module for instance uses this order for displaying objects on a screen.
 *
 * \section geodef Geometric objects definition
 *
 * Geometry is defined in 2 dimensions (the SVS format supports 3D but not the SIV SDK yet).
 * There are 8 geometric types :
 *
 * - #EB_GEOTYPE_ABSTRACT :\n
 *   These objects have no geometric definition (they only have a semantic description, see \ref objsemantic)
 *
 * - #EB_GEOTYPE_CLOSED :\n
 *   These objects represent polygons (an object can be constitued of several polygons).
 *
 * - #EB_GEOTYPE_RECTANGLE :\n
 *   These objects represent simple rectangles (an object can be constitued of several rectangles).
 *
 * - #EB_GEOTYPE_ELLIPSE :\n
 *   These objects represent ellipses (an object can be constitued of several ellipses).
 *
 * - #EB_GEOTYPE_COMPLEX :\n
 *   These objects represent any combination of all other geometric types.
 *
 * - #EB_GEOTYPE_OPEN :\n
 *   These objects represent polylines (an object can be constitued of several polylines).
 *
 * - #EB_GEOTYPE_ARC * :\n
 *   These objects represent elliptic arcs (an object can be constitued of several arcs).
 *
 * - #EB_GEOTYPE_POINT :\n
 *   These objects represent points (an object can be constitued of several points).
 * 
 *  ( * These types are not yet supported by the rendering module).
 *
 * \section objsemantic Object Semantic definition
 *
 * To each object can be associated a set of semantic attributes.
 * Each attribute is composed of three fields :
 *
 *  -# Attribute's code :\n
 *   An attribute's code is a numerical value which defines the category (or meaning) 
 *   of an attribute. All attributes of same code define an information of same nature. 
 *   For instance, a code can be used to define names of objects (See #KB_ATT_NAME).
 *  -# Attribute's type :
 *   An attribute's type describes the nature of the information : numerical value, string, etc.
 *   There are 10 possible types :
 *    - #EB_ATTTYPE_KEY :\n
 *      This type defines an numerical attribute interpreted as numerical key used as the 
 *      object's ID. One object may have only one key and its value must be unique.
 *    - #EB_ATTTYPE_LABEL :\n
 *      This type defines an numerical attribute which value is the value of another 
 *      object's key. This attribute type is used for defining relations between objetcs.
 *    - #EB_ATTTYPE_SIGNED :\n
 *      This type defines a signed integer attribute (4 bytes).
 *    - #EB_ATTTYPE_UNSIGNED :\n
 *      This type defines an unsigned integer attribute (4 bytes).
 *    - #EB_ATTTYPE_FLOAT :\n
 *      This type defines a float value attribute (4 bytes).
 *    - #EB_ATTTYPE_ALPHA :\n
 *      This type defines a string attribute.
 *    - #EB_ATTTYPE_USER_ALPHA :\n
 *      This type defines a string attribute. It is identical to #EB_ATTTYPE_ALPHA. 
 *      The only difference is that the user is the owner of the string which means that 
 *      he is responsible for destroying it. Therefore, this type of attribute is normally 
 *      associated to an object created by the user (dynamic object).
 *    - #EB_ATTTYPE_META :\n
 *      This type defines a structured attribute of type #TB_META_ATT (a buffer and buffer's size 
 *      in bytes). This type may be used, for example, to associate a bitmap to an object.
 *    - #EB_ATTTYPE_USER_META :\n
 *      This type defines a structured attribute of type #TB_META_ATT (a buffer and buffer's size 
 *      in bytes). It is identical to #EB_ATTTYPE_META. The only difference is that the user is 
 *      the owner of the buffer which means that he is responsible for destroying it. 
 *      Therefore, this type of attribute is normally associated to an object created by the user
 *      (dynamic object).
 *    - #EB_ATTTYPE_USER_ANY :\n
 *      This type defines a user attribute (interpreted as a void *). It is therefore normally 
 *      associated to an object created by the user (dynamic object) and it cannot be saved in an SVS file.
 *  -# Attribute's value :\n
 *   Attribute's value is the information itself which meaning and type depends on attribute's code and type.
 * 
 * @warning Inside a same class, two attributes of same code must have same type.
 *
 */

#endif // __BTYPES_H__
