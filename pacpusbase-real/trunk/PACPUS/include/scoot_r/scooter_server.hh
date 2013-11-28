
#ifndef _SERVER_H_
#define _SERVER_H_

#include "scooter_data.hh"

class Sub_Server;
class L_e_s;
class Message;

class scooter_accept_server
{
public:
  virtual void low_accept( unsigned int *ask, unsigned int *reply) = 0;
  //  virtual void disconnected_server() {}
  // if the local server is unvalidated, this routine is called,
  // in the server parent process
  // the argument is the server process id (as returned by "fork").
  // so the parent can wait for it or kill it or whatever is needed.
};

class Xscooter_server; // different in rtai or lxrt.

class scooter_server: public scooter_accept_server
{
  friend class Xscooter_server;
  NameType Name;
  L_e_s *myL_e_s;
  int Max_Clients;
  Sub_Server *sub;
  Xscooter_server *xserver;

protected:
  int init_server(); // to be called after the creation because there is things which can be done in the constructor. 
  // return 0 if no error.
  void low_accept( unsigned int *ask, unsigned int *reply);
  virtual void accept( scooter_data *ask, scooter_data* reply) =0;
  // each time a request arrise, this routine is called: the argument is
  // a data of a type which have to be from the "type" returned by 
  // get_buffer_in.
  // It return an object the type of which is the same as get_buffer_out 
  // (really it is the same object). (a pointer to reply if this one is non NULL).


public:
  scooter_server( char *name, scooter_l_e_s *myl_e_s );  
  virtual ~scooter_server();
  //  NameType *name(){ return & Name ;}
  
  int on();
  // return TRUE if the server is on FALSE elsewhere..

  virtual scooter_data* get_buffer_in() =0;
  // an object of the good class type but nothing usefull inside

  virtual scooter_data* get_buffer_out() =0;
  // no data acquisition or command completion, only return
  // an object of the good class type.
  
  virtual RTIME worst_case() = 0;
  virtual RTIME max_period() = 0;
  virtual RTIME min_period() = 0;
  virtual RTIME max_recover() = 0;
  virtual int max_at_once_clients() { return 3; }
  virtual int server_priority() { return DEFAULT_SERVER_PRIORITY ; } // default server  priority
  virtual int stack_size() { return 0; } // default RTAIor lxrt stack size

  int quality();
  int set_quality( unsigned int qualite) ;
  // set the server quality (must be set to non zero or the server tu run).
  // dont do anithing but return FALSE if there is not at least 
  // 1 / MaxServerRate second since last call
};

#endif
