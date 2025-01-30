/*
 * Fahrzeug.cpp
 *
 *  Created on: Nov 9, 2024
 *      Author: Karime Soriano
 */

#include "Fahrzeug.h"
#include <iostream>
#include <iomanip> //Aufgabe 1 Punkt 6
//#include "PKW.h"
#include "Weg.h"
#include "Fahrend.h"
#include "Parkend.h"
using std::cout;
using std::endl;

//4.2.6
extern double dGlobaleZeit;//Globale Simulationszeitvariable, deklariert in main.cpp



Fahrzeug::Fahrzeug()
        : Simulationsobjekt(), p_dMaxGeschwindigkeit(0.0),p_dGesamtStrecke(0.0),p_dGesamtZeit(0.0),p_dAbschnittStrecke(0.0) {}

Fahrzeug::Fahrzeug(const std::string& sName)
        : Simulationsobjekt(sName), p_dMaxGeschwindigkeit(0.0),p_dGesamtStrecke(0.0),p_dGesamtZeit(0.0),p_dAbschnittStrecke(0.0) {}

Fahrzeug::Fahrzeug(const std::string& sName, double maxGeschwindigkeit)
        : Simulationsobjekt(sName), p_dMaxGeschwindigkeit(maxGeschwindigkeit),p_dGesamtStrecke(0.0),p_dGesamtZeit(0.0),p_dAbschnittStrecke(0.0) {}



//Start Aufgabe 1 4.2.6
void Fahrzeug::vKopf(){  //kopffunktion
	std::cout << std::setw(0) << "ID"
			<< std::setw(7) << "Name"
			<< std::setw(25) << "MaxGeschwindigkeit"
			<< std::setw(20) << "Gesamtstrecke "
			<< std::setw(25) << "Geschwindigkeit "
			<< std::setw(15) << "Gesamtverbrauch"
			<< std::setw(13) << "Tankinhalt"
			//<< std::setw(14) << "Tankvolumen"
			<< std::endl << "-----------------------------------------------------------------------------------------------------"<<std::endl;

}


//Funktion um die Daten zu drucken   4.2.4
void Fahrzeug::vAusgeben() const{//-----------------------
	cout<<std::left<<std::setw(5)<<p_iID<<
		  std::left << std::setw(10) <<std::setiosflags(std::ios::left)<< p_sName <<std::resetiosflags(std::ios::left)<<
		  std::right << std::setw(20) << std::fixed << std::setprecision(2) << p_dMaxGeschwindigkeit << //Permite definir cuántos dígitos decimales se mostrarán en la salida.
		  std::right << std::setw(20) << std::fixed << std::setprecision(2) << p_dGesamtStrecke<<
		  std::setw(15) << std::fixed << std::setprecision(2)  << dGeschwindigkeit();


}


//Methodenänderung initiieren, um ostream zu unterstützen. Punkt 1 von 4.4 von Aufgabe 1
void Fahrzeug::vAusgeben(std::ostream& os) const {
	//cout << std::setiosflags(std::ios::left);
	Simulationsobjekt::vAusgeben(os);
	//os << std::left << std::setw(5) << p_iID <<
			//std::left << std::setw(10) << std::setiosflags(std::ios::left)<<p_sName <<std::resetiosflags(std::ios::left)<<
		os<<std::right << std::setw(20) << std::fixed << std::setprecision(2) << p_dMaxGeschwindigkeit <<
			std::right << std::setw(20) << std::fixed << std::setprecision(2) << p_dGesamtStrecke <<
			std::setw(20) << p_dGesamtZeit << //Erweiterung für PKW-Daten
			std::setw(20) << dGeschwindigkeit();  // Aktuelle Geschwindigkeit mit Methode
}

