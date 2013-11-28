
#ifndef _DBTPLYTCPMANAGER_H_
#define _DBTPLYTCPMANAGER_H_

#include <QApplication>
#include <QObject>
#include <QLabel>
#include <QDialog>
#include <QTextBrowser>

#include "cvisServer.h"
#include "kernel/ComponentBase.h"
#include "kernel/ComponentFactory.h"


class SensorTcpServer: public QWidget, public ComponentBase {

	Q_OBJECT
	public:
		SensorTcpServer(QString name);
		~SensorTcpServer();
		cvisServer *cs;
		
	protected:
		void startActivity();
		void stopActivity();
		COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

		
	private:
		
		QWidget *w;
		QLabel* label;
		QTextBrowser* text;

		
	protected slots:
		void endSending(uint t);
		void conEstab(int t);
		void setProp(QString t);
		void propSet(uint t);
		void propNotSet(uint t);
		void attemptToCon();
		
};
 
#endif