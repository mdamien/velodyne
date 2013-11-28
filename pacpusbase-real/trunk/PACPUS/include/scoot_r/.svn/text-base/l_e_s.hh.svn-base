/* * Last edited: Feb 18 19:14 1993 (crubille) */

#ifndef _L_E_S_H_
#define _L_E_S_H_

#define TRUE 1
#define FALSE 0

#include "scoot_r/scooter.hh"
#include "scoot_r/scooter_data.hh"
#include "scoot_r/noeuds_info.h"
#include "scoot_r/port.hh"

#define NB_BUFFERS 30

class L_e_s;

// const int MAX_NETWORK_SERVICES = 1024; // too big need special allocation
// const int SIZE_H_NETWORK_SERVICES = 1536 ; // 2/3 maximum for fast access.
const unsigned int MAX_NETWORK_SERVICES = 128;
const unsigned int SIZE_H_NETWORK_SERVICES = 192 ; // 2/3 maximum for fast access.
// Assertion: SIZE_H_NETWORK_SERVICES > (MAX_NETWORK_SERVICES*11)/10 
const unsigned int MAX_NODE_SERVERS = 64;
const unsigned int MAX_NODE_CLIENTS = 64;
const unsigned int MAX_NODE_PRODUCERS = 64; // 64 iso channels on ieee1394
const unsigned int MAX_NODE_CONSUMMERS = 64;


// define the value for the STATE of a Service class.
#define FREE 0x00  
// The slot is unused  
#define NAMED 0x01  
// The slot is used, the name cant be modified unless rebuilding the h-code table
#define NEVER_IRQ  0x0
#define ALWAYS_IRQ 0x3
#define ONPB_IRQ   0x1

