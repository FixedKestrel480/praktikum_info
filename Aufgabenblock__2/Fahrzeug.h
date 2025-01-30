/*
 * Fahrzeug.h
 *
 *  Created on: Nov 9, 2024
 *      Author: Karime Soriano
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_
#include <iostream> //Für output und input
#include <string> // Für std::string
#include <limits>
#include <iomanip>
using std::string;
#include "Simulationsobjekt.h"
#include "Verhalten.h"

class Weg;

class Fahrzeug : public Simulationsobjekt{ //Klasse Fahrzeug mit ein Name und eine unique ID

protected:// Attribute, die für Unterklassen für bestimmte Berechnungen oder Simulationen als zugänglich gelten. Aufgabe 1 Abschnitt 4.3 Punkt 1
    //Start-Aufgabe 1 Punkt 4.4.5
    double p_dMaxGeschwindigkeit; //Maximum Geschwindigkeit der Fahrzeug  ;
    double p_dGesamtStrecke=0.0;         // Totale strecke der Fahrzeug
    double p_dGesamtZeit=0.0;            // Totale zeit
    //double p_dZeit=0.0; //Zeit der letzte Simulation
    std::unique_ptr<Verhalten> p_pVerhalten; // Comportamiento del vehículo 5.4.1----------------------------
    double p_dAbschnittStrecke; //Atributo de distancia en el camino actual
    //Aufgabe 1 Punkt 4 beenden

public: // se pueden definir objetos dentro de public
    //Aufgabenblock 1. Ende 4.4 Punkt 3
    //Konstruktor
    Fahrzeug();  // Standardkonstruktor
	Fahrzeug(const string& sName);  // Benannter Konstruktor, dies hat die Standardgeschwindigkeit von 0
	Fahrzeug(const string& sName, double dMaxGeschwindigkeit); // Konstruktor mit Namen und maximaler Geschwindigkeit, Sie können die gewünschte Geschwindigkeit einstellen
	Fahrzeug(const Fahrzeug&) = delete; // Kopierkonstruktor verbieten  4.4.5
	//void vOutput();//Funktion, die die Daten des Fahrzeugobjekts druckt
	//const string& getName() const { return p_sName; } //Zugriff auf die Namensdaten von der main aus

	~Fahrzeug() override = default; // Destructor por defecto de Simulationsobjekt
	//virtual ~Fahrzeug(); //Destructor del objeto vehículo

	//const std::string& getName() const { return p_sName; } //Se elimina porque se implementa en Simulationsobjekt

	static void vKopf();
	virtual void vAusgeben() const;
	static void vKopf(std::ostream& os);
	void vAusgeben(std::ostream& os) const override; //Virtual wird entfernt und Override wird für reine Simulationsobjekt-Methode hinzugefügt
	void vSimulieren() override; //Virtual wird entfernt und Override wird für reine Simulationsobjekt-Methode hinzugefügt
	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());
	virtual double dGeschwindigkeit() const;
	bool operator<(const Fahrzeug& other) const;
	Fahrzeug& operator=(const Fahrzeug& other);
	double getGesamtStrecke() const { return p_dGesamtStrecke; }; //Gibt die vom Fahrzeug zurückgelegte Gesamtstrecke zurück
	void setVerhalten(std::unique_ptr<Verhalten> verhalten); // Fahrzeugverhalten einstellen 5.4.1
	void vNeueStrecke(Weg& weg); //Neue Strecke--------------------------
	void vNeueStrecke(Weg& weg, double dStartzeit); //Neuer Weg für geparktes Fahrzeug
	double getAbschnittStrecke() const { return p_dAbschnittStrecke; }
	virtual void vZeichnen(const Weg& weg) const; //5.6.3
	Verhalten* getVerhalten() {return p_pVerhalten.get();}
	bool operator==(const Fahrzeug& other) const;
	void setGesamtStrecke(double dStrecke);
	void setAbschnittStrecke(double dStrecke);
	double getGesamtZeit() const { return p_dGesamtZeit; };//Gibt die gesamte Fahrzeit zurück
	void setGesamtZeit(double dZeit);
};


// Überladen des <<-Operators (außerhalb der Klasse)
std::ostream& operator<<(std::ostream& os, const Fahrzeug& fz);




#endif /* FAHRZEUG_H_ */
