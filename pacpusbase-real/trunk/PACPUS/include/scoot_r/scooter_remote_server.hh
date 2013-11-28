
#ifndef _REMOTE_SERVEUR_H_
#define _REMOTE_SERVEUR_H_

#include "scooter_data.hh"

class Remote_Sub_Server;
class L_e_s;
class Message;

class scooter_remote_server
{
  NameType Name;
  L_e_s *myL_e_s;
  Remote_Sub_Server *sub;
  unsigned int *buffer_request;
  unsigned int *buffer_reply;

  int size_request; int size_reply; // usefull for the lxrt extension

protected:
  void init_remote_server(); // called only the first time the service is used

public:
  scooter_remote_server( char *name, scooter_l_e_s *myl_e_s );
  virtual ~scooter_remote_server();
  NameType *name(){ return & Name ;}
  int max_msg_size(){ if( size_request > size_reply ) return size_request; else return size_reply; } 

  virtual scooter_data* get_buffer_request() =0;
  // an object of the good class type but nothing usefull inside

  virtual scooter_data* get_buffer_reply( ) =0;
  // no data acquisition or command completion, only return
  // an object of the good class type.

  //  virtual Message *call( data *send_to, data *get_back );
  Message *call( scooter_data **get_back );
  // this method allow access to remote or local servers.
  // the request to be send is stored in get_buffer_in()
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

  virtual RTIME worst_case() = 0;
  virtual RTIME min_period() = 0;
  virtual RTIME max_recover() = 0;
  // the time i expect a server to recover in case of incident.
  // may integrate time to unregister and reregister the service and the time needed for the current remote_server and for the server to send their unregister and register message on the bus that is the time the current remote server need tot send on the bus plus  the_server->max_recover()+2*L_E_S_WORST_REGISTER_TIME;

  //  virtual Message *call_no_log( data *send_to, data *get_back );
  Message *call_no_log( scooter_data **get_back );
  // idem call but no log in case of exception ("call" use it).

protected: // called by the "call" function when exception occurs in order to send the log messages..
  virtual void type_mismatch();
  virtual void timeout_too_short();
  virtual void timeout();
  virtual void server_down();
  virtual void too_many_clients();
  virtual void rate_too_hight();
  virtual void overrate();
};

#endif