#ifndef LOOPBACK_ONLY
// this class is the message and the data locally stored on each l_e_s
// object which is used to send multiple aknowledgments at once on the network.
SCOOTER_DATA_CLASS( ack_data, sub_scooter_data, 
  unsigned int first_num[ 63 ]; // one per host on the bus
public:
  void init()
  {
    int i;
    rt_global_cli_cpp();
    for( i = 0 ; i < 63 ; i++ )
      first_num[ i ] = 0 ;
    rt_global_sti_cpp();
  }
    int  local_size() { return 63 * size_32bits() ;}
    void local_swap_byte() 
    { 
    int i;
    rt_global_cli_cpp();
    for( i = 0 ; i < 63 ; i++ )
            SWAP_U32bits( &first_num[ i ] ) ;
    rt_global_sti_cpp();
    }
    void* local_h2n( void *addr)
{
    int i;
    rt_global_cli_cpp();
    for( i = 0 ; i < 63 ; i++ )
        addr = h2n_U32bits( addr, &first_num[ i ] ) ;
    rt_global_sti_cpp();
  return addr ; 
}
    void * local_n2h(void * addr )
{ 
    int i;
    rt_global_cli_cpp();
    for( i = 0 ; i < 63 ; i++ )
        addr = n2h_U32bits( addr, &first_num[ i ] ) ;
    rt_global_sti_cpp();
  return addr ; 
}

  int copy( ack_data *a)
  {
    int i; int non_null;
    non_null = FALSE;
    rt_global_cli_cpp();
    for( i = 0 ; i < 0x3f ; i++ )
      {
	first_num[ i ] = a->first_num[ i ] ;
	non_null = non_null || (( first_num[ i ] & 0xffff) != 0 );
      }
    rt_global_sti_cpp();
    return non_null;
  }
  void add( int host, int trans_num )
  {
    if( trans_num == 0 ) return; // in most most case it is a resend  else it dont match so much
    rt_global_cli_cpp();
    host = host & 0x3f ; // be sure i don't use an extented address

    if( ((first_num[ host ] >> 16 ) + (( first_num[ host ] + 1) & 0xffff )) == ((unsigned int) trans_num )) 
      {
	first_num[ host ]  = ( first_num[ host ] & 0xffff0000 ) | ((( first_num[ host ] & 0xffff) +1 ) & 0xffff );
      }
    else if( ( first_num[ host ] >> 16 ) <= ((unsigned int) trans_num )) 
      {
	first_num[ host ] = ( (trans_num-1)  << 16 ) + 1 ;
      }
    rt_global_sti_cpp();
    // #ifdef DEBUG
    //    rt_printk( "to ack: from %x number %x  first_num[ %x ] = %x\n", host, trans_num, host, first_num[ host ] );
    // #endif
  }
  unsigned int ack_first( int host )
  {
    host = host & 0x3f ; // be sure i don't use an extented address
    return ( first_num[ host ] >> 16 );
  }
  unsigned int ack_last( int host )
  {
    host = host & 0x3f ; // be sure i don't use an extented address
    return ( first_num[ host ] >> 16 ) + ( first_num[ host ] & 0xffff );
  }
);
#endif
// this class contain all the data needed to describe a service
// it is used to send on the network
// and to store these description in the service table
// (in the service form associated with one semaphore)
SCOOTER_DATA_CLASS( Service_data, Register_data, 
public:
  NameType request_type_name;
  NameType reply_type_name;
  NameType ancestor_type_name;
  RTIME worst_case_reply_time; // nanoseconds 
  RTIME max_period; 
  RTIME min_period;
  unsigned int request_type_size;
  unsigned int reply_type_size;
  unsigned int ancestor_type_size;
  unsigned int server_port_indice ; // in the server_ports_table

///////////////////////////////////////
    int  local_size() { return 3*NAME_SIZE + 3*size_64bits() + 4*size_32bits() ;}
    void local_swap_byte() 
    { 
     SWAP_string( (char*)&request_type_name, NAME_SIZE );
     SWAP_string( (char*)&reply_type_name, NAME_SIZE );
     SWAP_string( (char*)&ancestor_type_name, NAME_SIZE );
   
     SWAP_64bits( &worst_case_reply_time );
     SWAP_64bits( &max_period );
     SWAP_64bits( &min_period );
  
     SWAP_U32bits( &request_type_size ) ;
     SWAP_U32bits( &reply_type_size ) ;
     SWAP_U32bits( &ancestor_type_size ) ;
     SWAP_U32bits( &server_port_indice ) ;
    }
    void* local_h2n( void *addr)
    {
        addr = h2n_string( addr, (char*)&request_type_name, NAME_SIZE );
        addr = h2n_string( addr, (char*)&reply_type_name, NAME_SIZE );
        addr = h2n_string( addr, (char*)&ancestor_type_name, NAME_SIZE );
   
        addr = h2n_64bits( addr, &worst_case_reply_time );
        addr = h2n_64bits( addr, &max_period );
        addr = h2n_64bits( addr, &min_period );
  
        addr = h2n_U32bits( addr, &request_type_size ) ;
        addr = h2n_U32bits( addr, &reply_type_size ) ;
        addr = h2n_U32bits( addr, &ancestor_type_size ) ;
        addr = h2n_U32bits( addr, &server_port_indice ) ;
        return addr ; 
    }
    void * local_n2h(void * addr )
    { 
        addr = n2h_string( addr, (char*)&request_type_name, NAME_SIZE );
        addr = n2h_string( addr, (char*)&reply_type_name, NAME_SIZE );
        addr = n2h_string( addr, (char*)&ancestor_type_name, NAME_SIZE );

        addr = n2h_64bits( addr, &worst_case_reply_time );
        addr = n2h_64bits( addr, &max_period );
        addr = n2h_64bits( addr, &min_period );

        addr = n2h_U32bits( addr, &request_type_size ) ;
        addr = n2h_U32bits( addr, &reply_type_size ) ;
        addr = n2h_U32bits( addr, &ancestor_type_size ) ;
        addr = n2h_U32bits( addr, &server_port_indice ) ;
        return addr ; 
    }

///////////////////////////////////////

  void init()
  {
    request_type_name.w1 = 0; request_type_name.w4 = 0;
    request_type_size = 0;
    time_creation_min = 0;
    quality = 0;
  }
void Set( Service_data *L );
void Get( Service_data *L );
);

