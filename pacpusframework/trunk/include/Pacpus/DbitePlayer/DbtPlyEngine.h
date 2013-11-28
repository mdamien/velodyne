// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Gerald Dherbomez <firstname.surname@utc.fr>
/// @author  Marek Kurdej <firstname.surname@utc.fr>
/// @date    April, 2007
/// @version $Id: DbtPlyEngine.h 91 2013-05-19 10:32:48Z gdherbom $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief DbitePlayer DbitePlayer.
///
/// Detailed description.

#ifndef DEF_PACPUS_DBTPLYENGINE_H
#define DEF_PACPUS_DBTPLYENGINE_H

#include <Pacpus/kernel/ComponentBase.h>
#include <Pacpus/kernel/ComponentFactory.h>
#include <Pacpus/DbitePlayer/DbitePlayerConfig.h>
#include <Pacpus/DbitePlayer/DbtPlyEngineStateChart.h>
#include <Pacpus/DbitePlayer/DbtPlyUserInterface.h>

#include <QSemaphore>
#include <QThread>

namespace pacpus {

class DbtPlyEngineStateChart;
class DbtPlyEngineState;

/// @todo Documentation
enum PlayMode
{
    PlayModeLastData = 1,   ///< replay_mode="1"
    PlayModeAllData = 2     ///< replay_mode="2"
};

/// XML config properties:
///     datadir         PATH    root data directory,
///         e.g. datadir="/home/user/dbt_data"
///     replay_mode     STRING  {1}|2
///         e.g. replay_mode="2"
class DBITE_PLAYER_API DbtPlyEngine
        : public QThread
        , public ComponentBase
{
    Q_OBJECT

public:
    /// Constructor
    DbtPlyEngine(QString name);
    /// Destructor
    ~DbtPlyEngine();

    /// @returns the directory where the data are stored
    QString getDataDir();

    /// @returns the current replay time
    road_time_t getTime()
    {
        return tDbt_;
    }

    /// @returns @b true if the player is playing, @b false otherwise
    bool isPlaying();
    /// Accessor to playmode
    int replayMode()
    {
        return replayMode_;
    }

    /// @todo Documentation
    const DbtPlyEngineState * getState();
    /// @todo Documentation
    void setState(DbtPlyEngineState * newState);

    /// Goes back to the beginning, sets speed to initial value
    void reset();

    /// @todo Documentation
    void speedUp();
    /// @todo Documentation
    void speedDown();
    /// @todo Documentation
    void setLastTNow(road_time_t newTNow)
    {
        this->lastTNow_= newTNow;
    }

protected:
    /// @todo Documentation
    virtual void startActivity();
    /// @todo Documentation
    virtual void stopActivity();
    /// @todo Documentation
    virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

    /// Thread main loop
    virtual void run();

private:
    DbtPlyEngineState * mCurrentState;
    float mSpeed;
    bool mIsReverse;

    /// The state chart of the engine (speed, state and direction)
    DbtPlyEngineStateChart * stateChart_;

    /// A semaphore of protection of the critical section
    QSemaphore * tMinMaxSem_;
    /// tmin and tmax regarding to all the DBT files replayed
    road_time_t tDbtMin_, tDbtMax_;

    /// tNow_ = the current time when the trigger alerts the engine
    road_time_t tNow_;
    /// lastTNow_ = previous tNow_
    road_time_t lastTNow_;
    /// tDbt_ = the DBT time at which the data have to be replayed corresponding the state of the engine
    road_time_t tDbt_;
    /// lastTDbt_ = previous tDbt_
    road_time_t lastTDbt_;

    /// the direction of reading: forward=1 or backward=-1 used to compute the tDbt that must be replayed
    short direction_;

    /// the synchronization semaphore with the trigger
    QSemaphore * sync_;

    /// where the data are stored
    QString dataDir_;

    /// mode
    PlayMode replayMode_;

Q_SIGNALS:
    /// @todo Documentation
    void play(road_time_t timeToPlay, road_time_t actualTime, bool direction);
    /// @todo Documentation
    void stopfile();
    /// @todo Documentation
    void displayStateSig(DbtPlyEngineState * state, float speed);
    /// @todo Documentation
    void timeMinMax(road_time_t tMin, road_time_t tMax);
    /// @todo Documentation
    void curReplayTime(road_time_t time);

public Q_SLOTS:
    /// @todo Documentation
    void engReceiver();
    /// @todo Documentation
    void changeDirection(bool reverse);
    /// @todo Documentation
    void tMinMax(road_time_t tMin, road_time_t tMax);

    /// @todo Documentation
    void playEvent();
    /// @todo Documentation
    void pauseEvent();
    /// @todo Documentation
    void stopEvent();
    /// @todo Documentation
    void speedUpEvent();
    /// @todo Documentation
    void speedDownEvent();
};

} // namespace pacpus

#endif // DEF_PACPUS_DBTPLYENGINE_H
