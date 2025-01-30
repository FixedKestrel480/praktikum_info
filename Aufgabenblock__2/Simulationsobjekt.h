/*
 * Simulationsobjekt.h
 *
 *  Created on: Dec 5, 2024
 *      Author: Karime Soriano
 */

#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_
#include <iostream> //Für output und input
#include <string> // Für std::string
#include <limits>
using std::string;
class Simulationsobjekt{
protected:
    string p_sName;
    double p_dZeit;
    const int p_iID;

private:
    static int p_iMaxID;  //Attribut der Klasse zur Aufnahme der maximalen Fahrzeuganzahl
//Konstantes Attribut, dessen Wert beim Erstellen festgelegt wird und sich nicht ändert, da es für jedes Objekt eindeutig ist

//Aufgabenblock 1. Endpunkt 3

public:
	Simulationsobjekt();
	Simulationsobjekt(const string& sName);
	virtual ~Simulationsobjekt();
	virtual void vAusgeben(std::ostream& os) const=0;  // Methode zum Drucken von ID und Name
	virtual void vSimulieren() = 0;
	const string& getName() const { return p_sName; }

	//5.3.1
	bool operator==(const Simulationsobjekt& other) const; // Objekte nach ID vergleichen

	Simulationsobjekt(const Simulationsobjekt&) = delete;  // Kopierkonstruktor verbieten
	Simulationsobjekt& operator=(const Simulationsobjekt&) = delete;//Das bedeutet, dass Sie ein Simulationsobjekt keinem bestehenden Objekt zuweisen können.


};

std::ostream& operator<<(std::ostream& os, const Simulationsobjekt& fz);


#endif /* SIMULATIONSOBJEKT_H_ */
