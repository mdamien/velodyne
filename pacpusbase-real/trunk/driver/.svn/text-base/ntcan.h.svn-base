/**************************************************************************
*                                                                         *
* ntcan.h -- NTCAN-API procedure declarations and constant definitions    *
*                                                                         *
* Copyright (c) 1997-2007, esd gmbh. All rights reserved.                 *
*                                                                         *
**************************************************************************/

#ifndef _ntcan_h_
#define _ntcan_h_

#ifdef __cplusplus
extern "C" {
#endif

#include <windows.h>

#if !defined(EXPORT)
#define EXPORT __declspec (dllexport)    /* Macro to export from DLL */
#endif

#if !defined(CALLTYPE)
#define CALLTYPE __cdecl
#endif

#ifndef UNDER_RTSS
# pragma comment(lib,"ntcan.lib")       /* Link with NTCAN.LIB (Only for VC++)*/
#else
# pragma comment(lib,"ntcan_rtss.lib")  /* Link with NTCAN_RTSS.LIB (Only for VC++)*/
#endif

/*------------------ Defines ------------------------------------------------*/
#define NTCAN_EV_BASE                   0x40000000
#define NTCAN_EV_USER                   0x40000080
#define NTCAN_EV_LAST                   0x400000FF

#define NTCAN_EV_CAN_ERROR              NTCAN_EV_BASE
#define NTCAN_EV_BAUD_CHANGE    (NTCAN_EV_BASE + 0x1)
#define NTCAN_EV_CAN_ERROR_EXT  (NTCAN_EV_BASE + 0x2)

/* mode in canOpen() */
#define NTCAN_MODE_NO_INTERACTION       0x00000100  /* No interaction                 */
#define NTCAN_MODE_MARK_INTERACTION     0x00000200  /* Mark interaction frames        */
#define NTCAN_MODE_LOCAL_ECHO           0x00000400  /* No interaction */
#define NTCAN_MODE_OVERLAPPED           0x20000000  /* Open for overlapped operations */
#define NTCAN_MODE_OBJECT               0x10000000  /* Open for Rx object mode        */


/* Queue-Size in canOpen() */
#define NTCAN_MAX_TX_QUEUESIZE          2047
#define NTCAN_MAX_RX_QUEUESIZE          2047
#define NTCAN_NO_QUEUE                  -1

/* Max for parameter net canOpen() */
#define NTCAN_MAX_NETS                  255

/* Flags in can-ids */
#define NTCAN_20B_BASE                  0x20000000

/* Flags in frame-length's  */
#define NTCAN_RTR                       0x10
#define NTCAN_NO_DATA                   0x20     /* Supported in object mode */
#define NTCAN_INTERACTION               0x20     /* Supported in FIFO mode   */

/* Defines for canSetBaudrate() / canGetBaudrate() */
#define NTCAN_USER_BAUDRATE             0x80000000  /* Configure BTR register     */
#define NTCAN_LISTEN_ONLY_MODE          0x40000000  /* Configure listen only mode */
#define NTCAN_USER_BAUDRATE_NUM         0x20000000  /* Numerical baudrate         */
#define NTCAN_NO_BAUDRATE               0x7FFFFFFF  /* No baudrate configured     */

/*
 * Predefined CiA-recommended baudrates for canSetBaudrate() / canGetBaudrate()
 * of the ESD baudrate table
 */
#define NTCAN_BAUD_1000			 0
#define NTCAN_BAUD_800			14
#define NTCAN_BAUD_500			 2
#define NTCAN_BAUD_250			 4
#define NTCAN_BAUD_125			 6
#define NTCAN_BAUD_100			 7
#define NTCAN_BAUD_50			 9
#define NTCAN_BAUD_20			11
#define NTCAN_BAUD_10			13 

/*------------------- error-codes--------------------------------------------*/
#define NTCAN_SUCCESS                   ERROR_SUCCESS
#define NTCAN_RX_TIMEOUT                0xE0000001
#define NTCAN_TX_TIMEOUT                0xE0000002
#define NTCAN_TX_ERROR                  0xE0000004
#define NTCAN_CONTR_OFF_BUS             0xE0000005
#define NTCAN_CONTR_BUSY                0xE0000006
#define NTCAN_CONTR_WARN                0xE0000007
#define NTCAN_NO_ID_ENABLED             0xE0000009
#define NTCAN_ID_ALREADY_ENABLED        0xE000000A
#define NTCAN_ID_NOT_ENABLED            0xE000000B
   
#define NTCAN_INVALID_FIRMWARE          0xE000000D
#define NTCAN_MESSAGE_LOST              0xE000000E
#define NTCAN_INVALID_HARDWARE          0xE000000F

#define NTCAN_PENDING_WRITE             0xE0000010
#define NTCAN_PENDING_READ              0xE0000011
#define NTCAN_INVALID_DRIVER            0xE0000012    /* wrong dll/driver-combination */

#define NTCAN_SOCK_CONN_TIMEOUT         0xE0000080
#define NTCAN_SOCK_CMD_TIMEOUT          0xE0000081
#define NTCAN_SOCK_HOST_NOT_FOUND       0xE0000082    /* gethostbyname() failed */

#define NTCAN_INVALID_PARAMETER         ERROR_INVALID_PARAMETER
#define NTCAN_INVALID_HANDLE            ERROR_INVALID_HANDLE
#define NTCAN_IO_INCOMPLETE             ERROR_IO_INCOMPLETE
#define NTCAN_IO_PENDING                ERROR_IO_PENDING
#define NTCAN_NET_NOT_FOUND             ERROR_FILE_NOT_FOUND  
#define NTCAN_INSUFFICIENT_RESOURCES    ERROR_NO_SYSTEM_RESOURCES

#define NTCAN_OPERATION_ABORTED         ERROR_OPERATION_ABORTED
#define NTCAN_WRONG_DEVICE_STATE        ERROR_NOT_READY
#define NTCAN_HANDLE_FORCED_CLOSE       ERROR_HANDLE_EOF
#define NTCAN_NOT_IMPLEMENTED           ERROR_INVALID_FUNCTION
#define NTCAN_NOT_SUPPORTED             ERROR_NOT_SUPPORTED
 
    /*
     * POSIX data types usually not defined in Windows so we define them
	 * now to prevent warnings 
     */
// _C_STD_BEGIN defined by Windows (stdint.h)
#ifndef _C_STD_BEGIN
#ifndef _WIN64
typedef unsigned char     uint8_t;
typedef signed   char     int8_t;
typedef unsigned short    uint16_t;
typedef signed   short    int16_t;
typedef unsigned long     uint32_t;
typedef signed   long     int32_t;
#else
typedef unsigned __int8   uint8_t;
typedef signed __int8     int8_t;
typedef unsigned __int16  uint16_t;
typedef signed __int16    int16_t;
typedef unsigned __int32  uint32_t;
typedef signed __int32    int32_t;
#endif
#endif
typedef unsigned __int64  uint64_t;
typedef signed __int64    int64_t;
typedef DWORD             NTCAN_RESULT;
typedef HANDLE            NTCAN_HANDLE;


#pragma pack(1)

typedef struct
{
  int32_t       id;             /* can-id                                   */
  uint8_t       len;            /* length of message: 0-8                   */
  uint8_t       msg_lost;       /* count of lost rx-messages                */
  uint8_t       reserved[2];    /* reserved                                 */
  uint8_t       data[8];        /* 8 data-bytes                             */
} CMSG;

typedef struct
{
  int32_t id;                   /* can-id                                    */
  uint8_t len;                  /* length of message: 0-8                    */
  uint8_t msg_lost ;            /* count of lost rx-messages                 */
  uint8_t reserved[2] ;         /* reserved                                  */
  uint8_t data[8] ;             /* 8 data-bytes                              */
  uint64_t timestamp ;          /* time stamp of this message                */
} CMSG_T;

typedef struct
{
  int32_t       evid;          /* event-id: possible range:EV_BASE...EV_LAST */
  uint8_t       len;           /* length of message: 0-8                     */
  uint8_t       reserved[3];   /* reserved                                   */
  union
  {
    uint8_t  c[8];
    uint16_t s[4];
    uint32_t l[2];
  } evdata;
} EVMSG;


typedef struct
{
  uint16_t hardware;
  uint16_t firmware;
  uint16_t driver;
  uint16_t dll;
  uint32_t boardstatus;
  uint8_t  boardid[14];
  uint16_t features;
} CAN_IF_STATUS;

typedef struct
{
  int32_t id;
  int32_t flags;
  uint64_t time_start;
  uint64_t time_interval;
  uint8_t reserved[8];
} CSCHED;

#pragma pack()

/*
 * Interface/Driver feature flags
 */
#define NTCAN_FEATURE_FULL_CAN         (1<<0) /* Full CAN controller          */
#define NTCAN_FEATURE_CAN_20B          (1<<1) /* CAN 2.OB support             */
#define NTCAN_FEATURE_DEVICE_NET       (1<<2) /* Device net adapter           */
#define NTCAN_FEATURE_CYCLIC_TX        (1<<3) /* Cyclic Tx support            */
#define NTCAN_FEATURE_RX_OBJECT_MODE   (1<<4) /* Rx object mode support       */
#define NTCAN_FEATURE_TIMESTAMP        (1<<5) /* Timestamp support            */
#define NTCAN_FEATURE_LISTEN_ONLY_MODE (1<<6) /* Listen-only-mode support     */
#define NTCAN_FEATURE_SMART_DISCONNECT (1<<7) /* Go-from-bus-after-last-close */

/*
 * IOCTL codes for canIoctl()
 */
#define NTCAN_IOCTL_FLUSH_RX_FIFO         0x0001   /* Flush Rx FIFO           */
#define NTCAN_IOCTL_GET_RX_MSG_COUNT      0x0002   /* Ret # CMSG in Rx FIFO   */
#define NTCAN_IOCTL_GET_RX_TIMEOUT        0x0003   /* Ret configured Rx tout  */
#define NTCAN_IOCTL_GET_TX_TIMEOUT        0x0004   /* Ret configured Tx tout  */
#define NTCAN_IOCTL_SET_20B_HND_FILTER    0x0005   /* Set 2.0B filter mask    */
#define NTCAN_IOCTL_GET_SERIAL            0x0006   /* Get HW serial number    */
#define NTCAN_IOCTL_GET_TIMESTAMP_FREQ    0x0007   /* Get timestamp frequency in Hz  */
#define NTCAN_IOCTL_GET_TIMESTAMP         0x0008   /* Get timestamp counter   */  
#define NTCAN_IOCTL_ABORT_RX              0x0009   /* Abort pending Rx I/O    */
#define NTCAN_IOCTL_ABORT_TX              0x000A   /* Abort pending Tx I/O    */
#define NTCAN_IOCTL_SET_RX_TIMEOUT        0x000B   /* Change Rx timeout       */
#define NTCAN_IOCTL_SET_TX_TIMEOUT        0x000C   /* Change Rx timeout       */
#define NTCAN_IOCTL_TX_OBJ_CREATE         0x000D   /* Create obj, arg->CMSG          */
#define NTCAN_IOCTL_TX_OBJ_AUTOANSWER_ON  0x000E   /* Switch autoanswer on,arg->CMSG */
#define NTCAN_IOCTL_TX_OBJ_AUTOANSWER_OFF 0x000F   /* Switch autoanswer off,arg->CMSG*/
#define NTCAN_IOCTL_TX_OBJ_UPDATE         0x0010   /* update  obj, arg->CMSG         */ 
#define NTCAN_IOCTL_TX_OBJ_DESTROY        0x0011   /* Destroy obj, arg->id           */

#define NTCAN_IOCTL_TX_OBJ_SCHEDULE_START 0x0013   /* Start scheduling for handle    */
#define NTCAN_IOCTL_TX_OBJ_SCHEDULE_STOP  0x0014   /* Stop scheduling for handle     */ 
#define NTCAN_IOCTL_TX_OBJ_SCHEDULE       0x0015   /* Set sched. for obj,arg->CSCHED */

/*
 *	Types for canFormatError()
 */
#define NTCAN_ERROR_FORMAT_LONG        0x0000   /* Error text as string   */
#define NTCAN_ERROR_FORMAT_SHORT       0x0001   /* Error code as string   */

/*
 * Exports
 */
EXPORT NTCAN_RESULT CALLTYPE canSetBaudrate(
                NTCAN_HANDLE   handle,      /* nt-handle                     */
                uint32_t       baud );      /* baudrate-constant             */

EXPORT NTCAN_RESULT CALLTYPE canGetBaudrate(    /* ret NTCAN_OK, if success  */    
                NTCAN_HANDLE   handle,      /* nt-handle                     */
                uint32_t       *baud );     /* baudrate-constant             */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canOpen(      /* ret NTCAN_OK, if success       */
                int          net,          /* net number                     */
                uint32_t     flags,        /*                                */
                int32_t      txqueuesize,  /* nr of entries in message queue */
                int32_t      rxqueuesize,  /* nr of entries in message queue */
                int32_t      txtimeout,    /* tx-timeout in milliseconds     */
                int32_t      rxtimeout,    /* rx-timeout in milliseconds     */
                NTCAN_HANDLE *handle );    /* out: nt-handle                 */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canClose(        /* ret NTCAN_OK, if success         */
                NTCAN_HANDLE  handle );  /* handle                           */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE      canIdAdd(  /* ret NTCAN_OK, if success         */
                NTCAN_HANDLE  handle,    /* read handle                      */
                int32_t       id  );     /* can identifier                   */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE      canIdRangeAdd(  /* ret NTCAN_OK, if success    */
                NTCAN_HANDLE  handle,    /* read handle                      */
                int32_t       idStart,   /* 1st can identifier               */
                int32_t       idEnd  );  /* last can identifier              */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canIdDelete(    /* ret NTCAN_OK, if success         */
                NTCAN_HANDLE  handle,    /* read handle                      */
                int32_t       id  );     /* can identifier                   */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canIdRangeDelete( /* ret 0, if success              */
                NTCAN_HANDLE  handle,    /* read handle                      */
                int32_t       idStart,   /* 1st can identifier               */
                int32_t       idEnd  );  /* last can identifier              */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canGetOverlappedResult( /* ret NTCAN_OK, if success */
                NTCAN_HANDLE  handle,    /* handle                           */
                OVERLAPPED    *ovrlppd,  /* overlapped-structure             */
                int32_t       *len,      /* out: cnt of available CMSG-Buffer*/
                BOOL          bWait );   /* FALSE =>do not wait, else wait   */ 
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canTake(        /* ret 0, if success                */
                NTCAN_HANDLE  handle,    /* handle                           */
                CMSG          *cmsg,     /* ptr to data-buffer               */
                int32_t       *len );    /* out: size of CMSG-Buffer         */
                                         /* in:  count of read messages      */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canRead(        /* ret 0, if success                */
                NTCAN_HANDLE  handle,    /* handle                           */
                CMSG          *cmsg,     /* ptr to data-buffer               */
                int32_t       *len,      /* out: size of CMSG-Buffer         */ 
                                         /* in:  count of read messages      */
                OVERLAPPED    *ovrlppd); /* NULL or overlapped-structure     */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canSend(        /* ret 0, if success                */
                NTCAN_HANDLE  handle,    /* handle                           */
                CMSG          *cmsg,     /* ptr to data-buffer               */
                int32_t       *len );    /* size of CMSG-Buffer              */ 
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canWrite(       /* ret 0, if success                */
                NTCAN_HANDLE  handle,    /* handle                           */
                CMSG          *cmsg,     /* ptr to data-buffer               */
                int32_t       *len,      /* size of CMSG-Buffer              */ 
                OVERLAPPED    *ovrlppd); /* NULL or overlapped-structure     */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canReadEvent(
                NTCAN_HANDLE  handle,    /* handle                           */
                EVMSG         *evmsg,    /* ptr to event-msg-buffer          */
                OVERLAPPED    *ovrlppd); /* NULL or overlapped-structure     */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canSendEvent(
                NTCAN_HANDLE  handle,    /* handle                           */
                EVMSG         *evmsg );  /* ptr to event-msg-buffer          */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canStatus(
                NTCAN_HANDLE  handle,    /* handle                           */
                CAN_IF_STATUS *cstat );  /* ptr to can-status-buffer         */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canIoctl(
                NTCAN_HANDLE  handle,  /* handle                             */
                uint32_t      ulCmd,   /* Command                            */
                void *        pArg );  /* Ptr to command specific argument   */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canTakeT(
                NTCAN_HANDLE  handle,    /* In: handle                       */
                CMSG_T        *cmsg_t,   /* In: ptr to receive buffer        */
                int32_t       *len );    /* out: size of CMSG_T-Buffer       */
                                         /* in:  count of read messages      */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canReadT(
                NTCAN_HANDLE  handle,    /* In: handle                       */
                CMSG_T        *cmsg_t,   /* Int ptr to receive buffer        */
                int32_t       *len,      /* out: size of CMSG_T-Buffer       */
                                         /* in:  count of read messages      */
                OVERLAPPED    *ovrlppd); /* In: always NULL                  */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canSendT(   /* ret 0, if success                */
                NTCAN_HANDLE  handle,    /* handle                           */
                CMSG_T        *cmsg_t,   /* ptr to data-buffer               */
                int32_t       *len );    /* size of CMSG-Buffer              */ 
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canWriteT(   /* ret 0, if success               */
                NTCAN_HANDLE  handle,    /* handle                           */
                CMSG_T        *cmsg_t,   /* ptr to data-buffer               */
                int32_t       *len,      /* size of CMSG-Buffer              */ 
                OVERLAPPED    *ovrlppd); /* NULL or overlapped-structure     */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canFormatError( /* ret 0, if success           */
                NTCAN_RESULT  error,     /* error code                       */
                uint32_t      type,      /* error message type               */
                char          *pBuf,     /* pointer to destination buffer    */
                uint32_t      bufsize);  /* Size of the buffer above         */

#ifndef UNDER_RTSS

/*
 * Function pointer to ease loading DLL dynamically
 */
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_SET_BAUDRATE)(NTCAN_HANDLE handle,
                                                      uint32_t     baud);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_GET_BAUDRATE)(NTCAN_HANDLE handle,
                                                      uint32_t     *baud);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_OPEN)(int          net,
                                              uint32_t     flags,
                                              int32_t      txqueuesize,
                                              int32_t      rxqueuesize,
                                              int32_t      txtimeout,
                                              int32_t      rxtimeout,
                                              NTCAN_HANDLE *handle );
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_CLOSE)(NTCAN_HANDLE handle);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_ID_ADD)(NTCAN_HANDLE handle,
                                                int32_t      id);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_ID_DELETE)(NTCAN_HANDLE handle,
                                                   int32_t id);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_GET_OVERLAPPED_RESULT)(NTCAN_HANDLE handle,
                                                               OVERLAPPED   *ovrlppd,
                                                               int32_t      *len,
                                                               BOOL         bWait);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_SEND)(NTCAN_HANDLE handle,
                                              CMSG         *cmsg,
                                              int32_t      *len);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_WRITE)(NTCAN_HANDLE handle,
                                               CMSG         *cmsg,
                                               int32_t      *len,
                                               OVERLAPPED   *ovrlppd);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_TAKE)(NTCAN_HANDLE handle,
                                              CMSG         *cmsg,
                                              int32_t      *len);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_READ)(NTCAN_HANDLE handle,
                                              CMSG         *cmsg,
                                              int32_t      *len,
                                              OVERLAPPED   *ovrlppd);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_READ_EVENT)(NTCAN_HANDLE handle,
                                                    EVMSG        *cmsg,
                                                    OVERLAPPED   *ovrlppd);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_SEND_EVENT)(NTCAN_HANDLE handle,
                                                    EVMSG        *cmsg);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_STATUS)(NTCAN_HANDLE  handle,
                                                CAN_IF_STATUS *cstat);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_IOCTL)(NTCAN_HANDLE handle,
                                               uint32_t     ulCmd,
                                               void         *pArg );
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_TAKE_T)(NTCAN_HANDLE handle,
                                                CMSG_T       *cmsg_t,
                                                int32_t      *len);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_READ_T)(NTCAN_HANDLE handle,
                                                CMSG_T       *cmsg_t,
                                                int32_t      *len,
                                                OVERLAPPED   *ovrlppd);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_SEND_T)(NTCAN_HANDLE handle,
                                                CMSG_T       *cmsg_t,
                                                int32_t      *len);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_WRITE_T)(NTCAN_HANDLE handle,
                                                 CMSG_T       *cmsg_t,
                                                 int32_t      *len,
                                                 OVERLAPPED   *ovrlppd);

typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_FORMAT_ERROR)(NTCAN_RESULT  error,
                                                      uint32_t      type,
                                                      char          *pBuf,
                                                      uint32_t      bufsize);



/*
 * Macros to ease loading DLL dynamically
 */
#define FUNCPTR_CAN_SET_BAUDRATE(hDll) \
(PFN_CAN_SET_BAUDRATE)GetProcAddress(hDll, "canSetBaudrate")
#define FUNCPTR_CAN_GET_BAUDRATE(hDll) \
(PFN_CAN_GET_BAUDRATE)GetProcAddress(hDll, "canGetBaudrate")
#define FUNCPTR_CAN_OPEN(hDll) \
(PFN_CAN_OPEN)GetProcAddress(hDll, "canOpen")
#define FUNCPTR_CAN_CLOSE(hDll) \
(PFN_CAN_CLOSE)GetProcAddress(hDll, "canClose")
#define FUNCPTR_CAN_ID_ADD(hDll) \
(PFN_CAN_ID_ADD)GetProcAddress(hDll, "canIdAdd")
#define FUNCPTR_CAN_ID_DELETE(hDll) \
(PFN_CAN_ID_DELETE)GetProcAddress(hDll, "canIdDelete")
#define FUNCPTR_CAN_SEND(hDll) \
(PFN_CAN_SEND)GetProcAddress(hDll, "canSend")
#define FUNCPTR_CAN_WRITE(hDll) \
(PFN_CAN_WRITE)GetProcAddress(hDll, "canWrite")
#define FUNCPTR_CAN_TAKE(hDll) \
(PFN_CAN_TAKE)GetProcAddress(hDll, "canTake")
#define FUNCPTR_CAN_READ(hDll) \
(PFN_CAN_READ)GetProcAddress(hDll, "canRead")
#define FUNCPTR_CAN_SEND_EVENT(hDll) \
(PFN_CAN_SEND_EVENT)GetProcAddress(hDll, "canSendEvent")
#define FUNCPTR_CAN_READ_EVENT(hDll) \
(PFN_CAN_READ_EVENT)GetProcAddress(hDll, "canReadEvent")
#define FUNCPTR_CAN_STATUS(hDll) \
(PFN_CAN_STATUS)GetProcAddress(hDll, "canStatus")
#define FUNCPTR_CAN_IOCTL(hDll) \
(PFN_CAN_IOCTL)GetProcAddress(hDll, "canIoctl")
#define FUNCPTR_CAN_SEND_T(hDll) \
(PFN_CAN_SEND_T)GetProcAddress(hDll, "canSendT")
#define FUNCPTR_CAN_WRITE_T(hDll) \
(PFN_CAN_WRITE_T)GetProcAddress(hDll, "canWriteT")
#define FUNCPTR_CAN_TAKE_T(hDll) \
(PFN_CAN_TAKE_T)GetProcAddress(hDll, "canTakeT")
#define FUNCPTR_CAN_READ_T(hDll) \
(PFN_CAN_READ_T)GetProcAddress(hDll, "canReadT")
#define FUNCPTR_CAN_FORMAT_ERROR(hDll) \
(PFN_CAN_FORMAT_ERROR)GetProcAddress(hDll, "canFormatError")
#endif /* of !defined UNDER_RTSS */

#ifdef __cplusplus
}
#endif

#endif /* _ntcan_h_ */

