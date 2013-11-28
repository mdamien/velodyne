/*********************************************************************
//  created:    2011/05/18
//  filename:   FaceLabComponent.cpp
//
//  author:     Anthony Chaikha Douaihy
//              Copyright Heudiasyc UMR UTC/CNRS 6599
//
//  version:    $Id: $
//
//  purpose:    RAMIAC
*********************************************************************/

#include "FaceLABComponent.h"

#include <cmath>

#include "kernel/DbiteFileTypes.h"

using namespace pacpus;

float x, y;

//////////////////////////////////////////////////////////////////////////
// Construction de la fabrique de composant FaceLABComponent
//////////////////////////////////////////////////////////////////////////
static ComponentFactory<FaceLABComponent> * factory = new ComponentFactory<FaceLABComponent>("FaceLAB");

//////////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////////
FaceLABComponent::FaceLABComponent(QString name): ComponentBase(name)
{
	w_ = new QWidget();
	w_->setWindowTitle("FaceLAB");
	w_->show();
	w_->setFixedSize (800,600);
	lab_ = new QLabel("o",w_);
	lab_->setFixedSize (20,20);
}

//////////////////////////////////////////////////////////////////////////
// Destructor
//////////////////////////////////////////////////////////////////////////
FaceLABComponent::~FaceLABComponent()
{
}

//////////////////////////////////////////////////////////////////////////
// Configure the component
//////////////////////////////////////////////////////////////////////////
ComponentBase::COMPONENT_CONFIGURATION FaceLABComponent::configureComponent(XmlComponentConfig config)
{
  port_ = config.getProperty("port").toInt();
  recording_ = (config.getProperty("recording") == "true" ? true : false);
  
  return ComponentBase::CONFIGURED_OK;
}

//////////////////////////////////////////////////////////////////////////
// Start the component
//////////////////////////////////////////////////////////////////////////
void FaceLABComponent::startActivity()
{
	if (recording_) {
		// create the DBT file
        dbtFile_.open("FaceLAB.dbt", WriteMode, FILE_DBT_UNKNOWN, sizeof(FaceLABDatas));
	}

	// create the shared memory
	shMemFaceLAB_ = new ShMem("FaceLAB", sizeof(FaceLABDatas));

	udpSocket_ = new QUdpSocket(this);
	udpSocket_->bind(QHostAddress::Any, port_, QUdpSocket::ShareAddress);

	connect(udpSocket_, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));

	printf ("Listening for FaceLAB on port %d\n",port_);
}

//////////////////////////////////////////////////////////////////////////
// Stop the component 
//////////////////////////////////////////////////////////////////////////
void FaceLABComponent::stopActivity()
{
	if (recording_) {
        dbtFile_.close();
	}

	delete shMemFaceLAB_;
}

void FaceLABComponent::readPendingDatagrams()
 {
     while (udpSocket_->hasPendingDatagrams()) {
		QByteArray datagram;
		datagram.resize(udpSocket_->pendingDatagramSize());
		QHostAddress sender;
		quint16 senderPort;

		// acquire data
		faceLABDatas_.time = road_time();

		udpSocket_->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);

		processTheDatagram(datagram.data(), datagram.size(), sender, senderPort);

		shMemFaceLAB_->write(&faceLABDatas_, sizeof(FaceLABDatas)); 

		// record data in DBT file
		if (recording_) {
            size_t dataSize = sizeof(FaceLABDatas);
            dbtFile_.writeRecord(faceLABDatas_.time, 0, reinterpret_cast<const char *>(&faceLABDatas_), dataSize);
		}
     }
 }