SCOOTER_DATA_CLASS( ObjectFlow, Register_data, 
  public:
NameType request_type_name;
NameType ancestor_type_name;

RTIME max_period; 
RTIME min_period;
RTIME jitter;
unsigned int request_data_size;
unsigned int ancestor_type_size;
unsigned int producer_channel ; 

///////////////////////////////////////
int  local_size() { return 2*NAME_SIZE + 3*size_64bits() + 3*size_32bits() ;}
void local_swap_byte() 
{ 
  SWAP_string( (char*)&request_type_name, NAME_SIZE );
  SWAP_string( (char*)&ancestor_type_name, NAME_SIZE );
  
  SWAP_64bits( &max_period );
  SWAP_64bits( &min_period );
  SWAP_64bits( &jitter );
  
  SWAP_U32bits( &request_data_size ) ;
  SWAP_U32bits( &ancestor_type_size ) ;
  SWAP_U32bits( &producer_channel ) ;
}
void* local_h2n( void *addr)
{
  addr = h2n_string( addr, (char*)&request_type_name, NAME_SIZE );
  addr = h2n_string( addr, (char*)&ancestor_type_name, NAME_SIZE );
  
  addr = h2n_64bits( addr, &max_period );
  addr = h2n_64bits( addr, &min_period );
  addr = h2n_64bits( addr, &jitter );
  
        addr = h2n_U32bits( addr, &request_data_size ) ;
        addr = h2n_U32bits( addr, &ancestor_type_size ) ;
        addr = h2n_U32bits( addr, &producer_channel ) ;
rt_printk( "ObjectFlow_data h2n\n" );
        return addr ; 
    }
    void * local_n2h(void * addr )
    { 
        addr = n2h_string( addr, (char*)&request_type_name, NAME_SIZE );
        addr = n2h_string( addr, (char*)&ancestor_type_name, NAME_SIZE );
        
        addr = n2h_64bits( addr, &max_period );
        addr = n2h_64bits( addr, &min_period );
        addr = n2h_64bits( addr, &jitter );

        addr = n2h_U32bits( addr, &request_data_size ) ;
        addr = n2h_U32bits( addr, &ancestor_type_size ) ;
        addr = n2h_U32bits( addr, &producer_channel ) ;
	rt_printk( "ObjectFlow_data n2h\n" );
        return addr ; 
    }

///////////////////////////////////////

  void init()
  {
    name.w1 = name.w4 = 0;
    request_type_name.w1 = 0; request_type_name.w4 = 0;
    time_creation_min = 0;
    request_data_size = 0;
    quality = 0;
  }
void Set( ObjectFlow *L );
void Get( ObjectFlow *L );
);

template <class r_data> class Register : private r_data
{
  SEM* s;
  short name_size; // store the size of the name to optimize name cmp.
public:
  Register();
  void Set( r_data *L )
  {
    rt_global_cli_cpp();
    name_size = strlen( (char*) & L->name ) +1;
    r_data::Set( L );
    rt_global_sti_cpp();
  }
  void Get( r_data *L )
  {
    rt_global_cli_cpp();
    r_data::Get( L );    
    rt_global_sti_cpp();
  }
  void Get( Register_data *L )
  {
    rt_global_cli_cpp();
    Register_data::Get( L );    
    rt_global_sti_cpp();
  }
  int namecmp( NameType *n )
  {
    int r;
    r = memcmp( &name, n , name_size) ;
    return r;
  }
  void signal() // restart all the pending tasks
  {
    if( s != NULL ) 
      {
	// run away all blocked task.
	rt_sem_broadcast( s );
      }
  }
  int wait( SEM *n ) // n can become the new semaphore if s == NULL .
  {
    rt_global_cli_cpp();
    if( s == NULL ) s = n ;
    rt_global_sti_cpp();
    return rt_sem_wait( s ) ;
  }
  int wait_until( SEM *n , RTIME until) // in nanosecond
  {
    rt_global_cli_cpp();
    if( s == NULL ) s = n ;
    rt_global_sti_cpp();
    return rt_sem_wait_until( s , nano2count( until )) ;
  }
  void link( SEM *n ) // n become the new semaphore if s == NULL .
  {
    rt_global_cli_cpp();
    if( s == NULL ) s = n ;
    rt_global_sti_cpp();
  }
  void unlink( SEM *n ); // if n == s signal it and remove it .
  unsigned int Quality() { return quality ;}

#ifdef PROC_SCOOTER
  int data_print( char * page ); // really Service_Data method
  int print( char * page );
#endif
};

