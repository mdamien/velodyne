/*********************************************************************
// created:    2007/04/12 - 16:30

//
// author:     Elie Al Alam & Gerald Dherbomez
// 
// version:    $Id: $
//
// purpose:    Dbite Player Image Manager header file
*********************************************************************/

#ifndef DBTPLYIMAGEMANAGER_H
#define DBTPLYIMAGEMANAGER_H

#include <qobject.h>

#include "StdDbtPlayerComponentsConfig.h"
#include "DbitePlayer/DbtPlyFileManager.h"

class ImageViewer;

class QImage;
class QMutex;

namespace pacpus {
    
class ShMem;

///
///     shmem=STRING (name of output shared memory) default=IMAGE
class STDDBTPLAYERCOMPONENTS_API DbtPlyImageManager
        : public DbtPlyFileManager
{
    Q_OBJECT

public:
    DbtPlyImageManager(QString name);
    ~DbtPlyImageManager();

    virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

    void displayUI();

private:
    QString mShMemName;
    QString imageFile_;
    QImage * im_;

    ImageViewer * imviewer_;

protected:
    void processData(road_time_t, road_timerange_t, void * dataBuffer);
    virtual void startActivity();
    virtual void stopActivity();

Q_SIGNALS:
    void displayIm(QImage *);

private:
    QMutex * imageMutex_;
    ShMem * shMem_;
    bool firstTime;

    road_time_t tic_;
    void tic();
    void toc(char * text);

    void YtoRGB32(unsigned char * dest, unsigned char * src);
};

} // namespace pacpus

#endif // DBTPLYIMAGEMANAGER_H
