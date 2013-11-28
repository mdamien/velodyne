#ifndef OHCI_CONTEXT_HH
#define OHCI_CONTEXT_HH

#define AR_REQ_BUF_SIZE      4096      /* size of AR req buffers */
//#define IR_BUF_SIZE        1920*480  /* size of IR req buffers = 1 image (640*480*3) */
#define IR_BUF_SIZE          4096*64   /* size of IR req buffers = 1 image (640*480*3) */
//#define FIRST_DESC_SIZE      1928*16 /* RGB 640*480 Mode */
//#define FIRST_DESC_SIZE      1288*16 /* Mono 640*480 Mode */
//#define PACKET_LENGTH      968         /* RGB 640*480 Mode @7.5 frames/sec */
#define PACKET_LENGTH      1928        /* RGB 640*480 Mode @15 frames/sec */
#define FIRST_DESC_SIZE      PACKET_LENGTH*16    /* RGB 640*480 Mode */

class Liste_Flow_Des
{
public:
  unsigned int *O_M;
  unsigned int O_M_handle;
  unsigned int *buf;
  unsigned int buf_handle;

  Liste_Flow_Des *suivant;  
};

class Liste_Des
{
public:
  unsigned int *O_M;
  unsigned int O_M_handle;
  unsigned int *buf;
  unsigned int buf_handle ;

  Liste_Des *suivant;  
};


// receive buffer management:
class  INPUT_CONTEXT_BUFFER 
{
  int CURRENT_REQUEST_BUFFER;
  int ASKED_REQUEST_BUFFER;
  Liste_Des *Queue, *Head;
  ti_ohci *last_adapter;
public:
  INPUT_CONTEXT_BUFFER();
  ~INPUT_CONTEXT_BUFFER(){}
  
  /////////////////  Buffers oriented function //////////////////////////
  void clean_all();
  int need_input_buffer( int size , ti_ohci *adapter) ;
  // return the size allocated if success, 0 elsewhere.

  void unneed_input_buffer( int size ) ;
  void requeue_head() ;

  /////////////////  Messages oriented function //////////////////////////
private:
  Liste_Des *current_des;
  int current_offset;
public:
  unsigned int *msg_pointer_go_and_get_value( int i ); // advance in the buffer and return the address in the buffer.
  unsigned int to_end_of_buf()// in bytes
  { return (AR_REQ_BUF_SIZE - current_offset*4) ;}
  unsigned int *next_buf() 
  { 
    if( current_des->suivant == NULL ) return NULL;
    else return current_des->suivant->buf ;
  }
  int msg_pointer_at_end(); // return TRUE if all the received data have been read.

};

// receive isochronous buffer management:
class  INPUT_FLOW_CONTEXT_BUFFER 
{
public:

  int CURRENT_REQUEST_BUFFER;
  int ASKED_REQUEST_BUFFER;
  Liste_Flow_Des *Queue, *Head;
  ti_ohci *last_adapter;
  int context;
  int channel;
  
  INPUT_FLOW_CONTEXT_BUFFER();
  ~INPUT_FLOW_CONTEXT_BUFFER(){}
  
  /////////////////  Buffers oriented function //////////////////////////
  void clean_all();
  unsigned int** need_input_buffer( int size , ti_ohci *adapter, int channel, int context ) ;
  void set_channel_context(int channel, int context);
  void run_program();
  // return the size allocated if success, 0 elsewhere.
  
  void unneed_input_buffer( int size, int channel, int context ) ;
  void requeue_head() ;
  
  /////////////////  Messages oriented function /////////////////////////
  
public:

  unsigned int to_end_of_buf()// residual in bytes
  { return  (int)(Head->O_M[3])&0x0000ffff;}
  
  unsigned int to_end_of_next_buf()// in bytes
  { return  (int)(Head->suivant->O_M[3])&0x0000ffff;}

};
#endif
