/*==========================================================  (-*- C++ -*-)
 *
 * @file BCartoConst.h
 * 
 * @version  $Id: BCartoConst.h,v 1.66 2006/07/26 14:59:19 dlabrousse Exp $
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2006 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file.
 * Contains internal information protected by international copyright laws
 *
 *========================================================================*/

#ifndef __BCARTOCONST_H__
#define __BCARTOCONST_H__

/*!
  @file BCartoConst.h
	This file contains all cartographic constants (Class IDs + Attribute codes)
*/

/**
 * @name Cartographic class IDs
 */
//@{
#define KB_HEADER                        0  //!< General informations 
#define KB_COUNTRY                    1111  //!< Country
#define KB_ORDRE_1_AREA               1112  //!< State, Region, etc.
#define KB_ORDRE_2_AREA               1113  //!< Unused
#define KB_ORDRE_3_AREA               1114  //!< Unused
#define KB_ORDRE_4_AREA               1115  //!< Unused
#define KB_ORDRE_5_AREA               1116  //!< Unused
#define KB_ORDRE_6_AREA               1117  //!< Unused
#define KB_ORDRE_7_AREA               1118  //!< Department, etc.
#define KB_ORDRE_8_AREA               1119  //!< City
#define KB_ORDRE_9_AREA               1120  //!< District
#define KB_POSTAL_DISTRICT            1150  //!< Postal district
#define KB_ISLAND                     1200  //!< Island
#define KB_BUILT_UP_AREA              1300  //!< Main urban areas (not an administrative area)
#define KB_BUILT_UP_AREA_2            1310  //!< Secondary urban areas (not an administrative area)
#define KB_BUILT_UP_AREA_3            1320  //!< Other urban areas (not an administrative area)
#define KB_LAND_USAGE                 2000  //!< Parc/garden, industrial area, industrial harbour area
#define KB_LAND_COVERAGE              3000  //!< Woodland, moor/heathland, beach/dune/sand
#define KB_WATER_ELEMENT              3700  //!< Ocean, sea
#define KB_WATER_ELEMENT_2            3710  //!< Lac, river, etc. Main
#define KB_WATER_ELEMENT_3            3720  //!< Lac, river, etc. Secondary
#define KB_WATER_ELEMENT_4            3730  //!< Lac, river, etc. Third
#define KB_OTHER_AREAS                3800  //!< Military base, native american reserve, etc
#define KB_AIRPORT_AREA               3850  //!< Airport contour, ports
#define KB_AIRCRAFT_ROAD              3851  //!< Aircraft roads
#define KB_BUILDING                   3900  //!< Building contour
#define KB_RAILWAY_ELEMENT            3998  //!< Railway
#define KB_ROAD_ELEMENT_MIN           4000  //!< Min value for road elements (Range : 4000 - 6990)
#define KB_ROAD_FOURTH_PEDESTRIAN     4000  //!< Fourth - Pedestrian
#define KB_ROAD_FOURTH_ROUNDABOUT     4016  //!< Fourth - Roundabout
#define KB_ROAD_FOURTH_SLIPROAD       4032  //!< Fourth - Slip road
#define KB_ROAD_FOURTH                4048  //!< Fourth
#define KB_ROAD_FOURTH_MOTORWAY       4064  //!< Fourth - Motorway
#define KB_ROAD_FOURTH_FERRY          4080  //!< Fourth - Ferry
#define KB_ROAD_TERTIARY_PEDESTRIAN   4256  //!< Tertiary - Pedestrian
#define KB_ROAD_TERTIARY_ROUNDABOUT   4272  //!< Tertiary - Roundabout
#define KB_ROAD_TERTIARY_SLIPROAD     4288  //!< Tertiary - Slip road
#define KB_ROAD_TERTIARY              4304  //!< Tertiary
#define KB_ROAD_TERTIARY_MOTORWAY     4320  //!< Tertiary - Motorway
#define KB_ROAD_TERTIARY_FERRY        4336  //!< Tertiary - Ferry
#define KB_ROAD_SECONDARY_PEDESTRIAN  4512  //!< Secondary - Pedestrian
#define KB_ROAD_SECONDARY_ROUNDABOUT  4528  //!< Secondary - Roundabout
#define KB_ROAD_SECONDARY_SLIPROAD    4544  //!< Secondary - Slip road
#define KB_ROAD_SECONDARY             4560  //!< Secondary
#define KB_ROAD_SECONDARY_MOTORWAY    4576  //!< Secondary - Motorway
#define KB_ROAD_SECONDARY_FERRY       4592  //!< Secondary - Ferry
#define KB_ROAD_MAIN_PEDESTRIAN       4768  //!< Main - Pedestrian
#define KB_ROAD_MAIN_ROUNDABOUT       4784  //!< Main - Roundabout
#define KB_ROAD_MAIN_SLIPROAD         4800  //!< Main - Slip road
#define KB_ROAD_MAIN                  4816  //!< Main
#define KB_ROAD_MAIN_MOTORWAY         4832  //!< Main - Motorway
#define KB_ROAD_MAIN_FERRY            4848  //!< Main - Ferry
#define KB_ROAD_ELEMENT_MAX           6899  //!< Max value for road elements (Range : 4000 - 6899)
#define KB_ROUTE_CLASS                6900  //!< Class for dynamic route forms
#define KB_RESTRICTION                6997  //!< Restriction definitions for manoeuvres in road network
#define KB_JUNCTION                   6998  //!< Border nodes of road network
#define KB_NODE                       6999  //!< Nodes of road network
#define KB_CAPITAL                    7000  //!< National or regional capitals OR main cities (i.e. population >= 50000)
#define KB_POLICE_RADAR               7100  //!> Police radars (Not contained in default SVS datasets)
#define KB_VEHICLE_REPAIR             7310  //!< Vehicle repair facility
#define KB_PETROL_STATION             7311  //!< Petrol station
#define KB_RENT_A_CAR                 7312  //!< Rent a car facility
#define KB_PARKING_GARAGE             7313  //!< Parking garage
#define KB_HOTEL_MOTEL                7314  //!< Hotel or motel
#define KB_RESTAURANT                 7315  //!< Restaurant
#define KB_TOURIST_OFFICE             7316  //!< Tourist office
#define KB_MUSEUM                     7317  //!< Museum
#define KB_THEATRE                    7318  //!< Theatre
#define KB_CULTURAL_CENTRE            7319  //!< Cultural centre
#define KB_SPORTS_ACTIVITY            7320  //!< Sports activity
#define KB_HOSPITAL                   7321  //!< Hospital polyclinic
#define KB_POLICE_STATION             7322  //!< Police station
#define KB_CITY_HALL                  7323  //!< City hall
#define KB_POST_OFFICE                7324  //!< Post office
#define KB_PHARMACY                   7326  //!< Pharmacy
#define KB_BANK                       7328  //!< Bank
#define KB_SKI_RESORT                 7334  //!< Ski resort
#define KB_PANORAMIC_VIEW             7337  //!< Scenic / panoramic view
#define KB_SWIMMING_POOL              7338  //!< Swimming pool
#define KB_WORSHIP_PLACE              7339  //!< Place of worship
#define KB_FERRY_TERMINAL             7352  //!< Ferry terminal
#define KB_AIRLINE_ACCESS             7356  //!< Airline access
#define KB_CAMPING_GROUND             7360  //!< Camping ground
#define KB_COMMUNITY_CENTRE           7363  //!< Community centre
#define KB_EMBASSY                    7365  //!< Embassy
#define KB_FRONTIER_CROSSING          7366  //!< Frontier crossing
#define KB_GOVERNMENT_OFFICE          7367  //!< Government office
#define KB_MOTORING_ORG_OFFICE        7368  //!< Motoring organization office
#define KB_OPEN_PARKING_AREA          7369  //!< Open parking area
#define KB_RECREATION_FACILITY        7370  //!< Recreation facility
#define KB_SCHOOL                     7372  //!< School
#define KB_SHOPPING_CENTRE            7373  //!< Shopping centre
#define KB_STADIUM                    7374  //!< Stadium
#define KB_TOURIST_ATTRACTION         7376  //!< Tourist attraction
#define KB_UNIVERSITY                 7377  //!< University or college
#define KB_BUSINESS_FACILITY          7378  //!< Business facility
#define KB_CITY_CENTER                7379  //!< City center
#define KB_RAILWAY_STATION            7380  //!< Railway station
#define KB_AIRPORT                    7383  //!< Airport
#define KB_BUS_STATION                7384  //!< Bus station
#define KB_EXHIBITION_CENTER          7385  //!< Exhibition centre
#define KB_PARK_AND_RIDE              7387  //!< Park & ride
#define KB_REST_AREA                  7395  //!< Rest area
#define KB_GOLF_COURSE                9101  //!< Golf course
#define KB_ATM                        9102  //!< ATM
#define KB_GROCERY_STORE              9105  //!< Grocery store
#define KB_LIBRARY                    9107  //!< Library
#define KB_MARINA                     9108  //!< Marina
#define KB_COMMUTER_RAIL_STATION      9110  //!< Commuter rail station
#define KB_COURT_HOUSE                9111  //!< Court house
#define KB_HISTORICAL_MONUMENT        9113  //!< Historical monument
#define KB_BOWLING_CENTRE             9118  //!< Bowling centre
#define KB_CASINO                     9119  //!< Casino
#define KB_CINEMA                     9120  //!< Cinema
#define KB_ICE_SKATING_RINK           9121  //!< Ice skating rink
#define KB_NIGHTLIFE                  9122  //!< Nightlife
#define KB_PUBLIC_SPORT_AIRPORT       9123  //!< Public sport airport
#define KB_SPORTS_CENTRE              9124  //!< Sports centre
#define KB_WINERY                     9125  //!< Winery
#define KB_AUTOMOBILE_DEALERSHP       9126  //!< Automobile/Motorcycle dealership
#define KB_COMPANY                    9352  //!< Company
#define KB_BEACH                      9357  //!< Beach
#define KB_DRIVE_THROUGH_BOTTLE_SHOP  9358  //!< Drive through bottle shop
#define KB_RESTAURANT_AREA            9359  //!< Restaurant area
#define KB_SHOP                       9361  //!< Shop
#define KB_PARK_AND_RECREATION_AREA   9362  //!< Park and recreation area
#define KB_MOUNTAIN_PEAK              9364  //!< Mountain peak
#define KB_OPERA                      9365  //!< Opera
#define KB_CONCERT_HALL               9367  //!< Concert hall
#define KB_TENNIS_COURT               9369  //!< Tennis court
#define KB_WATER_SPORT                9371  //!< Water sport
#define KB_MUSIC_CENTER               9372  //!< Music center
#define KB_DOCTOR                     9373  //!< Doctor
#define KB_DENTIST                    9374  //!< Dentist
#define KB_VETERINARIAN               9375  //!< Veterinarian
#define KB_CONVENTION_CENTER          9377  //!< Convention centre
#define KB_LEISURE_CENTRE             9378  //!< Leisure centre
#define KB_YACHT_BASIN                9380  //!< Yacht basin (deprecated)
#define KB_CEMETERY                   9390  //!< Cemetery
#define KB_BAR_PUB                    9532  //!< Bar Café or pub
#define KB_ENTERTAINMENT              9900  //!< Entertainment
#define KB_ABBEY                      9901  //!< Abbey
#define KB_AMUSEMENT_PARK             9902  //!< Amusement park
#define KB_ARTS_CENTER                9903  //!< Arts center
#define KB_BUILDING_FOOTPRINT         9904  //!< Building footprint 
#define KB_CASTLE                     9905  //!< Castle
#define KB_CHURCH                     9906  //!< Church
#define KB_FORTRESS                   9909  //!< Fortress
#define KB_CAR_DEALER                 9910  //!< Car dealer (deprecated)
#define KB_HOLIDAY_AREA               9912  //!< Holiday area
#define KB_LIGHTHOUSE                 9914  //!< Lighthouse
#define KB_MILITARY_CEMETERY          9915  //!< Military cemetery
#define KB_MONASTERY                  9916  //!< Monastery
#define KB_MONUMENT                   9917  //!< Monument
#define KB_NATURAL_RESERVE            9918  //!< Natural reserve
#define KB_PRISON                     9919  //!< Prison
#define KB_ROCKS                      9921  //!< Rocks
#define KB_WALKING_AREA               9924  //!< Walking area
#define KB_WATER_MILL                 9925  //!< Water mill
#define KB_WINDMILL                   9926  //!< Windmill
#define KB_ZOO                        9927  //!< Zoo
#define KB_RENT_A_CAR_PARKING         9930  //!< Rent-a-Car parking
#define KB_MOUNTAIN_PASS              9935  //!< Mountain pass
#define KB_PUBLIC_TRANSPORT_STOP      9942  //!< Public transportation stop (Bus stop, Light rail, Taxi rank)

