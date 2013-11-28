// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Samuel Gosselin <firstname.surname@utc.fr>
/// @date    December, 2012
/// @version $Id: AsyncWorkerBase.h 116 2013-06-25 11:44:25Z kurdejma $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Async worker base class
///
/// Detailed description.

#ifndef DEF_PACPUS_ASYNC_WORKER_BASE_H
#define DEF_PACPUS_ASYNC_WORKER_BASE_H

#include <boost/noncopyable.hpp>
#include <QObject>

#include "Pacpus/kernel/PacpusToolsConfig.h"

namespace pacpus
{

/// A simple base class for asynchronous workers able to partake in the
/// Qt slot / signal mechanism
///
/// This class represents an asynchronous event-based worker able to receive and
/// send Qt signals to other workers or threads. The rationale is to be able to
/// define stateful objects that perform calculations asynchronously, triggered
/// by external user-defined messages.
class PACPUSTOOLS_API AsyncWorkerBase
    : public QObject
    , private boost::noncopyable
{
    Q_OBJECT

public:
    /// Constructor.
    AsyncWorkerBase();

    /// Destructor.
    virtual ~AsyncWorkerBase();

    /// Starts the worker by creating a new thread for it, and calling the setup() virtual method. */
    void start();

    /// Terminates the worker as soon as there are no more requests pending and its current processing
    /// is finished.
    ///
    /// This method tries to end the worker gracefully. All pending signals sent before the stop() request will
    /// be honored.
    /// It is safe to call this method from any thread.
    ///
    ///  @param autoDelete if true, deletes the worker as soon as its event loop has finished processing.
    void stop(bool autoDelete);

    /// @returns @b true if the worker is active, @b false otherwise.
    bool isActive() const
    {
        return active_;
    }

Q_SIGNALS:
    /// @todo Documentation
    void finished();
    /// @todo Documentation
    void stopped();

protected:
    /// @todo Documentation
    virtual void setup();
    /// @todo Documentation
    virtual void process();
    /// @todo Documentation
    virtual void cleanup();

    /// Returns true if the worker is stopping.
    bool isStopping() const { return stopping_; }

private Q_SLOTS:
    /// @todo Documentation
    void doSetup();
    /// @todo Documentation
    void doFinish();

private:
    /// Ends the worker, asking the underlying thread to terminate
    ///
    /// This method signals the end of processing and requests the underlying thread to terminate. Actual termination
    /// will occur as soon as all pending signals (including those that may come from other workers during the
    /// finish request handling) have been processed.
    void finish();

    // Attributes
    bool active_;
    bool stopping_;
};

} // namespace pacpus

#endif // DEF_PACPUS_ASYNC_WORKER_BASE_H