typedef Register<Service_data> Service;
typedef Register<ObjectFlow> Flow;

typedef Service *PService;
typedef Flow *PFlow;

///////////////////////////////////////////////////////////////////
// Descriptor allow us to link data instance and the descriptors
// used to send them on a network
///////////////////////////////////////////////////////////////////
class Descriptor
{
protected:
  L_e_s *adapter;
  unsigned int *des_data;  int des_data_size; // the data block and
  unsigned *p_first_block; // used only to allow local message delivery
  int Type;
public:
  Descriptor( unsigned int *d ,int size_d, L_e_s *dev, int type ) 
  {
    adapter = dev;
    des_data = d ;
    des_data_size = size_d ;
    Type = type;
    p_first_block = new unsigned int[4];
    p_first_block[0] = (unsigned int) d;
    p_first_block[1] = 0 ; // source_id <<16 & tlabel
    p_first_block[2] = 0 ; // used by low level software
    p_first_block[3] = des_data_size << 16 ;
  }
  virtual unsigned int to_send( int dest_addr, int speed, int port_addr, int transaction_index, int priority, int current_size) = 0 ;
  void to_local( int local_addr, int port_addr, int t_label );
  virtual void head_list( ) = 0 ;
  virtual unsigned int xferstatus( ) = 0 ;
  virtual ~Descriptor(){  if(p_first_block != NULL)  delete p_first_block;   }
};

typedef Descriptor *PDescriptor; 

///////////////////////////////////////////////////////////////////
// Descriptor_flow allow us to link data instance and the descriptors
// used to send them on a network
///////////////////////////////////////////////////////////////////
class Descriptor_flow
{
protected:
  L_e_s *adapter;
  unsigned int *des_data; int des_data_size; // the data block and
  int Type;
public:
  Descriptor_flow( unsigned int*d ,int size_d, L_e_s *dev, int type ) 
  {
    adapter = dev;
    des_data = d ;
    des_data_size = size_d ;
    Type = type;
  }
  virtual unsigned int to_send_flow( int context) = 0 ;
  void to_local( int channel );
  virtual ~Descriptor_flow(){}
};

typedef Descriptor_flow *PDescriptor_flow; 

//typedef Safe_Send *PSafe_Send;

const int SAFE_FREE = 0; // the object is not in the queue
const int SAFE_IN_PROGRESS = 1; // the object is in the queue 
const int SAFE_IN_CONTEXT = 2; // the object is in the ohci context queue
class Safe_List;
class Safe_Send
{
public:
  Safe_Send *next;       
  Safe_Send *previous;  
  RTIME echeance;
  Descriptor *des;
  unsigned int * SD_buf;
  int register_index; // the index all the other scoot-r node identitfy this message to send back the ack message. 
  URTIME bit_str;
  int status; // SAFE_xxx
  Safe_Send( L_e_s *L, sub_scooter_data *SD, int type );
  ~Safe_Send()
  {
    if( SD_buf != NULL ) rt_kfree( SD_buf );
    if( des != NULL ) delete des;
  }
  void h2n( sub_scooter_data* SD ) 
  {
    SD->h2n( SD_buf );
  }
  int extract( L_e_s *out_of);
  unsigned int xferstatus()
  {
    return des->xferstatus();
  }
}; 

