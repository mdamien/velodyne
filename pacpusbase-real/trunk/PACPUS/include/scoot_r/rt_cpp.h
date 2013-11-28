#ifndef RT_CPP_H
#define RT_CPP_H
#ifdef RTAI
#define URTIME unsigned long long 
extern int rtf_put(unsigned int fifo, void * buf, int count);
extern int rtf_create(unsigned int fifo, int size);
extern int rtf_destroy(unsigned int fifo);
extern int rtf_sem_init(unsigned int fifo, int fifo_id);
extern int rtf_sem_post(unsigned int fifo);
extern int rtf_sem_destroy(unsigned int fifo);
extern int rt_sem_broadcast(SEM *sem); // missing in the include i can use

extern void rt_global_cli_cpp();

extern void rt_global_sti_cpp();


extern void * rtai_kmalloc_cpp(unsigned long name, int size);
extern void rtai_kfree_cpp ( int name);

extern unsigned long nam2num_cpp (char *name);
extern void num2nam_cpp (unsigned long num, char *name);
extern char* strcat_cpp(char *des, char *source);

extern SEM *rt_sem_create_cpp();
extern void rt_sem_init_cpp( SEM *s , int v );
void rt_res_sem_init_cpp( SEM *s , int v );
void rt_bin_sem_init_cpp( SEM *s , int v );
unsigned int rt_sem_wait_timed_cpp( SEM *s , RTIME timeout);

void *rt_kmalloc( int size );
void rt_kfree(void* p);

//extern void * rt_virt_to_bus(void *buf);

extern unsigned int rt_my_priority( void );

extern int __do_global_ctors_aux();
extern int __do_global_dtors_aux();

#endif
inline int log_2( URTIME i )
{
  int r;
  for( r = 0 ; r < 64 ; r++ )
    {
      //if( ( i >> r ) == 1 ) return r;
      if( i == 1 ) return r;
      i = i >> 1 ; 
    }
  return 0;
}

#endif
