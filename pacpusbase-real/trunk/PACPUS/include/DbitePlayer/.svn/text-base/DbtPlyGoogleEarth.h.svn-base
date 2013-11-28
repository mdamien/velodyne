/*********************************************************************
//  created:    2008/05/01 - 16:30
//  filename:   DbtPlyGoogleEarth.h
//
//  author:     Adrien Loison & Mickael Buranello 
// 
//  version:    $Id: $
//
//  purpose:    Use of Google Earth via Dbite Player
*********************************************************************/


#ifndef _DBTPLYGOOGLEEARTH_H_
#define _DBTPLYGOOGLEEARTH_H_

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <fstream>
#include <QT/qthread.h>

#include "PacpusTools/ShMem.h"
#include "kernel/ComponentBase.h"
#include "kernel/ComponentFactory.h"

#import "C:\Program Files\Google\Google Earth\client\googleearth.exe" named_guids
//#import "C:\Program Files\Google\Google Earth\googleearth.exe" named_guids
//QString geDir = ComponentBase::param.getProperty("geDir") + "\googleearth.exe";
//#import geDir named_guids


/*************************************************************************************/
/*** Classe définissant un point ***/

class Point
{
	public:
		double lat; // Latitude
		double lon; // Longitude
		float a, b, phi; // paramètres pour l'ellipse

		Point(double latitude = 0, double longitude = 0, float _a = 0, float _b = 0, float _phi = 0) :
			lat(latitude), lon(longitude), a(_a), b(_b), phi(_phi) {}
};
typedef Point* PPoint;


/*************************************************************************************/
/*** Classe du composant GoogleEarth ***/

class DbtPlyGoogleEarth : public ComponentBase, public QThread
{
	public:
		static int nb_pts_simultanes;
		EARTHLib::IApplicationGE* ge;
	
	public:
		DbtPlyGoogleEarth(QString name);
		~DbtPlyGoogleEarth();

		void run(); // rédéfinition de la méthode du QThread

	protected:
		virtual ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);
		virtual void startActivity();
		virtual void stopActivity();

	private :
		// Lecture des points lus en mémoire partagée
		int readSharedMem(Point * point, ShMem * shMem_);
		
		// Calcul de l'ellipse d'incertitude pour chaque coordonnée
		void calculEllipse(Point * point, Point** tab, double nbPoints);

		// Importation des données via la fonction LoadKMLData() -> chaine de caractères
		void importViaLoadKmlData();

		// Importation des données dans GoogleEarth via la fonction via la fonction OpenKmlFile() -> fichier KML
		void importViaOpenKmlFile();

		// Création d'un fichier KML représentant le trajet parcouru
		void creerFichierTrajet(PPoint * array, const char * nomFichier, std::string * debutKml, int passage = 1);

		void importViaOpenKmlFileSnakeMode();

		void importViaLoadKmlDataSnakeMode();


	/*************************************************************************************/
	/*** Initialisation de la caméra ***/

		void initialiserCamera(double latitude,
							   double longitude,
							   double altitude = 800, 
							   EARTHLib::AltitudeModeGE altitudeMode = EARTHLib::AbsoluteAltitudeGE,
							   double range = 0,
							   double tilt = 0,
							   double azimuth = 0,
							   double speed = 0.3
							   );

}; // fin de la classe DbyPlyGoogleEarth

// Définition de la variable static (est changé dans le constructeur)
int DbtPlyGoogleEarth::nb_pts_simultanes = 20;



/*************************************************************************************/
/*** DEFINITION DES CONSTANTES KML ***/

// KML créant le début du document
std::string KMLBEGIN = \
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<kml xmlns=\"http://earth.google.com/kml/2.2\">\n\
	<Document>\n\
		<name>Etude Expérimentale</name>\n\
		<open>0</open>\n\
		<description>Représentation du déplacement d&apos;un véhicule expérimental via GoogleEarth</description>\n";

// KML fermant le document
std::string KMLEND = "\
	</Document>\n\
</kml>";

// KML créant le début du Placemark indiquant le début du trajet
std::string KMLSTARTTAGBEGIN = "\
		<Style id=\"start\">\n\
			<IconStyle id=\"ID\">\n\
				<Icon>\n\
					<href>http://maps.google.com/mapfiles/kml/paddle/D.png</href>\n\
				</Icon>\n\
			</IconStyle>\n\
		</Style>\n\
		<Placemark>\n\
			<name>Début</name>\n\
			<description>Point de Départ du parcours</description>\n\
			<altitudeMode>relativeToGround</altitudeMode>\n\
			<Point>\n\
				<coordinates>";

// KML fermant le Placemark de début de trajet
std::string KMLSTARTTAGEND = "\n\
				</coordinates>\n\
			</Point>\n\
			<styleUrl>#start</styleUrl>\n\
		</Placemark>\n";

// KML créant le début de l'itinéraire parcouru
std::string KMLROUTEBEGIN = "\
		<Style id=\"roadStyle\">\n\
			<LineStyle>\n\
				<color>ff0000ff</color>\n\
				<width>5</width>\n\
			</LineStyle>\n\
		</Style>\n\
		<Placemark>\n\
			<name>Route</name>\n\
			<description>Itinéraire parcouru</description>\n\
			<styleUrl>#roadStyle</styleUrl>\n\
			<MultiGeometry>\n\
				<LineString>\n\
					<altitudeMode>relativeToGround</altitudeMode>\n\
					<coordinates>";

// KML fermant l'itinéraire parcouru
std::string KMLROUTEEND = "\
					</coordinates>\n\
				</LineString>\n\
			</MultiGeometry>\n\
		</Placemark>\n ";

// KML ouvrant l'ellipse
std::string KMLELLIPSEBEGIN = "\
		<Style id=\"ellipseStyle\">\n\
			<LineStyle>\n\
				<color>ff00ffff</color>\n\
				<width>3</width>\n\
			</LineStyle>\n\
			<PolyStyle>\n\
				<fill>0</fill>\n\
				<outline>1</outline>\n\
				<width>3</width>\n\
			</PolyStyle>\n\
		</Style>\n\
		<Placemark>\n\
			<name>Ellipse</name>\n\
			<description>Ellipse incertitude</description>\n\
			<styleUrl>#ellipseStyle</styleUrl>\n\
			<MultiGeometry>\n\
				<Polygon>\n\
					<altitudeMode>relativeToGround</altitudeMode>\n\
					<outerBoundaryIs>\n\
						<LinearRing>\n\
							<coordinates>";

// KML fermant l'ellipse
std::string KMLELLIPSEEND = "\
							</coordinates>\n\
						</LinearRing>\n\
					</outerBoundaryIs>\n\
				</Polygon>\n\
			</MultiGeometry>\n\
		</Placemark>\n ";

// KML créant le Placemark représentant la voiture
std::string KMLCARBEGIN = "\
		<Style id=\"voiture\">\n\
			<IconStyle id=\"ID\">\n\
				<Icon>\n\
					<href>http://maps.google.com/mapfiles/kml/shapes/cabs.png</href>\n\
				</Icon>\n\
			</IconStyle>\n\
		</Style>\n\
		<Placemark>\n\
			<name>Voiture</name>\n\
			<description>Véhicule Expérimental: \n\
	- Pilote: Gérald Dherbomez\n\
	- Copilote: Philippe Bonnifait</description>\n\
			<styleUrl>#voiture</styleUrl>\n\
			<Point>\n\
				<coordinates>";

// KML fermant le Placemark de la voiture
std::string KMLCAREND = "\
				</coordinates>\n\
			</Point>\n\
		</Placemark>\n";


/*************************************************************************************/

#endif