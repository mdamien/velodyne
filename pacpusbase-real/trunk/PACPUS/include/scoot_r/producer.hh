#ifndef _PRODUCER_H_
#define _PRODUCER_H_

#include "scooter_data.hh"

class Sub_Producer;
class L_e_s;
class Message;

class Producer_Deposit
{
public:
  virtual void disconnected_producer(){};
  // if the local producer is unvalidated, this routine is called,
  // in the producer parent process
  // the argument is the producer process id (as returned by "fork").
  // so the parent can wait for it or kill it or whatever is needed.
};

class Producer:public Producer_Deposit
{
  char *Name;
  unsigned int *out;
  int size_object;
  L_e_s * myL_e_s;
  int Producer_Priority;
  Sub_Producer *sub;
  int data_size; // useful for the lxrt extension
  int channel;
  int context;

protected:
  int init_producer(); // to be called after the creation because there is things which can be done in the constructor. 
  // return 0 if no error.

public:
  Producer(char *name, scooter_l_e_s *myl_e_s, int producer_priority);  
  virtual ~Producer();
  char *name(){ return Name ;}
  
  int on();
  // return TRUE if the producer is on FALSE elsewhere..
  virtual scooter_data* get_buffer_out() = 0;
  
  // no data acquisition or command completion, only return
  // an object of the good class type.
  
  virtual RTIME max_period(){return 1000;} 
  virtual RTIME min_period(){return 10;} 
  virtual RTIME max_recover(){return 100;}
  virtual RTIME jitter(){return 200;}
  virtual RTIME worst_case(){return 100;} 
  int deposit(scooter_data *object, int size, int sync);
  int producer_priority();
  int get_channel();
  int get_context();
  int quality();
  int set_quality( unsigned int qualite) ;
  // set the producer quality (must be set to non zero or the producer tu run).
  // dont do anithing but return FALSE if there is not at least 
  // 1 / MaxProducerRate second since last call
};

#endif

