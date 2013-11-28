/*==========================================================  (-*- C++ -*-)
 *
 * @file CBRouteSheet.h
 * 
 * @version  $Id: CBRouteSheet.h,v 1.38 2006/07/12 17:51:20 dlabrousse Exp $ 
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2004 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBROUTESHEET_H__
#define __CBROUTESHEET_H__

/**
 * @file CBRouteSheet.h
 * CBRouteSheet class definition and list of possible values for route manoeuvres 
 * and route special instructions (see CBRouteSheet::TB_INSTRUCTION).
 */

#include "CBPlanner.h"
#include "BCartoConst.h"

/**
 * @name Route manoeuvre constants
 */
//@{
#define KB_MANOEUVRE_STRAIGHT     0  /*!< Straight : -10° < a < 10°, a = angle with azimuth */
#define KB_MANOEUVRE_SLIGHT_LEFT  1  /*!< Slight left turn : -60° < a <= -10°, a = angle with azimuth */
#define KB_MANOEUVRE_LEFT         2  /*!< Left turn : -120° < a <= -60°, a = angle with azimuth */
#define KB_MANOEUVRE_SHARP_LEFT   3  /*!< Sharp left turn : -170° < a <= -120°, a = angle with azimuth */
#define KB_MANOEUVRE_U_TURN       4  /*!< U turn : a >= 170° or a <= -170°, a = angle with azimuth */
#define KB_MANOEUVRE_SHARP_RIGHT  5  /*!< Sharp right turn : 120° <= a < 170°, a = angle with azimuth */
#define KB_MANOEUVRE_RIGHT        6  /*!< Right turn : 60° <= a < 120°, a = angle with azimuth */
#define KB_MANOEUVRE_SLIGHT_RIGHT 7  /*!< Slight right turn : 10° <= a < 60°, a = angle with azimuth */
//@}
/**
 * @name Route special instructions
 */
//@{
#define KB_INSTRUCTION_FOLLOW           0  /*!< No special instruction */
#define KB_INSTRUCTION_FOLLOW_SIGN      1  /*!< Follow a sign post */
#define KB_INSTRUCTION_ENTER_MOTORWAY   2  /*!< Enter a motorway */
#define KB_INSTRUCTION_EXIT_MOTORWAY    3  /*!< Exit a motorway */
#define KB_INSTRUCTION_ENTER_ROUNDABOUT 4  /*!< Enter a roundabout */
#define KB_INSTRUCTION_EXIT_ROUNDABOUT  5  /*!< Exit a roundabout */
#define KB_INSTRUCTION_TAKE_FERRY       6  /*!< Take a ferry */
#define KB_INSTRUCTION_LEAVE_FERRY      7  /*!< Leave a ferry */
#define KB_INSTRUCTION_TAKE_RAMP        8  /*!< Take ramp / slip road */
#define KB_INSTRUCTION_STOP             9  /*!< Stop (last instruction of a route sheet) */
//@}

class CBGraph;
class CBForm2D;
class CBForm3D;
class CBBitStream;
class CBPlannerImp;
class CBRoute;
class CBVector;

struct TB_CROSS_DATA;

