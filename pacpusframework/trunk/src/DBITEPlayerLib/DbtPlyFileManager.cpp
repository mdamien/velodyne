// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @author  Gerald Dherbomez <firstname.surname@utc.fr>
/// @version $Id: DbtPlyFileManager.cpp 91 2013-05-19 10:32:48Z gdherbom $

#include <Pacpus/DbitePlayer/DbtPlyFileManager.h>
#include <Pacpus/kernel/ComponentManager.h>
#include <Pacpus/kernel/DbiteException.h>
#include <Pacpus/kernel/Log.h>

#include <cassert>
#include <iostream>
#include <limits>
#include <QMetaType>
#include <QSemaphore>

using namespace pacpus;
using namespace std;

DECLARE_STATIC_LOGGER("pacpus.core.DbtPlyFileManager");

const string kPropertyVerbose = "verbose";
const int kPropertyVerboseDefaultValue = 1;

const string kPropertyDbiteFileName = "dbt";

// It is the maximum time elapsed between the computation of the tDbt and the data replay in microseconds
static const int kMaxPendingTimeFromEngineMicrosecs = 10000;

////////////////////////////////////////////////////////////////////////////////
/// Constructor.
DbtPlyFileManager::DbtPlyFileManager(QString name):ComponentBase(name)
{
    LOG_TRACE("constructor");

    sync_ = new QSemaphore(1);
    sync_->acquire();
    tMin_ = numeric_limits<road_time_t>::max();
    tMax_ = numeric_limits<road_time_t>::min();
}

////////////////////////////////////////////////////////////////////////////////
/// Destructor.
DbtPlyFileManager::~DbtPlyFileManager() 
{
    LOG_TRACE("destructor");

    for (QList<dbtStructFile>::iterator it = dbt_.begin(), itend = dbt_.end(); it != itend; ++it) {
        dbtStructFile & dbtFile = *it;

        delete[] dbtFile.cur.buffer;
        delete[] dbtFile.toProcess.buffer;
    }
}

