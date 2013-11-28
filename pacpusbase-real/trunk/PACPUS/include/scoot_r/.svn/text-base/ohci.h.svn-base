#ifndef _OHCI_H
#define _OHCI_H


struct ti_ohci;
extern struct ti_ohci *ohci_find_dev(struct ti_ohci *dev );
extern void send(struct ti_ohci *host,void * buf, int size, int dest);
extern void rt_remove_card(struct ti_ohci *ohci);
extern void handle_Selfid(struct ti_ohci *ohci);

extern unsigned long get_cycle_timer_register( struct ti_ohci *ohci );
extern SEM *get_some_message( struct ti_ohci *ohci );
extern void bus_reset(struct ti_ohci *ohci);

#endif





