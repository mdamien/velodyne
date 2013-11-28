
#ifndef _CONSUMER_H_
#define _CONSUMER_H_

#include "scoot_r/scooter_data.hh"
#include "scoot_r/l_e_s.hh"

class Sub_Consumer;
class L_e_s;
class Message;

class Consumer
{
  NameType Name;
  L_e_s *myL_e_s;
  int context;
  Sub_Consumer *sub;
  int size_reply; // usefull for the lxrt extension
  
protected:
  void init_consumer(); // called only the first time the service is used

public:
  
  Consumer( char *name, scooter_l_e_s *myl_e_s );
  virtual ~Consumer();
  NameType name(){ return  Name ;}

  virtual scooter_data* get_buffer_reply() = 0;
  // no data acquisition or command completion, only return
  // an object of the good class type.

  virtual RTIME worst_case() = 0;
  virtual RTIME min_period() = 0;
  virtual RTIME max_recover() = 0;
  virtual RTIME jitter() = 0;

  int get_channel();
  int get_context();
  
  void need_buffer( int packet_length);

  virtual int consume( int channel, int context ) = 0;

};

#endif
