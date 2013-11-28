#ifndef SCOOTER_HH 
#define SCOOTER_HH

#include "scooter.h"

class scooter_l_e_s
{
public:
  virtual unsigned int local_addr() = 0 ; // the local node address for this network
  virtual void net_timestamp_min(RTIME *min) = 0; // get the network synchronized time
  virtual void net_timestamp_max(RTIME *max) = 0; // get the network synchronized time
  virtual void net_timestamp(RTIME *min, RTIME *max) = 0; // get the network synchronized time
  virtual unsigned int nb_reset() = 0; 
};

// class L_e_s ; // a descendant of the previous class ...
// typedef scooter_l_e_s *pL_e_s;


extern scooter_l_e_s *find_l_e_s( int N );

#endif
