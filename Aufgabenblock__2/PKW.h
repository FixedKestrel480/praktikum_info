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
	void vSimulieren() override; //Beschreibt die PKW-spezifische Simulation
	void vAusgeben() const override; //Ausgabe der Ausgabefunktion, die wir für die Ausgabe auf der Konsole verwenden.
	void vAusgeben(std::ostream&os)const override; //////////////////// Überschreibt PKW-spezifische Ausgabe, geändert zur Unterstützung von ostream
	//void vZeichnen(const Weg& weg)const override;

	// Überschreibt der dTanken-Füllfunktion für PKW
	double dTanken(double dMenge = std::numeric_limits<double>::infinity()); //4.3.2
	double dGeschwindigkeit() const override;
	double getTankinhalt() const { return p_dTankinhalt;	}
	void vZeichnen(const Weg& weg) const override;
	double getVerbrauch() const { return p_dVerbrauch;	} // Kraftstoffverbrauch ermitteln
	void setTankinhalt(double dTank);     // Tankfüllstand aktualisieren
	void setGesamtVerbrauch(double dTank);      // Gesamtkraftstoffverbrauch aktualisieren
	double getGesamtVerbrauch() const { return p_dGesamtverbrauch;	} // Den gesamten Kraftstoffverbrauch ermitteln



private: // Die in Punkt 2 von 4.3 geforderten Variablen sind enthalten.
    double p_dVerbrauch=0.0;    // Verbrauch in Liter pro 100 km
    double p_dTankvolumen=55.0;  // Maximales Tankvolumen (Liter)
    double p_dTankinhalt=0.0;// Aktuelle Inhalt im Tank (Liter)
    double p_dGesamtverbrauch=0.0; // Gesamtkraftstoffverbrauch (in Litern)
};




#endif /* PKW_H_ */
