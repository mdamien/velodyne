#ifndef __IMAGEPROJECTION__
#define __IMAGEPROJECTION__


#include "structure/structure_telemetre.H"
#include "AlascaDataModule.h"

//=============================================================================
//OpenCV Includes
//=============================================================================
#include "cv.h"
#include "cvaux.h"
#include "cxcore.h"

class ImageProjection
{
public:
	ImageProjection();
	~ImageProjection();

	void ProjectionTrame(QImage * , ScanAlascaData * , CvMat*, CvMat*, CvMat*);
	void ProjectLidarObjects(QImage*, lidarObjectList*, int, CvMat*, CvMat*, CvMat*);

private:

	CvMat* array3x1; 
	CvMat* pt;

	CvMat* bboxPoint1;
	CvMat* bboxPoint2;

	CvMat* tmpPoint1;
	CvMat* tmpPoint2;

	CvMat* imLine1;
	CvMat* imLine2;

	CvMat*  road_line_r1;
	CvMat*  road_line_r2;

	CvMat*  road_line_l1;
	CvMat*  road_line_l2;

	QColor*		hot;			
	QColor*		warm;		
	QColor*		cool;		
	QColor*		cold;		
	QColor*		ice;			
	QColor*		black;		
	QColor*		object_color;


	void DrawPoint (QImage* , int , int , int );
	void DrawLine  (QImage* , CvMat*, CvMat*, CvMat* , CvMat*, CvMat* );
    void DrawTarget(QImage* , double , double , double , unsigned int , unsigned int , CvMat*, CvMat*, CvMat*);
};

#endif