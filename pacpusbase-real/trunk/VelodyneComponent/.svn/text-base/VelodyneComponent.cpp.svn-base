/*********************************************************************
//  created:    2010/03/26 - 14:38
//  filename:   VelodyneComponent.cpp
//
//  author:     Gerald Dherbomez
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
//  version:    $Id: $
//
//  purpose:    The acquisition component of the Velodyne HDL64S2 sensor
//
*********************************************************************/

#include "VelodyneComponent.h"

#include "kernel/cstdint.h"
#include "kernel/ComponentFactory.h"
#include "kernel/DbiteFileTypes.h"
#include "kernel/Log.h"

#include <QtEndian>
#include <QUdpSocket>
#include <string>

using namespace pacpus;
using namespace std;

DECLARE_STATIC_LOGGER("pacpus.base.VelodyneComponent");

/// Construct the factory
static ComponentFactory<VelodyneComponent> sFactory("VelodyneComponent");

/// Default host address = 0.0.0.0 (any address)
static const string kDefaultHostAddress = "0.0.0.0";

/// Default host port = 2368
static const uint16_t kDefaultHostPort = 2368;

static const string kPropertyRecording = "recording";

static const string kVelodyneSharedMemoryName = "VELODYNE";
static const string kDefaultOutputFilename = "velodyne_spheric.dbt";

//////////////////////////////////////////////////////////////////////////
/// Constructor
VelodyneComponent::VelodyneComponent(QString name)
    : ComponentBase(name)
    , mPort(kDefaultHostPort)
{
    LOG_TRACE("constructor(" << name << ")");
    
    ComponentManager * mgr = ComponentManager::getInstance();
    LOG_DEBUG("manager = " << mgr);

    recording = true;

    // default values
    if (!(mHost.setAddress(kDefaultHostAddress.c_str()))) {
        LOG_ERROR("cannot set address");
    }
    LOG_DEBUG("host address = " << mHost.toString());
}

//////////////////////////////////////////////////////////////////////////
/// Destructor
VelodyneComponent::~VelodyneComponent()
{
}

//////////////////////////////////////////////////////////////////////////
/// Called by the ComponentManager to start the component
void VelodyneComponent::startActivity()
{
    mStartOfScan = false;
    mEndOfScan = false;
    mBlockIndex = 0;
    mCurrentVelodyneData = 0;
    mPreviousAngle = 0;
    mVelodyneData = &(mVelodyneDataBuffer[mCurrentVelodyneData]);

    mRunning = true;
    initialize();
}

//////////////////////////////////////////////////////////////////////////
/// TODO: doc
void VelodyneComponent::run()
{ 
    initialize();
    exec(); // launch the exec loop, blocking until receiving exit() signal ...
    close();
}

//////////////////////////////////////////////////////////////////////////
/// TODO: doc
void VelodyneComponent::initialize()
{
    if (recording) {
        mVelodyneSphericDataFile.open(kDefaultOutputFilename, WriteMode, VELODYNE_RAW_SPHERIC_DATA, sizeof(VelodynePolarData));
    }

    initSocket();
    if (!connect(mSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()))) {
        LOG_ERROR("cannot connect SIGNAL(readyRead()) to SLOT(readPendingDatagrams())");
    }

    mShMem = new ShMem(kVelodyneSharedMemoryName.c_str(), sizeof(VelodynePolarData) );
    if (!mShMem) {
        LOG_FATAL("cannot create Velodyne shared memory");
        return;
    }
}

//////////////////////////////////////////////////////////////////////////
/// TODO: doc
void VelodyneComponent::initSocket()
{
    if (!(mHost.setAddress(kDefaultHostAddress.c_str()))) {
        LOG_FATAL("failed to set address");
    }
    mPort = kDefaultHostPort;
    mSocket = new QUdpSocket();
    if (!mSocket) {
        LOG_FATAL("cannot create socket");
        return;
    }
    if (!(mSocket->bind(mHost, mPort))) {
        LOG_ERROR("error when binding velodyne");
    }
}

//////////////////////////////////////////////////////////////////////////
/// Called by the ComponentManager to stop the component
void VelodyneComponent::stopActivity()
{
    mRunning = false;
    /*
    exit();
    if (!wait(2000)) {
        // wait termination during 2 seconds
        LOG_ERROR("thread blocking, terminate it");
        terminate();
    }
    */

    close();
}

//////////////////////////////////////////////////////////////////////////
/// TODO: doc
void VelodyneComponent::close()
{
    closeSocket();

    if (recording) {
        mVelodyneSphericDataFile.close();
    }

    if (mShMem) {
        delete mShMem;
        mShMem = NULL;
    }
}

//////////////////////////////////////////////////////////////////////////
/// TODO: doc
void VelodyneComponent::closeSocket()
{
    if (mSocket) {
        mSocket->close();
        delete mSocket;
        mSocket = NULL;
    }
}

