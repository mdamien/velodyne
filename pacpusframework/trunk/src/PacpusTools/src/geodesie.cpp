// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
/// @author  Jean Laneurit <firstname.surname@utc.fr>
/// @date    April, 2010
// %pacpus:license}

#include <Pacpus/PacpusTools/geodesie.h>

#include <fstream>

#ifdef _MSC_VER
#   pragma warning(disable:4244)
#endif //_MSC_VER

namespace Geodesie {
/// ////////////////////////////////////////////////////////////////////
Matrice::Matrice(const Matrice & A) {
    c0_l0=A.c0_l0;c1_l0=A.c1_l0;c2_l0=A.c2_l0;
    c0_l1=A.c0_l1;c1_l1=A.c1_l1;c2_l1=A.c2_l1;
    c0_l2=A.c0_l2;c1_l2=A.c1_l2;c2_l2=A.c2_l2;
}
/// ////////////////////////////////////////////////////////////////////
Matrice::Matrice() {
    c0_l0=0.0;c1_l0=0.0;c2_l0=0.0;
    c0_l1=0.0;c1_l1=0.0;c2_l1=0.0;
    c0_l2=0.0;c1_l2=0.0;c2_l2=0.0;
}
/// ////////////////////////////////////////////////////////////////////
void Matrice::Apply(double v0,double v1,double v2, double& Mv0,double& Mv1,double& Mv2) {
    Mv0 = c0_l0*v0 + c1_l0*v1 + c2_l0*v2;
    Mv1 = c0_l1*v0 + c1_l1*v1 + c2_l1*v2;
    Mv2 = c0_l2*v0 + c1_l2*v1 + c2_l2*v2;
}
/// ////////////////////////////////////////////////////////////////////
Matrice ProdMat(const Matrice A, const Matrice B) {
    Matrice out;

    out.c0_l0=A.c0_l0 * B.c0_l0 + A.c1_l0 * B.c0_l1 + A.c2_l0 * B.c0_l2;
    out.c1_l0=A.c0_l0 * B.c1_l0 + A.c1_l0 * B.c1_l1 + A.c2_l0 * B.c1_l2;
    out.c2_l0=A.c0_l0 * B.c2_l0 + A.c1_l0 * B.c2_l1 + A.c2_l0 * B.c2_l2;

    out.c0_l1=A.c0_l1 * B.c0_l0 + A.c1_l1 * B.c0_l1 + A.c2_l1 * B.c0_l2;
    out.c1_l1=A.c0_l1 * B.c1_l0 + A.c1_l1 * B.c1_l1 + A.c2_l1 * B.c1_l2;
    out.c2_l1=A.c0_l1 * B.c2_l0 + A.c1_l1 * B.c2_l1 + A.c2_l1 * B.c2_l2;

    out.c0_l2=A.c0_l2 * B.c0_l0 + A.c1_l2 * B.c0_l1 + A.c2_l2 * B.c0_l2;
    out.c1_l2=A.c0_l2 * B.c1_l0 + A.c1_l2 * B.c1_l1 + A.c2_l2 * B.c1_l2;
    out.c2_l2=A.c0_l2 * B.c2_l0 + A.c1_l2 * B.c2_l1 + A.c2_l2 * B.c2_l2;
    return out;
}

/// ////////////////////////////////////////////////////////////////////
Matrice TransMat(const Matrice A) {
    Matrice out;
    out.c0_l0=A.c0_l0 ; out.c1_l0 = A.c0_l1 ; out.c2_l0 = A.c0_l2 ; 
    out.c0_l1=A.c1_l0 ; out.c1_l1 = A.c1_l1 ; out.c2_l1 = A.c1_l2 ; 
    out.c0_l2=A.c2_l0 ; out.c1_l2 = A.c2_l1 ; out.c2_l2 = A.c2_l2 ; 
    return out;
}

/// ////////////////////////////////////////////////////////////////////
void Write(const Matrice A,std::ostream& out) {
    out<< A.c0_l0<<"\t"<< A.c1_l0<<"\t"<< A.c2_l0<<"\n";
    out<< A.c0_l1<<"\t"<< A.c1_l1<<"\t"<< A.c2_l1<<"\n";
    out<< A.c0_l2<<"\t"<< A.c1_l2<<"\t"<< A.c2_l2<<"\n";
}

/// ////////////////////////////////////////////////////////////////////
Raf98::~Raf98() {
    m_dvalues.clear();
}

//-----------------------------------------------------------------------------
bool Raf98::Interpol(double longitude, double latitude, double* Hwgs84) const {
    *Hwgs84 = 0.0;
    if (m_dvalues.size()==0)
        return false;
    const double longitude_min =  -5.5;
    const double longitude_max =  8.5;
    if (longitude < longitude_min)
        return false;
    if (longitude > longitude_max)
        return false;

    const double latitude_min =  42;
    const double latitude_max =  51.5;
    if (latitude < latitude_min)
        return false;
    if (latitude > latitude_max)
        return false;

    //conversion en position
    double longPix = (longitude - longitude_min) * 30.;
    double latPix  = (latitude_max - latitude) * 40.;

    double RestCol,RestLig;      
    double  ColIni,LigIni;     
    RestCol = modf(longPix,&ColIni);
    RestLig = modf(latPix,&LigIni);
    
    
    double Zbd = (1.0-RestCol) * (1.0-RestLig) * LitGrille(ColIni  , LigIni  );
    Zbd += RestCol * (1.0-RestLig) * LitGrille(ColIni+1, LigIni  );
    Zbd += (1.0-RestCol) *   RestLig  * LitGrille(ColIni  , LigIni+1);
    Zbd += RestCol * RestLig * LitGrille(ColIni+1, LigIni+1);
    *Hwgs84 = Zbd;


    return true;
}
/// ////////////////////////////////////////////////////////////////////
double Raf98::LitGrille(unsigned int c,unsigned int l) const{
    const unsigned int w=421;
    //    const unsigned int h=381;
    return m_dvalues.at(c+l*w);
}
/// ////////////////////////////////////////////////////////////////////
bool Raf98::Load(const std::string & sin) {
    std::ifstream in(sin.c_str());
    unsigned int w = 421;
    unsigned int h = 381;
    
    m_dvalues.reserve(w*h);

    char entete[1024];//sur 3 lignes
    in.getline(entete,1023);
    in.getline(entete,1023);
    in.getline(entete,1023);

    char bidon[1024];
    double val;
    for (unsigned int i=0; i< h; ++i) {
        for (unsigned int j=0; j< 52; ++j)  {
            for (unsigned int k=0; k< 8; ++k) {
                in >> val;
                m_dvalues.push_back( val );
            }
            in.getline(bidon,1023);
        }
        for (unsigned int k=0; k< 5; ++k) {
            in >> val;
            m_dvalues.push_back( val );
        }
        in.getline(bidon,1023);
        if (!in.good())         {
            m_dvalues.clear();
            return false;
        }
    }
    return in.good();
}

} // namespace Geodesie