/**
 * @class CBRouteSheet
 *
 * @brief This class defines a list of instructions called 'route sheet'.
 *
 * CBRouteSheet is a class that defines a list of instructions called 'route sheet'.
 * A route of \a n route elements provided by #CBPlanner (see #CBRoute::TB_ROUTE_ELEM) is used
 * to build an array \a m route sections (\a m <= \a n).
 * For each route section an instruction indicates what to do to go to next route section.
 * Each instruction is composed of (see CBRouteSheet::TB_INSTRUCTION) :
 * \arg name of current route section
 * \arg name of next route section (or name of sign post to follow)
 * \arg a length information (length of current route section in meters)
 * \arg a time information (time of current route section in seconds)
 * \arg a manoeuvre instruction (see #KB_MANOEUVRE_STRAIGHT ...)
 * \arg a 'special' instruction (see #KB_INSTRUCTION_FOLLOW ...))
 * \arg an exit instruction (only for entering roundabouts - repeated for exiting roundabouts)
 * \arg an index in route's CBRoute::TB_ROUTE_ELEM array of first form of this instruction
 * \arg a position of manoeuvre from current instruction to next instruction
 *
 * Examples :
 *
 * \arg fromName = "BOULEVARD SAINT-GERMAIN"
 * \arg toName   = "RUE DES SAINTS-PERES"
 * \arg length = 420
 * \arg time   = 45
 * \arg manoeuvre   = #KB_MANOEUVRE_RIGHT
 * \arg instruction = #KB_INSTRUCTION_FOLLOW
 * \arg roundAboutExitNumber = 0
 *
 * Should be understood as :\n
 * "From BOULEVARD SAINT-GERMAIN, at 420 meters (45 seconds), turn right on RUE DES SAINTS-PERES".
 *
 * \arg fromName = "A1"
 * \arg toName   = "PARIS"
 * \arg length = 14500
 * \arg time   = 560
 * \arg manoeuvre   = #KB_MANOEUVRE_SLIGHT_RIGHT
 * \arg instruction = #KB_INSTRUCTION_FOLLOW_SIGN
 * \arg roundAboutExitNumber = 0 
 *
 * Should be understood as : "From A1, at 14.5 km (9 min 20 s), follow sign 'PARIS' (slight right turn)".
 *
 * \arg fromName = ""
 * \arg toName   = "N7"
 * \arg length = 30
 * \arg time   = 9
 * \arg manoeuvre   = #KB_MANOEUVRE_RIGHT
 * \arg instruction = #KB_INSTRUCTION_EXIT_ROUNDABOUT
 * \arg roundAboutExitNumber = 2
 *
 * Should be understood as : "From roundabout, at 30 meters (9 seconds), take 2nd exit (right turn) N7".
 *
 * Note that \a roundAboutExitNumber counts only connected road segments which have outgoing traffic flow
 *
 * Field \a angles :
 * This field (of CBRouteSheet::TB_INSTRUCTION) is used for symbolic display purpose in a navigation application.
 * It representes a vector (see #CBVector) of angles relative to incoming road segment of all out going road segments
 * at instruction's intersection.
 * Note that incoming segment is never listed among the angles (because incoming segment can be always represented by
 * a vertical segment).
 * The field \a outAngleIdx (of CBRouteSheet::TB_INSTRUCTION) gives the index in array \a angles which corresponds to next road
 * segment in route.
 * 
 * Roundabouts are processed differently : the aim is to make it possible to display a global symbolic representation
 * of a roundabout in the form of a circle and outgoing segments.
 * Whenever the field \a instruction equals #KB_INSTRUCTION_ENTER_ROUNDABOUT the list of angles corresponds to the angles
 * of every outgoing segments (ordered conter clockwise in right side driving countries and vice versa) of the roundabout
 * relative to the direction defined by the enter point in roundabout and the center of roundabout's circle.
 * This means that we assume that outgoing segments are all orthogonal to roundabout's circle which is often not the case.
 * But for symbolic display, this assumption should not be a problem.
 * The field \a outAngleIdx is than the index in vector \a angles that corresponds to roundabout's exit
 * (or -1 if route stops on the roundabout)
 * Note that for instruction #KB_INSTRUCTION_EXIT_ROUNDABOUT angles are processed as for any instruction.
 * 
 */
class BPLN_EXPORT CBRouteSheet
{
public:

	/**
	 * @struct TB_INSTRUCTION
	 * A structure that represents all available informations of a route instruction.
   * @since 1.9.0 Added bearing information 
	 */
	struct TB_INSTRUCTION {
    TBint8          bear;                 //!< -1: bear left, 1: bear right, 0: no bearing
    TBuint8         manoeuvre;            //!< Direction to follow (see #KB_MANOEUVRE_STRAIGHT ...)
	  TBuint8         instruction;          //!< Special instruction (see #KB_INSTRUCTION_FOLLOW ...)
	  TBuint8         roundAboutExitNumber; //!< Exit number of a roundabout
		TBint16         fromAngle;            //!< Angle (in degrees) between the last segment of current instruction and geographical north.
		TBint16         dAngle;               //!< Angle (in degrees) of manoeuvre from current instruction to next instruction.
	  const TBint8  * fromName;             //!< Name of current route section
	  const TBint8  * toName;               //!< Name of next route section (or name of sign post to follow)
    TBuint32        classID;              //!< ClassID in route's #TB_ROUTE_ELEM array of first form of this instruction
    TBuint32        length;               //!< Length of current route section in meters
	  TBuint32        time;                 //!< Time of current route section in seconds
		TBuint32        frmIdx;               //!< Index in route's #TB_ROUTE_ELEM array of first form of this instruction
    CBVector      * angles;               //!< An array of (TBint16) angles (in degrees) relative to incoming segment (for symbolic display purpose)
    TBint16         outAngleIdx;          //!< The index in \a angles that corresponds to the next segment in route sheet
		TB_2D_LONGPOINT p;                    //!< Position of manoeuvre from current instruction to next instruction
	};