#define KB_HIGHLIGHT_CLASS            0xFFFFFF00
//@}

/***********************************************************************/
/*****                 Useful 'class IDs' Macros                   *****/
/***********************************************************************/

/**
 * \def IS_ROAD_NETWORK
 * A useful macro that checks for a Road Netword Class ID.
 */
#define IS_ROAD_NETWORK(c)  (((c) >= KB_ROAD_ELEMENT_MIN) && ((c) <= KB_ROAD_ELEMENT_MAX))

/**
 * \def IS_ADMIN_AREA
 * A useful macro that checks for an Administrative Area Class ID.
 */
#define IS_ADMIN_AREA(c)    (((c) >= KB_COUNTRY) && ((c) <= KB_ORDRE_9_AREA))


/***********************************************************************/
/*****                      Attribute codes :                      *****/
/***********************************************************************/

/**
 * @name Reserved Attribute codes
 */
//@{
#define KB_ATT_KEY                                 0      //!< KEY
#define KB_ATT_FEATURE_CLASS_CODE                  1      //!< FCC  = feature class code
#define KB_ATT_INCLUSION_RELATION                  2      //!< LAB
#define KB_ATT_SELF_REF                            3      //!< For dynamic objects (self reference)
#define KB_ATT_ADMINISTRATIVE_CLASS                16711  //!< AC  = administrative class of a city (0: capital of a country, 1: capital of an order 1 area, etc.)
#define KB_ATT_BELARUSIAN_NAME                     16969  //!< BE  = BELARUSIAN name (cyrillic alphabet)
#define KB_ATT_BULGARIAN_NAME                      16971  //!< BG  = BULGARIAN name (cyrillic alphabet)
#define KB_ATT_BULGARIAN_LATIN_NAME                16976  //!< BL  = BULGARIAN name (latin alphabet)
#define KB_ATT_BRAND_NAME                          16978  //!< BN  = brand name
#define KB_ATT_BOSNIAN_NAME                        16983  //!< BS  = BOSNIAN name
#define KB_ATT_BELARUSIAN_LATIN_NAME               16984  //!< BT  = BELARUSIAN name (latin alphabet)
#define KB_ATT_CATALAN_NAME                        17221  //!< CA  = CATALAN name
#define KB_ATT_ENCODING                            17228  //!< CH  = character encoding
#define KB_ATT_COORDINATE_TYPE                     17235  //!< CO  = co-ordinates' sytem
#define KB_ATT_CZECH_NAME                          17239  //!< CS  = CZECH name
#define KB_ATT_WELSH_NAME                          17245  //!< CY  = WELSH name
#define KB_ATT_DANISH_NAME                         17477  //!< DA  = DANISH name
#define KB_ATT_GERMAN_NAME                         17481  //!< DE  = GERMAN name
#define KB_ATT_TRAFFIC_DIRECTION                   17482  //!< DF  = direction of traffic flow
#define KB_ATT_EXTRA_ATTRIBUTE                     17733  //!< EA  = extra attributes for POIs objects
#define KB_ATT_COORDINATE_ELLIPSOID                17736  //!< ED  = co-ordinates' ellipsoid
#define KB_ATT_GREEK_GREEK_NAME                    17739  //!< EG  = GREEK name (greek alphabet)
#define KB_ATT_GREEK_NAME                          17744  //!< EL  = GREEK name (latin alphabet)
#define KB_ATT_ENGLISH_NAME                        17746  //!< EN  = ENGLISH name
#define KB_ATT_SPANISH_NAME                        17751  //!< ES  = SPANISH name
#define KB_ATT_ESTONIAN_NAME                       17752  //!< ET  = ESTONIAN name
#define KB_ATT_BASQUE_NAME                         17753  //!< EU  = BASQUE name
#define KB_ATT_FINNISH_NAME                        17997  //!< FI  = FINNISH name
#define KB_ATT_SOURCE_FORMAT                       18003  //!< F0  = source format
#define KB_ATT_FRENCH_NAME                         18006  //!< FR  = FRENCH name
#define KB_ATT_FRISIAN_NAME                        18013  //!< FY  = FRISIAN name
#define KB_ATT_IRISH_NAME                          18245  //!< GA  = IRISH name
#define KB_ATT_GAELIC_NAME                         18248  //!< GD  = GAELIC name
#define KB_ATT_GALICIAN_NAME                       18256  //!< GL  = GALICIAN (Gallegan) name
#define KB_ATT_HEADER                              18504  //!< HD  = header
#define KB_ATT_HUNGARIAN_NAME                      18521  //!< HU  = HUNGARIAN name
#define KB_ATT_INTERNATIONAL_CODE                  18759  //!< IC  = international code
#define KB_ATT_ITALIAN_NAME                        18776  //!< IT  = ITALIAN name
#define KB_ATT_LANGUAGE                            19525  //!< LA  = default language for objects' names
#define KB_ATT_LETZEBURGESCH_NAME                  19526  //!< LB  = LETZEBURGESCH name
#define KB_ATT_HOUSE_NUMBER_LEFT                   19529  //!< LE  
#define KB_ATT_LENGTH                              19531  //!< LG  = length in meters
#define KB_ATT_LITHUANIAN_NAME                     19544  //!< LT  = LITHUANIAN name
#define KB_ATT_LATVIAN_NAME                        19546  //!< LV  = LATVIAN name
#define KB_ATT_MACEDONIAN_LATIN_NAME               19783  //!< MC  = MACEDONIAN name (latin alphabet)
#define KB_ATT_MACEDONIAN_NAME                     19791  //!< MK  = MACEDONIAN name (cyrillic alphabet)
#define KB_ATT_MOLDAVIAN_NAME                      19795  //!< MO  = MOLDAVIAN name
#define KB_ATT_NB_BORDER_JUNCTIONS                 20038  //!< NB  
#define KB_ATT_NB_JUNCTIONS                        20046  //!< NJ  
#define KB_ATT_DUTCH_NAME                          20048  //!< NL  = DUTCH name
#define KB_ATT_NORWEGIAN_NAME                      20051  //!< NO  = NORWEGIAN name
#define KB_ATT_STREET_NAME_AND_HOUSE_NUMBER        20055  //!< NS  
#define KB_ATT_OFFICIAL_CODE                       20295  //!< OC  = official code
#define KB_ATT_NAME                                20306  //!< ON  = official name (default language)
#define KB_ATT_POPULATION_CATEGORY                 20551  //!< PC  = population category: 1:>=1000000; 2:>=500000; 3:>=100000; 4:>=50000; 5:>=10000; 6:>=5000; 7:>=1000; 8:<1000
#define KB_ATT_POLISH_NAME                         20560  //!< PL  = POLISH name
#define KB_ATT_POPULATION                          20563  //!< PO  = population
#define KB_ATT_DATA_PROVIDER                       20566  //!< PR  = data provider's name
#define KB_ATT_POSTAL_CODE                         20567  //!< PS  = postal code
#define KB_ATT_PORTUGUESE_NAME                     20568  //!< PT  = PORTUGUESE name
#define KB_ATT_HOUSE_NUMBER_RIGHT                  21065  //!< RE  
#define KB_ATT_RUSSIAN_LATIN_NAME                  21072  //!< RL  = RUSSIAN name (latin alphabet)
#define KB_ATT_RHAETO_ROMANCE_NAME                 21073  //!< RM  = RHAETO-ROMANCE name
#define KB_ATT_ROUTE_NUMBER                        21074  //!< RN  = Route Number (ex. E15, A6, N7, etc.)
#define KB_ATT_ROMANIAN                            21075  //!< RO  = ROMANIAN name
#define KB_ATT_ROMANIAN_NAME                       21075  //!< RO  = ROMANIAN name
#define KB_ATT_RUSSIAN_NAME                        21081  //!< RU  = RUSSIAN name (cyrillic alphabet)
#define KB_ATT_SCALE                               21319  //!< SC  = SVS coordinates' scale
#define KB_ATT_SERBO_CROATIAN_NAME                 21324  //!< SH  = SERBO-CROATIAN name
#define KB_ATT_SIGN_INFORMATION                    21325  //!< SI  = sign information
#define KB_ATT_SLOVAK_NAME                         21327  //!< SK  = SLOVAK name
#define KB_ATT_SLOVENIAN_NAME                      21328  //!< SL  = SLOVENIAN name
#define KB_ATT_SPEED_CATEGORY                      21332  //!< SP  = speed category (km/h): 0=10;1=20;2=30;3=40;4=50;5=60;6=70;7=80;8=90;9=100;10=110;11=120
#define KB_ATT_ALBANIAN_NAME                       21333  //!< SQ  = ALBANIAN name
#define KB_ATT_SVS_TYPE                            21336  //!< ST  = SVS type
#define KB_ATT_SWEDISH_NAME                        21338  //!< SV  = SWEDISH name
#define KB_ATT_TELEPHONE                           21584  //!< TL  = telephone number
#define KB_TOLL_ROAD                               21590  //!< TR  = toll road
#define KB_ATT_TOLL_ROAD                           21590  //!< TR  = toll road
#define KB_ATT_TURKISH_NAME                        21593  //!< TU  = TURKISH name
#define KB_ATT_UKRAINIAN_NAME                      21839  //!< UK  = UKRAINIAN name (cyrillic alphabet)
#define KB_ATT_UKRAINIAN_LATIN_NAME                21840  //!< UL  = UKRAINIAN name (latin alphabet)
#define KB_ATT_UTM_ZONE                            21848  //!< UT  = UTM zone  : 1 - 60, positif for north, negative for south
#define KB_ATT_VT_MASK                             22104  //!< VT  = vehicle type mask
#define KB_ATT_ANY_LANG                            22620  //!< XX  = Any language code

