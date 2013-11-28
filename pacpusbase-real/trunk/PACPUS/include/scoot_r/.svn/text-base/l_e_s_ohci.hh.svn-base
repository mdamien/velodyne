/* * Last edited: Feb 18 19:14 1993 (crubille) */

#ifndef _L_E_S_H_OHCI
#define _L_E_S_H_OHCI

#include "l_e_s.hh"
#include "ohci_context.hh"

class L_e_s_OHCI;

class Descriptor_OHCI : public Descriptor
// this structure contain everithing is needed to send a message:
// the addresses for the data block, for two descriptors (in case 
// this message is resend twice and a pseudo "first block" to emulate
// a standart reception for local delivery.
{
  unsigned int *descriptors[2]; // We use 2 descriptors attached for each data messages
  // each message can be send only at one but we have to be care because the ohci adapter
  // can use the last one as a end queue cell for the context.
  unsigned int dma_handle[2]; // an handle for each descriptor.
  int current; // which descriptor is the current one
  L_e_s_OHCI *adapter_ohci ;
  unsigned int dma_handle_data;

public: 
  int nb_output_blocks;
  Descriptor_OHCI( unsigned int *d, int size_d, L_e_s_OHCI *dev, unsigned int type, int irq_policy );
  virtual ~Descriptor_OHCI();

  unsigned int to_send( int dest_addr, int port_addr, int speed, int transaction_index, int priority, int current_size );
  void head_list( );
  //  void to_local( int local_addr, int port_addr, int t_label );
  //  unsigned int Type();
  unsigned int send_status() ; // the status word for the last message sended whith this descriptor
  unsigned int xferstatus( ) ;
};

  class Descriptor_OHCI_flow : public Descriptor_flow
  // this structure contain everithing is needed to send an object:
  // the addresses for the data block, for two descriptors (in case 
  // this message is resend twice and a pseudo "first block" to emulate
  // a standart reception for local delivery.
  {
  unsigned int **descriptors; // We use as many descriptors attached for each data messages
  // each message can be send only at one but we have to be care because the ohci adapter
  // can use the last one as a end queue cell for the context.
  unsigned int *dma_handle; // We use as many descriptors attached for each data messages
  int current;
  L_e_s_OHCI *adapter;
  unsigned int *des_data;  
  int des_data_size; 
  unsigned int dma_handle_data;
  
  public: 
    int nb_output_blocks;
    Descriptor_OHCI_flow( unsigned int  *d, int size_d, L_e_s_OHCI *dev, int channel );
    virtual ~Descriptor_OHCI_flow();
    unsigned int to_send_flow(int context);
  };
////////////////////////////////////////////////////////////////
void irq_task( int p);

class L_e_s_OHCI :public virtual L_e_s
{
  friend class Descriptor_OHCI;
  friend class Descriptor_OHCI_flow;
  friend void irq_task(int p);
private: 
  ti_ohci *adapter;

  SEM *irq_sem;
  RT_TASK *irq_task_id;

  // receive buffer management:
  INPUT_CONTEXT_BUFFER Input_Request_Buffer; 
  INPUT_FLOW_CONTEXT_BUFFER Input_Request_Flow_Buffer[MAX_NODE_CONSUMMERS]; 
  // data for the at_req_context managment.
  unsigned int *at_req_context_last_descriptor_block; 
  unsigned int at_req_context_branch_address_Z_offset; 
  
  SEM *buffer_to_list( INPUT_CONTEXT_BUFFER *Request_Buffer); // ( build the low_level_data_list for each client, server and register)
  // SEM *to_list( unsigned int scooter_type, unsigned int from, unsigned int *msg_first_block_addr, int msg_first_block_size );
  SEM *buffer_to_iso_list( INPUT_FLOW_CONTEXT_BUFFER *Request_Buffer, int context ); // ( build the low_level_data_list for each client, server and register)
public:
  L_e_s_OHCI( int id ,ti_ohci *ohci_dev );
  virtual void start_task(); // To be called after the construction.
  virtual ~L_e_s_OHCI();
  virtual int reset();
  virtual int send(Descriptor *buf_des, int dest, int port_addr, int transaction_index , int current_size); // current_size = 0xffff mean the whole message is send.
  virtual int consume ( int channel, int context);
  
  virtual int deposit( Descriptor_flow *buf_des, int channel,  int context, int sync);
  virtual int get_nb_iso_ctx(unsigned int reg);
  virtual unsigned int local_addr() ; // the local node address for this network
  virtual unsigned int net_nb_128s();
  virtual unsigned int net_nb_100ns();
  //  virtual unsigned int bus_cycle();

  virtual Descriptor *new_descriptor( unsigned int *SD, int size_SD , unsigned int type , int irq_policy)
  {
    return new Descriptor_OHCI( SD, size_SD, this , type , irq_policy );
  }
  virtual Descriptor_flow *new_descriptor_flow( unsigned int *SD, int size_SD ,int channel)
  {
    return new Descriptor_OHCI_flow( SD, size_SD, this , channel );
  }
  
  virtual void need_input_buffer( int size_message, int nb_messages);
  virtual void unneed_input_buffer( int size_message, int nb_messages);
  virtual void need_input_buffer( int size );
  virtual void unneed_input_buffer( int size );

  virtual unsigned int ** need_input_flow_buffer( int size, int channel, int context );
  virtual void unneed_input_flow_buffer( int size, int channel, int context );

  //  virtual void need_output_buffer( int size );

  virtual SEM *received_message() // called from the irq handler
  {
    return buffer_to_list( &Input_Request_Buffer );
  }

  virtual SEM *received_iso_message( int context ) // called from the irq handler
  {
    return buffer_to_iso_list( &Input_Request_Flow_Buffer[context], context  );
  }

#ifdef PROC_SCOOTER
  int read_les_ohci(char *page, char**start, off_t off, int count, int *eof);
#endif
  
};

#endif
