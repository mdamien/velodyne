///////////////////
// file : io_hdfile.h
// date : 17/09/03
// Please don't change the values the types without abrobation
///////////////////


#ifndef IO_HDFILE_H
#define IO_HDFILE_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include "ioctl.h"
#include "road_time.h"


#define VERSION_NUMBER	2

    //=============== Type of file ===================

    //original types
#define  FILE_IMAGE   0
#define  FILE_CAN     1
#define  FILE_TEXT    2
#define  FILE_IMAGE3D 3
#define  FILE_DBT_UNKNOWN 4
#define  FILE_JPEG	  5
#define  STREAM8POSITION	100

    //extended types
#define  SIGNAL_PPS   511
#define  FILE_AUDIO   512
#define  AUDIO_WAV	  513
#define  TYPE_DOUBLE  518
#define  TYPE_FLOAT   519
#define  TYPE_INT     520
#define  TYPE_INT64   521
#define  DATA_PHYSIO  600

    //UTC/Heudiasyc types
#define  WGS84_POSITION                 500
#define  TRAME_GGA			514
#define  TRAME_GGA_DBL	614
#define  TRAME_VTG			515
#define  TRAME_GST			516
#define	 TRAME_HDT		  615
#define	 TRAME_ROT		  616
#define	 TRAME_GSV		  617
#define  TRAME_GSA      618
#define  TRAME_RMC      619
#define  TRAME_ZDA      620
#define  DYNA_ROADYN    621
#define  DYNA_HT500     622
#define  DYNA_CUBE_RAWDATA 623 
#define  DATA_ABS				517
#define  GYRO_KVH				522
#define  TELEM_SICK			523
#define  CORREVIT				524
#define  SIG						525
#define  LOC						526
#define  DATA_INS				540
#define  DATA_ABS_CITROEN   541
#define  VOLANT					542
#define  DATA_3DMG			543
#define  DATA_COMODOS		544
#define  CROSSBOW_VG700		545
#define  CARMEN_CAN_RAW           2200
#define  CARMEN_CAN_WHEELSPEED    2201
#define  CARMEN_CAN_SUSPENSION    2202
#define  CARMEN_CAN_RAWLATDYN     2203
#define  CARMEN_CAN_ODOMETRY      2204
#define  CARMEN_CAN_LATDYN        2205
#define  CARMEN_CAN_STEERINGWHEEL 2206
#define  RADAR_TRW_AC20		3000
#define  SMS_RADAR			4000 // by Arthur Miranda 23/02/2012 (PAMU Project)
#define	 TELEM_100			8192
#define	 TELEM_180			8193
#define  TELEM_360      8194
#define  ALASCA_XT      8200
#define  VELODYNE_RAW_SPHERIC_DATA    8300
#define	 FILE_MJPEG			4096
// Stereo Camera
#define  STEREO_RIGHT_IMAGE 1982
#define  STEREO_LEFT_IMAGE  1983
#define  CARMEN_VISUAL_ODOMETRY 1984
#define  CARMEN_LIDAR_DETECTION 1985
#define	 CARMEN_VISUAL_DETECTOR 1986
//for the Renault's Case study
#define  FILE_FACELAB		610
#define DBT_T_HEADWAY		1001
#define DBT_PERC_T_HEADWAY	1002
#define DBT_D_O_C_F_DIST	1003
#define DBT_F_DIST			1004
#define DBT_S_INDICATOR		1005
    //Lane Changing
#define DBT_L_CHANGE		1006
#define DBT_M_SPEED			1007
#define DBT_V_I_L_SPEED		1008
#define DBT_R_TIME			1009
#define DBT_B_R_TIME		1010
#define DBT_E_B_EPISOD		1011
    //state of the road
#define DBT_R_STATE			1012
    //Comments from the ergonom
#define DBT_COMMENTS		1013
    //State of the HVI of the ADAS
#define DBT_ADAS		1014
#define DBT_R_SPEED		1015
#define DBT_TTC			1016
#define DBT_D_BRAKE_ACTUATION	1017
#define DBT_ACC_PED_RELEASE		1018
#define DBT_COV_DISTANCE		1019
    // classes of time headway: [2.0 2.5]  [1.5 2.0]  [1.0 1.5]  [0.5 1.0]  [0.0 0.5] -> c2
#define DBT_T_HEADWAY_CLASSES	1020