class Safe_List
{
  int size_list;
public:
  int nb()
  {
    Safe_Send *ptr;
    int size_list; size_list = 0;
    for( ptr = first ; ptr != NULL ; ptr = ptr->next )
      size_list ++;
    return size_list ;
  }
  Safe_Send *first; Safe_Send *last;
  Safe_List();
  void put( Safe_Send *buf );
  Safe_Send *get();
  void reset();
  int register_index; // the index for the next message i send.
};
///////////////////////////////////////////////////////////////////
//           The L_e_s class
///////////////////////////////////////////////////////////////////
#ifdef WIN32
DWORD WINAPI register_task( LPVOID p );
DWORD WINAPI send_safe_broadcast_task( LPVOID p );
#else
void register_task( int p);
void send_safe_broadcast_task( int p);
#endif

class L_e_s: public scooter_l_e_s
{
#ifdef WIN32
friend DWORD WINAPI register_task( LPVOID p );
#else
  friend void register_task(int p);
#endif
  friend void send_safe_broadcast_task(int p);
  friend void handle_Selfid(struct ti_ohci *ohci);
  friend class Safe_Send;

  unsigned long les_id; // this l_e_s identifier 
  int NB_reset; // the number of reset
protected:
  Tree_Topology Nodes; // the node tree and the nodes speed.
public:
  virtual unsigned int local_addr()=0 ; // the local node address for this network
  virtual unsigned int net_nb_128s()=0 ;
  virtual unsigned int net_nb_100ns() = 0;
  //  virtual unsigned int bus_cycle() = 0;
  virtual unsigned int nb_reset() { return NB_reset ; } 
  virtual void net_timestamp_min(RTIME *min); // get the network synchronized time
  virtual void net_timestamp_max(RTIME *max) ; // get the network synchronized time
  virtual void net_timestamp(RTIME *min, RTIME *max); // get the network synchronized time

  int FREE_Xmit_CONTEXTS;
  int FREE_Recv_CONTEXTS;
  int MAX_Xmit_CONTEXTS; 
  int MAX_Recv_CONTEXTS; 
  int FREE_CHANNELS; // the number of flow names the module heard about 
  int MAX_CHANNELS; // the number of flow names the module heard about 
  unsigned int NB_producer_port;    //  the number of servers ports < MAX_NODE_SERVERS
  unsigned int NB_consumer_port;    //  the number of servers ports < MAX_NODE_SERVERS
private: 
  Service services_table[ MAX_NETWORK_SERVICES ];
  PService services_h_table[ SIZE_H_NETWORK_SERVICES ] ;
  Flow flow_table[ MAX_NETWORK_SERVICES ];
  PFlow flow_h_table[ SIZE_H_NETWORK_SERVICES ] ;

protected:
  PServer_Port server_ports_table[ MAX_NODE_SERVERS ];
  PClient_Port client_ports_table[ MAX_NODE_CLIENTS ];
  PConsumer_Port receiver_ports_table[ MAX_NODE_CONSUMMERS ];
  unsigned int *Buffer_OHCI_addr_table[ MAX_NODE_CONSUMMERS][NB_BUFFERS]; // table of buffer OHCI address
  PProducer_Ressources producer_ports_table[ MAX_NODE_PRODUCERS ];
  PConsumer_Ressources consumer_ports_table[ MAX_NODE_CONSUMMERS ];
private: 
  int first_free_server_port;    // the next allocated +1 % MAX_NODE_...
  int first_free_receiver_port;    // the next allocated +1 % MAX_NODE_...
  int first_free_client_port;    // the next allocated +1 % MAX_NODE_...