void FaceLABComponent::processTheDatagram(char* echoBuffer, int recvMsgSize , QHostAddress sourceAddress, quint16 /*sourcePort*/)
 {
	//printf("Received packet from %s : %d \n",sourceAddress.toString().toStdString().c_str(),sourcePort);
	echoBuffer[recvMsgSize]='\0';

	//Reading Frame Number
	faceLABDatas_.frameNumber = readInt(4,echoBuffer);

	//Reading GMT_S
	faceLABDatas_.gmt_s = readInt(21,echoBuffer);

	//Reading GMY_mS
	short yy1 =echoBuffer[25];
	short zz1 =echoBuffer[26];
	int ya=int2bin(yy1);
	int za=int2bin(zz1);
	std::string aw="0";
	std::string ax="0";
	std::string ay="0";
	std::string az="0";
	ay=IntToString(ya);
	az=IntToString(za);
	faceLABDatas_.gmt_ms=bin2dec(aw,ax,ay,az);

	//Reading Delay
	faceLABDatas_.delay=readFloat(27,echoBuffer);

	//Reading Annotation_ID
	faceLABDatas_.annotation_ID = readInt(31,echoBuffer);

	//Reading HPOS_FILT_X
	faceLABDatas_.hpos_filtx = readFloat(41,echoBuffer);

	//Reading HPOS_FILT_Y
	faceLABDatas_.hpos_filty = readFloat(45,echoBuffer);

	//Reading HPOS_FILT_Z
	faceLABDatas_.hpos_filtz = readFloat(49,echoBuffer);

	//Reading HROT_FILT_X
	faceLABDatas_.hrot_filtx = readFloat(53,echoBuffer);

	//Reading HROT_FILT_Y
	faceLABDatas_.hrot_filty = readFloat(57,echoBuffer);

	//Reading HROT_FILT_Z
	faceLABDatas_.hrot_filtz = readFloat(61,echoBuffer);

	//Reading HPOS_CONF
	faceLABDatas_.hpos_conf = readFloat(65,echoBuffer);

	//Reading H_EYEBALL_R_X
	faceLABDatas_.h_eyeball_r_x = readFloat(70,echoBuffer);

	//Reading H_EYEBALL_R_Y
	faceLABDatas_.h_eyeball_r_y = readFloat(74,echoBuffer);

	//Reading H_EYEBALL_R_Z
	faceLABDatas_.h_eyeball_r_z = readFloat(78,echoBuffer);

	//Reading H_EYEBALL_L_X
	faceLABDatas_.h_eyeball_l_x = readFloat(82,echoBuffer);

	//Reading H_EYEBALL_L_Y
	faceLABDatas_.h_eyeball_l_y = readFloat(86,echoBuffer);

	//Reading H_EYEBALL_L_Z
	faceLABDatas_.h_eyeball_l_z = readFloat(90,echoBuffer);

	//Reading RIGHT_EYE_CLOSE
	faceLABDatas_.right_eye_close = readFloat(104,echoBuffer);

	//Reading LEFT_EYE_CLOSE
	faceLABDatas_.left_eye_close = readFloat(108,echoBuffer);

	//Reading RIGHT_CLOS_CONF
	faceLABDatas_.right_clos_conf = readFloat(112,echoBuffer);

	//Reading LEFT_CLOS_CONF
	faceLABDatas_.left_clos_conf = readFloat(116,echoBuffer);

	//Reading EYE_CLOSE_CALIB
	faceLABDatas_.eye_close_calib = readFloat(120,echoBuffer);

	//Reading BLINKING_FREQ
	faceLABDatas_.blinking_freq = readFloat(125,echoBuffer);

	//Reading BLINKING_DURATION
	faceLABDatas_.blinking_duration = readFloat(129,echoBuffer);

	//Reading PERCLOS
	faceLABDatas_.perclos = readFloat(133,echoBuffer);

	//Reading Gaze_Quality_R
	faceLABDatas_.gaze_quality_r = echoBuffer[142];
		
	//Reading EYEBALL_R_X
	faceLABDatas_.eyeball_r_x = readFloat(143,echoBuffer);
		
	//Reading EYEBALL_R_Y
	faceLABDatas_.eyeball_r_y = readFloat(147,echoBuffer);
	
	//Reading EYEBALL_R_Z
	faceLABDatas_.eyeball_r_z = readFloat(151,echoBuffer);
		
	//Reading GAZEROT_R_X
	faceLABDatas_.gazerot_r_x = readFloat(155,echoBuffer);
		
	//Reading GAZEROT_R_Y
	faceLABDatas_.gazerot_r_y = readFloat(159,echoBuffer);
		
	//Reading Gaze_Quality_L
	faceLABDatas_.gaze_quality_l = echoBuffer[163];
		
	//Reading EYEBALL_L_X
	faceLABDatas_.eyeball_l_x = readFloat(164,echoBuffer);
		
	//Reading EYEBALL_L_Y
	faceLABDatas_.eyeball_l_y = readFloat(168,echoBuffer);
		
	//Reading EYEBALL_L_Z
	faceLABDatas_.eyeball_l_z = readFloat(172,echoBuffer);
		
	//Calculating the mean of eyes
	faceLABDatas_.eyeball_x = (faceLABDatas_.eyeball_r_x+faceLABDatas_.eyeball_l_x)/2;
	faceLABDatas_.eyeball_y = (faceLABDatas_.eyeball_r_y+faceLABDatas_.eyeball_l_y)/2;
	faceLABDatas_.eyeball_z = (faceLABDatas_.eyeball_r_z+faceLABDatas_.eyeball_l_z)/2;
	
	//Reading GAZEROT_L_X
	//Pitch Angle
	faceLABDatas_.gazerot_l_x = readFloat(176,echoBuffer);
		
	//Reading GAZEROT_L_Y
	//Yaw Angle
	faceLABDatas_.gazerot_l_y = readFloat(180,echoBuffer);

	//Calculating Gaze' vector
	faceLABDatas_.r_nx = -sin(faceLABDatas_.gazerot_r_y)*cos(faceLABDatas_.gazerot_r_x);
	faceLABDatas_.r_ny = sin(faceLABDatas_.gazerot_r_x);
	faceLABDatas_.r_nz = -cos(faceLABDatas_.gazerot_r_y)*cos(faceLABDatas_.gazerot_r_x);
		
	faceLABDatas_.l_nx = -sin(faceLABDatas_.gazerot_l_y)*cos(faceLABDatas_.gazerot_l_x);
	faceLABDatas_.l_ny = sin(faceLABDatas_.gazerot_l_x);
	faceLABDatas_.l_nz = -cos(faceLABDatas_.gazerot_l_y)*cos(faceLABDatas_.gazerot_l_x);
	
	faceLABDatas_.nx = (faceLABDatas_.r_nx+faceLABDatas_.l_nx)/2;
	faceLABDatas_.ny = (faceLABDatas_.r_ny+faceLABDatas_.l_ny)/2;
	faceLABDatas_.nz = (faceLABDatas_.r_nz+faceLABDatas_.l_nz)/2;

	//Reading Gaze_Obj_Index
	faceLABDatas_.gaze_obj_index = readInt(279,echoBuffer);

	//Reading GSI_World_X
	faceLABDatas_.gsi_world_x=readFloat(292,echoBuffer);

	//Reading GSI_World_Y
	faceLABDatas_.gsi_world_y=readFloat(296,echoBuffer);

	//Reading GSI_World_Z
	faceLABDatas_.gsi_world_z=readFloat(300,echoBuffer);

	//Reading GSI_SCREEN_X
	faceLABDatas_.gsi_screen_x = readFloat(304,echoBuffer);

	//Reading GSI_SCREEN_Y
	faceLABDatas_.gsi_screen_y = readFloat(308,echoBuffer);

	//Reading GSI_Pixel_X
	faceLABDatas_.gsi_pixel_x = readInt(312,echoBuffer);

	//Reading GSI_Pixel_Y
	faceLABDatas_.gsi_pixel_y = readInt(316,echoBuffer);

	//Reading GOI_X
	faceLABDatas_.goi_x = readFloat(320,echoBuffer);

	//Reading GOI_Y
	faceLABDatas_.goi_y = readFloat(324,echoBuffer);

	//Reading GOI_Z
	faceLABDatas_.goi_z = readFloat(328,echoBuffer);

	//Reading R_PUPILOS_CA_X
	faceLABDatas_.r_pupilos_ca_x = readFloat(346,echoBuffer);

	//Reading R_PUPILOS_CA_Y
	faceLABDatas_.r_pupilos_ca_y = readFloat(350,echoBuffer);

	//Reading L_PUPILOS_CA_X
	faceLABDatas_.l_pupilos_ca_x = readFloat(357,echoBuffer);

	//Reading L_PUPILOS_CA_Y
	faceLABDatas_.l_pupilos_ca_y = readFloat(361,echoBuffer);

	//Reading FACERECT_CA_X
	faceLABDatas_.facerect_ca_x = readFloat(368,echoBuffer);

	//Reading FACERECT_CA_Y
	faceLABDatas_.facerect_ca_y = readFloat(372,echoBuffer);

	//Reading FACERECT_CA_W
	faceLABDatas_.facerect_ca_w = readFloat(376,echoBuffer);

	//Reading FACERECT_CA_H
	faceLABDatas_.facerect_ca_h = readFloat(380,echoBuffer);

	//Reading REYERECT_CA_X
	faceLABDatas_.reyerect_ca_x = readFloat(387,echoBuffer);

	//Reading REYERECT_CA_Y
	faceLABDatas_.reyerect_ca_y = readFloat(391,echoBuffer);

	//Reading REYERECT_CA_W
	faceLABDatas_.reyerect_ca_w = readFloat(395,echoBuffer);

	//Reading REYERECT_CA_H
	faceLABDatas_.reyerect_ca_h = readFloat(399,echoBuffer);

	//Reading LEYERECT_CA_X
	faceLABDatas_.leyerect_ca_x = readFloat(406,echoBuffer);

	//Reading LEYERECT_CA_Y
	faceLABDatas_.leyerect_ca_y = readFloat(410,echoBuffer);

	//Reading LEYERECT_CA_W
	faceLABDatas_.leyerect_ca_w = readFloat(414,echoBuffer);

	//Reading LEYERECT_CA_H
	faceLABDatas_.leyerect_ca_h = readFloat(418,echoBuffer);

	//Reading MOUTRECT_CA_X
	faceLABDatas_.moutrect_ca_x = readFloat(425,echoBuffer);

	//Reading MOUTRECT_CA_Y
	faceLABDatas_.moutrect_ca_y = readFloat(429,echoBuffer);

	//Reading MOUTRECT_CA_W
	faceLABDatas_.moutrect_ca_w = readFloat(433,echoBuffer);

	//Reading MOUTRECT_CA_H
	faceLABDatas_.moutrect_ca_h = readFloat(437,echoBuffer);

	//Reading R_PUPILOS_CB_X
	faceLABDatas_.r_pupilos_cb_x = readFloat(449,echoBuffer);

	//Reading R_PUPILOS_CB_Y
	faceLABDatas_.r_pupilos_cb_y = readFloat(453,echoBuffer);

	//Reading L_PUPILOS_CB_X
	faceLABDatas_.l_pupilos_cb_x = readFloat(460,echoBuffer);

	//Reading L_PUPILOS_CB_Y
	faceLABDatas_.l_pupilos_cb_y = readFloat(464,echoBuffer);

	//Reading FACERECT_CB_X
	faceLABDatas_.facerect_cb_x = readFloat(471,echoBuffer);

	//Reading FACERECT_CB_Y
	faceLABDatas_.facerect_cb_y = readFloat(475,echoBuffer);

	//Reading FACERECT_CB_W
	faceLABDatas_.facerect_cb_w = readFloat(479,echoBuffer);

	//Reading FACERECT_CB_H
	faceLABDatas_.facerect_cb_h = readFloat(483,echoBuffer);

	//Reading REYERECT_CB_X
	faceLABDatas_.reyerect_cb_x = readFloat(490,echoBuffer);

	//Reading REYERECT_CB_Y
	faceLABDatas_.reyerect_cb_y = readFloat(494,echoBuffer);

	//Reading REYERECT_CB_W
	faceLABDatas_.reyerect_cb_w = readFloat(498,echoBuffer);

	//Reading REYERECT_CB_H
	faceLABDatas_.reyerect_cb_h = readFloat(502,echoBuffer);

	//Reading LEYERECT_CB_X
	faceLABDatas_.leyerect_cb_x = readFloat(509,echoBuffer);

	//Reading LEYERECT_CB_Y
	faceLABDatas_.leyerect_cb_y = readFloat(513,echoBuffer);

	//Reading LEYERECT_CB_W
	faceLABDatas_.leyerect_cb_w = readFloat(517,echoBuffer);

	//Reading LEYERECT_CB_H
	faceLABDatas_.leyerect_cb_h = readFloat(521,echoBuffer);

	//Reading MOUTRECT_CB_X
	faceLABDatas_.moutrect_cb_x = readFloat(528,echoBuffer);

	//Reading MOUTRECT_CB_Y
	faceLABDatas_.moutrect_cb_y = readFloat(532,echoBuffer);

	//Reading MOUTRECT_CB_W
	faceLABDatas_.moutrect_cb_w = readFloat(536,echoBuffer);

	//Reading MOUTRECT_CB_H
	faceLABDatas_.moutrect_cb_h = readFloat(540,echoBuffer);

	//Affichage
	/*printf("Received packet from %s : %d \n",sourceAddress.toString().toStdString().c_str(),sourcePort);
	printf("Frame Number:%d\n",faceLABDatas_.frameNumber);
	printf("Time:%d%d millisecondes \n",faceLABDatas_.gmt_s,faceLABDatas_.gmt_ms);
	printf ("X:%f\n",faceLABDatas_.nx);
	printf ("Y:%f\n",faceLABDatas_.ny);
	printf ("Z:%f\n",faceLABDatas_.nz);*/
	x=faceLABDatas_.gsi_pixel_x;
	y=faceLABDatas_.gsi_pixel_y;
	lab_->move((x),y);
	lab_->show();
	fflush(stdout);
 }

