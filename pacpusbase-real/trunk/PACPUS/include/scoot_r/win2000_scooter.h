//18 sept 03
#ifndef WIN2000_SCOOTER_H
#define WIN2000_SCOOTER_H
typedef __int64 RTIME;
typedef __int64 URTIME;

extern HANDLE cli_sti_sem;
// #define DEBUG 1

#define RT_TASK void
#define SEM void
#define SEM_TIMOUT  WAIT_TIMEOUT

#define SEM_ERR  WAIT_FAILED
inline void brk_pt(){}

#define rt_global_cli_cpp()   WaitForSingleObject( cli_sti_sem, INFINITE )
#define rt_global_sti_cpp()   brk_pt();ReleaseSemaphore( cli_sti_sem, 1, NULL )

#define rt_printk printf

#define rt_malloc( _s_ ) malloc( _s_ )
#define rt_free( _x_ )  if( _x_ != NULL ) free( _x_ )
#define rt_kmalloc( _s_ ) malloc( _s_ )
#define rt_kfree( _x_ )  if( _x_ != NULL ) free( _x_ )

#define rt_sleep( count ) Sleep( count +10)
#define rt_busy_sleep( count ) Sleep( count +10)
inline int nano2count( RTIME count ) { return (count / 1000000 );}
// as we use FILETIME 100 ns in side of nano and milliseconds as count unit 
inline RTIME rt_get_time_ns() 
	{ LARGE_INTEGER i1, i2; RTIME r;
	  QueryPerformanceFrequency( &i2 ); QueryPerformanceCounter( &i1 ); 
	  r = i1.QuadPart ; r = r * 1000; r = r / (i2.QuadPart/100) ; r = r * 10000; return r;}
#define rt_get_time() rt_get_time_ns() / 1000000

#define rt_sem_create_cpp() (void*)-1
#define rt_sem_init_cpp( _sem_ , _count_ ) _sem_ = CreateSemaphore( NULL,  _count_ , 1, NULL); 
#define rt_sem_wait_timed_cpp( _sem_ , _delay_ )  WaitForSingleObject( _sem_, 1+ _delay_ )
#define rt_sem_wait_until( _sem_ , _delay_ )  rt_sem_wait_timed_cpp( _sem_, _delay_ - rt_get_time() )

#define rt_sem_wait( _sem_ )  WaitForSingleObject( _sem_, INFINITE )
#define rt_sem_signal( _sem_ )   ReleaseSemaphore( _sem_ , 1, NULL )
// A VOIR BUG ? ? ? 
// #define rt_sem_broadcast( _sem_ )   ReleaseSemaphore( _sem_ , 1, NULL )
#define rt_sem_broadcast( _sem_ )  { long tmp; \
	 ReleaseSemaphore( _sem_ , 1, &tmp ); tmp -- ;\
	 if( tmp > 0 ) ReleaseSemaphore( _sem_ , tmp, NULL ); };

// #define rt_sem_broadcast( _sem_ )   PulseEvent( _sem_ )
#define rt_sem_delete( _s_ ) CloseHandle( _s_ )
#define SEM_TIMOUT WAIT_TIMEOUT

#define rt_alloc_dynamic_task() (void*)-1
#define rt_task_init( task_id, fct, arg , stack_size, PRIORITY, flags , signal ) ( NULL ==( \
	task_id = CreateThread( NULL, stack_size, fct, arg, CREATE_SUSPENDED, NULL ) ))
#define rt_task_resume( task_id ) (ResumeThread( task_id )==0xffffffff)
#define  rt_task_delete( task_id ) TerminateThread( task_id , 0 )
#define rt_task_suspend( _task_ ) SuspendThread( _task_ )


inline int rt_my_priority(){ return 10 ;}

#define ACK_DATA_ERROR IEEE1394_ACK_DATA_ERROR

#define MODULE_RUNNING  0x100
#define MODULE_STOPPED 0x200

DWORD WINAPI scooter_task( LPVOID p );
class scooter_module 
{
  char *Name; //module name
  friend DWORD WINAPI scooter_task( LPVOID p ); 
  //  HANDLE les_ready_Event; 
  //  HANDLE les_stop_Event; 
  //  RT_TASK *register_task_id; 
  int status; // MODULE_RUNING, MODULE_STOPPED
 protected:
  virtual int task(){ return 0;}
  virtual void init_module()  =0;
  virtual void cleanup_module() =0;
 public:
  static int NB_modules;
  static scooter_module *Tete_Liste_Module ;
  scooter_module *Module_Suivant;
  scooter_module( char *name ) 
    { 
      Name = name ; status = MODULE_STOPPED;
      NB_modules ++;
      Module_Suivant = Tete_Liste_Module ;
      Tete_Liste_Module = this;
    }
  ~scooter_module() 
    { // quadratic solution 
      if(Tete_Liste_Module == this )
		Tete_Liste_Module = Module_Suivant;
      else {
		scooter_module *tmp;
		tmp = Tete_Liste_Module ; 
		while( tmp->Module_Suivant != NULL )
		  {
		    if ( tmp->Module_Suivant == this )
		      tmp->Module_Suivant = Module_Suivant;
		    else tmp = tmp->Module_Suivant;
		  }
      }
      NB_modules --;
    } 

  void start()
    {
      if( status == MODULE_STOPPED )
		{
		status = MODULE_RUNNING;
		init_module();
   	    fprintf( stderr, "The module %s is started.\n", Name);
		}
    }

  void stop()
  {
	  if( status == MODULE_RUNNING )
		{
		  status = MODULE_STOPPED;
		  cleanup_module();
	  	  fprintf( stderr, "The module %s is stopped.\n", Name);
		}
  }
}; 

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Modif Gerald 11/02/05
// Launch_SCOOTR() sera appelée dans le amin du projet

//void main( int argc, char** argv)
void Launch_SCOOTR();
// Stop_SCOOTR() sera appelé dans le projet pour arrêter Scooter
void Stop_SCOOTR();

#endif