/// ////////////////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////////////////

/// ////////////////////////////////////////////////////////////////////
//ALGO0001
double Geodesie::LatitueIsometrique(double latitude,double e) {
    double li;
    li = log(tan(M_PI_4 + latitude/2.)) + e*log( (1-e*sin(latitude))/(1+e*sin(latitude)) )/2;
    return li;
}

/// ////////////////////////////////////////////////////////////////////
//ALGO0002
double Geodesie::LatitueIsometrique2Lat(double latitude_iso,double e,double epsilon) {
    double latitude_i=2*atan(exp(latitude_iso)) - M_PI_2;
    double latitude_ip1=latitude_i+epsilon*2;
    while (fabs(latitude_i-latitude_ip1)>epsilon) {
        latitude_i=latitude_ip1;
        latitude_ip1=2*atan(
                    exp(e*0.5*
                        log(
                            (1+e*sin(latitude_i))/(1-e*sin(latitude_i))
                            )
                        )
                    *exp(latitude_iso)
                    ) - M_PI_2;
    }
    return latitude_ip1;
}
/// ////////////////////////////////////////////////////////////////////
void Geodesie::Geo2ProjLambert(
    double lambda,double phi,
    double n, double c,double e,
    double lambdac,double xs,double ys,
    double& X,double& Y)
{
    double lat_iso=LatitueIsometrique(phi,e);
    X=xs+c*exp(-n*lat_iso)*sin(n*(lambda-lambdac));
    Y=ys-c*exp(-n*lat_iso)*cos(n*(lambda-lambdac));
}
/// ////////////////////////////////////////////////////////////////////
//ALGO0004
void Geodesie::Proj2GeoLambert(
    double X,double Y,
    double n, double c,double e,
    double lambdac,double xs,double ys,
    double epsilon,
    double& lambda,double& phi)
{
    double X_xs=X-xs;
    double ys_Y=ys-Y;
    double R=sqrt(X_xs*X_xs+ys_Y*ys_Y);
    double gamma=atan(X_xs/ys_Y);
    lambda=lambdac+gamma/n;
    double lat_iso=-1/n*log(fabs(R/c));
    phi=LatitueIsometrique2Lat(lat_iso,e,epsilon);
}
/// ////////////////////////////////////////////////////////////////////
double Geodesie::ConvMerApp(double longitude) {
    double phi0_Lambert93 = Deg2Rad(46.5);
    double lambda0_Lambert93 = Deg2Rad(3.0);
    double conv=-sin(phi0_Lambert93)*(longitude-lambda0_Lambert93);
    return  conv;
}

