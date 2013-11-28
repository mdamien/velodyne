/*----------------------------------------------------------------------------
| File:
|   VCAND.H
| Project:
|   CAN driver for Win NT and Win 95
|
| Description:
|   Driver Interface Prototypes
|
|-----------------------------------------------------------------------------
| $Author: Jörg $    $Locker: $   $Revision: 48 $
| $Header: /CANdriver/dll/VCanD.h 48    22.01.04 9:26 Jörg $
|-----------------------------------------------------------------------------
| Copyright (c) 1996 by Vector Informatik GmbH.  All rights reserved.
 ----------------------------------------------------------------------------*/

#ifndef _V_CAND_H_
#define _V_CAND_H_

#ifdef __cplusplus
extern "C" {
#endif

#if (__FLAT__) || defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
  #if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)
    #define _EXPORT_API     __stdcall
  #else
    #define _EXPORT_API
  #endif
#else
  #define _EXPORT_API       _far _pascal
#endif

#ifndef DYNAMIC_CANDRIVER_DLL
  // not used for dynamic load of dll
  #define _EXPORT_DECL  __declspec(dllimport) _EXPORT_API
  #define _EXPORT_DEF  __declspec(dllimport) _EXPORT_API
#endif

#include <pshpack1.h>

typedef char * ncdStringType;

//------------------------------------------------------------------------------
// accessmask
typedef unsigned long Vaccess;


//------------------------------------------------------------------------------
// structure for V_RECEIVE_MSG, V_TRANSMIT_MSG 

// message flags 
#ifndef MAX_MSG_LEN
#define MAX_MSG_LEN 8
#endif

#define EXT_MSG                     0x80000000 // signs an extended identifier
#define VCAN_EXT_MSG_ID             EXT_MSG

#define VCAN_MSG_FLAG_ERROR_FRAME   0x01
#define VCAN_MSG_FLAG_OVERRUN       0x02  /* Overrun in Driver or CAN Controller */
                                          /* special case: OVERRUN combined with TIMER
                                           * means the 32 bit timer has overrun
                                           */
#define VCAN_MSG_FLAG_NERR          0x04  /* Line Error on Lowspeed */
#define VCAN_MSG_FLAG_WAKEUP        0x08  /* High Voltage Message on Single Wire CAN */
#define VCAN_MSG_FLAG_REMOTE_FRAME  0x10
#define VCAN_MSG_FLAG_RESERVED_1    0x20
#define VCAN_MSG_FLAG_TX_NOTIFY     0x40  /* Message Transmitted */
#define VCAN_MSG_FLAG_TX_START      0x80  /* Transmit Message stored into Controller  */

// old style flags
#define MSGFLAG_ERROR_FRAME         VCAN_MSG_FLAG_ERROR_FRAME  // Msg is a bus error
#define MSGFLAG_OVERRUN             VCAN_MSG_FLAG_OVERRUN      // Msgs following this has been lost
#define MSGFLAG_NERR                VCAN_MSG_FLAG_NERR         // NERR active during this msg
#define MSGFLAG_WAKEUP              VCAN_MSG_FLAG_WAKEUP       // Msg rcv'd in wakeup mode
#define MSGFLAG_REMOTE_FRAME        VCAN_MSG_FLAG_REMOTE_FRAME // Msg is a remote frame
#define MSGFLAG_RESERVED_1          VCAN_MSG_FLAG_RESERVED_1   // Reserved for future usage
#define MSGFLAG_TX                  VCAN_MSG_FLAG_TX_NOTIFY    // TX acknowledge
#define MSGFLAG_TXRQ                VCAN_MSG_FLAG_TX_START     // TX request

struct s_vcan_msg {  /* 14 Bytes */
         unsigned long id;
         unsigned char flags;
         unsigned char dlc;
         unsigned char data [MAX_MSG_LEN];
       };


//------------------------------------------------------------------------------
// structure for V_CHIP_STATE 

#define CHIPSTAT_BUSOFF              0x01
#define CHIPSTAT_ERROR_PASSIVE       0x02
#define CHIPSTAT_ERROR_WARNING       0x04
#define CHIPSTAT_ERROR_ACTIVE        0x08

struct s_vcan_chip_state {
         unsigned char busStatus;
         unsigned char txErrorCounter;
         unsigned char rxErrorCounter;
       };

//------------------------------------------------------------------------------
// structure for SET_OUTPUT_MODE
#define OUTPUT_MODE_SILENT 0
#define OUTPUT_MODE_NORMAL 1

//------------------------------------------------------------------------------
// Transceiver modes 
#define TRANSCEIVER_EVENT_ERROR   1
#define TRANSCEIVER_EVENT_CHANGED 2

//------------------------------------------------------------------------------
// Transceiver types 
#define VCAN_TRANSCEIVER_TYPE_NONE              0
#define VCAN_TRANSCEIVER_TYPE_251               1
#define VCAN_TRANSCEIVER_TYPE_252               2
#define VCAN_TRANSCEIVER_TYPE_DNOPTO            3
#define VCAN_TRANSCEIVER_TYPE_W210              4
#define VCAN_TRANSCEIVER_TYPE_SWC_PROTO         5  // Prototype. Driver may latch-up.
#define VCAN_TRANSCEIVER_TYPE_SWC               6
#define VCAN_TRANSCEIVER_TYPE_EVA               7
#define VCAN_TRANSCEIVER_TYPE_FIBER             8
#define VCAN_TRANSCEIVER_TYPE_K251              9
#define VCAN_TRANSCEIVER_TYPE_K                10 
#define VCAN_TRANSCEIVER_TYPE_1054_OPTO        11  // 1054 with optical isolation
#define VCAN_TRANSCEIVER_TYPE_SWC_OPTO         12  // SWC with optical isolation
#define VCAN_TRANSCEIVER_TYPE_B10011S          13  // B10011S truck-and-trailer
#define VCAN_TRANSCEIVER_TYPE_1050             14  // 1050 
#define VCAN_TRANSCEIVER_TYPE_1050_OPTO        15  // 1050 with optical isolation
#define VCAN_TRANSCEIVER_TYPE_1041             16  // 1041
#define VCAN_TRANSCEIVER_TYPE_1041_OPTO        17  // 1041 with optical isolation


// piggy backs 
#define VCAN_TRANSCEIVER_TYPE_PB_251               0x0101 
#define VCAN_TRANSCEIVER_TYPE_PB_1054              0x0103 
#define VCAN_TRANSCEIVER_TYPE_PB_251_OPTO          0x0105 
// 0x0107, 0x0109 are not supported!!           
#define VCAN_TRANSCEIVER_TYPE_PB_SWC               0x010B 
// 0x010D not supported, 0x010F, 0x0111, 0x0113 reserved for future use!! 
#define VCAN_TRANSCEIVER_TYPE_PB_1054_OPTO         0x0115 
#define VCAN_TRANSCEIVER_TYPE_PB_SWC_OPTO          0x0117 
#define VCAN_TRANSCEIVER_TYPE_PB_TT_OPTO           0x0119 
#define VCAN_TRANSCEIVER_TYPE_PB_1050              0x011B 
#define VCAN_TRANSCEIVER_TYPE_PB_1050_OPTO         0x011D 
#define VCAN_TRANSCEIVER_TYPE_PB_1041              0x011F 
#define VCAN_TRANSCEIVER_TYPE_PB_1041_OPTO         0x0121 


//------------------------------------------------------------------------------
// old style Transceiver types 
#define TRANSCEIVER_TYPE_NONE           VCAN_TRANSCEIVER_TYPE_NONE
#define TRANSCEIVER_TYPE_251            VCAN_TRANSCEIVER_TYPE_251
#define TRANSCEIVER_TYPE_252            VCAN_TRANSCEIVER_TYPE_252
#define TRANSCEIVER_TYPE_DNOPTO         VCAN_TRANSCEIVER_TYPE_DNOPTO
#define TRANSCEIVER_TYPE_W210           VCAN_TRANSCEIVER_TYPE_W210
#define TRANSCEIVER_TYPE_SWC_PROTO      VCAN_TRANSCEIVER_TYPE_SWC_PROTO
#define TRANSCEIVER_TYPE_SWC            VCAN_TRANSCEIVER_TYPE_SWC


//------------------------------------------------------------------------------
// Transceiver modes 
#define VCAN_TRANSCEIVER_LINEMODE_NA         0
#define VCAN_TRANSCEIVER_LINEMODE_TWO_LINE   1
#define VCAN_TRANSCEIVER_LINEMODE_CAN_H      2
#define VCAN_TRANSCEIVER_LINEMODE_CAN_L      3
#define VCAN_TRANSCEIVER_LINEMODE_SWC_SLEEP  4  // SWC Sleep Mode.
#define VCAN_TRANSCEIVER_LINEMODE_SWC_NORMAL 5  // SWC Normal Mode.
#define VCAN_TRANSCEIVER_LINEMODE_SWC_FAST   6  // SWC High-Speed Mode.
#define VCAN_TRANSCEIVER_LINEMODE_SWC_WAKEUP 7  // SWC Wakeup Mode.
#define VCAN_TRANSCEIVER_LINEMODE_SLEEP      8
#define VCAN_TRANSCEIVER_LINEMODE_NORMAL     9
#define VCAN_TRANSCEIVER_LINEMODE_STDBY      10  // Standby for those who support it
#define VCAN_TRANSCEIVER_LINEMODE_TT_CAN_H   11  // truck & trailer: operating mode single wire using CAN high
#define VCAN_TRANSCEIVER_LINEMODE_TT_CAN_L   12  // truck & trailer: operating mode single wire using CAN low
#define VCAN_TRANSCEIVER_LINEMODE_EVA_00     13  // CANcab Eva 
#define VCAN_TRANSCEIVER_LINEMODE_EVA_01     14  // CANcab Eva 
#define VCAN_TRANSCEIVER_LINEMODE_EVA_10     15  // CANcab Eva 
#define VCAN_TRANSCEIVER_LINEMODE_EVA_11     16  // CANcab Eva 

//------------------------------------------------------------------------------
// old style Transceiver modes 
#define TRANSCEIVER_LINEMODE_NA         VCAN_TRANSCEIVER_LINEMODE_NA
#define TRANSCEIVER_LINEMODE_TWO_LINE   VCAN_TRANSCEIVER_LINEMODE_TWO_LINE
#define TRANSCEIVER_LINEMODE_CAN_H      VCAN_TRANSCEIVER_LINEMODE_CAN_H
#define TRANSCEIVER_LINEMODE_CAN_L      VCAN_TRANSCEIVER_LINEMODE_CAN_L
#define TRANSCEIVER_LINEMODE_SWC_SLEEP  VCAN_TRANSCEIVER_LINEMODE_SWC_SLEEP
#define TRANSCEIVER_LINEMODE_SWC_NORMAL VCAN_TRANSCEIVER_LINEMODE_SWC_NORMAL
#define TRANSCEIVER_LINEMODE_SWC_FAST   VCAN_TRANSCEIVER_LINEMODE_SWC_FAST
#define TRANSCEIVER_LINEMODE_SWC_WAKEUP VCAN_TRANSCEIVER_LINEMODE_SWC_WAKEUP
#define TRANSCEIVER_LINEMODE_SLEEP      VCAN_TRANSCEIVER_LINEMODE_SLEEP
#define TRANSCEIVER_LINEMODE_NORMAL     VCAN_TRANSCEIVER_LINEMODE_NORMAL


#define VCAN_TRANSCEIVER_RESNET_NA           0
#define VCAN_TRANSCEIVER_RESNET_MASTER       1
#define VCAN_TRANSCEIVER_RESNET_MASTER_STBY  2
#define VCAN_TRANSCEIVER_RESNET_SLAVE        3
// old style 
#define TRANSCEIVER_RESNET_NA                VCAN_TRANSCEIVER_RESNET_NA
#define TRANSCEIVER_RESNET_MASTER            VCAN_TRANSCEIVER_RESNET_MASTER
#define TRANSCEIVER_RESNET_MASTER_STBY       VCAN_TRANSCEIVER_RESNET_MASTER_STBY
#define TRANSCEIVER_RESNET_SLAVE             VCAN_TRANSCEIVER_RESNET_SLAVE

//------------------------------------------------------------------------------
// definitions for the events and commands used by the driver
enum e_vevent_type {
       V_NO_COMMAND            = 0,
       V_RECEIVE_MSG           = 1,
       V_CHIP_STATE            = 4,
       V_TIMER                 = 8,
       V_TRANSMIT_MSG          =10,
     };

union s_vcan_tag_data {
        struct s_vcan_msg                  msg;
        struct s_vcan_chip_state           chipState;
      };


typedef unsigned char VeventTag;

//------------------------------------------------------------------------------
// VCAN_EVENT structure 

// event type definition 
struct s_vcan_event {
         VeventTag     tag;             // 1
         unsigned char chanIndex;       // 1
         unsigned char transId;         // 1
         unsigned char portHandle;      // 1 internal use only !!!!
         unsigned long timeStamp;       // 4
         union s_vcan_tag_data
                       tagData;         // 14 Bytes (_VMessage)
       };
                                        // --------
                                        // 22 Bytes

typedef struct s_vcan_event VCAN_EVENT, Vevent, *PVevent;

// message name to aquire a unique message id from windows
#define DriverNotifyMessageName  "VectorCanDriverChangeNotifyMessage"

typedef enum {
  UNKNOWN = 0, 
  HARDWARE_CHANGED = 1,
  APP_SETTINGS_CHANGED = 2,
} VCAN_NOTIFY_REASON;

// defines for the supported hardware
#define HWTYPE_NONE                  0
#define HWTYPE_VIRTUAL               1
#define HWTYPE_CANCARDX              2
#define HWTYPE_CANPARI               3
#define HWTYPE_CANAC2                5
#define HWTYPE_CANAC2PCI             6
#define HWTYPE_CANCARDY             12
#define HWTYPE_CANCARDXL            15
#define HWTYPE_CANCARD2             17  
#define HWTYPE_EDICCARD             19

#define HWTYPE_CANCASEXL            21
#define HWTYPE_CANBOARDXL           25
#define HWTYPE_CANBOARDXL_COMPACT   27  

#define MAX_HWTYPE                  27

//------------------------------------------------------------------------------
// build a channels mask from the channels index
#define CHANNEL_MASK(x) (1<<(x))

#define MAX_APPNAME 32

//------------------------------------------------------------------------------
// define for ReceiveMode
#define VCAN_WAIT   0
#define VCAN_POLL   1
#define VCAN_NOTIFY 2

//------------------------------------------------------------------------------
// driver status
typedef short Vstatus;

#define VSUCCESS                     0
#define VPENDING                     1

#define VERR_QUEUE_IS_EMPTY          10
#define VERR_QUEUE_IS_FULL           11
#define VERR_TX_NOT_POSSIBLE         12
#define VERR_NO_LICENSE              14
#define VERR_WRONG_PARAMETER         101
#define VERR_TWICE_REGISTER          110
#define VERR_INVALID_CHAN_INDEX      111
#define VERR_INVALID_ACCESS          112
#define VERR_PORT_IS_OFFLINE         113
#define VERR_CHAN_IS_ONLINE          116
#define VERR_NOT_IMPLEMENTED         117
#define VERR_INVALID_PORT            118
#define VERR_HW_NOT_READY            120
#define VERR_CMD_TIMEOUT             121
#define VERR_HW_NOT_PRESENT          129
#define VERR_NOTIFY_ALREADY_ACTIVE   131
#define VERR_NO_RESOURCES            152
#define VERR_WRONG_CHIP_TYPE         153
#define VERR_WRONG_COMMAND           154
#define VERR_INVALID_HANDLE          155
#define VERR_CANNOT_OPEN_DRIVER      201
#define VERROR                       255

#define MAX_DRIVER_NAME               31
#define MAX_CHANNEL_NAME              31
#define MAX_CHAN_NAME           MAX_CHANNEL_NAME


//------------------------------------------------------------------------------
// acceptance filter
typedef struct _Vset_acceptance {
  unsigned long code;
  unsigned long mask;
} VsetAcceptance;

//------------------------------------------------------------------------------
// bit timing
typedef struct {
          unsigned long bitRate;
          unsigned char sjw;
          unsigned char tseg1;
          unsigned char tseg2;
          unsigned char sam;  // 1 or 3
        } VchipParams;


// porthandle
#define INVALID_PORTHANDLE (-1)
typedef long VportHandle, *PVportHandle;

typedef struct s_vcan_channel_config {
          char              name [MAX_CHANNEL_NAME + 1];
          unsigned char     hwType;         // HWTYPE_xxxx (see above)
          unsigned char     hwIndex;        // Index of the hardware (same type) (0,1,...)
          unsigned char     hwChannel;      // Index of the channel (same hardware) (0,1,...)
          unsigned char     tranceiverType; // TRANCEIVER_TYPE_xxxx (see above)
          unsigned char     channelIndex;   // Global channel index (0,1,...)
          unsigned long     channelMask;    // Global channel mask (=1<<channelIndex)

          // Channel
          unsigned char     isOnBus;        // The channel is on bus
          VchipParams       chipParams;     // Actual bittiming
          unsigned char     outputMode;     // Actual output mode
          unsigned char     flags;          // Actual options MSGFLAG_TX,MSGFLAG_TXRQ
        } VCAN_CHANNEL_CONFIG;

typedef VCAN_CHANNEL_CONFIG  VChannelConfig;
typedef VCAN_CHANNEL_CONFIG* PVChannelConfig;


typedef struct s_vcan_driver_config {
          char              driverName [MAX_DRIVER_NAME + 1];
          unsigned short    driverVersion;
          void*             dispatcher;
          unsigned char     channelCount;  // total number of channels
          VChannelConfig    channel[1];    // [channelCount]
        } VCAN_DRIVER_CONFIG;

typedef VCAN_DRIVER_CONFIG  VDriverConfig;
typedef VCAN_DRIVER_CONFIG* PVDriverConfig;

#define SIZEOF_VDRIVERCONFIG(n) (sizeof(VDriverConfig)+(n-1)*sizeof(VChannelConfig))

/*******************************************************************
ncdOpenDriver():

The Application calls this function to get access to the driver.
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDOPENDRIVER) (void);
  extern NCDOPENDRIVER ncdDllOpenDriver;
  Vstatus ncdOpenDriver();
#else
  Vstatus _EXPORT_DECL ncdOpenDriver(void);
#endif

/********************************************************************
ncdGetDriverConfig():

The application gets the information, which
CAN channels are available in the system. The user
must provide the memory, pChanCount is pointing to
and the size of pDriverConfig. Passing NULL
for pDriverConfig only the ChanCount is given back.
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDGETDRIVERCONFIG) (
    int           *pChanCount,
    VDriverConfig *pDriverConfig
  );
  extern NCDGETDRIVERCONFIG ncdGetDriverConfig;
#else
  Vstatus _EXPORT_DECL ncdGetDriverConfig(
    int           *pChanCount,
    VDriverConfig *pDriverConfig
  );
#endif

/********************************************************************
ncdGetChannelIndex():
ncdGetChannelMask():

Get the channel index for a channel of a certain hardware.
Parameter -1 means "don't care"
Result -1 (ncdGetChannelIndex) or 0 (ncdGetChannelMask) means "not found"
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef int (_EXPORT_API *NCDGETCHANNELINDEX) (
    int hwType,     // [-1,HWTYPE_CANCARDX,HWTYPE_VIRTUAL,...]
    int hwIndex,    // [-1,0,1]
    int hwChannel   // [-1,0,1]
  );
  extern NCDGETCHANNELINDEX ncdGetChannelIndex;

  typedef Vaccess (_EXPORT_API *NCDGETCHANNELMASK) (
    int hwType,     // [-1,HWTYPE_CANCARDX,HWTYPE_VIRTUAL,...]
    int hwIndex,    // [-1,0,1]
    int hwChannel   // [-1,0,1]
  );
  extern NCDGETCHANNELMASK ncdGetChannelMask;
#else
  int _EXPORT_DECL ncdGetChannelIndex(
    int hwType,     // [-1,HWTYPE_CANCARDX,HWTYPE_VIRTUAL,...]
    int hwIndex,    // [-1,0,1]
    int hwChannel   // [-1,0,1]
  );

  Vaccess _EXPORT_DECL ncdGetChannelMask(
    int hwType,     // [-1,HWTYPE_CANCARDX,HWTYPE_VIRTUAL,...]
    int hwIndex,    // [-1,0,1]
    int hwChannel   // [-1,0,1]
  );
#endif


/********************************************************************
ncdOpenPort():

The application tells the driver to which channels
it wants to get access to and which of these channels
it wants to get the permission to initialize the channel.
Only one port can get the permission to initialize a channel.
The permitted init access is returned.
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDOPENPORT) (
    VportHandle   *portHandle,
    char          *userName,
    Vaccess        accessMask,
    Vaccess        initMask,
    Vaccess       *permissionMask,
    int            rxQueueSize
  );
  extern NCDOPENPORT ncdOpenPort;
#else
  Vstatus _EXPORT_DECL ncdOpenPort(
    VportHandle   *portHandle,
    char          *userName,
    Vaccess        accessMask,
    Vaccess        initMask,
    Vaccess       *permissionMask,
    int            rxQueueSize
  );
#endif

/********************************************************************
ncdSetChannelMode():

For the CAN channels defined by AccessMask is set
whether the caller will get a TX and/or a TXRQ
receipt for transmitted messages.
The port must have init access to the channels.
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDSETCHANNELMODE) (VportHandle    portHandle,
    Vaccess       accessMask,
    int           tx,
    int           txrq
  );
  extern NCDSETCHANNELMODE ncdSetChannelMode;
#else
  Vstatus _EXPORT_DECL ncdSetChannelMode(VportHandle    portHandle,
    Vaccess       accessMask,
    int           tx,
    int           txrq
  );
#endif

/********************************************************************
ncdSetChannelOutput():

The output mode for the CAN chips of the channels defined by accessMask, is set
to OUTPUT_MODE_NORMAL or OUTPUT_MODE_SILENT.
The port must have init access to the channels.
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDSETCHANNELOUTPUT) (VportHandle portHandle,
    Vaccess    accessMask,
    int        mode
  );
  extern NCDSETCHANNELOUTPUT ncdSetChannelOutput;
#else
  Vstatus _EXPORT_DECL ncdSetChannelOutput(VportHandle portHandle,
    Vaccess    accessMask,
    int        mode
  );
#endif

/********************************************************************
ncdSetChannelTransceiver():

The transceiver mode for the channels defined by accessMask, is set.
The port must have init access to the channels.
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDSETCHANNELTRANSCEIVER) (
    VportHandle  portHandle,
    Vaccess      accessMask,
    int          type,
    int          lineMode,
    int          resNet
  );
  extern NCDSETCHANNELTRANSCEIVER ncdSetChannelTransceiver;
#else
  Vstatus _EXPORT_DECL ncdSetChannelTransceiver(
    VportHandle  portHandle,
    Vaccess      accessMask,
    int          type,
    int          lineMode,
    int          resNet
  );
#endif

/********************************************************************
ncdSetChannelParams():
ncdSetChannelParamsC200():
ncdSetChannelBitrate():

The channels defined by accessMask will be initialized with the
given parameters.
The port must have init access to the channels.
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDSETCHANNELPARAMS) (VportHandle   portHandle,
    Vaccess       accessMask,
    VchipParams*  pChipParams
  );
  extern NCDSETCHANNELPARAMS ncdSetChannelParams;

  typedef Vstatus (_EXPORT_API *NCDSETCHANNELPARAMSC200) (VportHandle   portHandle,
    Vaccess       accessMask,
    unsigned char btr0,
    unsigned char btr1
  );
  extern NCDSETCHANNELPARAMSC200 ncdSetChannelParamsC200;

  typedef Vstatus (_EXPORT_API *NCDSETCHANNELBITRATE) (VportHandle   portHandle,
    Vaccess       accessMask,
    unsigned long bitrate
  );
  extern NCDSETCHANNELBITRATE ncdSetChannelBitrate;

#else
  Vstatus _EXPORT_DECL ncdSetChannelParams(VportHandle   portHandle,
    Vaccess       accessMask,
    VchipParams*  pChipParams
  );

  Vstatus _EXPORT_DECL ncdSetChannelParamsC200(VportHandle   portHandle,
    Vaccess       accessMask,
    unsigned char btr0,
    unsigned char btr1
  );

  Vstatus _EXPORT_DECL ncdSetChannelBitrate(VportHandle   portHandle,
    Vaccess       accessMask,
    unsigned long bitrate
  );
#endif

/********************************************************************
ncdSetAcceptance():

Set the acceptance filter
Filters for std and ext ids are handled independant in the driver.
Use mask=0xFFFF,code=0xFFFF or mask=0xFFFFFFFF,code=0xFFFFFFFF to fully close
the filter.
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDSETCHANNELACCEPTANCE) (VportHandle     portHandle,
    Vaccess         accessMask,
    VsetAcceptance *filter
  );
  extern NCDSETCHANNELACCEPTANCE ncdSetChannelAcceptance;
#else
  Vstatus _EXPORT_DECL ncdSetChannelAcceptance(VportHandle     portHandle,
    Vaccess         accessMask,
    VsetAcceptance *filter
  );
#endif

/********************************************************************
ncdSetTimerRate():

The timer of the port will be activated/deacticated and the
rate for cyclic timer events is set (10us resolution).
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDSETTIMERRATE) (
    VportHandle    portHandle,
    unsigned long  timerRate
  );
  extern NCDSETTIMERRATE ncdSetTimerRate;
#else
  Vstatus _EXPORT_DECL ncdSetTimerRate(
    VportHandle    portHandle,
    unsigned long  timerRate
  );
#endif

/********************************************************************
ncdResetClock():

The clock generating timestamps for the port will be reset
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDRESETCLOCK) (
    VportHandle portHandle
  );
  extern NCDRESETCLOCK ncdResetClock;
#else
  Vstatus _EXPORT_DECL ncdResetClock(
    VportHandle portHandle
  );
#endif

/********************************************************************
ncdSetNotification():

Setup a event to notify the application if there are messages in the
ports receive queue.
queueLevel specifies the number of messages that triggeres the event.
Note that the event is triggered only once, when the queueLevel is
reached. An application should read all available messages by ncdReceive
to be sure to reenable the event.
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDSETNOTIFICATION) (
    VportHandle portHandle,
    unsigned long *handle,
    int queueLevel
  );
  extern NCDSETNOTIFICATION ncdSetNotification;
#else
  Vstatus _EXPORT_DECL ncdSetNotification(
    VportHandle     portHandle,
    unsigned long  *handle,
    int             queueLevel
  );
#endif

/********************************************************************
ncdTransmit():

A CAN message will be put to the designated channels to be transmitted.

*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDTRANSMIT) (VportHandle    portHandle,
    Vaccess       accessMask,
    Vevent       *pEvent
  );
  extern NCDTRANSMIT ncdTransmit;
#else
  Vstatus _EXPORT_DECL ncdTransmit(VportHandle    portHandle,
    Vaccess       accessMask,
    Vevent       *pEvent
  );
#endif

/********************************************************************
ncdReceive1():

The driver is asked to retrieve a single Events from the
application's receive queue. This function is optimized
for speed. It returns a pointer to the received event.
Lifetime of the data is until the next call of ncdReceive1.
It returns VERR_QUEUE_IS_EMPTY and *ppEvent=NULL if no event
is available.
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDRECEIVE1) (VportHandle portHandle,
    Vevent    **ppEvent
  );
  extern NCDRECEIVE1 ncdReceive1;
#else
  Vstatus _EXPORT_DECL ncdReceive1(VportHandle portHandle,
    Vevent    **ppEvent
  );
#endif

/********************************************************************
ncdReceive():

The driver is asked to retrieve Events from the
application's receive queue. You can choose wether
it will be polled or waited for an incoming event.
Its possible to read multiple events at a time, but the
caller must provide the memory. In pEventCount the actual
number of received events will be returned.
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDRECEIVE) (VportHandle     portHandle,
    int             receiveMode,
    unsigned int    waitHandle,
    int            *pEventCount,
    Vevent         *pEventList
  );
  extern NCDRECEIVE ncdReceive;
#else
  Vstatus _EXPORT_DECL ncdReceive(VportHandle     portHandle,
    int             receiveMode,
    unsigned int    waitHandle,
    int            *pEventCount,
    Vevent         *pEventList
  );
#endif

/********************************************************************
ncdRequestChipState():

The state of the selected channels is requested.
The answer will be received as an event (V_CHIP_STATE).
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDREQUESTCHIPSTATE) (VportHandle portHandle,
    Vaccess    accessMask
  );
  extern NCDREQUESTCHIPSTATE ncdRequestChipState;
#else
  Vstatus _EXPORT_DECL ncdRequestChipState(VportHandle portHandle,
    Vaccess    accessMask
  );
#endif

/********************************************************************
ncdFlushTransmitQueue():

The transmit queue of the selected channel will be flushed.
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDFLUSHTRANSMITQUEUE) (VportHandle portHandle,
    Vaccess    accessMask
  );
  extern NCDFLUSHTRANSMITQUEUE ncdFlushTransmitQueue;
#else
  Vstatus _EXPORT_DECL ncdFlushTransmitQueue(VportHandle portHandle,
    Vaccess    accessMask
  );
#endif

/********************************************************************
ncdFlushReceiveQueue():

The receive queue of the port will be flushed.
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDFLUSHRECEIVEQUEUE) (VportHandle portHandle);
  extern NCDFLUSHRECEIVEQUEUE ncdFlushReceiveQueue;
#else
  Vstatus _EXPORT_DECL ncdFlushReceiveQueue(VportHandle portHandle);
#endif

/********************************************************************
ncdGetReceiveQueueLevel():

The count of event´s in the receive queue of the port will be returned.
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDGETRECEIVEQUEUELEVEL) (VportHandle portHandle,
    int       *level
  );
  extern NCDGETRECEIVEQUEUELEVEL ncdGetReceiveQueueLevel;
#else
  Vstatus _EXPORT_DECL ncdGetReceiveQueueLevel(VportHandle portHandle,
    int       *level
  );
#endif

/********************************************************************
ncdGetState():

The state of the port is returned.
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDGETSTATE) (VportHandle portHandle);
  extern NCDGETSTATE ncdGetState;
#else
  Vstatus _EXPORT_DECL ncdGetState(VportHandle portHandle);
#endif

/********************************************************************
ncdActivateChannel():

The selected channels go 'on the bus'.
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDACTIVATECHANNEL) (VportHandle portHandle,
    Vaccess    accessMask
  );
  extern NCDACTIVATECHANNEL ncdActivateChannel;
#else
  Vstatus _EXPORT_DECL ncdActivateChannel(VportHandle portHandle,
    Vaccess    accessMask
  );
#endif

/********************************************************************
DeactivateChannel():

The selected channels go 'off the bus'.
Its now possible to initialize
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDDEACTIVATECHANNEL) (VportHandle portHandle,
    Vaccess    accessMask
  );
  extern NCDDEACTIVATECHANNEL ncdDeactivateChannel;
#else
  Vstatus _EXPORT_DECL ncdDeactivateChannel(VportHandle portHandle,
    Vaccess    accessMask
  );
#endif

/********************************************************************
ncdClosePort():

The port is closed, channels are deactivated.
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDCLOSEPORT) (VportHandle portHandle);
  extern NCDCLOSEPORT ncdClosePort;
#else
  Vstatus _EXPORT_DECL ncdClosePort(VportHandle portHandle);
#endif

/********************************************************************
ncdCloseDriver ():

The driver is closed.
This is used to unload the driver, if no more application is useing it.
Does not close the open ports !!!
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDCLOSEDRIVER) (void);
  extern NCDCLOSEDRIVER ncdDllCloseDriver;
  Vstatus ncdCloseDriver();
#else
  Vstatus _EXPORT_DECL ncdCloseDriver(void);
#endif

/********************************************************************

ncdGetErrorString()
ncdGetEventString()

Utility Functions
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef ncdStringType (_EXPORT_API *NCDGETERRORSTRING) ( Vstatus err );
  typedef ncdStringType (_EXPORT_API *NCDGETEVENTSTRING) ( Vevent *ev );
  extern NCDGETERRORSTRING ncdGetErrorString;
  extern NCDGETEVENTSTRING ncdGetEventString;
#else
  ncdStringType _EXPORT_DECL ncdGetErrorString( Vstatus err );
  ncdStringType _EXPORT_DECL ncdGetEventString( Vevent *ev );
#endif

/********************************************************************
ncdSetApplConfig():
ncdGetApplConfig():

Handle the application configuration for VCANCONF.EXE
*/

/*
Returns the hwIndex, hwChannel and hwType for a specific Application and application channel.
This gives the ability to register own applications into the Vector
CAN DRIVER CONFIGURATION.
AppName: Zero terminated string containing the Name of the Application.
AppChannel: Channel of the application
hwType, hwIndex, hwChannel: contains the the hardware information on success.
This values can be used in a subsequent call to ncdGetChannelMask or ncdGetChannelIndex.
*/
#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDGETAPPLCONFIG) (
    char   *appName,        // Name of Application
    int     appChannel,     // 0,1
    int    *hwType,         // HWTYPE_xxxx
    int    *hwIndex,        // Index of the hardware (slot) (0,1,...)
    int    *hwChannel       // Index of the channel (connector) (0,1,...)
  );
  extern NCDGETAPPLCONFIG ncdGetApplConfig;
