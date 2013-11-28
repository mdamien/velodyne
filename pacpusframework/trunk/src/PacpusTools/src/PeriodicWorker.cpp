// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
/// @author  Samuel Gosselin <firstname.surname@utc.fr>
/// @date    December, 2012
// %pacpus:license}

#include <Pacpus/PacpusTools/PeriodicWorker.h>

#include <QTimer>

using namespace pacpus;

PeriodicWorker::PeriodicWorker()
  : AsyncWorkerBase()
  , mHeartbeat(NULL)
{
  mHeartbeat = new QTimer(this);
}

PeriodicWorker::~PeriodicWorker()
{
}

void
PeriodicWorker::startWork(int msec)
{
  mHeartbeat->start(msec);
  connect(mHeartbeat, SIGNAL(timeout()), this, SLOT(doWork()));
  
  this->start();
}

void
PeriodicWorker::stopWork()
{
  disconnect(mHeartbeat, SIGNAL(timeout()), this, SLOT(doWork()));
}