//SBAS
#define  DBT_SBAS_MT1	10001
#define  DBT_SBAS_MT2	10002
#define  DBT_SBAS_MT3	10003
#define  DBT_SBAS_MT4	10004
#define  DBT_SBAS_MT5	10005
#define  DBT_SBAS_MT6	10006
#define  DBT_SBAS_MT7	10007
#define  DBT_SBAS_MT10	10010
#define  DBT_SBAS_MT18	10018
#define  DBT_SBAS_MT24	10024
#define  DBT_SBAS_MT25	10025
#define  DBT_SBAS_MT26	10026
//#define  DBT_SBAS_MT1	10001


//Ublox
#define  DBT_UBX_RXM_RAW	10121
#define  DBT_UBX_RXM_SFRB	10122
#define  DBT_UBX_NAV_CLOCK	10110
#define  DBT_UBX_NAV_POSLLH	10111
#define  DBT_UBX_NAV_POSUTM	10112
#define  DBT_UBX_NAV_SBAS	10113
#define  DBT_UBX_NAV_SOL	10114
#define  DBT_UBX_NAV_SVINFO	10115
#define  DBT_UBX_NAV_VELNED	10116

//SBF
#define  DBT_SBF_FRAMERAW        11000
#define  DBT_SBF_MEASEPOCH	 11889
#define  DBT_SBF_SHORTMEASEPOCH  11890
#define  DBT_SBF_GENMEASEPOCH    11944
#define  DBT_SBF_ENDOFMEAS	 11922

#define  DBT_SBF_GPSNAV          11891
#define  DBT_SBF_GPSALM          11892
#define  DBT_SBF_GPSION          11893
#define  DBT_SBF_GPSUTC          11894
#define  DBT_SBF_GPSRAW          11895
#define  DBT_SBF_CNAVRAW         11947

#define  DBT_SBF_GEOMT00               11925
#define  DBT_SBF_GEOPRNMASK            11926
#define  DBT_SBF_GEOFASTCORR           11927
#define  DBT_SBF_GEOINTEGRITY          11928
#define  DBT_SBF_GEOFASTCORRDEGR       11929
#define  DBT_SBF_GEONAV                11896
#define  DBT_SBF_GEODEGRFACTORS        11930
#define  DBT_SBF_GEONETWORKTIME        11918
#define  DBT_SBF_GEOALM                11897
#define  DBT_SBF_GEOIGPMASK            11931
#define  DBT_SBF_GEOLONGTERMCORR       11932
#define  DBT_SBF_GEOIONODELAY          11933
#define  DBT_SBF_GEOSERVICELEVEL       11917
#define  DBT_SBF_GEOCLOCKEPHCOVMATRIX  11934
#define  DBT_SBF_GEORAW                11898

#define  DBT_SBF_PVTCARTESIAN	       11903
#define  DBT_SBF_PVTGEODETIC           11904
#define  DBT_SBF_POSCOVCARTESIAN       11905
#define  DBT_SBF_POSCOVGEODETIC        11906
#define  DBT_SBF_VELCOVCARTESIAN       11907
#define  DBT_SBF_VELCOVGEODETIC        11908
#define  DBT_SBF_DOP                   11909
#define  DBT_SBF_PVTRESIDUALS          11910
#define  DBT_SBF_RAIMSTATISTICS        11915
#define  DBT_SBF_GEOCORRECTIONS        11935
#define  DBT_SBF_BASELINE              11950
#define  DBT_SBF_ENDOFPVT              11921

#define  DBT_SBF_ATTITUDEEULER      11938
#define  DBT_SBF_ATTITUDECOVEULER   11939
#define  DBT_SBF_ATTITUDEQUAT       11940
#define  DBT_SBF_ATTITUDECOVQUAT    11941
#define  DBT_SBF_AUXANTPOSITIONS    11942
#define  DBT_SBF_ENDOFATTITUDE      11943

#define  DBT_SBF_RECEIVERTIME    11914
#define  DBT_SBF_XPPSOFFSET      11911
#define  DBT_SBF_EXTEVENT        11924

#define  DBT_SBF_DIFFCORRIN      11919
#define  DBT_SBF_BASESTATION     11949
#define  DBT_SBF_BASELINK        11948

#define  DBT_SBF_TRACKINGSTATUS  11912
#define  DBT_SBF_RECEIVERSTATUS  11913
#define  DBT_SBF_RECEIVERSETUP   11902

#define  DBT_SBF_COMMENT   11936