/*
Corresponding to ncdGetApplConfig this function sets the application
configuration, but it can also done in the CAN DRIVER CONFIGURATION.
If the application name does not exist, a new one is generated.
*/
  typedef Vstatus (_EXPORT_API *NCDSETAPPLCONFIG) (
    char   *appName,        // Name of Application
    int     appChannel,     // 0,1
    int     hwType,         // HWTYPE_xxxx
    int     hwIndex,        // Index of the hardware (slot) (0,1,...)
    int     hwChannel       // Index of the channel (connector) (0,1,...)
  );
  extern NCDSETAPPLCONFIG ncdSetApplConfig;

/*Get version information if available */
  typedef Vstatus (_EXPORT_API *NCDGETCHANNELVERSION) (
    unsigned long   ChannelIndex,   // Global channel index (0,1,...)
    unsigned long  *FwVersion,      // Firmware Version
    unsigned long  *HwVersion,      // Hardware Version
    unsigned long  *SerialNumber    // Hardware Serial Number
  );
  extern NCDGETCHANNELVERSION ncdGetChannelVersion;

/*Suppress Error Frames and ChipState Events */
  typedef Vstatus (_EXPORT_API *NCDSETRECEIVEMODE) (
    VportHandle     Port,        // Port Handle
    unsigned char   ErrorFrame,  // suppress Error Frames
    unsigned char   ChipState    // suppress Chip States
  );
  extern NCDSETRECEIVEMODE ncdSetReceiveMode;