//////////////////////////////////////////////////////////////////////////
/// Called by the ComponentManager to pass the XML parameters to the
/// component
ComponentBase::COMPONENT_CONFIGURATION VelodyneComponent::configureComponent(XmlComponentConfig config)
{
    QString recordingParam = param.getProperty(kPropertyRecording.c_str());
    if (!recordingParam.isNull()) {
        recording = recordingParam.toInt();
    }
    LOG_INFO("property " << kPropertyRecording << "=\"" << recording << "\"");
    /*
    if (!param.getProperty("velodyneIP").isNull()) {
        host_ = param.getProperty("velodyneIP");
    }
    if (!param.getProperty("velodynePort").isNull()) {
        port_ = param.getProperty("velodynePort").toInt();
    }
    */
    return ComponentBase::CONFIGURED_OK;
}

//////////////////////////////////////////////////////////////////////////
/// new data coming from Velodyne sensor
void VelodyneComponent::readPendingDatagrams() 
{
    // get a timestamp
    road_time_t t = road_time();
    if (mRunning) {
        while (mSocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(mSocket->pendingDatagramSize());
            mSocket->readDatagram(datagram.data(), datagram.size(), &mHost, &mPort);
            processTheDatagram(t, datagram);
            if (mEndOfScan) {
                // we have a complete scan of 360° so we can expose it the application
                exposeData();
                if (recording) {
                    record();
                }
                mEndOfScan = false;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////
/// TODO: doc
void VelodyneComponent::processTheDatagram(road_time_t time, QByteArray data)
{
    // envoi des paquets de 1206 octets 12 x 100 + 6
    // 12 fois :
    //    2 octets identifiant le bloc laser (haut ou bas)
    //    2 octets 0 35999, /100 => angle en degré
    //    96 octets : 32 laser beams, 2 octets distance 0.2 cm increment et 1 octet sur intensité
    // 6 octets : 0xhhhhDegC : température ou version firmware Vxxx

    const int packetSize = data.size();

    // check the size of the packet
    if (packetSize != VELODYNE_PACKET_SIZE) {
        LOG_WARN("strange packet size:"
                 << " EXPECTED = " << VELODYNE_PACKET_SIZE
                 << " ACTUAL = " << packetSize
                 );
        return;
    }

    // check angle to know if we have done a complete revolution
    //LOG_TRACE("1st angle of packet = " << firstAngle);
    LOG_TRACE(data.data());
    //LOG_TRACE(data.mid(2,2).toHex());

    unsigned short scanCount;
    int angle;
    if (!mStartOfScan) {
        for (int i = 0; i < VELODYNE_NB_BLOCKS_PER_PACKET; ++i) {
            {
                bool ok = false;
                // for each 100 data bytes, we extract the corresponding azimuth angle
                angle = qFromBigEndian(data.mid(VELODYNE_BLOCK_SIZE*i+2, 2).toHex().toUShort(&ok, 16));
                scanCount = qFromBigEndian(data.mid(1202, 2).toHex().toUShort(&ok, 16));
                LOG_TRACE("1:" << "start of scan = " << mStartOfScan << "\t"
                          << "angle = " << angle << "\t"
                          << "ok = " << ok << "\t"
                          << "size = " << packetSize
                          );
            }
            int delta = angle - mPreviousAngle;
            LOG_TRACE("angle = " << angle);
            LOG_TRACE("delta = " << delta);
            LOG_TRACE("#scans = " << scanCount);

            if (delta < 0) {
                // we are looking for a new revolution
                mPreviousAngle = angle;
                mStartOfScan=true;
                mVelodyneData->time = time;

                int sizeToCopy = packetSize - i*VELODYNE_BLOCK_SIZE - 6;
                memcpy(&(mVelodyneData->polarData[mBlockIndex]), data.mid(i*VELODYNE_BLOCK_SIZE, sizeToCopy).data(), sizeToCopy);

/* samuel                // Copy the time in each blocks.
                for (size_t j = 0; j < VELODYNE_NB_BLOCKS_PER_PACKET - i; ++j)
                  mVelodyneData->dataTime[mBlockIndex + j] = time;
//*/
                mBlockIndex += VELODYNE_NB_BLOCKS_PER_PACKET - i;
                LOG_TRACE("block index = " << mBlockIndex);
                LOG_TRACE("#scans = " << scanCount);
                break;
            } else {
                mPreviousAngle = angle;
            }
        }
    } else {
        // start of scan
        int lastBlockIndex = 0;
        for (int i = 0; i < VELODYNE_NB_BLOCKS_PER_PACKET; ++i) {
            {
                bool ok = false;
                angle = qFromBigEndian(data.mid(VELODYNE_BLOCK_SIZE*i+2, 2).toHex().toUShort(&ok, 16));
                scanCount = qFromBigEndian(data.mid(1202, 2).toHex().toUShort(NULL, 16));
                LOG_TRACE("2:" << "start of scan = " << mStartOfScan << "\t"
                          << "angle = " << angle << "\t"
                          << "ok = " << ok << "\t"
                          << "size = " << packetSize
                          );
            }
            int delta = angle - mPreviousAngle;
            LOG_TRACE("angle = " << angle);
            LOG_TRACE("delta = " << delta);
            LOG_TRACE("#scans = " << scanCount);

            if (delta < 0) {
                // we are looking for a new revolution
                LOG_TRACE("block index = " << mBlockIndex);
                LOG_TRACE("#scans = " << scanCount);
                //char c;
                //cin >> c;
                mEndOfScan = true;
                // we add +1 because we detect the new revolution in the upper block and we have to copy the lower block too!
                lastBlockIndex = i+1;
            }
            mPreviousAngle = angle;
        }
        if (!mEndOfScan) {
            // we don't reach a complete revolution so only copy bytes in the current buffer
            memcpy(&(mVelodyneData->polarData[mBlockIndex]), data.data(), VELODYNE_PACKET_SIZE - 6);
/*samuel            // Copy the time in each blocks.
            for (size_t j = 0; j < VELODYNE_NB_BLOCKS_PER_PACKET; ++j)
				mVelodyneData->dataTime[mBlockIndex + j] = time;
            //*/
			// Next offset.
            mBlockIndex += VELODYNE_NB_BLOCKS_PER_PACKET;
        } else {
            // we have a complete revolution, we copy the starting data to the current buffer, then switch buffer
            // and copy the rest of datagram in the new buffer.
            if (lastBlockIndex > 1) {
                int sizeToCopy =  packetSize - (VELODYNE_NB_BLOCKS_PER_PACKET - (lastBlockIndex - 1)) * VELODYNE_BLOCK_SIZE  - 6;
                memcpy(&(mVelodyneData->polarData[mBlockIndex]), data.left(sizeToCopy).data(), sizeToCopy);
/* samuel                // Copy the time in each blocks.
                for (size_t j = 0; j < VELODYNE_NB_BLOCKS_PER_PACKET - (lastBlockIndex - 1); ++j)
                  mVelodyneData->dataTime[mBlockIndex + j] = time;
            //*/
			}
			
            mVelodyneData->range = mBlockIndex+(lastBlockIndex - 1);
            LOG_DEBUG("range = " << mVelodyneData->range);
            mVelodyneData->timerange = time - mVelodyneData->time;
            mBlockIndex = 0;
            switchBuffer(); // switch the circular buffer of data. Previous one will be exported later.

            // copy the rest of incoming data in the new buffer
            mVelodyneData->time = time;
            int sizeToCopy =  packetSize - (lastBlockIndex - 1)*VELODYNE_BLOCK_SIZE - 6;
            memcpy(&(mVelodyneData->polarData[mBlockIndex]), data.mid((lastBlockIndex-1) * VELODYNE_BLOCK_SIZE, sizeToCopy).data(), sizeToCopy);
 /* samuel           // Copy the time in each blocks.
            for (size_t j = 0; j < lastBlockIndex - 1; ++j)
              mVelodyneData->dataTime[mBlockIndex + j] = time;
 //*/
            mBlockIndex += sizeToCopy / VELODYNE_BLOCK_SIZE;
        }
    }
}

/// TODO: doc
void VelodyneComponent::record()
{
    LOG_TRACE("record()");

    //qDebug() << fullBuffer_ << velodyneData_<< &(velodyneDataBuffer_[0]) << &(velodyneDataBuffer_[1]);
    /*LOG_DEBUG(mFullBuffer->time);
    LOG_DEBUG(mFullBuffer->timerange);
    LOG_DEBUG((intptr_t)mFullBuffer);
    LOG_DEBUG((intptr_t)mVelodyneData);
    LOG_DEBUG((intptr_t) &(mVelodyneDataBuffer[0]));
    LOG_DEBUG((intptr_t) &(mVelodyneDataBuffer[1]));*/
    if (recording) {
        size_t dataSize = sizeof(VelodynePolarData);
        mVelodyneSphericDataFile.writeRecord(mFullBuffer->time, mFullBuffer->timerange, (const char *) mFullBuffer, dataSize);
    }

    LOG_INFO("record succeed");
}

/// TODO: doc
void VelodyneComponent::switchBuffer()
{
    mFullBuffer = mVelodyneData;
	/*
    LOG_DEBUG("full buffer = " << mFullBuffer);
    LOG_DEBUG("data = " << mVelodyneData);
    LOG_DEBUG("current data = " << mVelodyneData);*/
    mCurrentVelodyneData = (mCurrentVelodyneData+1)%2; // a hack to switch between 0 & 1
    //LOG_DEBUG("current data = " << mVelodyneData);
    // switch circular buffer
    mVelodyneData = &(mVelodyneDataBuffer[mCurrentVelodyneData]);
}

/// TODO: doc
void VelodyneComponent::exposeData()
{
    mShMem->write(mFullBuffer, sizeof(VelodynePolarData) );
}
