#ifndef _SUB_CONSUMER_H_
#define _SUB_CONSUMER_H_

#include "scoot_r/scooter_data.hh"

class Consumer_Port;

class Sub_Consumer
{
  NameType Name;
  NameType request_data_name;
  int request_data_size ;
  int channel;
  int context;
  unsigned int*request;

  RTIME worst_case; RTIME min_period; RTIME max_recover; RTIME jitter;

  pL_e_s myL_e_s;
  PFlow myPFlow;
  ObjectFlow *myFlow_data;
  RTIME consumer_creation_time;// the time the producer i used was created
  SEM  *consumer_sem[MAX_NODE_CONSUMMERS]; // one semaphore by consumer
  Consumer_Port *port;
  int port_index;
  Descriptor *out_des;
  
  ObjectFlow *SD; // the data structure to store the data to unregister the current producer if it dont request..
  Safe_Send *SDSD; // a structure needed to send the previous one using the safe broadcast protocol
  RTIME max_period;
  int asked_input_buffer; 

public:
  Sub_Consumer( pL_e_s myl_e_s, NameType *name, 
		unsigned int *Request,
		NameType *request_type_name,
		int request_size,
		int context,
		RTIME Worst_case, RTIME Min_period, RTIME Max_recover, RTIME Jitter
		);
  
  ~Sub_Consumer();
  NameType *name(){ return &Name ;}

  int get_channel();
  void need_buffer( int packet_length);
#ifdef PROC_SCOOTER
  int read_proc(char *page, char**start, off_t off, int count, int *eof );
#endif
};

#endif
