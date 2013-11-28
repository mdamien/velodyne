#ifndef __IMAGEPROJECTION__
#define __IMAGEPROJECTION__

#include "WrapperLOVe2/LOVe.h"
#include "matrix.h"
#include "structure/structure_telemetre.H"
#include "viewer/AlascaViewer3D.h"

class ImageProjection
{
public:
	ImageProjection();
	~ImageProjection();

	void ProjectionTrame(QImage * , ScanAlascaData * , matrice , matrice , matrice );
	void ProjectionPistes(QImage * , lprusl* , int , matrice , matrice , matrice , zrusl* );
	void ProjectionObjets(QImage * , lorusl* , int , matrice , matrice , matrice , zrusl* );

private:
	void DrawPoint (QImage* , int , int , int );
	void DrawLine  (QImage* , matrice , matrice , matrice , matrice , matrice );
  void DrawTarget(QImage* , double , double , double , unsigned int , unsigned int , matrice , matrice , matrice );
	void TargetProjection(QImage* , prusl* , matrice , matrice , matrice );
	void ObjectProjection(QImage* , orusl* , matrice , matrice , matrice );
};

#endif