// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
/// @author  Samuel Gosselin <firstname.surname@utc.fr>
/// @date    December, 2012
// %pacpus:license}

#include <Pacpus/PacpusTools/AsyncWorkerBase.h>

#include <Pacpus/kernel/Log.h>

#include <QThread>

using namespace pacpus;
DECLARE_STATIC_LOGGER("pacpus.core.workers");

AsyncWorkerBase::AsyncWorkerBase()
  : active_(false)
  , stopping_(false)
{
}

AsyncWorkerBase::~AsyncWorkerBase()
{
}

void
AsyncWorkerBase::start()
{
  if (!isActive())
  {
    QThread* theThread = new QThread;

    // Executes the setup() method as soon as theThread is started
    connect(theThread, SIGNAL(started()), SLOT(doSetup()));

    // Executes the finish() method as soon as theThread 

    // Allows stopping requests to be handled withing the worker thread instead
    // of the thread that made the stop() call.
    connect(this, SIGNAL(stopped()), this, SLOT(doFinish()));

    // Guarantees theThread is terminated and deleted once the worker has 
    // stopped and is destroyed
    connect(this, SIGNAL(finished()), theThread, SLOT(quit()));
    connect(theThread, SIGNAL(finished()), theThread, SLOT(deleteLater()));
    
    active_ = true;
    this->moveToThread(theThread);
    theThread->start();
  }
}

void
AsyncWorkerBase::stop(bool autoDelete)
{
	if (isActive())
  {
    if (autoDelete)
    {
      // Guarantees deletion of this once all pending signals have been handled
      connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
    }
		stopping_ = true;
		emit stopped();
	}
  else
  {
    if (autoDelete)
      delete this;
  }
}

void AsyncWorkerBase::finish()
{
	if (isActive())
  {
    cleanup();
		emit finished();
		active_ = false;
	}
}

void AsyncWorkerBase::setup()
{
}

void AsyncWorkerBase::process()
{
}

void AsyncWorkerBase::cleanup()
{
}

void AsyncWorkerBase::doSetup()
{
  setup();
  process();
}

void AsyncWorkerBase::doFinish()
{ 
  finish();
}