////////////////////////////////////////////////////////////////////
void Geodesie::Geographique_2_Lambert93(const Raf98& raf98,double lambda,double phi,double he,Matrice in,double& E,double& N,double& h,Matrice& out) {
    Matrice passage;
    double conv=Geodesie::ConvMerApp(lambda);
    double c_=cos(conv);
    double s_=sin(conv);

    passage.c0_l0 = c_;
    passage.c0_l1 = s_;
    passage.c0_l2 =  0.0;

    passage.c1_l0 = -s_;
    passage.c1_l1 = c_;
    passage.c1_l2 =  0.0;

    passage.c2_l0 =  0.0; 
    passage.c2_l1 =  0.0; 
    passage.c2_l2 =  1.0; 
    
    out=ProdMat(passage,in);
    double diff_h;
    raf98.Interpol(Rad2Deg(lambda),Rad2Deg(phi),&diff_h);
    h=he-diff_h;
    
    Geodesie::Geo2ProjLambert(
                lambda,phi,
                n_Lambert93,c_Lambert93,e_Lambert93,
                lambda0_Lambert93,xs_Lambert93,ys_Lambert93,
                E,N);
}
////////////////////////////////////////////////////////////////////////
void Geodesie::Geographique_2_Lambert93(const Raf98& raf98,double lambda,double phi,double he,double& E,double& N,double& h) {
    Geodesie::Geo2ProjLambert(
                lambda,phi,
                n_Lambert93,c_Lambert93,e_Lambert93,
                lambda0_Lambert93,xs_Lambert93,ys_Lambert93,
                E,N);

    double diff_h;
    raf98.Interpol(Rad2Deg(lambda),Rad2Deg(phi),&diff_h);
    h=he-diff_h;
}
/**
    Converts Lambert93 coordinates (East, North, Height) into geographical coordinates in radians (Longitude = Rad2Deg(lambda), Latitude = Rad2Deg(phi), Height)
*/
void Geodesie::Lambert93_2_Geographique(const Raf98& raf98,double E,double N,double h,double& lambda,double& phi,double& he) {
    Geodesie::Proj2GeoLambert(
                E,N,
                n_Lambert93,c_Lambert93,e_Lambert93,
                lambda0_Lambert93,xs_Lambert93,ys_Lambert93,
                0.0000000000000001,
                lambda,phi);

    double diff_h;
    raf98.Interpol(Rad2Deg(lambda),Rad2Deg(phi),&diff_h);
    he=h+diff_h;
}
////////////////////////////////////////////////////////////////////////
void Geodesie::Lambert93_2_Geographique(const Raf98& raf98,double E,double N,double h,Matrice in,double& lambda,double& phi,double& he,Matrice& out) {
    Geodesie::Proj2GeoLambert(
                E,N,
                n_Lambert93,c_Lambert93,e_Lambert93,
                lambda0_Lambert93,xs_Lambert93,ys_Lambert93,
                0.0000000000000001,
                lambda,phi);

    Matrice passage;
    double conv=Geodesie::ConvMerApp(lambda);
    double c_=cos(conv);
    double s_=sin(conv);

    passage.c0_l0 = c_;
    passage.c0_l1 = -s_;
    passage.c0_l2 =  0.0;

    passage.c1_l0 = s_;
    passage.c1_l1 = c_;
    passage.c1_l2 =  0.0;

    passage.c2_l0 =  0.0; 
    passage.c2_l1 =  0.0; 
    passage.c2_l2 =  1.0; 
    
    out=ProdMat(passage,in);
    
    double diff_h;
    raf98.Interpol(Rad2Deg(lambda),Rad2Deg(phi),&diff_h);
    he=h+diff_h;
}

////////////////////////////////////////////////////////////////////////
void Geodesie::Geographique_2_ECEF(double longitude,double latitude,double he,double& x,double& y,double& z) {
    const double n = GRS_a / sqrt(1.0 - pow(GRS_e,2) * pow(sin(latitude),2));
    x = (n + he) * cos(latitude) * cos(longitude);
    y = (n + he) * cos(latitude) * sin(longitude);
    z = (n * (1.0 - pow(GRS_e,2)) + he) * sin(latitude);
}

////////////////////////////////////////////////////////////////////////
void Geodesie::ECEF_2_ENU(double x,double y,double z,double& e,double& n,double& u,double lon0,double lat0,double he0) {
    double slat = std::sin(lat0);
    double clat = std::cos(lat0);
    double slon = std::sin(lon0);
    double clon = std::cos(lon0);

    Geodesie::Matrice C;
    C.c0_l0 = -slon;
    C.c1_l0 = clon;

    C.c0_l1 = -clon * slat;
    C.c1_l1 = -slon * slat;
    C.c2_l1 = clat;

    C.c0_l2 = clon * clat;
    C.c1_l2 = slon * clat;
    C.c2_l2 = slat;

    double x0, y0, z0;
    Geographique_2_ECEF(lon0,lat0,he0, x0,y0,z0);

    x -= x0;
    y -= y0;
    z -= z0;

    C.Apply(x,y,z, e,n,u);
}
