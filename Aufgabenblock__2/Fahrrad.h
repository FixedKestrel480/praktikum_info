/*
 * Fahrrad.h
 *
 *  Created on: Nov 14, 2024
 *      Author: Karime Soriano
 */

#ifndef FAHRRAD_H_
#define FAHRRAD_H_
#include "Fahrzeug.h"


//4.3.1
class Fahrrad: public Fahrzeug{
public:
	Fahrrad(const string sName, double dMaxGeschwindigkeit);
	//virtual ~Fahrrad();

	void vSimulieren() override;   // Man Überschreibt die spezifische Simulation für Fahrrad, los atributos van cambiando
	void vAusgeben() const override; // Man überschreibt die spezifische Ausgabe für Fahrrad, este no cambian, solo presenta los datos

	void vAusgeben(std::ostream& os) const override; //Modifiziert zur Unterstützung von ostream
	void vZeichnen(const Weg& weg)const override;

	double dGeschwindigkeit() const override;//Berechnung der Höchstgeschwindigkeit überschreiben  4.3.3

};



#endif /* FAHRRAD_H_ */
