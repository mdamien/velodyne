#include <string.h>

class Producer_Ressources
{
public:
  char *name;
  int channel;
  int context;
  void new_entrie(char *Name, int Channel, int Context)
  {
    name = Name;
    channel = Channel;
    context = Context;
  }
  void clear()
  {
    name = NULL;
    channel = -1; 
    context = -1;
  }
};
typedef Producer_Ressources *PProducer_Ressources;

class Consumer_Ressources
{
public:
  char *name;
  int channel;
  int context;
  void new_entrie( char *Name, int Channel, int Context)
  {
    name = Name;
    context = Context;
    channel = Channel;
  }
 void clear()
  {
    name = NULL;
    context = -1;
    channel = -1;
  }
};
typedef Consumer_Ressources *PConsumer_Ressources;

class  low_level_data_list
{
  unsigned int* list_head;
  int list_head_first_block_size;
  unsigned int* list_queue;
  int list_queue_first_block_size;

protected:
  void reinit()
  {
    rt_global_cli_cpp(); 
    list_queue = NULL ;
    list_head = NULL ;
    rt_global_sti_cpp(); 
  }

public:
  low_level_data_list()
  {
    list_queue = NULL ;
    list_head = NULL ;
  }

  void add_message( unsigned int * message_addr, unsigned int first_block_size)
  {
    unsigned int *addr_to_addr;
    unsigned int *addr_to_size;
    int first_block_i;
    unsigned int *second_block;
    rt_global_cli_cpp(); 
    if( list_queue == NULL )
      {
	list_head = message_addr;
	list_head_first_block_size = first_block_size;
      }
    else {
      if( list_queue_first_block_size >= 12 )
	{
	  addr_to_addr = & list_queue[ 2 ] ;
	  if( list_queue_first_block_size >= 16 )
	    {
	      addr_to_size = & list_queue[ 3 ];
	    }
	  else{
	    //	    addr_to_size = (unsigned int*)list_queue[ 0 ];// the second block address is here
	    second_block = (unsigned int*)list_queue[ 0 ];// the second block address is here
	    addr_to_size = & (second_block[ 0 ]);// the second block address is here
	  }
	}
      else {
	first_block_i = list_queue_first_block_size /4 ; 
	second_block = (unsigned int*) list_queue[ 0 ] ;// the second block address is here
	addr_to_addr = & (second_block[ 2 - first_block_i ]);
	addr_to_size = & (second_block[ 3 - first_block_i ]);
      }
      addr_to_addr[0] = (unsigned int) message_addr;
      addr_to_size[0] = ( addr_to_size[0] & 0xffff0000 ) | first_block_size;
    }
    list_queue = message_addr;
    list_queue_first_block_size = first_block_size;
    rt_global_sti_cpp(); // end for global spinlock
  }

