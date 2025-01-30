/*
 * PKW.cpp
 *
 *  Created on: Nov 14, 2024
 *      Author: Karime Soriano
 */
#include "PKW.h"
#include<iostream>
#include<iomanip>
#include <limits>
using std::string;
using std::cout;
using std::endl;

extern double dGlobaleZeit;
//4.3.1
//using namespace std;
PKW::PKW(const string sName, double dmaxGeschwindigkeit)
: Fahrzeug(sName, dmaxGeschwindigkeit) {
	cout << "Auto \"" << sName << "\" von maximal Geschwindigkeit "
		 << dmaxGeschwindigkeit << " km/std" << endl;
}

//4.3.2
PKW::PKW(const string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen)
    : Fahrzeug(sName, dMaxGeschwindigkeit), p_dVerbrauch(dVerbrauch), p_dTankvolumen(dTankvolumen), p_dTankinhalt(dTankvolumen / 2) {// Initialisierung des Tanks auf die Hälfte seiner Kapazität
	cout << "Auto:\"" << sName << "\" von maximaler Geschwindigkeit: "
			 << dMaxGeschwindigkeit << " km/std, Kraftstoffverbrauch: "
			 << dVerbrauch << "L/100 km, mit einem Panzer: "
			 << dTankvolumen << "L und derzeit mit: "
			 << p_dTankinhalt << "L im Tank."
			 << endl;
}

PKW::~PKW() {
	// TODO Auto-generated destructor stub
}

//4.3.2
void PKW::vSimulieren(){
	 if (p_dTankinhalt > 0.0) { //Wenn noch Kraftstoff vorhanden ist
		 // Man berechnet den Zeitunterschied seit der letzten Simulation
	        double dZeitdifferenz = dGlobaleZeit - p_dZeit;

	        if (dZeitdifferenz > 0) { // Nur simulieren, wenn die Zeit fortgeschritten ist
	        	// Man berechnet die in diesem Intervall zurückgelegte Strecke
	            double dStrecke = p_dMaxGeschwindigkeit * dZeitdifferenz;

	            // Man berechnet die verbrauchte Kraftstoffmenge
	            double dVerbrauchte = (dStrecke / 100.0) * p_dVerbrauch;

	            // Prüfen, ob genügend Treibstoff vorhanden ist
	            if (dVerbrauchte <= p_dTankinhalt) {
	            	// Basisklassensimulation aufrufen
	                Fahrzeug::vSimulieren();

	                // Gesamtverbrauch aktualisieren und verfügbaren Kraftstoff reduzieren
	                p_dGesamtverbrauch += dVerbrauchte;
	                p_dTankinhalt -= dVerbrauchte;
	            } else {
	            	// Nicht genügend Kraftstoff: PKW stoppt
	                cout << "PKW \"" << p_sName << "\" hat keinen Treibstoff mehr und kann nicht weiterfahren." << endl;
	            }

	            // Aktualisiere die letzte Simulationszeit auf die aktuelle globale Zeit
	            p_dZeit = dGlobaleZeit;
	        }
	    } else {
	    	// Nicht genügend Kraftstoff: PKW stoppt
	        cout << "PKW \"" << p_sName << "\" hat keinen Treibstoff mehr und kann nicht weiterfahren." << endl;
	    }


}

//4.3.2
void PKW::vAusgeben()const{
	// Aufrufen der Ausgabefunktion der Basisklasse zur Vermeidung von Doppelarbeit
	Fahrzeug::vAusgeben();
	// Tankstatus und Gesamtverbrauch anzeigen
	cout << std::setw(15) << p_dGesamtverbrauch << " L"
		     << std::setw(15) << p_dTankinhalt << " / " << p_dTankvolumen << " L";
}

void PKW::vAusgeben(std::ostream& os)const{
	Fahrzeug::vAusgeben(os);
	os<<"Fahrrad";
	os << std::setw(15) << p_dGesamtverbrauch << " L"
			     << std::setw(15) << p_dTankinhalt << " / " << p_dTankvolumen << " L";

}

// dTanken für PKW überschreiben    4.3.2
double PKW::dTanken(double dMenge){
	// Berechnen des verfügbaren Platzes im Tank
	double dverfugbarePlatz = p_dTankvolumen-p_dTankinhalt;
	// Die tatsächlich abzufüllende Menge bestimmen
	double dabfullmenge = (dMenge == std::numeric_limits<double>::infinity()) ? dverfugbarePlatz : dMenge; //ternary operator
	// Wenn die zu tankende Menge den verfügbaren Platz übersteigt, ist sie zu begrenzen.
	if (dabfullmenge > dverfugbarePlatz) {
		dabfullmenge = dverfugbarePlatz;
	}
	// Man erhöht den Tankinhalt um die zu füllende Menge
	p_dTankinhalt += dabfullmenge;

	// Füllmenge und Tankstatus drucken
	cout << "PKW \"" << p_sName << "\" würde gefüllt mit " << dabfullmenge<< " liter. Aktueller Tankfüllstand: " << p_dTankinhalt << " / " << p_dTankvolumen << " L.\n";

	// Rückgabe der tatsächlich getankten Menge
	return dabfullmenge;
}

double PKW::dGeschwindigkeit() const {
	return p_dMaxGeschwindigkeit;
}







