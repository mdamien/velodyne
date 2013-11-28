
#ifndef _REMOTE_SUB_SERVEUR_H_
#define _REMOTE_SUB_SERVEUR_H_

extern "C" {
#include "scoot_r/rt_cpp.h"
}


#include "scoot_r/message.hh"
#include "scoot_r/scooter_data.hh"

class Client_Port;

class Remote_Sub_Server
{
  NameType Name;

  NameType request_data_name;
  NameType reply_data_name;
  NameType ancestor_request_data_name;
  int request_data_size ;
  int reply_data_size ;
  int ancestor_request_data_size ;

  RTIME worst_case; RTIME min_period; RTIME max_recover;

  pL_e_s myL_e_s;
  PService myPService;
  Service_data *myService_data;
  RTIME server_creation_time;// the time the server i used was created
  RTIME last_request_time;// the time i ask for the service
  SEM     *client_sem;  Client_Port *port;  int port_index;
  Descriptor *out_des;

  Service_data *SD; // the data structure to store the data to unregister the current server if it dont reply..
  Safe_Send *SDSD; // a structure needed to send the previous one using the safe broadcast protocol

  int NB_CLIENTDOWN ;

  RTIME current_request_time; // used by call_no_log
  unsigned int request_MULTIFIELD ; // used by call_no_log
  RTIME current_period;
  RTIME max_period;
  int next_transaction_label; // I expect the next transaction as this label.

  int asked_input_buffer; // store get_buffer_in()->size();

  unsigned int* buffer_request;
  unsigned int* buffer_reply;
  scooter_data en_tete;
#ifdef PROC_SCOOTER
#ifdef STAT_SCOOTER
  long nb_transactions;
  RTIME average_transaction_time;
  RTIME min_transaction_time ;
  RTIME max_transaction_time;

  long  nb_server_down_exception;
  long  nb_timeout_exception;
  long  nb_type_mismatch_exception;
  long  nb_timeout_too_short_exception;
  long  nb_recover_timeout_too_short_exception;
  long  nb_rate_too_hight_exception;
  long  nb_overrate_exception;
  long  nb_strange_timeout_exception;
  long  nb_too_many_clients_exception;
  long  nb_reset_server_down_exception;
  
  long  nb_ignore_reply;
  long  nb_bad_reply_messages;

#endif
#endif

public:
  Remote_Sub_Server( pL_e_s myl_e_s, NameType *name, 
		     NameType *request_type_name,
		     int request_size,
		     NameType *ancestor_type_name,
		     int ancestor_request_type_size,
		     unsigned int *buf_request,
		 
		     NameType *reply_type_name,
		     int reply_size,

		     RTIME Worst_case, RTIME Min_period, RTIME Max_recover
		 );

  ~Remote_Sub_Server();
  NameType *name(){ return &Name ;}

  Message *call_no_log( unsigned int **get_back );
  // this method allow access to remote or local servers.
  // the request to be send is stored in buffer_in()
  // get_back contain an address to where to get back the address for the result.
  // 
  // the following error Message could be returned:
  //     TIMEOUT :       timeout expire and the delay is at least the 
  //                     worst case server + max nominal network delay,
  //                     So the server is probabbly faulty and the network 
  //                     software have discarded it.
  //     SERVER_DOWN: the client allow a delay sufficient but there 
  //                     is no server or this one comme up too late.
  //                     raise before timeout expire: when the time for 
  //                     the server to do its work is NULL.
  //     TIMEOUT_TOO_SHORT : the client allow a time shorter to the worst
  //                     case server + max nominal network delay nothing
  //                     is done just constat it cant work safely.,
  //     TYPE_MISMATCH : send_to or get_back are off uncompatible type 
  //                     for this server : there is a conception or 
  //                     configuration bug.
  //     TOO_MANY_CLIENTS: There is already as many clients as this server
  //                     can accept. The server receive the request
  //                     but refuse it.
  //     RATE_TOO_HIGHT: the rate required  by the client is more than can 
  //                     support the server
  //     OVERRATE:       the client ask for the service too frequently.
  // the call function attempt to send messages to the log server whenever
  // such an exception occur.

#ifdef PROC_SCOOTER
  int read_proc(char *page, char**start, off_t off, int count, int *eof );
#endif
};

#endif