std::string FaceLABComponent::IntToString(int intValue) {
	return(QString::number(intValue).toStdString());
}

int FaceLABComponent::int2bin(int x)
{
	int y=0;
	if(x>=0)
	{
		if(x>=128)
		{
			y=y+10000000;
			x=x-128;
		}
		if(x>=64)
		{
			y=y+1000000;
			x=x-64;
		}
		if(x>=32)
		{
			y=y+100000;
			x=x-32;
		}
		if(x>=16)
		{
			y=y+10000;
			x=x-16;
		}
		if(x>=8)
		{
			y=y+1000;
			x=x-8;
		}
		if(x>=4)
		{
			y=y+100;
			x=x-4;
		}
		if(x>=2)
		{
			y=y+10;
			x=x-2;
		}
		if(x>=1)
		{
			y=y+1;
			x=x-1;
		}
	}
	else
	{
		char z[8];
		for(int u=0;u<=7;u++)
			z[u]=0;
		x=x*(-1);
		if(x>=128)
		{
			z[0]=1;
			x=x-128;
		}
		if(x>=64)
		{
			z[1]=1;
			x=x-64;
		}
		if(x>=32)
		{
			z[2]=1;
			x=x-32;
		}
		if(x>=16)
		{
			z[3]=1;
			x=x-16;
		}
		if(x>=8)
		{
			z[4]=1;
			x=x-8;
		}
		if(x>=4)
		{
			z[5]=1;
			x=x-4;
		}
		if(x>=2)
		{
			z[6]=1;
			x=x-2;
		}
		if(x>=1)
		{
			z[7]=1;
			x=x-1;
		}

		for(int k=0;k<=7;k++)
			if(z[k]==0)
				z[k]=1;
			else
				z[k]=0;

		if(z[7]==0)
			z[7]=1;
		else
		{
			z[7]=0;
			if(z[6]==0)
				z[6]=1;
			else
			{
				z[6]=0;
				if(z[5]==0)
					z[5]=1;
				else
				{
					z[5]=0;
					if(z[4]==0)
						z[4]=1;
					else
					{
						z[4]=0;
						if(z[3]==0)
							z[3]=1;
						else
						{
							z[3]=0;
							if(z[2]==0)
								z[2]=1;
							else
							{
								z[2]=0;
								if(z[1]==0)
									z[1]=1;
								else
								{
									z[1]=0;
									if(z[0]==0)
										z[0]=1;
									else
										z[0]=0;
								}
							}
						}
					}
				}
			}

		}
		if(z[0]==1)
			y=y+10000000;
		if(z[1]==1)
			y=y+1000000;
		if(z[2]==1)
			y=y+100000;
		if(z[3]==1)
			y=y+10000;
		if(z[4]==1)
			y=y+1000;
		if(z[5]==1)
			y=y+100;
		if(z[6]==1)
			y=y+10;
		if(z[7]==1)
			y=y+1;
	}
	return y;
}

