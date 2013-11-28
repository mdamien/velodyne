/* * Last edited: Feb 18 19:14 1993 (crubille) */

#ifndef _L_E_S_H_OHCI
#define _L_E_S_H_OHCI

#include "l_e_s.hh"
#include "sdnet2.h"

class L_e_s_SEDNET;

class Descriptor_SEDNET : public Descriptor
// this structure contain everithing is needed to send a message:
// the addresses for the data block, for two descriptors (in case 
// this message is resend twice and a pseudo "first block" to emulate
// a standart reception for local delivery.
{
  int des_data_size;
  int nb_output_blocks; // always 1 here
  SDNET2_ASYNC msg;
  L_e_s_SEDNET *adapter_sdnet2 ;

public: 
  Descriptor_SEDNET( unsigned int * d, int size_d, L_e_s_SEDNET *dev, unsigned int type, int irq_policy );
  virtual ~Descriptor_SEDNET();

  unsigned int to_send( int dest_addr, int port_addr, int speed, int transaction_index, int priority, int current_size );
  void head_list( ){}
  //  unsigned int Type();
  unsigned int send_status() ; // the status word for the last message sended whith this descriptor
  unsigned int xferstatus( ) ;
};


class Descriptor_Flow_SEDNET : public Descriptor_flow
// this structure contain everithing is needed to send a message:
// the addresses for the data block, for two descriptors (in case 
// this message is resend twice and a pseudo "first block" to emulate
// a standart reception for local delivery.
{
  int des_data_size;
  int nb_output_blocks; 
  SDNET2_ISOCH msg;
  L_e_s_SEDNET *adapter_sdnet2 ;

public: 
  Descriptor_Flow_SEDNET( unsigned int * d, int size_d, L_e_s_SEDNET *dev, int channel );
  virtual ~Descriptor_Flow_SEDNET();

  unsigned int to_send_flow( int channel );
  void head_list( ){}
  //  unsigned int Type();
  unsigned int send_status( ) ; // the status word for the last message sended whith this descriptor
  unsigned int xferstatus( ) ;
};


////////////////////////////////////////////////////////////////
extern int selfid_handler( void *context,
					void *packet,
					UINT32 **newBuffer );
const int NB_recv_msg = 16 ; 

class L_e_s_SEDNET :public virtual L_e_s
{
  friend Descriptor_SEDNET;
  friend int selfid_handler( void *context,
					void *packet,
					UINT32 **newBuffer );
public:
  static SDNET2_HANDLE sdnet2_handle;
private: 
  SDNET2_HANDLE adapter;
  SDNET2_ISOCH  receive_flow_msg;
  SDNET2_SELFID selfid_msg;

  SEM *selfid_sem;
  
  int NB_128sec ; // to extend the cycle time to the net time
  int secondCount_old;
  // receive buffer management:

  // data for the at_req_context managment.
  unsigned int *at_req_context_last_descriptor_block; 
  unsigned int at_req_context_branch_address_Z_offset; 
  
public:
  L_e_s_SEDNET( int id );
  virtual ~L_e_s_SEDNET();
  virtual int reset();
  virtual int send(Descriptor *buf_des, int dest, int port_addr, int transaction_index , int current_size); // current_size = 0xffff mean the whole message is send.
  virtual int deposit(Descriptor_flow *buf_des, int channel, int context, int sync); // current_size = 0xffff mean the whole message is send.
  virtual int consume(int channel, int context);
  virtual unsigned int local_addr() ; // the local node address for this network
  unsigned int local_bus() ; // the local node address for this network
  unsigned int generation_count() ; // the local node address for this network
  virtual unsigned int net_nb_128s();
//  virtual unsigned int bus_cycle();
 virtual unsigned int net_nb_100ns();
  void do_bus_reset();

  virtual Descriptor *new_descriptor( unsigned int *SD, int size_d,
                     unsigned int type , int irq_policy)
  {
    return new Descriptor_SEDNET( SD, size_d, this , type , irq_policy );
  }
  
   virtual Descriptor_flow *new_descriptor_flow( unsigned int *SD ,int size_SD, int channel)
  {
    return new Descriptor_Flow_SEDNET( SD, size_SD, this , channel );
  }
  
  virtual void need_input_buffer( int size_message, int nb_messages);
  virtual void unneed_input_buffer( int size_message, int nb_messages);
  virtual void need_input_buffer( int size );
  virtual void unneed_input_buffer( int size );

  virtual unsigned int **need_input_flow_buffer( int size, int channel, int context );
  virtual void unneed_input_flow_buffer( int size, int channel, int context );

  //  virtual void need_output_buffer( int size );
};

#endif
