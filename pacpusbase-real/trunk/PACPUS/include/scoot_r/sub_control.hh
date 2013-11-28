class Sub_Control
{
  NameType Name;
  pL_e_s myL_e_s;
  PService myPService; Register_data my_register_data;
  RTIME server_creation_time;// the time the server i used was created
  SEM  *control_sem; 
public:
  Sub_Control( pL_e_s myl_e_s, NameType *name )
  {
    memcpy( &Name, name, NAME_SIZE );
    myL_e_s = myl_e_s;
    control_sem = rt_sem_create_cpp( ); 
    rt_sem_init_cpp( control_sem, 0 ); 
    
    myPService = NULL;
    server_creation_time = 0;
  }
  
  ~Sub_Control()
  {
    myPService->unlink( control_sem ); // I dont want to know each time there is an event for the service.
    if( control_sem != NULL )
      {
	rt_sem_delete( control_sem  ); 
	rt_free( control_sem );
      }
  }

  NameType *name(){ return &Name ;}
  
  int new_quality_until( int suposed_quality, Register_data *register_data_buf, RTIME until)
  {
    myPService = myL_e_s->find_service( & Name ); 
    myPService->Get( &my_register_data );
    if( (int)my_register_data.quality == suposed_quality )
      {
	if( my_register_data.time_creation_min == server_creation_time ) 
	  {
	    //	    myPService->link( control_sem );
	    if( until == -1 ) 
	      {
		if( myPService->wait( control_sem ) == SEM_ERR ) {}
	      }
	    else {
	      if( myPService->wait_until( control_sem, until ) == SEM_ERR ) {}
	    }
	    myPService->unlink( control_sem ); // it is better some server put it on
	    myPService = myL_e_s->find_service( & Name ); 
	    myPService->Get( &my_register_data );
	  }
	server_creation_time = my_register_data.time_creation_min;
      }
    if( register_data_buf != NULL ) my_register_data.Get( register_data_buf );
    return my_register_data.quality;
  }
};

