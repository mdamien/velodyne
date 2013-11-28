/* * Last edited: Feb 18 19:14 1993 (crubille) */

//////////////////////////////////////////////////////////////
//						ATTENTION							//
//////////////////////////////////////////////////////////////


// It is very important to undestand how work the "data" class
// before writing new client/serveur application.

// it is required to write correct "net_to-host", "host_to_net" 
// protected method and "size", "ancestor" and 
// "my_type_name" public method

// "net_to-host" and "host_to_net" methods have to call the 
// direct ancestor method "net_to-host" or "host_to_net" method 
// to convert to and from network byte ordered independant format.

//  "size" have to call the direct ancestor method "net_size" 
// method and add to its result the size needed to store the 
// network representqtion for the local extension.

// As these methods are redefinition of ancestor's function,
// ommiting them in a new descendant is not a problem for the 
// compilation and link process but they can cause very bad bugs
// such as corrupting another client-serveur communication.

#ifndef _SCOOTER_DATA_H_
#define _SCOOTER_DATA_H_


// #define MAX_Name_Size 16 // The max name size for the descendants of dat aclass.

// some usefull macro.
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif
#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif
#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif
#ifndef abs
#define abs(a) ((a) >= 0 ? (a) : -(a))
#endif
#ifndef odd
#define odd(n) ((n) & 1)
#endif

#define SCOOTER_DATA_CLASS( _data_ , _ancestor_ , _body_ ) \
        class _data_ : public _ancestor_  \
        {    \
	  _body_ \
	    public: \
	  _data_ () { _data_::init(); } \
	  virtual char* my_type_name( int ancestor ) \
	    { \
	      if( ancestor == 0 ) return #_data_;  \
	      else return _ancestor_ ::my_type_name( ancestor-1 ); \
	    } \
	  virtual int size( int ancestor ) \
	    { \
	      if( ancestor == 0 ) \
                 return _data_::local_size() + _ancestor_::size( 0 ); \
	      else return _ancestor_::size( ancestor-1 );\
	    } \
          virtual void* h2n( void *addr ) \
          {\
             addr = _ancestor_::h2n( addr );\
             return _data_::local_h2n( addr );\
          }\
          virtual void* n2h( void *addr)\
          {\
             addr = _ancestor_::n2h( addr );\
             return _data_::local_n2h( addr );\
          }\
	} \

// In this inline we use incode data structure size.
inline void *h2n_32bits( void *addr, int *x )
{ memcpy( addr, x, 4 ); addr = (void*) ((unsigned int)addr +4) ; return addr; }
inline void *h2n_64bits( void *addr, RTIME *x )
{ memcpy( addr, x, 8 ); addr = (void*) ((unsigned int)addr +8) ; return addr;}
inline void *h2n_U32bits( void *addr, unsigned int *x )
{ memcpy( addr, x, 4 ); addr = (void*) ((unsigned int)addr +4) ; return addr; }
inline void *h2n_U64bits( void *addr, URTIME *x )
{ memcpy( addr, x, 8 ); addr = (void*) ((unsigned int)addr +8) ; return addr;}
inline void *h2n_string( void *addr, char *x , int size )
{ memcpy( addr, x, size ); size = ( (size+3)/4 ) *4 ; addr = (void*)((unsigned int)addr +size) ; return addr;}

inline void *n2h_32bits( void *addr, int *x )
{ memcpy( x, addr, 4 ); addr = (void*) ((unsigned int)addr +4) ; return addr;}
inline void *n2h_64bits( void *addr, RTIME *x )
{ memcpy( x, addr, 8 ); addr = (void*) ((unsigned int)addr +8) ; return addr;}
inline void *n2h_U32bits( void *addr, unsigned int *x )
{ memcpy( x, addr, 4 ); addr = (void*) ((unsigned int)addr +4) ; return addr;}
inline void *n2h_U64bits( void *addr, URTIME *x )
{ memcpy( x, addr, 8 ); addr = (void*) ((unsigned int)addr +8) ; return addr;}
inline void *n2h_string( void *addr, char *x , int size )
{ memcpy( x, addr, size ); size = ( (size+3)/4 ) *4 ; addr = (void*) ((unsigned int)addr +size) ; return addr; }