  /**   
   * Constructs an empty route sheet.
	 * @param inLanguageCode Preferential language for objects' names (see #EB_LANGUAGE_CODE).
	 * @param setAngles Fill field \a angles in #TB_INSTRUCTION structure (default \c false)
   * @since 1.5.2 : Added inGetAngles argument.
   */
  CBRouteSheet(EB_LANGUAGE_CODE inLanguageCode = DEFAULT_LANGUAGE,
               TBbool           inGetAngles    = false);

  /**
   * Destructor.
   */
  ~CBRouteSheet(void);

  /**
   * Builds a route sheet : array of instructions (see #CBRouteSheet::TB_INSTRUCTION).
   * @param inRoute Route to build route sheet from (see #TB_ROUTE)
   */
  TBbool Build(const CBRoute * inRoute);

  /**
   * Returns number of instructions in route sheet (see #CBRouteSheet::TB_INSTRUCTION).
   * @return Number of instructions in route sheet
   */
  inline TBuint32 GetNbInstructions(void) const
	{
		return mNbInstructions;
	}

  /**
   * Returns \a inIdx -th instruction or \c NULL if \a inIdx is greater than number of instructions.
   * @param inIdx Index of instruction to return
   * @return \a inIdx -th instruction or \c NULL if \a inIdx >= mNbInstructions
   */
  inline const CBRouteSheet::TB_INSTRUCTION * GetInstruction(TBuint32 inIdx) const
	{
		return inIdx < mNbInstructions ? &mInstructions[inIdx] : NULL;
	}

  /**
   * Returns the character encoding of the route sheet.
   * @return The character encoding of the route sheet.
   * @since 1.7.0 Creation.
   * @since 1.8.0 Change scope to public.
   */
  EB_ENCODING GetEncoding(void);

private:

  TBbool Init(const CBRoute * inRoute);

  void   Reset             (TB_CROSS_DATA& data);

  TBbool SwitchGraph       (TB_CROSS_DATA& data, const CBGraph * graph);

  TBbool ExtractForms      (TB_CROSS_DATA& data, CBVector& forms);

  TBbool Instruction       (TB_CROSS_DATA& data);

  void   Update            (TB_CROSS_DATA& data);

  TBbool SetInstruction    (TB_CROSS_DATA& data);

  TBbool SetLastInstruction(TB_CROSS_DATA& data);

  TBbool CopyInstruction   (TB_CROSS_DATA& data, TBbool reset = true);

  CBForm * ExtractRoundaboutForm(TB_CROSS_DATA& data,
                                 TBuint32       nodeIdx,
                                 TBuint32&      prevFormPos,
                                 const CBSVS *& prevFormSVS,
                                 TBuint16&      outNbArcs);

  TBbool ComputeRoundaboutAngles(TB_CROSS_DATA& data);

  TBint8 * GetName(const CBForm * inFrm,
                   TBuint32       classID,
                   TBbool         sign = true) const;

  TBint16 GetAngle(const TB_2D_DELTAPOINT& inDelta1,
                   const TB_2D_DELTAPOINT& inDelta2,
                   TB_2D_LONGPOINT&        inPoint,
                   TBbool                  saveCurAngle = false);

  TBuint8 GetManoeuvre(const TB_2D_DELTAPOINT& inDelta1,
                       const TB_2D_DELTAPOINT& inDelta2);

  TBuint8 GetInstruction(const CBRoute::TB_ROUTE_ELEM * inFromElem,
                         const CBRoute::TB_ROUTE_ELEM * inToElem,
                         const TBint8                 * inToName) const;
	
private:

  TBbool                        mErr;
  TBbool                        mAngles;
  TBuint8                       mTranspShift;
	TBint16                       mCurAngle;
	TBint16                       mDAngle;
	TBuint16                      mLanguageCode;
  TBuint16                      mNbNodeAtt;
	TBuint32                      mGeoScale;
  TBuint32                      mNbInstructions;
  TB_INSTRUCTION              * mInstructions;
  CBPlannerImp                * mPlanner;
  const CBRoute               * mRoute;
  TB_ATTRIBUTE                * mNodeAtt;
  CBRoadNetwork::EB_TRANSP_MODE mTranspMode;
	TB_2D_LONGPOINT               mCurPoint;
};

#endif // __CBROUTESHEET_H__