#define KB_INFO_SOURCE                             0  //!< Information about source data
#define KB_INFO_SVS_TYPE                           1  //!< Information about SVS type
#define KB_INFO_COORDINATES                        2  //!< Information about svs coordinates' system
#define KB_INFO_PROVIDER                           3  //!< Information about data provider
#define KB_INFO_LANGUAGE                           4  //!< Information about texts language data in svs
#define KB_INFO_GEOCODING                          5  //!< Information about geocoding data in svs
#define KB_INFO_STREET_NUMBERS                     6  //!< Information about street numbers data in svs
#define KB_INFO_NAVIGATION                         7  //!< Information about navigation data in svs
#define KB_INFO_ENCODING                           8  //!< Information about character encoding used in svs
//@}


/**
 * \enum EB_LANGUAGE_CODE
 * Defines all possible language codes that might be used to set a preferential language
 * for certain operations such as geo-coding.
 * Codes are based on language codes defined by ISO 639 2/3 letters (except for Turkish: TU instead of TR)
 */
typedef enum {
  DEFAULT_LANGUAGE = KB_ATT_NAME,               //!< Default language
  ANY_LANGUAGE     = KB_ATT_ANY_LANG,           //!< Special code that allows you to search for a name in all available languages.
  COUNTRY_CODE     = KB_ATT_INTERNATIONAL_CODE, //!< Special code that allows you to get/search a country by its ISO 3166 Alpha 3-country code.
  ALB = KB_ATT_ALBANIAN_NAME,        //!< Albanian       (alb/sqi - sq)
  BAQ = KB_ATT_BASQUE_NAME,          //!< Basque         (baq/eus - eu)
  BEL = KB_ATT_BELARUSIAN_NAME,      //!< Belarusian     (bel     - be) (cyrillic alphabet)
  BET = KB_ATT_BELARUSIAN_LATIN_NAME,//!< Belarusian     (bet     - bt) (latin alphabet)
  BOS = KB_ATT_BOSNIAN_NAME,         //!< Bosnian        (bos     - bs)
  BUL = KB_ATT_BULGARIAN_NAME,       //!< Bulgarian      (bul     - bg) (cyrillic alphabet)
  BUN = KB_ATT_BULGARIAN_LATIN_NAME, //!< Bulgarian      (bun       bl) (latin alphabet)
  CAT = KB_ATT_CATALAN_NAME,         //!< Catalan        (cat     - ca)
  CZE = KB_ATT_CZECH_NAME,           //!< Czech          (ces/cze - cs)
  DAN = KB_ATT_DANISH_NAME,          //!< Danish         (dan     - da)
  DUT = KB_ATT_DUTCH_NAME,           //!< Dutch          (dut/nla - nl)
  ENG = KB_ATT_ENGLISH_NAME,         //!< English        (eng     - en)
  EST = KB_ATT_ESTONIAN_NAME,        //!< Estonian       (est     - et)
  FIN = KB_ATT_FINNISH_NAME,         //!< Finnish        (fin     - fi)
  FRE = KB_ATT_FRENCH_NAME,          //!< French         (fra/fre - fr)
  FRY = KB_ATT_FRISIAN_NAME,         //!< Frisian        (fry     - fy)
  GAE = KB_ATT_GAELIC_NAME,          //!< Gaelic         (gae/gdh - gd)
  GAG = KB_ATT_GALICIAN_NAME,        //!< Galician       (glg/gag - gl)
  GER = KB_ATT_GERMAN_NAME,          //!< German         (deu/ger - de)
  GLE = KB_ATT_IRISH_NAME,           //!< Irish          (gai/iri - ga)
  GRE = KB_ATT_GREEK_GREEK_NAME,     //!< Greek          (ell/gre - eg) (greek alphabet)
  GRL = KB_ATT_GREEK_NAME,           //!< Greek          (ell/gre - el) (latin alphabet)
  HUN = KB_ATT_HUNGARIAN_NAME,       //!< Hungarian      (hun     - hu)
  ITA = KB_ATT_ITALIAN_NAME,         //!< Italian        (ita     - it)
  LAV = KB_ATT_LATVIAN_NAME,         //!< Latvian        (lav     - lv)
  LIT = KB_ATT_LITHUANIAN_NAME,      //!< Lithuanian     (lit     - lt)
  LTZ = KB_ATT_LETZEBURGESCH_NAME,   //!< Letzeburgesch  (ltz     - lb)
  MAC = KB_ATT_MACEDONIAN_NAME,      //!< Macedonian     (mac/mak - mk) (cyrillic alphabet)
  MAT = KB_ATT_MACEDONIAN_LATIN_NAME,//!< Macedonian     (mat     - mc) (latin alphabet)
  MOL = KB_ATT_MOLDAVIAN_NAME,       //!< Moldavian      (mol     - mo)
  NOR = KB_ATT_NORWEGIAN_NAME,       //!< Norwegian      (nor     - no)
  POL = KB_ATT_POLISH_NAME,          //!< Polish         (pol     - pl)
  POR = KB_ATT_PORTUGUESE_NAME,      //!< Portuguese     (por     - pt)
  ROH = KB_ATT_RHAETO_ROMANCE_NAME,  //!< Rhaeto-Romance (roh     - rm)
  RON = KB_ATT_ROMANIAN_NAME,        //!< Romanian       (ron/rum - ro)
  RUL = KB_ATT_RUSSIAN_LATIN_NAME,   //!< Russian        (rul     - rl) (latin alphabet)
  RUS = KB_ATT_RUSSIAN_NAME,         //!< Russian        (rus     - ru) (cyrillic alphabet)
  SCR = KB_ATT_SERBO_CROATIAN_NAME,  //!< Serbo-croatian (scr     - sh)
  SLO = KB_ATT_SLOVAK_NAME,          //!< Slovak         (slk/slo - sk)
  SLV = KB_ATT_SLOVENIAN_NAME,       //!< Slovenian      (slv     - sl)
  SPA = KB_ATT_SPANISH_NAME,         //!< Spanish        (esl/spa - es)
  SWE = KB_ATT_SWEDISH_NAME,         //!< Swedish        (sve/swe - sv)
  TUR = KB_ATT_TURKISH_NAME,         //!< Turkish        (tur     - tr)
  UKL = KB_ATT_UKRAINIAN_LATIN_NAME, //!< Ukrainian      (ukl     - ul) (latin alphabet)
  UKR = KB_ATT_UKRAINIAN_NAME,       //!< Ukrainian      (ukr     - uk) (cyrillic alphabet)
  WEL = KB_ATT_WELSH_NAME            //!< Welsh          (cym/wel - cy)
} EB_LANGUAGE_CODE;