inline int size_32bits(){ return 4; } 
inline int size_64bits(){ return 8; } 

inline void SWAP_32bits( int *x) {} // on firewire, there is nothing to do
inline void SWAP_64bits( RTIME *x) { long t; t = *x >> 32 ; *x = ( *x << 32 ) | t ; }
inline void SWAP_U32bits( unsigned int *x) {} // on firewire, there is nothing to do
inline void SWAP_U64bits( URTIME *x) { long t; t = *x >> 32 ; *x = ( *x << 32 ) | t ; }
inline void SWAP_string( char *x, int l) 
{ 
  unsigned int * X; unsigned int y ; int i ; 
  X = (unsigned int*) x;
  for( i = 0 ; i < l; i = i + 4 )
    {
      y = X[ i>>2 ];
      X[ i>>2 ] = (( y & 0xff ) << 24) | (( y & 0xff00 ) << 8) | (( y & 0xff0000 ) >> 8) | (( y & 0xff000000 ) >> 24) ;
    }
}
// for firewire TODO

extern "C" {
#include "rt_cpp.h"
}

//****************************************************************
// Class and type declaration needed for server and remote_server.
//****************************************************************
//class Service;
//typedef Service *PService;
class Service_data;
class Descriptor;
typedef Descriptor *PDescriptor;

//****************************************************************
// conversion entre Big Endian et Litle Endian:
//****************************************************************

//****************************************************************

//inline DWORD align( DWORD s ) 
//{
//	return (sizeof(DWORD)*((s+sizeof(DWORD)-1)/sizeof(DWORD)));
//}
// As i cant use compilers with homogeneous class representation,
// i need to recopy all datas at least one. But here i can have 
// to recopy it twice depening of the low level buffer limit.
// This second data copy is avoidable, but this is not done now.
class sub_scooter_data
{
public:
  int nb_output_blocks(){ return 1 ; }
  //  virtual int size() = 0;
  virtual void * h2n(void * addr){ return addr ; }
  virtual void * n2h(void * addr){ return addr ; }

  sub_scooter_data() 
  {
  }
  virtual char* my_type_name( int ancestor )
  { 
    return "sub_scooter_data";  
  }
  virtual int size( int ancestor ) 
  {
    return 0;
  }
  virtual ~sub_scooter_data()  
  {
  }
};

#define CONNECTED_MASK 0x80000000
#define CLIENT_MASK( _x_ ) ( _x_ &  0x7fff0000 ) >> 16
#define MASK_CLIENT( _x_ ) ( _x_ << 16 ) &  0x7fff0000
#define COUNT_MASK 0xffff
SCOOTER_DATA_CLASS( scooter_data, sub_scooter_data, 
public:
  //  virtual int size() = 0;
  unsigned int MULTIFIELD ; // multifield quadlet 
  //                        CONNECTED 0x80000000
  //                        if (CONNECTED == 0)
  //                           client_index // (0x7fff0000) index for this client on the server
  //                           transaction_number // (0xffff)
  //                        else 
  //                             client_port // (0x7fff0000) index of the port on the client host
  //                             reply_size // (0xffff) the size of the returned data.
  RTIME CurrentTime; 
  RTIME ServerCreationTime; // decisive identification for the server.
 public:
  void init(){}
  int local_size() 
  { 
    return size_32bits() + size_64bits() + size_64bits() ; 
  }
  void * local_h2n( void *addr)
  {
    addr = h2n_U32bits( addr, &MULTIFIELD );
    addr = h2n_64bits( addr, &ServerCreationTime); 
    addr = h2n_64bits( addr, &CurrentTime );
    return addr ; 
  }
  void * local_n2h(void * addr )
  {
    addr = n2h_U32bits( addr, &MULTIFIELD );
    addr = n2h_64bits( addr, &ServerCreationTime); 
    addr = n2h_64bits( addr, &CurrentTime );
    return addr;
  }
		    );


