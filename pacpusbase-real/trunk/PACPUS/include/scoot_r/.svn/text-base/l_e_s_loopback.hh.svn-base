/* * Last edited: Feb 18 19:14 1993 (crubille) */

#ifndef _L_E_S_H_LOOPBACK
#define _L_E_S_H_LOOPBACK

#include "l_e_s.hh"

class L_e_s_loopback;

class Descriptor_loopback : public Descriptor
// this structure contain everithing is needed to send a message:
// the addresses for the data block, for two descriptors (in case 
// this message is resend twice and a pseudo "first block" to emulate
// a standart reception for local delivery.
{
  //  int des_data_size;
  //  int nb_output_blocks; // always 1 here

public: 
  Descriptor_loopback( unsigned int * d, int size_d, L_e_s_loopback *dev, unsigned int type, int irq_policy );
  virtual ~Descriptor_loopback();

  unsigned int to_send( int dest_addr, int port_addr, int speed, int transaction_index, int priority, int current_size );
  void head_list( ){}
  //  unsigned int Type();
  unsigned int send_status() ; // the status word for the last message sended whith this descriptor
  unsigned int xferstatus( ) ;
};

  class Descriptor_loopback_flow : public Descriptor_flow
  // this structure contain everithing is needed to send an object:
  // the addresses for the data block, for two descriptors (in case 
  // this message is resend twice and a pseudo "first block" to emulate
  // a standart reception for local delivery.
  {
  unsigned int **descriptors; // We use as many descriptors attached for each data messages
  // each message can be send only at one but we have to be care because the ohci adapter
  // can use the last one as a end queue cell for the context.
  int current;
  L_e_s_loopback *adapter;
  unsigned int *des_data;  
  int des_data_size; 
  
  public: 
    //    int nb_output_blocks;
    Descriptor_loopback_flow( unsigned int  *d, int size_d, L_e_s_loopback *dev, int channel );
    virtual ~Descriptor_loopback_flow();
    unsigned int to_send_flow(int context);
  };
////////////////////////////////////////////////////////////////

class L_e_s_loopback :public virtual L_e_s
{
  friend class Descriptor_loopback;
  friend class Descriptor_loopback_flow;
private: 
  // data for the at_req_context managment.
  //  unsigned int *at_req_context_last_descriptor_block; 
  // unsigned int at_req_context_branch_address_Z_offset; 
  
public:
  L_e_s_loopback( int id );
  virtual ~L_e_s_loopback();
  virtual void start_task();
  virtual int reset();
  virtual int send(Descriptor *buf_des, int dest, int port_addr, int transaction_index , int current_size); // current_size = 0xffff mean the whole message is send.
  virtual int deposit(Descriptor_flow *buf_des, int channel, int context, int sync);  
  virtual int consume ( int channel, int context);
  virtual unsigned int local_addr() {return 0;}
  unsigned int local_bus() {return 0;}
  unsigned int generation_count() { return 0;}
  virtual unsigned int net_nb_128s();
  virtual unsigned int net_nb_100ns();
  virtual void net_timestamp_min(RTIME *min); // redefined

  virtual Descriptor *new_descriptor( unsigned int *SD, int size_d,
                     unsigned int type , int irq_policy)
  {
    return new Descriptor_loopback( SD, size_d, this , type , irq_policy );
  }
    virtual Descriptor_flow *new_descriptor_flow( unsigned int *SD ,int size_SD, int channel)
  {
    return new Descriptor_loopback_flow( SD, size_SD, this , channel );
  }
   
  virtual void need_input_buffer( int size_message, int nb_messages){}
  virtual void unneed_input_buffer( int size_message, int nb_messages){}
  virtual void need_input_buffer( int size ){}
  virtual void unneed_input_buffer( int size ){}
  virtual unsigned int ** need_input_flow_buffer( int nb_buffers, int channel, int context){ return NULL;}
  virtual void unneed_input_flow_buffer( int nb_buffers, int channel, int context){}
  
  virtual int get_nb_iso_ctx(unsigned int reg ) { return MAX_NODE_PRODUCERS ; }

#ifdef PROC_SCOOTER
  int read_les_loopback(char *page, char**start, off_t off, int count, int *eof);
#endif
  
};

#endif



