
#ifndef _CONTROL_H_
#define _CONTROL_H_

class Sub_Control;
class L_e_s;
class Message;

class scooter_control
{
  char *Name;
  L_e_s *myL_e_s;
  Sub_Control *sub;

protected:
  int init_server(); // to be called after the creation because there is things which can be done in the constructor. 
  // return 0 if no error.
public:
  scooter_control( char *name, scooter_l_e_s *myl_e_s );  
  virtual ~scooter_control();
  int new_quality( int suposed_quality, Register_data *register_data_buf )
  {  return new_quality( suposed_quality, register_data_buf, -1 ); }
  // each time the quality of the server for this service change
  // this routine return the new quality value.
  // If the argument is of a different value than the current
  // quality, the function return immediately the current value.
  int new_quality( int suposed_quality, Register_data *register_data_buf, RTIME until );
  // idem with an timeout parameter
};

#endif
