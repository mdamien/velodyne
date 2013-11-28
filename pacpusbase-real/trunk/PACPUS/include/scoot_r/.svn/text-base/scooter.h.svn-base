#ifndef SCOOTER_H 
#define SCOOTER_H

#ifdef WIN32
#include "win2000_scooter.h"
#define URTIME RTIME
#else
extern unsigned long long ma_div_64 (unsigned long long a, unsigned long b0);
#define URTIME unsigned long long 
#endif

#ifdef WIN32
#define CAST_INT( _obj_ ) _obj_ 
#else
#define CAST_INT( _obj_ ) (int)_obj_ 
#endif

////////////////////////////////////////////////////////////////
// the following constant value must be the same for all nodes
// in an interconnected scooter system.
// const int WORST_SYNCHRO = 1000; // 1 microseconds but
const int WORST_SYNCHRO = 128000; // more than 125 microsecond whith current sednet software.
const int L_E_S_WORST_REGISTER_TIME      =  10000000 ; // 10 milliseconds
// this is the worst case time for the l_e_s system to register
// any request to register or unregister any service.
// Every node in a network have to claim and verify the same value. 
// So it is a very important global specification parameter
// and the whole application have to be designed in such a way 
// that it verify safely this constraint.

////////////////////////////////////////////////////////////////

// these values are part of ths spec for each node in the system: these are
// standart value. but there is no problem to get various value for each of these
// but be sure that delay_to_send_data_message < L_E_S_WORST_REGISTER_TIME < delay_to_send_register_message

const int delay_to_send_data_message     =  500000; // 500 microsecondes
const int delay_to_send_register_message = 5000000; // 5 millisecondes 


const unsigned int SCOOT_R_IEEE1394_HIGHT_BASE_ADDRESS = 0x00003360; // the base address for our Application
const unsigned short SERVER_LOW_ADDRESS   = 0x0058; // from server to client (request)
const unsigned short CLIENT_LOW_ADDRESS   = 0x0054; // from server to client (reply)
const unsigned short CONSUMER_LOW_ADDRESS   = 0x0064; // from server to client (reply)
const unsigned short REGISTER_LOW_ADDRESS = 0x0050; // registering service
const unsigned short REGISTER_FLOW_LOW_ADDRESS = 0x0060; // registering service
const unsigned short ACK_LOW_ADDRESS = 0x005C; // acknowledge register service



// tasks implementing the scoot-r commnunication run in those priority level:
const unsigned int DEFAULT_SERVER_PRIORITY = 0x1000; //  
const unsigned int HIGHT_SCOOTR_PRIORITY = 0x2000; // reset 
const unsigned int STD_SCOOTR_PRIORITY   = 0x3000; // registering service
const unsigned int LOW_SCOOTR_PRIORITY   = 0x4000; // recopy incommming message to module buffer for low priority task

const unsigned int LOW_RT_PRIORITY      = 0xf000; // very low priority (server_log priority)
// but the lower priority is RT_LOWEST_PRIOTITY

const  RTIME set_quality_periode = 1000000000 ; // prevent the server to reset Quality up soon.
const RTIME PURGATORY_TIME = 2000000000 ; // prevent the server to reset Quality up  soon.

#ifndef WIN32
#define SEM_ERR 0xffff
#endif

const int MAX_NB_LES = 4; // The node cant be part of more than MAX_NB_LES undependant real time network.

#define NAME_SIZE 16
typedef struct
{
  unsigned int w1;
  unsigned int w2;
  unsigned int w3;
  unsigned int w4;
} NameType;

typedef struct{  
  NameType Name;
  NameType RequestName; int size_request; 
  NameType AncestorRequestName; int ancestor_size_request; 
  NameType ReplyName; int size_reply;
  RTIME WorstCase; RTIME min_period; RTIME max_recover;
} Client_data;

typedef struct{ 
  NameType Name; int server_priority;
  NameType RequestName; int size_request; 
  NameType AncestorReplyName; int ancestor_size_reply; 
  NameType ReplyName; int size_reply;
  int max_nb_clients;
  RTIME WorstCase; RTIME min_period; RTIME max_period;  RTIME max_recover;
} Server_data;

typedef struct {
    RTIME min;
    RTIME max;
} buf_net_times;

#endif
