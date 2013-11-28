/*********************************************************************
//  created:    2009/11/10 - 15:34
//  filename:   StereoInterface.h
//
//  author:     Sergio Rodriguez
//              Heudiasyc UTC/CNRS UMR6599 Copyright
// 
//  version:    $Id: $
//
//  purpose:    
//              
*********************************************************************/


#ifndef __STEREOINTERFACE_H__
#define __STEREOINTERFACE_H__


#include <QThread>

#include "kernel/ComponentBase.h"
#include "pacpusTools/ShMem.h"
#include "kernel/road_time.h"

#include <QImageWriter>
#include "ImageViewer.h"

class StereoInterface : public QThread, public ComponentBase
{
	Q_OBJECT

public:
	StereoInterface(QString name);  
	~StereoInterface();

	void startActivity();
	void stopActivity();
	ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

	unsigned int getPhotos2Acquire_(void){return photos2Acquire_;}
	void		 setFileCount(int value){fileCount_=value;}
	void		 startGetButton_(void)	{getButton_=true;}

protected:
	void run();

signals:
	void leftImageEmission(QImage*);
	void rightImageEmission(QImage*);

private:

	//BEGIN log files variables
	bool			recording_;
	QString			filePath_;
	QString			subFolderName_;
	FILE*			logFile_;
	bool			getButton_;
	int				fileCount_;
	unsigned int	folderCount_;
	unsigned int	photos2Acquire_;

	QImageWriter    imageWriter_;
	//END log files variables
	
	//shared memory
	ShMem*				tobeReadStereo_;
	ShMem*				stereoBuffer_;
	void*				offsetStereo_;

	//Stereo vision control and data variables 
	void*				leftPtrIm_;
	void*				rightPtrIm_;

	QImage*				leftImage_;
	QImage*				rightImage_;

	ImageViewer*		leftImageViewer_;
	QMutex*				leftMutex_;

	ImageViewer*		rightImageViewer_;
	QMutex*				rightMutex_;
	
	QString				imageFormat_;
	unsigned int		depth_;			// number of channels
	int					imageWidth_;
	int					imageHeight_;
	
	void processingStereo_(void);

	void YtoRGB32(unsigned char *, const unsigned char *, int, int);
};
#endif // __SENSORINTERFACE_H__