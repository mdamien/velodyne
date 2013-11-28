// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Gerald Dherbomez <firstname.surname@utc.fr>
/// @date    April, 2007
/// @version $Id: DbtPlyFileManager.h 91 2013-05-19 10:32:48Z gdherbom $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief DbitePlayer file manager.
///
/// Detailed description.
///
/// @todo Manage a vector of dbite files and update the functions
///      playModen and configureComponent to support this funtionnality.
///      Put the type of data that has just been replayed in a protected 
///      variable of the abstract class in order to the derived class can
///      know what to do.
/// @todo Complete the function playMode2.
/// @todo Make the variable kMaxPendingTimeFromEngineMicrosecs a property.

#ifndef DEF_PACPUS_DBTPLYFILEMANAGER_H
#define DEF_PACPUS_DBTPLYFILEMANAGER_H

#include <Pacpus/DbitePlayer/DbitePlayerConfig.h>
#include <Pacpus/DbitePlayer/DbtPlyEngine.h>
#include <Pacpus/kernel/road_time.h>
#include <Pacpus/kernel/ComponentBase.h>
#include <Pacpus/kernel/DbiteFile.h>

#include <QThread>

class QSemaphore;

namespace pacpus {

class DbtPlyEngine;

/// XML config properties:
///     dbt             PATH(S) path to DBT data file(s), separated by pipe symbol '|', relative to datadir property of DbtPlyEngine
///         e.g. dbt="gps/ublox.dbt|gps/ublox2.dbt"
///     ui              INT     graphical user interface (GUI) window number
///         e.g. ui="0"
///     verbose         INT     verbosity level
///         e.g. verbose="1"
/// @see DbtPlyEngine
class DBITE_PLAYER_API DbtPlyFileManager
        : public QThread
        , public ComponentBase
{
    Q_OBJECT

public:
    /// constructor
    DbtPlyFileManager(QString name);
    /// destructor
    virtual ~DbtPlyFileManager();

    /// the player replays only the last data that has not been yet replayed
    /// @todo Rename
    void playMode1 (road_time_t tDbt, bool reverse);
    /// the player replays all the data that have not been yet replayed
    /// @todo Rename
    void playMode2 (road_time_t tDbt, bool reverse);

    /// virtual method: call when new DBT data are replayed
    virtual void processData(road_time_t time, road_timerange_t timeRange, void * data) = 0;
    /// @todo Documentation
    virtual void displayUI();

    /// 3 Virtual methods relative to the ComponentBase inheritance
    virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);
    /// @todo Documentation
    virtual void startActivity();
    /// @todo Documentation
    virtual void stopActivity();

    /// The loop of the thread
    virtual void run();

public Q_SLOTS:
    /// slot activated by the engine when it computes new DBT time
    void  playData(road_time_t tDbt,road_time_t tNow, bool reverse);

    /// put the file descriptor to the beginning of the file
    void beginfile();

Q_SIGNALS:
    /// signal sent to the engine to provide to it the tmin and tmax of the file
    void tMinMaxIs(road_time_t tmin, road_time_t tmax);

protected:
    /// Verbosity level
    int mVerbose;

    /// a pointer on the player engine
    DbtPlyEngine * mEngine;

    /// the absolute path of the DBT file
    QString dbtProperty_;
    /// @todo Documentation
    QStringList mDbtFilenameList;

    /// The directory where the DBT file is located
    QString mDbtDataPath;

    /// Display or not the graphical interface
    bool mShowGui;

    /// @todo Documentation
    struct dbtStruct
    {
        /// Data buffer
        char * buffer;
        /// Acquisition time
        road_time_t t;
        /// Acquisition timerange
        road_timerange_t tr;
    };

    /// @todo Documentation
    struct dbtStructFile
    {
        /// the DBT file descriptor
        pacpus::DbiteFile * pfile;
        /// the buffer where the data are stored after the reading and the associated time, timerange and file descriptor
        dbtStruct cur;
        /// the previous DBT data, these ones that must be processed
        dbtStruct toProcess;
    };

    /// @todo Documentation
    QList<dbtStructFile> dbt_;
    /// @todo Documentation
    int dbtIndex_;

private:
    /// @todo Documentation
    bool processDbtFileHdfile(dbtStructFile & dbtFile, pacpus::DbiteFile::ReadDirection direction);

private:
    // reading backward?
    bool reverse_;

    /// the estimated DBT time sent by the engine and computed relatively to the state of the player
    road_time_t timeToRead_;

    /// The mode of replay
    /// @see playMode1, playMode2 methods
    int mode_;

    /// The minimum and maximum time of the data contained in the file
    road_time_t tMin_, tMax_;

    /// the synchronization semaphore with the engine
    QSemaphore * sync_;

    /// For statistics purpose - delta time between the instant when the tDbt is computed and the instant when it is
    /// taken into account by the file manager
    int deltaTDbtTab_[1000];
    int deltaTDbtTabLoop_;
};

} // namespace pacpus

#endif // DEF_PACPUS_DBTPLYFILEMANAGER_H
