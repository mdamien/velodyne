/*********************************************************************
// created:    2006/04/24 - 10:13
// filename:   MapView.h
//
// author:     Gerald Dherbomez
// 
// version:    $Id: MapView.h 339 2007-12-17 17:40:47Z gdherbom $
// 
// purpose:    The class MapView is the frame where the map will be 
//             shown. 
*********************************************************************/

#ifndef _MAPVIEW_H_
#define _MAPVIEW_H_


#include <QFrame>
#include <QMutex>
#include <QTimer>
#include <QPopMenu>

#include "MapEngine.h"
#include "MapData.h"


#include "BeNomad/BTypes.h"
#include "BeNomad/CBDynamicPOI.h"

// Forward Declarations
class CBView;
class CBFleetMgr; 


typedef struct  {
  CBDynamicPOI* poi; 
  VEHICLE_POSITION position; 
} POI_OBJECT;



class MapView : public QFrame
{
  Q_OBJECT
    
public:
	MapView(QWidget * parent);
	~MapView();
  // Accessors
  inline  CBView * getMapView(void)       { return view_;       }
  inline  MapEngine * getMapEngine(void)  { return mapEngine_;  }
  inline  CBFleetMgr * getFleetManager(void) { return fleetMgr_;}
  
  POI_OBJECT vehiclePosition; 
  POI_OBJECT gpsPosition; 
  POI_OBJECT pose; 
  POI_OBJECT mapMatchedPose; 

  
public slots:
  bool initialize(const char * graphicChartFileName);
  void contextMenuActivation(int id); 
  void zoom(QRect rect); 
  void updatePosition( CBDynamicPOI* poi, int X, int Y); 
  void displayObject(int X, int Y, int xmlClass); 
  void displayEllipse(int X, int Y, float width, float height, float angle); 

private slots:
  void contextMenuTimerDone(); 

protected:
	CBView * view_;
  MapEngine * mapEngine_; 
  CBFleetMgr * fleetMgr_; 

  
  void mousePressEvent(QMouseEvent * e);  
  void mouseReleaseEvent(QMouseEvent * e); 
  void mouseMoveEvent(QMouseEvent * e); 
  void mouseDoubleClickEvent(QMouseEvent * e);
  void resizeEvent(QResizeEvent * e); 
  void paintEvent(QPaintEvent * e); 
  
private:
  enum ENAV_MODE { 
    NONE = 0, 
    MOVING = 1, 
    ZOOMING = 2,
    UNZOOMING = 3,
    SPECIAL = 4  };

  enum CONTEXT_MENU { 
    CONTEXT_ZOOM = 1, 
    CONTEXT_INITIAL_ZOOM = 2,  
    CONTEXT_SELECT_ROADS = 3   };
  
  ENAV_MODE   navMode_;
  TB_2D_POINT lastPoint_; 
  QRect selectedRect_; 
  bool rightButtonDown_, leftButtonDown_;
  bool rightDoubleClick_; 
  QTimer contextMenuTimer_; 
  QPopupMenu *contextMenu_;

  void reset(); 
  void create_TB_2D_RECT(TB_2D_RECT *rect, int x1, int y1, int x2, int y2);

  void redraw(); 
  void refresh(); 
  void displaySpecificObjects(); 


};



#endif
