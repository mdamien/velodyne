#ifndef TESTPACPUSSOCKET_HPP
#define TESTPACPUSSOCKET_HPP

#include "kernel/ComponentBase.h"
#include "kernel/ComponentFactory.h"

#include "PacpusSocket.hpp"

#include <qtimer.h>
#include <qstring.h>

namespace pacpus {

class TestPacpusSocket
        : public QObject
        , public ComponentBase
{
    Q_OBJECT

public:
    /// Constructor.
    TestPacpusSocket(QString name)
        : ComponentBase(name)
    {
    }

    // Destructor
    ~TestPacpusSocket()
    {

    }

protected:
    virtual void startActivity()
    {
        timer_ = new QTimer();
        connect(timer_, SIGNAL(timeout()),
                this, SLOT(update()));
        timer_->start(500);
    }

    virtual void stopActivity()
    {
        timer_->stop();
        delete timer_;
    }

    virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config)
    {
        QString pacpusSocket = config.getProperty("socketComponent");
        ComponentManager * mgr = ComponentManager::getInstance();
        pacpusSocket_ = dynamic_cast<PacpusSocket *>(mgr->getComponent(pacpusSocket));
        if (!pacpusSocket_)
        {
            qWarning() << "Failed to get component " << pacpusSocket;
            return ComponentBase::NOT_CONFIGURED;
        }
        
        return ComponentBase::CONFIGURED_OK;
    }

protected slots:
    void update()
    {
	QString toto = "toto";
	
        pacpusSocket_->sendDatagrams( toto );
    }

private:
    QTimer * timer_;
    PacpusSocket * pacpusSocket_;
};

static ComponentFactory<TestPacpusSocket> factory("TestPacpusSocket");

} // namespace pacpus

#endif // TESTPACPUSSOCKET_HPP