#else
  Vstatus _EXPORT_DECL ncdGetApplConfig(
    char   *appName,        // Name of Application
    int     appChannel,     // 0,1
    int    *hwType,         // HWTYPE_xxxx
    int    *hwIndex,        // Index of the hardware (slot) (0,1,...)
    int    *hwChannel       // Index of the channel (connector) (0,1,...)
  );

  Vstatus _EXPORT_DECL ncdSetApplConfig(
    char   *appName,        // Name of Application
    int     appChannel,     // 0,1
    int     hwType,         // HWTYPE_xxxx
    int     hwIndex,        // Index of the hardware (slot) (0,1,...)
    int     hwChannel       // Index of the channel (connector) (0,1,...)
  );

  /*Get version information if available */
  Vstatus _EXPORT_DECL ncdGetChannelVersion(
    unsigned long   ChannelIndex,   // Global channel index (0,1,...)
    unsigned long  *FwVersion,      // Firmware Version
    unsigned long  *HwVersion,      // Hardware Version
    unsigned long  *SerialNumber    // Hardware Serial Number
  );

  /*Suppress Error Frames and ChipState Events */
  Vstatus _EXPORT_DECL ncdSetReceiveMode(
    VportHandle     Port,        // Port Handle
    unsigned char   ErrorFrame,  // suppress Error Frames
    unsigned char   ChipState    // suppress Chip States
  );