  unsigned int NB_server_port;    //  the number of servers ports < MAX_NODE_SERVERS
  unsigned int NB_receiver_port;    //  the number of servers ports < MAX_NODE_SERVERS
  unsigned int NB_client_port;    //  the number of clients ports < MAX_NODE_CLIENTS 

#ifdef DYNAMIC_CHECK
  int NB_servers_clients
#endif // DYNAMIC_CHECK

  unsigned int NB_services; // the number of service names the module heard about 
  unsigned int NB_flow; // the number of flow names the module heard about
  
  Service_data L_data; // private buffer for "Service" access
  ObjectFlow data_flow; // private buffer for "Flow" access
  
protected:
  SEM *critical_section; 
  SEM *register_sem; 
  //  SEM *register_flow_sem; 
  SEM *send_safe_broadcast_sem; 
  RT_TASK *register_task_id;
  RT_TASK *send_safe_broadcast_task_id;
////////////////////////////////////////////////////////////////
//  Data for the registering activity
////////////////////////////////////////////////////////////////
  low_level_data_list register_data_list; // this contain the head and queue of the incomming message for the register service.
  low_level_data_list register_flow_data_list; // this contain the head and queue of the incomming message for the register flow service.
  low_level_data_list ack_data_list; // this contain the head and queue of the incomming message for the register message collective acknowledge message.

////////////////////////////////////////////////////////////////
//  Data for the safe broadcast with multiple acknowledge protocol
////////////////////////////////////////////////////////////////
  Safe_List safe_broadcast_list; // this is the list of message to send to all  nodes.
#ifndef LOOPBACK_ONLY
  Safe_List safe_resend_list; // this is the list of message to resend to some nodes.
  ack_data to_ack_data; // not a message, but ack in it first.
  ack_data to_ack_msg;  // recopy the previous in this one in order to send it
  unsigned int *buf_to_ack_msg; 
  Descriptor *D_to_ack;  // a structure needed to send the previous one on the media.
public:
  // Data to receive ack message need buffers and objects
  unsigned int *ack_buf ;// pass this to the received data extracter routine so that it can copy data into it if it need to (for example if there is a buffer limit)
  unsigned int *ack_addr ;
  ack_data ack_local ;
#endif
protected:
  Service_data service_local ;
  ObjectFlow flow_local ;
public:
  // Data to receive register message need buffers and objects

  unsigned int *reg_buf ;// pass this to the received data extracter routine so that it can copy data into it if it need to (for example if there is a buffer limit)
  unsigned int *reg_flow_buf ;// pass this to the received data extracter routine so that it can copy data into it if it need to (for example if there is a buffer limit)
  unsigned int *reg_addr ;
  unsigned int *reg_flow_addr ;

////////////////////////////////////////////////////////////////
public:
  L_e_s( int id );
  virtual ~L_e_s();
  virtual Descriptor *new_descriptor( unsigned int *SD ,int size_SD, unsigned int type, int irq_policy) = 0; // return an adequate structure for message sending
  virtual Descriptor_flow *new_descriptor_flow( unsigned int *SD ,int size_SD, int channel) = 0; // return an adequate structure for message sending
  // type is  REGISTER_LOW_ADDRESS or SERVER_LOW_ADDRESS or CLIENT_LOW_ADDRESS.

  virtual void start_task(); // To be called after the construction.
  Service *find_service( NameType *name);
  // return NULL only if the table is full else return the Service 
  // object for this name (eventually allocate a new one for it).
  // The Service slot for a name never change but on a reset event.
  Flow *find_flow( NameType *name);
  int hcode_key( char *name);
  
  virtual void need_input_buffer( int size_message, int nb_messages) = 0 ;
  virtual void unneed_input_buffer( int size_message, int nb_messages) = 0 ;
  /////////////////////////////////////////////////////////////////////////
  virtual unsigned int **need_input_flow_buffer( int nb_buffers, int channel, int context) = 0 ;
  virtual void unneed_input_flow_buffer( int nb_buffers, int channel, int context) = 0 ;
  
