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
using std::string;


class Fahrzeug { //Klasse Fahrzeug mit ein Name und eine unique ID
protected:
	//Aufgabenblock 1. Startpunkt 3
	string p_sName;  //Attribut, das den Namen des Fahrzeugs enthält. Es ist "protected", sodass von Unterklassen aus darauf zugegriffen werden kann
//punkt 3 Aufgabe 1

private:
    static int p_iMaxID;  //Attribut der Klasse zur Aufnahme der maximalen Fahrzeuganzahl
//Konstantes Attribut, dessen Wert beim Erstellen festgelegt wird und sich nicht ändert, da es für jedes Objekt eindeutig ist
    const int p_iID;
//Aufgabenblock 1. Endpunkt 3

protected:// Attribute, die für Unterklassen für bestimmte Berechnungen oder Simulationen als zugänglich gelten. Aufgabe 1 Abschnitt 4.3 Punkt 1
    //Start-Aufgabe 1 Punkt 4.4.5
    double p_dMaxGeschwindigkeit; //Maximum Geschwindigkeit der Fahrzeug  ;
    double p_dGesamtStrecke=0.0;         // Totale strecke der Fahrzeug
    double p_dGesamtZeit=0.0;            // Totale zeit
    double p_dZeit=0.0; //Zeit der letzte Simulation
    //Aufgabe 1 Punkt 4 beenden

public: // se pueden definir objetos dentro de public
    //Aufgabenblock 1. Ende 4.4 Punkt 3
    //Konstruktor
    Fahrzeug();  // Standardkonstruktor
	Fahrzeug(const string& sName);  // Benannter Konstruktor, dies hat die Standardgeschwindigkeit von 0
	Fahrzeug(const string& sName, double dMaxGeschwindigkeit); // Konstruktor mit Namen und maximaler Geschwindigkeit, Sie können die gewünschte Geschwindigkeit einstellen
	Fahrzeug(const Fahrzeug&) = delete; // Kopierkonstruktor verbieten  4.4.5
	void vOutput();//Funktion, die die Daten des Fahrzeugobjekts druckt
	const string& getName() const { return p_sName; } //Zugriff auf die Namensdaten von der main aus

	//Destruktor 4.2.3
    virtual ~Fahrzeug(); //Zerstörer des Fahrzeugobjekts

    //Starte Aufgabe 1 4.2.6
    //Funktion
    virtual void vAusgeben()const; //Funktion zur Anzeige spezifischer Daten für ein Fahrzeug. „Virtuell“ hinzugefügt, damit es überschrieben werden kann
    static void vKopf(); //Funktion für die Tabelle
//Ende Aufgabe 1 PUnkt 6

    //Methodenänderung initiieren, um ostream zu unterstützen. Punkt 1 von 4.4 von Aufgabe 1
    static void vKopf(std::ostream& os); // Geändert, um ostream zu akzeptieren
    virtual void vAusgeben(std::ostream& os) const;
    //end hat die Methoden geändert, um ostream zu unterstützen. Punkt 1 von 4.4 von Aufgabe 1

    //4.2.7
    virtual void vSimulieren(); //Funktion, die für die Simulation verwendet wird. „Virtuell“ hinzugefügt, damit es überschrieben werden kann

    // Aufgabe 1 Abschnitt 4.3 Punkt 2. Die dTanken-Funktion wird erstellt, die das Nachfüllen von Kraftstoff zum Fahrzeug darstellt
    virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());
    // Methode zur Berechnung der aktuellen Geschwindigkeit von Abschnitt 4.3 Punkt 3 von Aufgabe 1 (Standard: Höchstgeschwindigkeit)
	virtual double dGeschwindigkeit() const;

	//4.4.4
	bool operator<(const Fahrzeug& other) const; // Operatorüberladung <
	Fahrzeug& operator=(const Fahrzeug& other); // Man definiert einen benutzerdefinierten Zuweisungsoperator, um nur einige relevante Attribute zu kopieren
};


// Überladen des <<-Operators (außerhalb der Klasse)
std::ostream& operator<<(std::ostream& os, const Fahrzeug& fz);




#endif /* FAHRZEUG_H_ */
