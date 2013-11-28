/*********************************************************************
//  created:    2012/04/03 - 15:17
//  filename:   InterfaceDataCollector.h
//
//  author:     Pierre Hudelaine
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:	Get the data
//
*********************************************************************/

#ifndef INTERFACEDATACOLLECTOR_H
#define INTERFACEDATACOLLECTOR_H

#include <iostream>

#include "structureCanCarmen.h"
#include "structureXbow.h"

namespace pacpus {

class ShMem;

template <typename T>
class InterfaceDataCollector
{
public:
  // type et string pour le nom
  InterfaceDataCollector( std::string shMemName )
  {
    // attach listened shared memories
    shMem_  = new ShMem( shMemName.c_str(), sizeof( T ) );
    if ( !shMem_ ) {
        qFatal( "Failed to connect ", shMemName.c_str(), " shared memory" );
    }
  }
  
  ~InterfaceDataCollector()
  {
    delete shMem_;
  }
  
  T readData()
  {
    T data_;
    
    // read one by one data from shared memories
    
    if ( shMem_->wait( 10 ) ) {
      //shMem_->read(data_,sizeof(T));
      void * ptr = shMem_->read();
      shMem_->lockMemory();
      memcpy( &data_, ptr, sizeof( T ) );
      shMem_->unlockMemory();
    }
    
    return data_;
  }
  
private : 
  ShMem * shMem_; // array map from all listened
};

} // namespace pacpus

#endif // INTERFACEDATACOLLECTOR_H
