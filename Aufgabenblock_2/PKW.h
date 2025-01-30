/*
 * PKW.h
 *
 *  Created on: Nov 14, 2024
 *      Author: Karime Soriano
 */

#ifndef PKW_H_
#define PKW_H_
#include "Fahrzeug.h"
#include <limits>


//4.3.1

class PKW: public Fahrzeug{
public:
	PKW(string sName,double dmaxGeschwindigkeit);
	PKW(string sName, double dmaxGeschwindigkeit,double p_dVerbrauch, double p_dTankvolumen=55.0);
	~PKW() override;
	void vSimulieren() override; //Überschreibt die PKW-spezifische Simulation
	void vAusgeben() const override; // Überschreibt der Ausgabefunktion, es el que ocupamos para que la salida sea a consola
	void vAusgeben(std::ostream&os)const override; //////////////////// Überschreibt PKW-spezifische Ausgabe, geändert zur Unterstützung von ostream


	// Überschreibt der dTanken-Füllfunktion für PKW
	double dTanken(double dMenge = std::numeric_limits<double>::infinity()); //4.3.2
	double dGeschwindigkeit() const override;


private: // Die in Punkt 2 von 4.3 geforderten Variablen sind enthalten.
    double p_dVerbrauch=0.0;    // Verbrauch in Liter pro 100 km
    double p_dTankvolumen=55.0;  // Maximales Tankvolumen (Liter)
    double p_dTankinhalt=0.0;// Aktuelle Inhalt im Tank (Liter)
    double p_dGesamtverbrauch=0.0; // Gesamtkraftstoffverbrauch (in Litern)
};




#endif /* PKW_H_ */
