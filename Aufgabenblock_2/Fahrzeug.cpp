/*
 * Fahrzeug.cpp
 *
 *  Created on: Nov 9, 2024
 *      Author: Karime Soriano
 */

#include "Fahrzeug.h"
#include <iostream>
#include <iomanip> //Aufgabe 1 Punkt 6
#include "PKW.h"
using std::cout;
using std::endl;

//4.2.6
extern double dGlobaleZeit;//Globale Simulationszeitvariable, deklariert in main.cpp


//Fahrzeuganzahl
int Fahrzeug::p_iMaxID = 0; //Aufgabenblock 1. 4.2 Punkt 3

//Aufgabenblock 1 punkt 3
// Constructor por defecto

Fahrzeug::Fahrzeug()// 4.2.3, 4.2.5 //si las dos sumas de p_imaxid estuvieran adelante, no funcionaria, porque te daría primero el valor de pmaxid antes de incrementarlo, sería 0
    : p_sName(" "), p_iID(++p_iMaxID), p_dMaxGeschwindigkeit(0.0),
      p_dGesamtStrecke(0.0), p_dGesamtZeit(0.0), p_dZeit(0.0) { //Standardkonstruktor eines Fahrzeugs, der dem Namen „“ zuweist, der ID den Wert von p_iMaxID zuweist und p_iMaxID um 1 inkrementiert
	vOutput();//Funktion zum Drucken von Fahrzeugdaten beim Bau
}

//Konstruktor mit Name als Parameter
//sobrecarga de constructores, cuando en el mismo constructor puedes tener varias alternativas, y dependiendo de  los parametros que te manden va a ser diferente.
//Aufgabenblock 1 Punkt 3
Fahrzeug::Fahrzeug(const std::string& sName) //4.2.3, 4.2.5
   : p_sName(sName), p_iID(++p_iMaxID), p_dMaxGeschwindigkeit(0.0), p_dGesamtStrecke(0.0), p_dGesamtZeit(0.0), p_dZeit(0.0){ //Konstruktor: Wenn der Name des Fahrzeugs, der p_sName zugewiesen ist, als Parameter übergeben wird, wird der ID der Wert von p_iMaxID zugewiesen und p_iMaxID wird um 1 erhöht
    vOutput();
}
// Konstruktor mit Name und max Geschwindigkeit
//Aufgabe 1, 4.2.5
Fahrzeug::Fahrzeug(const std::string& sName, double dMaxGeschwindigkeit)
//Konstruktor: Wenn sie als Parameter den Namen des Fahrzeugs übergeben, das p_sName zugewiesen ist, wird der ID der Wert von p_iMaxID zugewiesen, p_iMaxID wird um 1 erhöht und die maximale Geschwindigkeit wird festgelegt
   : p_sName(sName), p_iID(++p_iMaxID),p_dMaxGeschwindigkeit(dMaxGeschwindigkeit > 0 ? dMaxGeschwindigkeit : 0.0),p_dGesamtStrecke(0.0), p_dGesamtZeit(0.0), p_dZeit(0.0) {
	//Überprüfen Sie, ob die Geschwindigkeit größer als 0 ist. Wenn ja, verwenden Sie den eingegebenen Wert, andernfalls setzen Sie den Wert auf 0
    cout << "Fahrzeug mit ID " << p_iID << " und Name " << p_sName << "\" mit Maximalgeschwindigkeit " << p_dMaxGeschwindigkeit << " erstellt." << endl;
}
//Aufgabe 1 Punkt 3
//Destruktor
Fahrzeug::~Fahrzeug() { //4.2.3,
    cout << "Fahrzeug mit ID " << p_iID << " und Name " << p_sName << "\" gelöscht." << endl;
}
void Fahrzeug::vOutput()	{ //Funktion, die die Daten des Fahrzeugobjekts für Aufgabe 1 Punkt 3 druckt
	cout << "Fahrzeug "<<p_sName<<" mit ID " << p_iID << " war erstellt." << endl;
}

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

	os << std::left << std::setw(5) << p_iID <<
			std::left << std::setw(10) << std::setiosflags(std::ios::left)<<p_sName <<std::resetiosflags(std::ios::left)<<
			std::right << std::setw(20) << std::fixed << std::setprecision(2) << p_dMaxGeschwindigkeit <<
			std::right << std::setw(20) << std::fixed << std::setprecision(2) << p_dGesamtStrecke <<
			std::setw(20) << p_dGesamtZeit << //Erweiterung für PKW-Daten
			std::setw(20) << dGeschwindigkeit();  // Aktuelle Geschwindigkeit mit Methode
}

void Fahrzeug::vKopf(std::ostream& os) { //Funktion zum Anzeigen des Headers, geändert, um ostream zu akzeptieren
	//os << std::setiosflags(std::ios::left);

	os << std::setw(0) << "ID" <<
			std::setw(7) << "Name";

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
    	// Wenn dieser kleiner oder gleich ist, bedeutet dies, dass er bereits simuliert wurde und die Funktion verlässt, ohne weitere Berechnungen durchzuführen
    	const double dAktuelleGeschwindigkeit = dGeschwindigkeit();  // Dynamische Geschwindigkeit aus Punkt 3 von Thema 4.3
        const double dZeitdifferenz = dGlobaleZeit - p_dZeit; //Es wird die Differenz zwischen der globalen Zeit und dem Zeitpunkt der letzten Fahrzeugsimulation berechnet
        //double dStrecke = p_dMaxGeschwindigkeit * dZeitdifferenz;  //Die zurückgelegte Strecke wird unter Berücksichtigung der Zeitdifferenz und unter Berücksichtigung der aktuellen Geschwindigkeit des Fahrzeugs berechnet
        p_dGesamtStrecke += (dAktuelleGeschwindigkeit* dZeitdifferenz);
        p_dGesamtZeit += dZeitdifferenz; //Die Zeitdifferenz wird zur Gesamtfahrzeit addiert
        p_dZeit = dGlobaleZeit; }//Die Zeit der letzten Simulation wird mit der globalen Zeit für die folgenden Simulationen aktualisiert
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
		p_dGesamtStrecke = other.p_dGesamtStrecke;// die Gesamt Strecke kopieren
		p_dGesamtZeit = other.p_dGesamtZeit; //die Gesamt Zeit kopieren
		p_dZeit = other.p_dZeit; //der Datei der andere Simulation kopieren
	}


	return *this;
}
