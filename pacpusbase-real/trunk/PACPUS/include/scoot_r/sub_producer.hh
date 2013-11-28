
#ifndef _SUB_PRODUCER_H_
#define _SUB_PRODUCER_H_

extern "C" {
#include "scoot_r/rt_cpp.h"
}


#include "scoot_r/message.hh"
#include "scoot_r/scooter_data.hh"
#include "scoot_r/l_e_s.hh"


#ifdef WIN32
DWORD WINAPI run_supervisor(LPVOID S);
#else
void run_supervisor(int S);
#endif



class Sub_Producer
{
public:

  NameType Name;
  NameType request_data_name;
  scooter_data *buffer_out;
  pL_e_s myL_e_s;
  int request_data_size ;
  int Producer_Priority;
  int channel;  
  int context;
  int port_index;
  RTIME max_period;
  RTIME min_period;
  RTIME max_recover;
  RTIME jitter;
  RTIME worst_case;
  Producer_Deposit *to_deposit; // the oject on which i can call the deposit method or the disconnected_producer method..
  
#ifdef WIN32
  friend DWORD WINAPI run_supervisor_flow(LPVOID S);
 #else
  friend void run_supervisor_flow(int S);
#endif
 
  PFlow myFlow;
  unsigned int Quality; // the producer dont run while this is 0
  
  int On; // boolean value which is TRUE if this producer is the current one for this service.
  RTIME last_time_set_quality ; // prevent the producer to set Quality up after the system
  RTIME time_creation ; // the max time.
  
  void supervisor(); // the supervisor task function, the one we control the producer behaviour.
  int Max_Pending_Request ;
  scooter_data **Pending_Request; // the array of data buffer where the low level software can recopy request

  RT_TASK *supervisor_task;
  SEM   *supervisor_sem;

  ObjectFlow *SD;  // the data structure to store the data to register.
  Descriptor_flow *DSD_flow; // a structure needed to send the previous one on the media.
  Safe_Send *SDSD; // a structure needed to send the previous one using the safe broadcast protocol
  public:
  Sub_Producer( pL_e_s myl_e_s,
		NameType *name,
		int producer_priority,
		int channel,
		int context,
		scooter_data *Request,
		NameType *request_type_name,
		int data_size,
		RTIME Worst_case, 
		RTIME Min_period, 
		RTIME Max_period,
		RTIME Max_recover,
		RTIME jitter,
		Producer_Deposit *to_Deposit
	      );

  virtual ~Sub_Producer();
  NameType *name(){ return & Name ;}
  int deposit(unsigned int *object, int size, int sync );
  int on(); // return TRUE if the producer is on FALSE elsewhere..
  int quality() { return Quality ;}
  int set_quality( unsigned int qualite) ;
    
  RTIME response_time_reg;
  RTIME response_net_time_reg;
  RTIME min_register_time;
  RTIME max_register_time;
  RTIME average_register_time;
  int nb_register;

#ifdef PROC_SCOOTER
  int read_proc(char *page, char**start, off_t off, int count, int *eof );
#endif

#ifdef STAT_SCOOTER
  // set the producer quality (must be set to non zero or the producer tu run).
  // dont do anithing but return FALSE if there is not at least 
  // 1 / MaxProducerRate second since last call
#endif
 };
#endif
