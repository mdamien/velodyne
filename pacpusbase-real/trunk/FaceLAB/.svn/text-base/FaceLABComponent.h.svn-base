/*********************************************************************
//  created:    2011/05/18
//  filename:   FaceLabComponent.h
//
//  author:     Anthony Chaikha Douaihy
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
//  version:    $Id: $
//
//  purpose:    RAMIAC
*********************************************************************/

#ifndef _FACELABCOMPONENT_H_
#define _FACELABCOMPONENT_H_

#include <qlabel.h>
#include <qpainter.h>
#include <qstring.h>
#include <qudpsocket.h>
#include <string>

#include "kernel/ComponentBase.h"
#include "kernel/ComponentFactory.h"
#include "kernel/DbiteFile.h"
#include "PacpusTools/ShMem.h"
#include "structure/structureFaceLAB.h"

// Export macro for FaceLAB DLL for Windows only
#ifdef WIN32
#   ifdef FACELAB_EXPORTS
        // make DLL
#       define FACELAB_API __declspec(dllexport)
#   else
        // use DLL
#       define FACELAB_API __declspec(dllimport)
#   endif
#else
    // On other platforms, simply ignore this 
#   define FACELAB_API /* nothing */
#endif

namespace pacpus {

class FACELAB_API FaceLABComponent
    : public QObject
    , public ComponentBase
{
	Q_OBJECT

public:
	FaceLABComponent(QString name);
	~FaceLABComponent();
	void initSocket(quint16 port);

protected:
	virtual ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);
	virtual void startActivity();
	virtual void stopActivity();
	void run();
	void processTheDatagram(char* datagram,int recvMsgSize, QHostAddress sender, quint16 senderPort);
	std::string IntToString(int intValue);
	int int2bin(int x);
	float puissance(int nb,int exp);
	int bin2dec(std::string w, std::string x, std::string y, std::string z);
	float bin2float(std::string w,std::string x, std::string y, std::string z);
	int number(int code);
	float readFloat(int nb1, char echoBuffer[]);
	int readInt(int nb1, char echoBuffer[]);

private:
	FaceLABDatas faceLABDatas_;
	quint16 port_;
	pacpus::DbiteFile dbtFile_;
	QUdpSocket* udpSocket_;
	bool recording_;
	ShMem* shMemFaceLAB_;
	QWidget* w_;
	QLabel* lab_;

private Q_SLOTS:
	void readPendingDatagrams();
};

} // namespace pacpus

#endif /* _FaceLABCOMPONENT_H_ */