float FaceLABComponent::puissance(int nb,int exp)
{

	float res=1;
	if(exp>=0)
	{
		for(int i=0;i<exp;i++)
			res=res*nb;
	}
	else
	{
		for(int j=0;j>exp;j--)
			res=res/nb;
	}
	return res;
}

int FaceLABComponent::bin2dec(std::string w, std::string x, std::string y, std::string z)
{
	int nombre=0;
	char nomb[32];
	for(int i=0;i<=31;i++)
		nomb[i]='0';
	int lw,lx, ly, lz;
	lw=w.length();
	lx=x.length();
	ly=y.length();
	lz=z.length();

	for(int i=0;i<=(lw-1);i++)
		nomb[i+8-lw]=w[i];
	for(int i=0;i<=(lx-1);i++)
		nomb[i+8+8-lx]=x[i];
	for(int i=0;i<=(ly-1);i++)
		nomb[i+16+8-ly]=y[i];
	for(int i=0;i<=(lz-1);i++)
		nomb[i+24+8-lz]=z[i];

	for(int j=0;j<=31;j++)
	{
		if (nomb[31-j]==49)
			nombre=nombre+ puissance(2,j);
	}
	return nombre;
}

float FaceLABComponent::bin2float(std::string w, std::string x, std::string y, std::string z)
{
	int signe=1;
	int exposant=0;
	float mantisse=1;
	float nombre=0;
	char nomb[32];
	for(int i=0;i<=31;i++)
		nomb[i]='0';
	int lw,lx, ly, lz;
	lw=w.length();
	lx=x.length();
	ly=y.length();
	lz=z.length();
	int count=-1;
	for(int i=0;i<=(lw-1);i++)
		nomb[i+8-lw]=w[i];
	for(int i=0;i<=(lx-1);i++)
		nomb[i+8+8-lx]=x[i];
	for(int i=0;i<=(ly-1);i++)
		nomb[i+16+8-ly]=y[i];
	for(int i=0;i<=(lz-1);i++)
		nomb[i+24+8-lz]=z[i];

	if(nomb[0]==49)
		signe=-1;

	for(int i=0;i<=7;i++)
		if(nomb[8-i]==49)
			exposant=exposant+puissance(2,i);
	exposant=exposant-127;
	for(int j=9;j<=31;j++)
	{

		if(nomb[j]==49)
		{
			mantisse=mantisse+puissance(2,count);
		}
		count--;
	}
	//mantisse=mantisse/2;
	nombre=signe*mantisse*puissance(2,exposant);


	return nombre;
}

