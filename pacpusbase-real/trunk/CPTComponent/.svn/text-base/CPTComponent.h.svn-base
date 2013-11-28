/*********************************************************************
//  created:    2011/06/28 - 18:18
//  filename:   cptComponent.h
//
//  author:     Sergio Rodriguez
//
//  version:    $Id: $
//
//  purpose:    Acquire SPAN CPT data
//
*********************************************************************/

#ifndef CPTCOMPONENT_H
#define CPTCOMPONENT_H

#include <fstream>
#include <qobject.h>
#include <string>

#include "extlib/NMEA0183/nmea0183.h"
#include "kernel/ComponentBase.h"
#include "kernel/DbiteFile.h"
#include "kernel/pacpus.h"
#include "structure/structure_gps.h"

#ifdef WIN32
#   include "../driver/win32SerialPort.h"
#else
#   include "../driver/PosixSerialPort.h"
#endif

// Export macro for CPTComponent DLL for Windows only
#ifdef WIN32
#   ifdef CPTCOMPONENT_EXPORTS
        // make DLL
#       define CPTCOMPONENT_API __declspec(dllexport)
#   else
        // use DLL
#       define CPTCOMPONENT_API __declspec(dllimport)
#   endif
#else
    // On other platforms, simply ignore this 
#   define CPTCOMPONENT_API 
#endif

namespace pacpus {

class ShMem;

struct CPTCOMPONENT_API Stream8Position
{
    int32_t dataPos;
    int32_t length;
};

#define UNKNOWN_NMEA_FRAME -1

/// The definition of the CPTComponent class
class CPTCOMPONENT_API CPTComponent
        : public QObject
        , public ComponentBase
{
    Q_OBJECT

public:
    CPTComponent(QString name);
    ~CPTComponent();

    virtual void stopActivity(); /*!< to stop the processing thread */
    virtual void startActivity(); /*!< to start the processing thread */
    virtual ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

    void setPortCOM(const char * port);

public slots:
    void processing(int v); /*!< to unlock the processing thread */

private:
    char * mAllFramesBuffer;
#ifdef WIN32
    Win32SerialPort * serialPort;
#else
    PosixSerialPort * serialPort;
#endif

    road_time_t currentRoadtime_;
    road_timerange_t currentTimerange_;
    int currentDataFrameLength_;

    bool mVerbose;
    bool enuRef_;
    double LAT_REF;
    double LON_REF;
    double HE_REF;

    QString portName;

    //ShMems
    ShMem * mShMem;

    //Dbt files
    pacpus::DbiteFile raws8hdFile;
    std::ofstream dataFile_;

    pacpus::DbiteFile bestgpsposaFile_;
    pacpus::DbiteFile rawimuFile_;
    pacpus::DbiteFile inspvaFile_;
    pacpus::DbiteFile inscovFile_;

    Stream8Position s8Data_;

    //Decoding
    QString currentDataFrame;
    road_time_t currentRoadtime;
    road_timerange_t currentTimerange;

    QString frameToDecode;
    road_time_t timeOfFrameToDecode;
    road_timerange_t timerangeOfFrameToDecode;

    QString restOfFrame;

    bool newFrameToDecode;
    bool startOfFrame;
    int  sofIdx_;
    bool endOfFrame;
    int type;
    int  eofIdx_;

    NMEA0183 nmea0183_;

    trame_gga_dbl ggaFrame_;
    trame_gsa gsaFrame_;
    trame_gst gstFrame_;
    trame_gsv gsvFrame_;
    trame_hdt hdtFrame_;
    trame_rmc rmcFrame_;
    trame_rot rotFrame_;
    trame_vtg vtgFrame_;
    trame_zda zdaFrame_;

    trame_bestgpsposa bestgpsposaFrame_;
    trame_rawimusa    rawimuFrame_;
    trame_inspvaa     inspvaFrame_;
    trame_inscov      inscovFrame_;

    int analyzeFrame(void);
    int frameType(const QString);
    int decodeFrame(int);

    int parseCPTbestgpsposa(QString);
    int parseCPTrawimusa(QString);
    int parseCPTinspvaa(QString);
    int parseCPTinscov(QString);

    void initBuffer( TimestampedBestgpsposaFrame*,
                     TimestampedRawimusaFrame*,
                     TimestampedInspvaaFrame*,
                     TimestampedInscovFrame*);
};

} // namespace pacpus

#endif // CPTCOMPONENT_H
