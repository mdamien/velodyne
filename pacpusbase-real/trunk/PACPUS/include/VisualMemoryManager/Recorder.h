/*********************************************************************
//  created:    2006/11/20 - 10:27
//  filename:   Recorder.h
//
//  author:     Pierre-Michel Bonnifait Copyright Heudiasyc UMR UTC/CNRS 6599
//
//  version:    $Id: Recorder.h 216 2007-04-03 13:33:56Z gdherbom $
//
//  purpose:    
*********************************************************************/

#ifndef _RECORDER_H_
#define _RECORDER_H_

# include "../../include/VisualMemoryManager/struct.h"

class Recorder : public QObject, public QThread
{
  Q_OBJECT

public:
	Recorder();
	~Recorder();
	void						run();
	void						init();
	void						stop();

signals:
	void						keyImage(QImage* image);
	void						setWay(int w);
	void						setDist(double d);
	void						setID(long id);
	void						setState(int s);

public slots:
	void						getImage(QImage* image);
	void						startIt();
	void						stopIt();
	
private:
	class ImageViewer*			recordedImage_;
	class ImageViewer*			realImage_;
	class Camera1394*			myCamera_;
	class RequestEmetor*		myRequestEmetor_;
	class FileManager*			myFileManager_;
	bool						active_;
	struct s_MatchedPosition*	myMatchedPosition_;
	long						dist_;
	QMutex						imageMutex_;
	QImage*						curImage_;
	class VisualManagerFrame*	myframe_;
	
private:
	
};

#endif /* !_RECORDER_H_ */