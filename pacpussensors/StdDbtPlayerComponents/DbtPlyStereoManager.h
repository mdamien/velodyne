/// purpose:    Dbite Player Stereo Manager header file
///
/// created @date 2008/01/19 - 21:23
/// @author Sergio Rodriguez
/// @version $Id: $

#ifndef DBTPLYSTEREOMANAGER_H
#define DBTPLYSTEREOMANAGER_H

#include "StdDbtPlayerComponentsConfig.h"
#include "kernel/ComponentBase.h"
#include "kernel/ComponentFactory.h"
#include "DbitePlayer/DbtPlyFileManager.h"
#include "PacpusTools/ShMem.h"

namespace pacpus {

class STDDBTPLAYERCOMPONENTS_API DbtPlyStereoManager
        : public DbtPlyFileManager
{
    Q_OBJECT

public:
    DbtPlyStereoManager(QString name);
    ~DbtPlyStereoManager();

    virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);
    void displayUI();

protected:
    void processData(road_time_t t, road_timerange_t tr, void * buffer);
    virtual void startActivity();
    virtual void stopActivity();

private:
    ShMem * tobeRead; //Buffer flag

    ShMem * left0;      //left image of Buffer 0
    ShMem * right0;     //right image of Buffer 0
    ShMem * timeStamp0; //Timestamp of stereo images in Buffer 0
    ShMem * timeRange0; //Uncertainty of timeStamp Buffer 0

    ShMem * left1;      //left image of Buffer 1
    ShMem * right1;     //right image of Buffer 1
    ShMem * timeStamp1; //Timestamp of stereo images in Buffer 1
    ShMem * timeRange1; //Uncertainty of timeStamp Buffer 1
    //#endif

    bool firstTime;
    bool offset;
    bool leftStatus;
    bool rightStatus;
    //image paramaters
    int width_;
    int height_;
    int depth_;

    road_time_t tic_;
    void tic();
    void toc(char * text);
};

} // namespace pacpus

#endif // DBTPLYSTEREOMANAGER_H