  void* extract( void *buffer, int buffsize, int *source_id, int *tlabel )
  {
    int i;
    int size_block;
    unsigned int *tmp_head;
    unsigned int *first_block;
    unsigned int *second_block;
    //    unsigned int Special_inheritance_key_code;
    //    Special_inheritance_key_code = ((unsigned int*)buffer)[ 0 ];
    rt_global_cli_cpp(); 
    tmp_head = list_head; // usefull to have a shortest cli-sti 
    if( (list_queue == NULL) || (list_head == NULL ) ) // no message in this list
      {
	list_queue = NULL; list_head = NULL;
	rt_global_sti_cpp(); // end for global spinlock
	return NULL;
      }
    if( tmp_head == list_queue )
      { // the last message in the list
	list_queue = NULL ; // tested in add_message to know if there is already some message
      }
    if( tmp_head[ 0 ] == 0 ) // fast case: only one block no recopy needed.
      {
	list_head_first_block_size = tmp_head[ 3 ] & 0xffff ;
	list_head = (unsigned int *) tmp_head[ 2 ];
	rt_global_sti_cpp(); // end for global spinlock
	*tlabel = ( tmp_head[ 1 ] ) & 0xffff ; 
	*source_id = ( tmp_head[ 1 ] >> 16 );
	first_block = & tmp_head[ 4 ];
	size_block = tmp_head[ 3 ] >> 16;
      }
    else { // need to go across the buffer boundary
      second_block = (unsigned int*) tmp_head[ 0 ];
      if( list_head_first_block_size == 4 )
	{
	  list_head_first_block_size = second_block[ 2 ] & 0xffff ;
	  list_head = (unsigned int *) second_block[ 1 ];
	  rt_global_sti_cpp(); // end for global spinlock
	  *tlabel = ( second_block[ 0 ] ) & 0xffff ; 
	  *source_id = second_block[ 0 ] >> 16 ;
	  first_block = & second_block[ 3 ];
	  size_block = second_block[ 2 ] >> 16;
	} else{
	  if( list_head_first_block_size == 8 )
	    {
	      list_head_first_block_size = second_block[ 1 ] & 0xffff ;
	      list_head = (unsigned int *) second_block[ 0 ];
	      rt_global_sti_cpp(); // end for global spinlock
	      *tlabel = ( tmp_head[ 1 ] ) & 0xffff ; 
	      *source_id = tmp_head[ 1 ] >> 16 ;
	      first_block = & second_block[ 2 ];
	      size_block = second_block[ 1 ] >> 16 ;
	    } else{
	      if( list_head_first_block_size == 12 )
		{
		  list_head_first_block_size = second_block[ 0 ] & 0xffff ;
		  list_head = (unsigned int *) tmp_head[ 2 ];
		  rt_global_sti_cpp(); // end for global spinlock
		  *tlabel = ( tmp_head[ 1 ] ) & 0xffff ; 
		  *source_id = tmp_head[ 1 ] >> 16 ;
		  first_block = & second_block[ 1 ];
		  size_block = second_block[ 0 ] >>16 ;
		} else{
		  if( list_head_first_block_size == 16 )
		    {
		      list_head_first_block_size = tmp_head[ 3 ] & 0xffff ;
		      list_head = (unsigned int *) tmp_head[ 2 ];
		      rt_global_sti_cpp(); // end for global spinlock
		      *tlabel = ( tmp_head[ 1 ] ) & 0xffff ; 
		      *source_id = tmp_head[ 1 ] >> 16 ;
		      first_block = & second_block[ 0 ];
		      size_block = tmp_head[ 3 ] >> 16 ;
		    } else 
		      { // list_head_first_block_size > 16 )
			i = list_head_first_block_size - 16; 
			list_head_first_block_size = tmp_head[ 3 ] & 0xffff ;
			list_head = (unsigned int *) tmp_head[ 2 ];
			rt_global_sti_cpp(); // end for global spinlock

			*tlabel = ( tmp_head[ 1 ] ) & 0xffff ; 
			*source_id = tmp_head[ 1 ] >> 16 ;
			size_block = tmp_head[ 3 ] >> 16 ;
			if( i >= buffsize )
			  { 
			    first_block = & tmp_head[ 4 ];
			  }
			else {
			  memcpy( buffer, & tmp_head[4] ,i );
			  memcpy( (unsigned int*) (((int)buffer) +i) , second_block, buffsize - i );
			  first_block = (unsigned int*) buffer;
			}
		      }
		}
	    }
	}
    }
    //    first_block[ 0 ] = Special_inheritance_key_code;
    *source_id = ( *source_id ) & 0x3f;
    return first_block;
  }
};


class  Port: public low_level_data_list
{
public:
  int priority; // the priority of the server task
  SEM *port_sem;
public:
  void unregister() { 
    if( port_sem != NULL ) 
      {
#ifdef DEBUG
	//	rt_printk( "port unregister and rt_sem_init %x \n", port_sem );
#endif
	//	rt_sem_init_cpp( port_sem, 0 ); // and waitng task will get SEM_ERR  // DOESNT WORK?
	//	reinit(); // suppress the old message but not critical
      }
  }

  Port( SEM *sem )
  {
    port_sem = sem;
    priority = rt_my_priority();
  }
  SEM *semaphore(){ return port_sem ; }

#ifdef PROC_SCOOTER
  int print( char * page );
#endif
};

class  Server_Port: public Port
{

public:
  Server_Port( SEM *sem) : Port( sem )
  {
  }
};
typedef Server_Port *PServer_Port;

class  Consumer_Port: public Port
{
  int nbr; unsigned int *iso_msg;
  int msg_size;

public:
  Consumer_Port( SEM *sem ) : Port( sem )
  {
     nbr = 0;
	 msg_size = 0;
	 iso_msg = NULL;

  }

  void set_new_message( unsigned int *msg_first_block_addr, int msg_first_block_size ) {
    
	iso_msg = msg_first_block_addr;
	msg_size = msg_first_block_size;
	nbr++;
  }


  int get_message(unsigned int **msg_addr, int *size) {
    *msg_addr = iso_msg;
	*size = msg_size;
	return nbr;   
  }
};
typedef Consumer_Port *PConsumer_Port;

class  Client_Port: public Port
{
public:
  Client_Port( SEM *sem) : Port( sem )
  {
  }
};
typedef Client_Port *PClient_Port;

class  Producer_Port
{
public:
  int channel; 
  int context;
  Producer_Port()
  {
  }
  void unregister() {
    channel=-1; 
    context=-1; 
  }
};
typedef Producer_Port *PProducer_Port;

class  Consummer_Port: public Port
{
public:
  Consummer_Port( SEM *sem) : Port( sem )
  {
  }
};
typedef Consummer_Port *PConsummer_Port;