/**
 * @enum EB_ENCODING
 * This enum defines all supported encodings for a textual attribute.
 */
typedef enum {  
  EB_ENCODING_ISO_8859_1  =  1, //!< ISO-8859-1  (Latin 1)
  EB_ENCODING_ISO_8859_2  =  2, //!< ISO-8859-2  (Latin 2)
  EB_ENCODING_ISO_8859_3  =  3, //!< ISO-8859-3  (Latin 3)
  EB_ENCODING_ISO_8859_4  =  4, //!< ISO-8859-4  (Latin 4)
  EB_ENCODING_ISO_8859_5  =  5, //!< ISO-8859-5  (Cyrillic)
  EB_ENCODING_ISO_8859_6  =  6, //!< ISO-8859-6  (Arabic)
  EB_ENCODING_ISO_8859_7  =  7, //!< ISO-8859-7  (Greek)
  EB_ENCODING_ISO_8859_8  =  8, //!< ISO-8859-8  (Hebrew)
  EB_ENCODING_ISO_8859_9  =  9, //!< ISO-8859-9  (Latin 5)
  EB_ENCODING_ISO_8859_10 = 10, //!< ISO-8859-10 (Latin 6)
  EB_ENCODING_ISO_8859_11 = 11, //!< ISO-8859-11 (Thai)
  EB_ENCODING_ISO_8859_13 = 13, //!< ISO-8859-13 (Latin 7)
  EB_ENCODING_ISO_8859_14 = 14, //!< ISO-8859-14 (Latin 8)
  EB_ENCODING_ISO_8859_15 = 15, //!< ISO-8859-15 (Latin 9)
  EB_ENCODING_ISO_8859_16 = 16, //!< ISO-8859-16 (Latin 10)
  EB_ENCODING_UTF8        = 17, //!< UTF-8
  EB_ENCODING_MAX         = 18  //!< An invalid value
} EB_ENCODING;