//////////////////////////////////////////////////////////
// this class contain the data needed for the registration process
// either for the "service" and for the "flow" 
SCOOTER_DATA_CLASS( Register_data, sub_scooter_data, 
public:
  NameType name;
  RTIME time_creation_min; // nanoseconds 
  RTIME max_recover; 
  unsigned int quality; 
  unsigned int my_host_address; // 0 .. 63

  int  local_size() { return (NAME_SIZE + 2*size_64bits() + 2*size_32bits());}
  inline RTIME time_creation_max(){ return time_creation_min + WORST_SYNCHRO;}
    void local_swap_byte() 
    { 
     SWAP_string( (char*)&name, NAME_SIZE );
     SWAP_64bits( &time_creation_min );
     SWAP_64bits( &max_recover );
     SWAP_U32bits( &quality ) ;
     SWAP_U32bits( &my_host_address ) ;
    }
    void* local_h2n( void *addr)
    {
        addr = h2n_string( addr, (char*)&name, NAME_SIZE );
        addr = h2n_64bits( addr, &time_creation_min );
        addr = h2n_64bits( addr, &max_recover );
        addr = h2n_U32bits( addr, &quality ) ;
        addr = h2n_U32bits( addr, &my_host_address ) ;
        return addr ; 
    }
    void * local_n2h(void * addr )
    { 
        addr = n2h_string( addr, (char*)&name, NAME_SIZE );
        addr = n2h_64bits( addr, &time_creation_min );
        addr = n2h_64bits( addr, &max_recover );
        addr = n2h_U32bits( addr, &quality ) ;
        addr = n2h_U32bits( addr, &my_host_address ) ;
        return addr ; 
    }
  void init()
  {
    name.w1 = name.w4 = 0;
    time_creation_min = 0;
    quality = 0;
  }
void Set( Register_data *L );
void Get( Register_data *L );
);

////////////////////////////////////////////////////////////////

SCOOTER_DATA_CLASS( scooter_sample, scooter_data,
    RTIME min_data_time; // the datas timestamp.
    RTIME max_data_time;
  public:
    void init(){}
    int  local_size() { return size_64bits() + size_64bits();}
    void* local_h2n( void *addr)
{
  addr = h2n_64bits( addr, &min_data_time); 
  addr = h2n_64bits( addr, &max_data_time );
  return addr ; 
}
    void * local_n2h(void * addr )
{ 
  addr = n2h_64bits( addr, &min_data_time); 
  addr = n2h_64bits( addr, &max_data_time );
  return addr;
}
public:
    void set_data_timestamp( RTIME pMin, RTIME pMax)
{
  min_data_time = pMin; max_data_time = pMax;
}
RTIME min_data_timestamp()
{
  return min_data_time;
}
RTIME max_data_timestamp()
{
  return max_data_time;
}
);

SCOOTER_DATA_CLASS( scooter_request, scooter_data,
  public:
    RTIME next_data_time; /* the offset from the transaction CurrentTime */
    unsigned int flags; /* after_offset 0x1, before_offset 0x2, current 0x0 */
  public:
    void init(){}
    int  local_size() { return size_64bits() + size_32bits();}
    void* local_h2n( void *addr)
    {
      addr = h2n_64bits( addr, &next_data_time); 
      addr = h2n_U32bits( addr, &flags );
      return addr ; 
    }
    void * local_n2h(void * addr )
    { 
      addr = n2h_64bits( addr, &next_data_time); 
      addr = n2h_U32bits( addr, &flags );
      return addr;
    }
);

#endif

