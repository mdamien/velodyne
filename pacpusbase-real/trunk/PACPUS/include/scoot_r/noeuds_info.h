
#ifndef _NOEUDS_INFO_
#define _NOEUDS_INFO_

#ifndef WIN32
#include "ohci.h"
#endif

struct noeud_info{ 
  int speed;
  int nb_fils;
};

class Tree_Topology
{

#ifdef WIN32
public:
	void handle( int node_addr, int speed, int nb_fils)
	{
		node_map[ node_addr ].speed = speed ;
		node_map[ node_addr ].nb_fils = nb_fils ;
		if( size <= node_addr ) size = node_addr +1;
	}

#else
  friend void handle_Selfid(struct ti_ohci *ohci);
#endif
  struct noeud_info node_map[64];
  int size;

  int min_speed_node, min_speed_leaf;
  int OK;
 public: 
 Tree_Topology()
   {
     OK = TRUE; // nothing usefull while there is no a complete reset and selfid.
     min_speed_node = 0; min_speed_leaf = 0; // 100 Mbits
     size = 1;
   }
 ~Tree_Topology()
   {
   }

 void reset()
   {
     OK = FALSE; size = 1;
   }
 void complete()
   {
     OK = TRUE;
   }
 int ok(){ return OK; }
 int speed_node( int ieee_1394_addr ) // return the speed to use to this node
   {
     ieee_1394_addr = ieee_1394_addr & 0x3f;
     if( ( 0 <= ieee_1394_addr ) && ( ieee_1394_addr < size ) )
       {
	 if( node_map[ ieee_1394_addr ].speed > min_speed_node ) 
	   return min_speed_node ;
	 else return node_map[ ieee_1394_addr ].speed ;
       } 
     else return 0; // return min_speed_leaf;
   }

 URTIME scoot_r_mask()
   { 
     URTIME local;
//     local = (RTIME) -1; //0xffffffffffffffff; 
    local = 0x7fffffff; local = local << 32; local = local | 0xffffffff; 
     return  local >> (64 - size ); 
   }
 int num(){ return size ; }
#ifdef PROC_SCOOTER
 int affiche(char *page); // designed to be used whith the linux proc_fs interface
#endif
};

#endif
