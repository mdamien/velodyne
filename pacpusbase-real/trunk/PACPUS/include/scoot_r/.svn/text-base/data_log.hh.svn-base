#ifndef _DATA_LOG_H_
#define _DATA_LOG_H_

#include "scooter_remote_server.hh"

const long TAILLE_MAX = 200;

#define printf_log S_LOG->log


class log_request : public scooter_sample
{
	
  char* caract;
  char buff[ TAILLE_MAX +1];

public:
  
  log_request()
  {
    caract = buff;
  }

  virtual ~log_request(){}
  
  virtual char* my_type_name( int ancestor )
  { 
    if( ancestor == 0 ) return "log_request";  
    else return scooter_sample::my_type_name( ancestor-1 ); 
  }
  virtual int size( int ancestor ) 
  { 
    if( ancestor == 0 ) return sizeof( log_request ); 
    else return scooter_sample::size( ancestor-1 );
  }
    
  char* car() { return buff;}
  void set_car( const char *format , ... ) ;	
};


class Remote_Server_log : public scooter_remote_server
{
  log_request Send;
  scooter_data Back;
  RTIME date_1, date_2;

public:
  Remote_Server_log( char *name, scooter_l_e_s *myl_e_s ) : scooter_remote_server( name, myl_e_s ){}
  void log( const char *format, ... ); // used as printf

  virtual RTIME worst_case() {  return 50000000 ;   } // 50 milli
  virtual RTIME min_period() {  return 100000000;   } // 100 milli = 10 Hertz

protected:
  virtual void type_mismatch()    {    }
  virtual void timeout_too_short(){    }
  virtual void timeout()          {    }
  virtual void server_down()      {    }
  virtual void too_many_clients() {    }
  virtual void rate_too_hight()   {    }
  virtual void overrate()         {    }
};

extern Remote_Server_log *S_LOG;

#endif