  virtual int reset(); // Called when an hardware reset occur
  // reinitialize data in critical section. 
  // return 0 if OK elsewhere, we get a very bad case.
  virtual int end_reset(); // Called when an hardware selfid occur
  // unlock any task waiting for some service semaphore
  void send_safe_broadcast_fct();

  virtual int send(Descriptor *buf_des, int dest, int port_addr, int transaction_index, int current_size ) = 0;// current_size = 0xffff mean the whole message is send.
  virtual int deposit(Descriptor_flow *buf_des, int channel, int context, int sync ) = 0;
  virtual int consume(int channel, int context) = 0;
 
#ifdef RTAI
  virtual int get_nb_iso_ctx(unsigned int reg ) = 0;
#endif
  
  int get_one_xmit_context();
  int get_one_recv_context();
  int get_one_channel();
  int release_xmit_context();
  int release_recv_context();
  int release_channel();
  virtual void safe_broadcast(Safe_Send *buf_des ) ;
  SEM *to_list( unsigned int scooter_type, unsigned int from, unsigned int *msg_first_block_addr, int msg_first_block_size ); // on reception function
  SEM *to_iso_list(  int channel, int sync,  unsigned int *msg_first_block_addr, int msg_first_block_size ); // on reception function
  
  int  new_client_port ( SEM *sem) ; // there is none now.
  void free_client_port ( int port_index );
  
  int  new_receiver_port ( SEM *sem) ; // there is none now.
  void free_receiver_port ( int port_index );
  
  void  new_consumer_port (char *name, int channel, int context);
  void free_consumer_port (int port_index);
  void  new_producer_port (char *name, int channel, int context);
  void free_producer_port (int port_index);
  
  int  new_server_port ( SEM *sem) ; // there is none now.
  void free_server_port ( int port_index );
#ifndef LOOPBACK_ONLY
  void ack_algo( ack_data *requete , unsigned int node);
#endif
  void register_algo( Service_data *scooter_data );
  void register_flow_algo( ObjectFlow *scooter_data );
  // called by the register task and apply the L_E_S algorithme to decide 
  PServer_Port server_port( int index )
  {
    return  server_ports_table[ index ];
  }
  PClient_Port client_port( int index )
  {
    return  client_ports_table[ index ];
  }
  PProducer_Ressources producer_port( int index )
  {
    return  producer_ports_table[ index ];
  }
  PConsumer_Ressources consumer_port( int index )
  {
    return  consumer_ports_table[ index ];
  }
  PConsumer_Port receiver_port( int index )
  {
    return  receiver_ports_table[ index ];
  }
  unsigned int * Buffer_OHCI_addr(int context, int index )
  {
    if( (index < NB_BUFFERS) && ( context <  MAX_NODE_CONSUMMERS) )
      return Buffer_OHCI_addr_table[context][ index ];
    else
      return NULL;
  }

  void set_Buffer_OHCI_addr( int context, unsigned int **tab )
  {
    int i = 0;
    for ( i = 0; i < NB_BUFFERS; i++ ) {
      if(tab[i] != NULL) Buffer_OHCI_addr_table[context][ i ] = tab[i] ;
      else
	rt_printk("address OHCI NULL !!! \n");
    }
  }


 
#ifdef PROC_SCOOTER
  int max_hoop;

  int read_les_service(char *page, char**start, off_t off, int count, int *eof);
  int read_les_flow(char *page, char**start, off_t off, int count, int *eof);
  int read_les_ports(char *page, char**start, off_t off, int count, int *eof);
  int read_les_channels(char *page, char**start, off_t off, int count, int *eof);
  int read_les_contexts(char *page, char**start, off_t off, int count, int *eof);
  int read_les_general(char *page, char**start, off_t off, int count, int *eof);
#endif

};

typedef L_e_s *pL_e_s;
extern  pL_e_s liste_L_e_s[ MAX_NB_LES ];
extern  int NB_LES;
#endif