void Fahrzeug::vKopf(std::ostream& os) { //Funktion zum Anzeigen des Headers, geändert, um ostream zu akzeptieren
	//os << std::setiosflags(std::ios::left);

	os << std::setw(17) << "ID" <<
			std::setw(18) << "Name";

	os << std::setw(25) << "MaxGeschwindigkeit" <<
			std::setw(20) << "Gesamtstrecke" <<
			// Erweitert für PKW-Daten
			std::setw(20) << "Gesamtzeit" <<
			std::setw(29) << "Geschwindigkeit" <<
			std::setw(20) << "Gesamtverbrauch" <<
			std::setw(13) << "Tankinhalt" << endl;
	os << "----------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}
// Methoden ändern, um ostream zu unterstützen. Punkt 1 von 4.4 von Aufgabe 1



// Funktion zur Simulation der Fortbewegung des Fahrzeugs
void Fahrzeug::vSimulieren() { //4.2.8
    if (p_dZeit < dGlobaleZeit) { //Die globale Simulationszeit wird mit der letzten Simulationszeit verglichen
    	const double dDifZeit = dGlobaleZeit - p_dZeit; //Se calcula la diferencia del tiempo global con el tiempo de la última simulación del vehículo
    			//Ahora se calcula la distancia con la función dStrecke de la clase Verhalten y depende del estado del vehículo
    			const double dDistancia = p_pVerhalten->dStrecke(*this, dDifZeit);
    			//const double dVelocidadActual = dGeschwindigkeit();  // Velocidad dinámica del punto 3 del tema 4.3
    			//p_dGesamtStrecke += (dVelocidadActual * dDifZeit); //Se calcula la distancia recorrida respecto a la diferencia de tiempo y considerando la velocidad actual del vehículo
    			p_dGesamtStrecke += dDistancia; // Actualiza distancia total del vehículo
    			p_dAbschnittStrecke += dDistancia; // Actualiza distancia total del vehículo en el camino
    			p_dGesamtZeit += dDifZeit; //Al tiempo total de conducción se acumula la diferencia del tiempo
    			p_dZeit = dGlobaleZeit; //Se actualiza el tiempo de la última simulación con el tiempo Global para las siguientes simulaciones
    }

    	/*
    	// Wenn dieser kleiner oder gleich ist, bedeutet dies, dass er bereits simuliert wurde und die Funktion verlässt, ohne weitere Berechnungen durchzuführen
    	const double dAktuelleGeschwindigkeit = dGeschwindigkeit();  // Dynamische Geschwindigkeit aus Punkt 3 von Thema 4.3
        const double dZeitdifferenz = dGlobaleZeit - p_dZeit; //Es wird die Differenz zwischen der globalen Zeit und dem Zeitpunkt der letzten Fahrzeugsimulation berechnet
        //double dStrecke = p_dMaxGeschwindigkeit * dZeitdifferenz;  //Die zurückgelegte Strecke wird unter Berücksichtigung der Zeitdifferenz und unter Berücksichtigung der aktuellen Geschwindigkeit des Fahrzeugs berechnet
        p_dGesamtStrecke += (dAktuelleGeschwindigkeit* dZeitdifferenz);
        p_dGesamtZeit += dZeitdifferenz; //Die Zeitdifferenz wird zur Gesamtfahrzeit addiert
        p_dZeit = dGlobaleZeit; }//Die Zeit der letzten Simulation wird mit der globalen Zeit für die folgenden Simulationen aktualisiert
    */
    }

// Implementierung von dTanken für Fahrzeuge ohne Kraftstofftank
double Fahrzeug::dTanken (double dMenge) {
	return 0.0;

}

// Methode zur Berechnung der aktuellen Geschwindigkeit von Abschnitt 4.3 Punkt 3 von Aufgabe 1 (Standard: Höchstgeschwindigkeit)
double Fahrzeug::dGeschwindigkeit() const {
    return p_dMaxGeschwindigkeit;
}


// Überladung des <<-Operators   //////
std::ostream& operator<<(std::ostream& os, const Fahrzeug& fz) {
    fz.vAusgeben(os); // Rufen Sie die virtuelle Funktion auf Rückkehr zum Betriebssystem;
    return os;
}

//////////
// Überladung des <-Operators
bool Fahrzeug::operator<(const Fahrzeug& other) const {
    return this->p_dGesamtStrecke < other.p_dGesamtStrecke;
}


////////////////// 4.4.5
Fahrzeug& Fahrzeug::operator=(const Fahrzeug& other){
	if(this != &other){//Es wird Sie fragen, ob es sich um dasselbe Objekt handelt
		p_sName =other.p_sName; // Kopiere den Namen
		p_dMaxGeschwindigkeit = other.p_dMaxGeschwindigkeit; //die Max Geschwindigkeit kopieren
		//p_dGesamtStrecke = other.p_dGesamtStrecke;// die Gesamt Strecke kopieren
		//p_dGesamtZeit = other.p_dGesamtZeit; //die Gesamt Zeit kopieren
		//p_dZeit = other.p_dZeit; //der Datei der andere Simulation kopieren
	}

	return *this;
}

void Fahrzeug::setVerhalten(std::unique_ptr<Verhalten>verhalten){
	p_pVerhalten=std::move(verhalten);
}

void Fahrzeug::vNeueStrecke(Weg& weg) {
	p_pVerhalten = std::make_unique<Fahrend>(weg); // Erstellen Sie eine neue Instanz des „Gehen“-Verhaltens, das mit dem neuen Pfad verknüpft ist
	p_dAbschnittStrecke = 0.0;// Distanz auf neuem Pfad zurücksetzen
	// Optional: Ortszeit des Fahrzeugs zurücksetzen
	p_dZeit = dGlobaleZeit;
}

void Fahrzeug::vNeueStrecke(Weg& weg, double dStartzeit){
	p_pVerhalten = std::make_unique<Parkend>(weg, dStartzeit);
	p_dAbschnittStrecke = 0.0;
	p_dZeit = dGlobaleZeit;
}

void Fahrzeug::vZeichnen(const Weg& weg) const{

}

bool Fahrzeug::operator==(const Fahrzeug& other) const {
    return this->p_iID == other.p_iID;// Vergleichen anhand eindeutiger ID
}

// Legen Sie die insgesamt zurückgelegte Strecke fest
void Fahrzeug::setGesamtStrecke(double dStrecke) {
    if (dStrecke >= 0.0) {
        p_dGesamtStrecke = dStrecke;
    } else {
        std::cerr << "Fehler: Die Gesamtentfernung darf nicht negativ sein.\n";
    }
}

// Setzt die Distanz der aktuellen Etappe
void Fahrzeug::setAbschnittStrecke(double dStrecke) {
    if (dStrecke >= 0.0) {
        p_dAbschnittStrecke = dStrecke;
    } else {
        std::cerr << "Fehler: Die Abschnittentfernung darf nicht negativ sein.\n";
    }
}

// Gesamtfahrzeit festlegen
void Fahrzeug::setGesamtZeit(double dZeit) {
    if (dZeit >= 0.0) {
    	p_dGesamtZeit = dZeit;
    } else {
        std::cerr << "Fehler: Die GesamtZeit darf nicht negativ seina.\n";
    }
}


