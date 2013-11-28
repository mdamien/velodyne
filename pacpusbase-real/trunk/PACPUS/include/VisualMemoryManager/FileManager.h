/*********************************************************************
//  created:    2006/11/20 - 10:31
//  filename:   FileManager.h
//
//  author:     Pierre-Michel Bonnifait Copyright Heudiasyc UMR UTC/CNRS 6599
//
//  version:    $Id: FileManager.h 216 2007-04-03 13:33:56Z gdherbom $
//
//  purpose:    
*********************************************************************/

#ifndef _FILEMANAGER_H_
#define _FILEMANAGER_H_

# include "../../include/VisualMemoryManager/struct.h"

class FileManager
{
public:
	FileManager();
	~FileManager();
	void						createDir();
	void						recordImage(QImage* img, QMutex* imgMutex);
	void						nameImage();
	QImage*						getNextImage();
	void						setMatchedPosition(struct s_MatchedPosition* );
	char*						myItoa(long );
	QString						getImageName();

private:
	QDir*						dir_;
	int							numberOfImages_;
	long						dist_;
	int							imageIndex_;
	QString						currentDir_;
	QString						currentImage_;
	struct s_MatchedPosition*	myMatchedPosition_;
	QImage						nextImage_;
};

#endif /* !_FILEMANAGER_H_ */
