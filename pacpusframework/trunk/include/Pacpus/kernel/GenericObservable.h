// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Stephane Bonnet <firstname.surname@utc.fr>
/// @date    October, 2012
/// @version $Id: GenericObservable.h 76 2013-01-10 17:05:10Z kurdejma $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Brief description.
///
/// Detailed description.

#ifndef DEF_PACPUS_GENERIC_OBSERVER_H
#define DEF_PACPUS_GENERIC_OBSERVER_H

#include <list>

#include <Pacpus/kernel/GenericObserverInterface.h>
#include <QMutex>

namespace pacpus {

/** Base class for te GenericObservable template.

    The purpose of this class is to be able to take generic pointers on
    GenericObservable class template instances.
*/
class GenericObservableBase
{
public:
    /// @todo Documentation
  virtual ~GenericObservableBase() {}
};

/** GenericObservable
    Base class template for observable objects (see Observable/Observer
    design pattern).

    This class implements a simple subject able to notify a list of 
    observers through calls to the notifyObservers protected method.
*/
template <typename T>
class GenericObservable
    : GenericObservableBase
{
public:
    /// @todo Documentation
  typedef GenericObserverInterface<T> ObserverType;

    /// @todo Documentation
  GenericObservable() {}
    /// @todo Documentation
  virtual ~GenericObservable() {}

  /** Attaches a new observer to the observable.
      @param observer A reference to a class obeying the GenericObserverInterface interface.
  */
  void attachObserver(ObserverType& observer) {
    observers_.push_back(&observer);
  }

  /** Detaches an observer.

      @param observer A reference to a class obeying the GenericObserverInterface interface.
      @note Does nothing if the observer has not been previously attached
  */
  void detachObserver(ObserverType& observer) {
    observers_.remove(&observer);
  }

  /** Notifies all observers about an observable event.
  */
  void notifyObservers() {
    typename std::list<ObserverType*>::const_iterator it;
    for (it = observers_.begin(); it != observers_.end(); ++it) {
      (*it)->update(static_cast<T*>(this));
    }
  }

private:
  std::list<ObserverType*> observers_;
};
  
} // namespace pacpus

#endif // DEF_PACPUS_GENERIC_OBSERVER_H