/**
 * @enum EB_COORD
 * This enum defines all the possible coordinate systems used for geometry definition of SVS objects.
 */
typedef enum {
  EB_COORD_UNDEFINED         = 0, //!< Undefined coordinate system
  EB_COORD_LONGLAT           = 1, //!< Longitude / latitude coordinate system
  EB_COORD_LAMBERT_I         = 3, //!< Lambert I coordinate system
  EB_COORD_LAMBERT_II        = 2, //!< Lambert II coordinate system
  EB_COORD_LAMBERT_III       = 4, //!< Lambert III coordinate system
  EB_COORD_LAMBERT_IV        = 5, //!< Lambert IV coordinate system
  EB_COORD_LAMBERT_II_ETENDU = 6, //!< Lambert II étendu coordinate system
  EB_COORD_LAMBERT_93        = 8, //!< Lambert 93 coordinate system
  EB_COORD_UTM               = 7, //!< UTM (Universal Transverse Mercator) coordinate system
  EB_COORD_MAX               = 9  //!< An invalid value
} EB_COORD;


/**
 * @enum EB_ELLIPSOID
 * This enum defines all the most common Ellipsoids
 * @since v1.8.0 Creation
 */
typedef enum {  
  EB_UNDEFINED_ELLIPSOID   = 0,
  EB_AIRY                  = 1,
  EB_AUSTRALIAN_NATIONAL   = 2,
  EB_BESSEL_1841           = 3,
  EB_BESSEL_1841_NAMBIA    = 4,
  EB_CLARKE_1866           = 5,
  EB_CLARKE_1880           = 6,
	EB_EVEREST               = 7,
  EB_FISCHER_1960_MERCURY  = 8,
  EB_FISCHER_1968          = 9,
  EB_GRS_1967              = 10,
  EB_GRS_1980              = 11,
  EB_HELMERT_1906          = 12,
  EB_HOUGH                 = 13,
  EB_INTERNATIONAL         = 14,
  EB_KRASSOVSKY            = 15,
  EB_MODIFIED_AIRY         = 16,
  EB_MODIFIED_EVEREST      = 17,
  EB_MODIFIED_FISCHER_1960 = 18,
  EB_SOUTH_AMERICAN_1969   = 19,
  EB_WGS_60                = 20,
	EB_WGS_66                = 21,
  EB_WGS_72                = 22,
  EB_WGS_84                = 23,
  EB_ELLIPSOID_MAX         = 24
} EB_ELLIPSOID;


