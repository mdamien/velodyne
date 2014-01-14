/*********************************************************************
// created:    2007/04/12 - 16:30
//
// author:     Elie Al Alam & Gerald Dherbomez
// 
// version:    $Id: DbtPlyImageManager.cpp 1239 2012-11-28 16:30:00Z kurdejma $
//
// purpose:    Dbite Player Image Manager implementation
*********************************************************************/

#include "DbtPlyImageManager.h"

#include "ImageViewer.h"

#include "kernel/ComponentFactory.h"
#include "kernel/ComponentManager.h"
#include "kernel/DbiteFileTypes.h"
#include "kernel/Log.h"
#include "PacpusTools/ShMem.h"

#include <iostream>
#include <QImage>
#include <QMutex>

namespace pacpus {

using namespace std;

DECLARE_STATIC_LOGGER("pacpus.base.DbtPlyImageManager");

static const string kDefaultMemoryName = "IMAGE";

/// Construction de la fabrique de composant DbtPlyImageManager
static ComponentFactory<DbtPlyImageManager> sFactory("DbtPlyImageManager");

/// Constructor
DbtPlyImageManager::DbtPlyImageManager(QString name)
    : DbtPlyFileManager (name)
    , im_(NULL)
    , shMem_(NULL)
    , imageMutex_(new QMutex())
    , firstTime(true)
{
}

/// Destructor
DbtPlyImageManager::~DbtPlyImageManager()
{ 
    // #if WIN32
    delete imageMutex_;
    // #endif
    if (shMem_) {
        delete shMem_;
        shMem_ = NULL;
    }
}

/// TODO: doc
void DbtPlyImageManager::processData(road_time_t /*t*/, road_timerange_t /*tr*/, void * buf)
{
    if (!buf) {
        LOG_WARN("no data to process: empty data buffer");
        return;
    }

    // look at the dbt index in file manager and get the identifier of dbt structure
    hdfile_header_t::DataTypeT id = dbt_[dbtIndex_].pfile->getType();

    switch (id) {
    case STEREO_LEFT_IMAGE:
    case STEREO_RIGHT_IMAGE:
    //{
    //    QMutexLocker mutexLocker(imageMutex_);
    //    Q_UNUSED(mutexLocker);
    //    if (firstTime) {
    //        im_ = new QImage(320, 240, QImage::Format_RGB32);
    //        if (!im_) {
    //            LOG_ERROR("invalid image");
    //        }
    //        shMem_ = new ShMem(kDefaultMemoryName.c_str(), im_->numBytes());
    //        firstTime = false;
    //    }
    //    // convert image to 32 bits for the display
    //    YtoRGB32(im_->bits(), (unsigned char *)buf);
    //    shMem_->write(im_->bits(), im_->numBytes());
    //}
    //    break;

    case FILE_JPEG:
        imageFile_ = mDbtDataPath + (char *)buf;
        LOG_TRACE("image path = " << imageFile_);
        if (mVerbose) {
            cout << "[IMAGE]:\t"
                 << imageFile_.toStdString() << endl
                    ;
        }

    {
        QMutexLocker mutexLocker(imageMutex_);
        Q_UNUSED(mutexLocker);
        if (!im_) {
            LOG_TRACE("allocating image");
            im_ = new QImage();
            if (!im_) {
                LOG_ERROR("cannot allocate image");
            }
        }
        static int shmemSize;
        bool imageLoaded = im_->load(imageFile_);
        if (!imageLoaded) {
            LOG_WARN("cannot load image file '" << imageFile_ << "'");
            return;
        }
        LOG_TRACE("image loaded");
        if (firstTime) {
            // send image in shared memory
            shmemSize = im_->byteCount();
            LOG_TRACE("'" << mShMemName << "'" << " memory size = " << shmemSize);
            shMem_ = new ShMem(mShMemName.toStdString().c_str(), shmemSize);
            firstTime = false;
        }
        shMem_->write(im_->bits(), shmemSize);
    }
        break;

    default:
        break;
    }

    Q_EMIT displayIm(im_);
}

ComponentBase::COMPONENT_CONFIGURATION DbtPlyImageManager::configureComponent(XmlComponentConfig config)
{    
    mShMemName = kDefaultMemoryName.c_str();
    if (param.getProperty("shmem") != QString::null) {
        mShMemName = param.getProperty("shmem");
    } 
    return DbtPlyFileManager::configureComponent(config);
}

void DbtPlyImageManager::startActivity()
{
    DbtPlyFileManager::startActivity();
}

void DbtPlyImageManager::stopActivity()
{
    delete im_; im_ = NULL;
    DbtPlyFileManager::stopActivity();
}

////////////////////////////////////////////////////////////////////////////////
/// Pour l'affichage de l'image
void DbtPlyImageManager::displayUI()
{
    imviewer_ = new ImageViewer;
    imviewer_->setMutex(imageMutex_);
    imviewer_->show();
    imviewer_->setWindowTitle(componentName);
    connect(this, SIGNAL(displayIm(QImage*)), imviewer_, SLOT(display(QImage*)));
}

////////////////////////////////////////////////////////////////////////////////
/// Convert the image from Y to RGB32
/// The image is stored using a 32-bit RGB format (0xffRRGGBB)
void DbtPlyImageManager::YtoRGB32(unsigned char * dest, unsigned char * src)
{
    unsigned char *srcptr, *srcend, *destptr;

    srcptr = src;
    srcend = srcptr + (320 * 240);
    destptr = dest;

    // single-stage idiotproofing
    if (src == NULL || dest == NULL)
        return;

    // just Y's (monochrome)

    // unroll it to 4 per cycle

    while(srcptr < srcend) {
        *destptr++ = *srcptr;
        *destptr++ = *srcptr;
        *destptr++ = *srcptr;
        destptr++;//A
        srcptr++;

        *destptr++ = *srcptr;
        *destptr++ = *srcptr;
        *destptr++ = *srcptr;
        destptr++;//A
        srcptr++;

        *destptr++ = *srcptr;
        *destptr++ = *srcptr;
        *destptr++ = *srcptr;
        destptr++;//A
        srcptr++;

        *destptr++ = *srcptr;
        *destptr++ = *srcptr;
        *destptr++ = *srcptr;
        destptr++;//A
        srcptr++;
    }
}

void DbtPlyImageManager::tic()
{
    tic_ = road_time();
}

void DbtPlyImageManager::toc(char * text)
{
    cout << "duration = " << (int)(road_time() - tic_) << "\t"
         << text << "\n"
            ;
}

} // namespace pacpus