int FaceLABComponent::number(int code)
{
	return (code-48);
}

float FaceLABComponent::readFloat(int nb1, char echoBuffer[])
{
	float res;
	int ww =echoBuffer[nb1];
	int xx =echoBuffer[nb1+1];
	int yy =echoBuffer[nb1+2];
	int zz =echoBuffer[nb1+3];

	int wa=int2bin(ww);
	int xa=int2bin(xx);
	int ya=int2bin(yy);
	int za=int2bin(zz);

	std::string aw=IntToString(wa);
	std::string ax=IntToString(xa);
	std::string ay=IntToString(ya);
	std::string az=IntToString(za);

	res=bin2float(aw,ax,ay,az);
	return res;
}

int FaceLABComponent::readInt(int nb1, char echoBuffer[])
{
	int res;
	int ww =echoBuffer[nb1];
	int xx =echoBuffer[nb1 + 1];
	int yy =echoBuffer[nb1 + 2];
	int zz =echoBuffer[nb1 + 3];

	int wa=int2bin(ww);
	int xa=int2bin(xx);
	int ya=int2bin(yy);
	int za=int2bin(zz);

	std::string aw=IntToString(wa);
	std::string ax=IntToString(xa);
	std::string ay=IntToString(ya);
	std::string az=IntToString(za);

	res=bin2dec(aw,ax,ay,az);
	return res;
}