#endif


#ifdef DYNAMIC_CANDRIVER_DLL
  typedef Vstatus (_EXPORT_API *NCDADDACCEPTANCERANGE)(VportHandle     portHandle,
    Vaccess         accessMask,
    unsigned long   first_id,
    unsigned long   last_id
  );
  extern NCDADDACCEPTANCERANGE ncdAddAcceptanceRange;

  typedef Vstatus (_EXPORT_API *NCDREMOVEACCEPTANCERANGE)(VportHandle     portHandle,
    Vaccess         accessMask,
    unsigned long   first_id,
    unsigned long   last_id
  );
  extern NCDREMOVEACCEPTANCERANGE ncdRemoveAcceptanceRange;

  typedef Vstatus (_EXPORT_API *NCDRESETACCEPTANCE)(VportHandle     portHandle,
    Vaccess         accessMask,
    int             extended
  );
  extern NCDRESETACCEPTANCE ncdResetAcceptance;
#else
  Vstatus _EXPORT_DECL ncdAddAcceptanceRange(VportHandle    portHandle,
    Vaccess         accessMask,
    unsigned long   first_id,
    unsigned long   last_id
  );

  Vstatus _EXPORT_DECL ncdRemoveAcceptanceRange(VportHandle   portHandle,
    Vaccess         accessMask,
    unsigned long   first_id,
    unsigned long   last_id
  );

  Vstatus _EXPORT_DECL ncdResetAcceptance(VportHandle     portHandle,
    Vaccess         accessMask,
    int             extended
  );
#endif



#include <poppack.h>

#ifdef __cplusplus
}
#endif   // _cplusplus

#endif