////////////////////////////////////////////////////////////////////////////////
/// Configures the file manager.
ComponentBase::COMPONENT_CONFIGURATION DbtPlyFileManager::configureComponent(XmlComponentConfig config)
{
    ComponentManager * mgr = ComponentManager::getInstance();
    mEngine = static_cast<DbtPlyEngine *>(mgr->getComponent("dbiteEngine"));
    if (NULL == mEngine ) {
        LOG_FATAL("cannot get a pointer of the 'dbiteEngine' component");
        return CONFIGURED_FAILED;
    }
    if (!mEngine->isConfigured()) {
        LOG_WARN("'dbiteEngine' component was not configured");
        return CONFIGURATION_DELAYED;
    }

    // Qt Signal-Slot connections
    // register the road_time_t type for the connection
    qRegisterMetaType<road_time_t>("road_time_t");
    connect(mEngine, SIGNAL(play(road_time_t,road_time_t, bool)),
            this, SLOT(playData(road_time_t,road_time_t, bool)),
            Qt::DirectConnection);
    connect(this, SIGNAL(tMinMaxIs(road_time_t,road_time_t )),
            mEngine, SLOT(tMinMax(road_time_t, road_time_t)));
    connect(mEngine, SIGNAL(stopfile()),
            this, SLOT (beginfile()));


    // get the properties in the XML node
    /////////////////////////////////////////
    {
        QString verbose = param.getProperty(kPropertyVerbose.c_str());
        if (verbose.isNull()) {
            LOG_INFO("property " << kPropertyVerbose << " not set."
                     << " Set to default = " << kPropertyVerboseDefaultValue
                     );
            // default value
            mVerbose = kPropertyVerboseDefaultValue;
        } else {
            verbose = verbose.toLower();
            LOG_DEBUG("property " << kPropertyVerbose << "=\""
                      << verbose.toStdString() << "\"");
            mVerbose = verbose.toInt();
            LOG_DEBUG("property interpreted as " << kPropertyVerbose << "=\""
                      << mVerbose << "\"");
        }
    }

    /////////////////////////////////////////
    dbtProperty_ = param.getProperty(kPropertyDbiteFileName.c_str());
    mShowGui = param.getProperty("ui").toInt();
    mDbtDataPath = mEngine->getDataDir();

    mDbtFilenameList = dbtProperty_.split("|");

    for (int i = 0; i < mDbtFilenameList.size(); ++i) {
        mDbtFilenameList[i] = mDbtDataPath + mDbtFilenameList.at(i);
        LOG_INFO("opening DBT file \"" << mDbtFilenameList.at(i) << "\"");

        // temporary dbt object
        dbtStructFile dbt;
        dbt.pfile = new DbiteFile();
        assert(dbt.pfile);
        try {
            dbt.pfile->open(mDbtFilenameList.at(i).toStdString(), ReadMode);
        } catch (DbiteException & e) {
            LOG_ERROR("cannot open DBT file \"" << mDbtFilenameList.at(i) << "\"");
            LOG_DEBUG("error: " << e.what());
            return CONFIGURED_FAILED;
        }
        if (!dbt.pfile->isOpen()) {
            LOG_ERROR("cannot open DBT file \"" << mDbtFilenameList.at(i) << "\"");
            return CONFIGURED_FAILED;
        }
        cout << "Header: " << "\n"
             << (string) *dbt.pfile << "\n";

        // alloc buffer with the Data Size given in the header
        dbt.cur.buffer = new char[dbt.pfile->getRecordSize()];
        dbt.toProcess.buffer = new char[dbt.pfile->getRecordSize()];

        dbt_.insert(i, dbt);

        // Reading of the first data to put in the buffer_
        dbt_[i].pfile->readRecord(dbt_[i].cur.t, dbt_[i].cur.tr, reinterpret_cast<char *>(dbt_[i].cur.buffer));

        if (dbt_.at(i).pfile->getRecordCount() > 0) {
            if (dbt_.at(i).pfile->getTimeMin() < tMin_) {
                tMin_ = dbt_.at(i).pfile->getTimeMin();
            }
            if (dbt_.at(i).pfile->getTimeMax() > tMax_ ) {
                tMax_ = dbt_.at(i).pfile->getTimeMax();
            }
            Q_EMIT tMinMaxIs(tMin_, tMax_);
        }
    }

    return CONFIGURED_OK;
}

////////////////////////////////////////////////////////////////////////////////
/// Starts activity of the file manager
void DbtPlyFileManager::startActivity()
{ 
    // graphical user interface
    if (mShowGui) {
        displayUI();
    }

    deltaTDbtTabLoop_ = 0;

    mode_ = mEngine->replayMode();
    LOG_INFO("replay mode " << mode_);
    start();
}

////////////////////////////////////////////////////////////////////////////////
/// Stops activity of the file manager
void DbtPlyFileManager::stopActivity()
{ 
    deltaTDbtTabLoop_ = 0;
}

void DbtPlyFileManager::displayUI()
{
    //LOG_WARN("component '" << componentName << "' has no user interface. Please set ui property to 0 in your XML configuration");
}

////////////////////////////////////////////////////////////////////////////////
/// Goes back to the beginning of the file.
/// Places the descriptor to the first data.
void DbtPlyFileManager::beginfile()
{
    LOG_DEBUG("called beginfile()");
    for (QList<dbtStructFile>::iterator it = dbt_.begin(), itend = dbt_.end(); it != itend; ++it) {
        dbtStructFile & dbtFile = *it;

        dbtFile.pfile->goToDataBegin();
        // reinitialize buffer and times to the 1st value
        dbtFile.pfile->readRecord(dbtFile.cur.t, dbtFile.cur.tr, reinterpret_cast<char *>(dbtFile.cur.buffer));
    }
}