#include "BTypes.h"

/**
 * @struct TB_COORD_SYSTEM
 * This structure has been added in order to modelize more accurately a coordinate system than the EB_COORD type does.
 * Indeed, it can be useful (or even mandatory) to deal with coordinate systems based on different ellipsoidal earth models. 
 * @since v1.8.0 Creation
 */
typedef struct {
  EB_COORD        coordType; //!< Coordinate system
  EB_ELLIPSOID    ellipsoid; //!< Reference ellipsoid
  TBint16         UTMZone;   //!< Optional UTM Zone (parameter not relevant for non UTM coordinate systems). Value of UTM zone must be in range [1,60] in the northern hemisphere or [-60,-1] in in the southern hemisphere.
} TB_COORD_SYSTEM;


/** 
 * A function that converts a string such as "PAIX,RUE DE LA" into
 * "RUE DE LA PAIX" or "HOPITAL, BOULEVARD DE L'" into "BOULEVARD DE L'HOPITAL"
 * @param inText The string to process.
 * @return The converted string.
 * @note If \a ioText does not have a coma, \a ioText is unchanged.
 */
extern "C" BSVS_EXPORT TBint8 * BFormatRoadText(TBint8 * ioText);

/** 
 * A function that converts a string such as "PAIX,RUE DE LA" into
 * "RUE DE LA PAIX" or "HOPITAL, BOULEVARD DE L'" into "BOULEVARD DE L'HOPITAL"
 * @param inText The string to process.
 * @return The length of converted string.
 * @note If \a ioText does not have a coma, \a ioText is unchanged.
 * @since v1.7.1
 */