//naviflow
#define  TRAME_3DMGX1	    12100
#define  TRAME_AVIONIQUE    12101
#define  TRAME_UEYE_STEREO_INDEX    12102

// Mobileye
#define	MOBILEYE_OBSTACLE_COUNT		12200

#define	MOBILEYE_OBSTACLE_0_PART_1	12210
#define	MOBILEYE_OBSTACLE_1_PART_1	12211
#define	MOBILEYE_OBSTACLE_2_PART_1	12212
#define	MOBILEYE_OBSTACLE_3_PART_1	12213
#define	MOBILEYE_OBSTACLE_4_PART_1	12214
#define	MOBILEYE_OBSTACLE_5_PART_1	12215
#define	MOBILEYE_OBSTACLE_6_PART_1	12216
#define	MOBILEYE_OBSTACLE_7_PART_1	12217
#define	MOBILEYE_OBSTACLE_8_PART_1	12218
#define	MOBILEYE_OBSTACLE_9_PART_1	12219

#define	MOBILEYE_OBSTACLE_0_PART_2	12220
#define	MOBILEYE_OBSTACLE_1_PART_2	12221
#define	MOBILEYE_OBSTACLE_2_PART_2	12222
#define	MOBILEYE_OBSTACLE_3_PART_2	12223
#define	MOBILEYE_OBSTACLE_4_PART_2	12224
#define	MOBILEYE_OBSTACLE_5_PART_2	12225
#define	MOBILEYE_OBSTACLE_6_PART_2	12226
#define	MOBILEYE_OBSTACLE_7_PART_2	12227
#define	MOBILEYE_OBSTACLE_8_PART_2	12228
#define	MOBILEYE_OBSTACLE_9_PART_2	12229

#define	MOBILEYE_CENTER_LANE		12300
#define	MOBILEYE_RIGHT_LANE			12301
#define	MOBILEYE_LEFT_LANE			12302

// SPAN CPT
#define  TRAME_BESTGPSPOSA     621
#define  TRAME_RAWIMUSA        622
#define  TRAME_INSPVAA         623
#define  TRAME_INSCOV          624
    //=============== Header in file ==================
    typedef struct
    {
        char Signature[4];
        int Type;		// IMAGE, CAN, UNKNOWN, etc.
        int VersionNumber;
        int DataOffset;	// starting of the data
        int DataSize;		// number of byte for data
        int FileSize; 		// current size of the file
        road_time_t TimeMin, TimeMax;
        int NbRecords;	// nb records
    } hdfile_header_t;

    //==================== file type ================

    typedef struct
    {
        FILE *desc;       	// file descriptor
        hdfile_header_t h;	// header of file
    } hdfile_t;


    // Open the file with the mode READ_MODE (0) or WRITE_MODE (1)
    hdfile_t *open_hdfile(char *path,int mode);

    // Create the file defined by path on the disk. If success return DBITE_SUCCESS (0)
    int create_hdfile(char *path);

    // Test the file path : try to open it and read the header. return DBITE_SUCCESS if good
    int test_hdfile(char *path);

    // Read the next data of the dbt file f. Copy the data in buffer, the associated timestamp
    // in t and the error of timestamping in tr.
    int read_hdfile(hdfile_t *f, void *buffer, road_time_t *time, road_timerange_t *tr);

    // Read the previous data of the dbt file f.
    int read_backward_hdfile(hdfile_t *f, void *buffer, road_time_t *time, road_timerange_t *tr);

    // Write the data buffer and timestamping informations t and tr in the file f.
    int write_hdfile(hdfile_t *f, void *buffer, road_time_t time, road_timerange_t tr, int buffer_data_size);

    // Close the dbt file.
    int close_hdfile(hdfile_t *f);

    // Get the configuration of the dbt file. request can be:
    // HEADER, HEADER_AUX, HEADER_AUX_SIZE, DATA_TYPE or DATA_SIZE
    int get_ioctl_hdfile(hdfile_t *f, int request, void *buf, int size);

    // Configure the header of dbt file f. request can be:
    // DATA_SIZE - buf contains the size of the dbt structure
    // DATA_TYPE - buf contains the type of dbt file. See constants in io_hdfile.h
    // HEADER_AUX
    int set_ioctl_hdfile(hdfile_t *f, int request, void *buf, int size);

    // Display the header on stdout
    void print_header(hdfile_header_t *h);

#ifdef __cplusplus
}
#endif
#endif