bool DbtPlyFileManager::processDbtFileHdfile(dbtStructFile & dbtFile, DbiteFile::ReadDirection direction)
{
    dbtFile.toProcess.t = dbtFile.cur.t;
    dbtFile.toProcess.tr = dbtFile.cur.tr;
    memcpy(dbtFile.toProcess.buffer, dbtFile.cur.buffer, dbtFile.pfile->getRecordSize());

    if (!dbtFile.pfile->readRecord(dbtFile.cur.t, dbtFile.cur.tr, reinterpret_cast<char *>(dbtFile.cur.buffer), direction)) {
        LOG_WARN("EOF or there was a problem in read function, no data read");
        dbtFile.cur.t = tMax_;
        return false;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////
/// play mode 1
/// the player replays only the last data that has not been yet replayed
void DbtPlyFileManager::playMode1(road_time_t tDbt, bool reverse)
{
    DbiteFile::ReadDirection readDirection = DbiteFile::ReadForward;
    if (reverse) {
        readDirection = DbiteFile::ReadBackward;
    }

    dbtIndex_ = 0;
    for (QList<dbtStructFile>::iterator it = dbt_.begin(), itend = dbt_.end(); it != itend; ++it) {
        dbtStructFile & dbtFile = *it;

        bool mustProcess = false;
        if (reverse) {
            // backward
            while (dbtFile.cur.t > tDbt) {
                mustProcess = true;
                if (!processDbtFileHdfile(dbtFile, readDirection)) {
                    break;
                }
            }
        } else {
            // forward
            while (dbtFile.cur.t < tDbt) {
                mustProcess = true;
                if (!processDbtFileHdfile(dbtFile, readDirection)) {
                    break;
                }
            }
        }

        if (mustProcess) {
            processData(dbtFile.cur.t, dbtFile.toProcess.tr, dbtFile.cur.buffer);
        }
        ++dbtIndex_;
    }
}

////////////////////////////////////////////////////////////////////////////////
// play mode 2
// the player replays all the data that have not been yet replayed
void DbtPlyFileManager::playMode2(road_time_t tDbt, bool reverse)
{
    DbiteFile::ReadDirection readDirection = DbiteFile::ReadForward;
    if (reverse) {
        readDirection = DbiteFile::ReadBackward;
    }

    dbtIndex_ = 0;
    for (QList<dbtStructFile>::iterator it = dbt_.begin(), itend = dbt_.end(); it != itend; ++it) {
        dbtStructFile & dbtFile = *it;

        if (reverse) {
            // backward
            while (dbtFile.cur.t > tDbt) {
                processDbtFileHdfile(dbtFile, readDirection);
                processData(dbtFile.cur.t, dbtFile.toProcess.tr, dbtFile.cur.buffer);
            }
        } else {
            // forward
            while (dbtFile.cur.t < tDbt) {
                processDbtFileHdfile(dbtFile, readDirection);
                processData(dbtFile.cur.t, dbtFile.toProcess.tr, dbtFile.cur.buffer);
            }
        }
        ++dbtIndex_;
    }
}

////////////////////////////////////////////////////////////////////////////////
// slot 
// Called by the player engine 
// Before replaying data, this funtion verifies that the replayed time is  
// included in the time interval of the data and that the time elapsed between  
// the estimation of this replayed time is not too big
void DbtPlyFileManager::playData(road_time_t tDbt,road_time_t tNow, bool reverse)
{
    // If tDbt is not included in the time interval of the data, we don't have any data to play
    if ((tDbt>tMax_) || (tDbt<tMin_)) {
        return;
    }

    // measure the difference between the current time and the tNow used to calculate the tDbt
    int deltaT = road_time() - tNow;
    deltaTDbtTab_[(deltaTDbtTabLoop_++)%1000] = deltaT;
    if (deltaT > kMaxPendingTimeFromEngineMicrosecs) {
        LOG_WARN(componentName << ": data not replayed: elapsed time since engine notification too big:" << deltaT << "us");
        return;
    }

    timeToRead_ = tDbt;
    reverse_ = reverse;
    sync_->release();
}

////////////////////////////////////////////////////////////////////////////////
/// Main loop of the thread.
/// Only synchronize on the player engine and when activated call the correct
/// replay method.
void DbtPlyFileManager::run()
{
    for (;;) {
        sync_->acquire();

        switch (mode_) {
        case 1:
            playMode1(timeToRead_, reverse_);
            break;

        case 2:
            playMode2(timeToRead_, reverse_);
            break;

        default:
            break;
        }
    }
}