extern "C" BSVS_EXPORT TBuint16 BFormatRoadTextLen(TBint8 * ioText);


/**
 * An helper function that converts an ISO 639-1 (2-letter) language code to
 * the corresponding #EB_LANGUAGE_CODE value.
 * @param inStr An ISO 639-1 Language Code (@see http://www.geo-guide.de/info/tools/languagecode.html)
 * @return The converted language code.
 * @note If \a inStr does not represent a valid (2-letter) language code,
 * the function returns the #EB_LANGUAGE_CODE::DEFAULT_LANGUAGE value.
 * @note You can use the special "IC" (or "ic") language code if you want to get/search a country by its ISO 3166 Alpha 3-country code.
 * @since v1.4
 */
extern "C" BSVS_EXPORT EB_LANGUAGE_CODE BISO639ToLangCode(const TBint8 * inStr);


/**
 * Checks whether the given attribute code is a language code
 * @return \c true if the specified attribute code is a language code, \c false otherwise.
 * @since v1.5
 */
extern "C" BSVS_EXPORT TBbool BIsLanguageCode(TBuint16 inAttCode);


#include "CBSVS.h"
/**
 * An helper function that allows you to get the name of any object into the specified language.
 * @param inFormParams A unique object identifier.
 * @param inLanguageCode Language code to use (see #EB_LANGUAGE_CODE)
 * @param outBufLength Length (in bytes) of the returned string (excluding the terminal NULL character).
 * @return Name of the object into the specified language or \c NULL if not available.
 * @note It's up to the caller to delete the returned (new allocated) string buffer.
 * @since v1.4
 */
extern "C" BSVS_EXPORT TBint8 * BGetNameFromLang(const TB_FORM_PARAMETERS & inFormParams,
                                                 EB_LANGUAGE_CODE           inLanguageCode,
                                                 TBuint16                 & outBufLength);


#endif // __BCARTOCONST_H__
