
#ifndef _SUB_SERVER_H_
#define _SUB_SERVER_H_

#include "scoot_r/scooter_data.hh"
// #include <../src/l_e_s.hh>

const int DEFAULT_STACK_SIZE=8000;

#ifdef WIN32
DWORD WINAPI run_supervisor(LPVOID S);
DWORD WINAPI run_worker(LPVOID S);
#else
void run_supervisor(int S);
void run_worker(int S);
#endif

class Sub_Server
{
  NameType Name;

  NameType request_data_name;
  NameType reply_data_name;
  NameType ancestor_reply_data_name;
  int request_data_size ;
  int reply_data_size ;
  int ancestor_reply_data_size ;
  unsigned int* buffer_in;  // just a buffer for request 
  //  unsigned int *addr_buffer_in;
  unsigned int** buffer_out; // as many message buffers as clients for this server for reply
  pL_e_s myL_e_s;
  int Max_at_once_clients;
  unsigned int Server_Priority ;
  RTIME worst_case;
  RTIME max_period;
  RTIME min_period;
  RTIME max_recover;

  scooter_accept_server *to_accept; // the oject on which i can call the accept method or the disconnected_server method..


#ifdef WIN32
  friend DWORD WINAPI run_supervisor(LPVOID S);
  friend DWORD WINAPI run_worker(LPVOID S);
#else
  friend void run_supervisor(int S);
  friend void run_worker(int S);
#endif

  PService myService;
  unsigned int Quality; // the server dont run while this is 0
  // set it to 1 (when the server fail to respect time constraint) and to set it frequently to 0 an up
  int On; // boolean value which is TRUE if this server is the current one for this service.
  RTIME last_time_set_quality ; // prevent the server to set Quality up after the system
  RTIME time_creation ; // the max time.

  void supervisor(); // the supervisor task function, the one we control the server behaviour.
  void worker(); // the child task function, the one we do the real job.


  RT_TASK *supervisor_task;
  RT_TASK *worker_task;
  SEM     *supervisor_sem;
  SEM     *worker_sem;

  //  Server_Port *myport;
  int port_index; // the server port.
  // Some array, the range of which is the range of client index.
  int round_port; // used to allocate the client port number 
  int *client_addr; // the client host address.
  int *client_port; // the port for the client on its (remote) host.
  int *client_reply_size; // the size of the message to send back (sending more than needed by this client can be dangerous for the client host).
  RTIME *client_ExpireTimeLimit; // the limit date for the next request from this one.
  int *client_next_transaction_label; // I expect the next transaction as this label.
  PDescriptor *client_out_des;//per client descriptor set
  int alloc_client_port();

  int Max_Pending_Request ;
  scooter_data **Pending_Request; // the array of data buffer where the low level software can recopy request
  // used only for server with low priority tasks.

  Service_data *SD; // the data structure to store the data to register.
  Safe_Send *SDSD; // a structure needed to send the previous one using the safe broadcast protocol

public:
  Sub_Server( pL_e_s myl_e_s, NameType *name, 
	      int server_priority, int max_clients,
	      NameType *request_type_name,
	      int request_size,

	      NameType *reply_type_name,
	      int reply_size,
	      NameType *ancestor_type_name,
	      int ancestor_reply_type_size,
	      
	      RTIME Worst_case, RTIME Min_period, 
	      RTIME Max_period, RTIME Max_recover,
	      scooter_accept_server *to_server
	      );


  virtual ~Sub_Server();
  NameType *name(){ return & Name ;}
  
  int on();
  // return TRUE if the server is on FALSE elsewhere..


  //   data* (*accept)( data *ask, data* reply);
  // each time a request arrise, this routine is called: the argument is
  // a data of a type which have to be from the "type" returned by 
  // get_buffer_in.
  // It return an object the type of which is the same as get_buffer_out 
  // (really it is the same object). (a pointer to reply if this one is non NULL).

  //  void (*disconnected_server)();
  // if the local server is unvalidated, this routine is called,
  // in the server parent process
  // the argument is the server process id (as returned by "fork").
  // so the parent can wait for it or kill it or whatever is needed.

  
  int quality() { return Quality ;}
  int set_quality( unsigned int qualite) ;
  // set the server quality (must be set to non zero or the server tu run).
  // dont do anithing but return FALSE if there is not at least 
  // 1 / MaxServerRate second since last call
  virtual int stack_size() { return DEFAULT_STACK_SIZE ;}

#ifdef PROC_SCOOTER
  int read_proc(char *page, char**start, off_t off, int count, int *eof );
#ifdef STAT_SCOOTER
  RTIME response_time_tr;
  RTIME min_transaction_time;
  RTIME max_transaction_time;
  RTIME average_transaction_time;
  int nb_transactions;
  int nb_bad_transactions_too_late ;
  int nb_bad_transactions_out_of_sequence;
  int nb_bad_connexion;
  int nb_bad_transactions_address;
  int nb_bad_transactions_client_number;
  int nb_bad_transactions_invalid_creation_time;
  int nb_no_transactions;

  RTIME response_time_reg;
  RTIME response_net_time_reg;
  RTIME min_register_time;
  RTIME max_register_time;
  RTIME average_register_time;
  int nb_register;

#endif
#endif
};

#endif
