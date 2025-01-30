/*
 * Verhalten.cpp
 *
 *  Created on: Dec 11, 2024
 *      Author: Karime Soriano
 */

#include "Verhalten.h"
#include "Fahrzeug.h"

Verhalten::Verhalten(const Weg& weg):p_rWeg(weg){
  //constructor vacio
}

Verhalten::~Verhalten(){

}

double Verhalten::dStrecke(Fahrzeug& fahrzeug, double dZeitIntervall) {
	double dMaxStrecke = fahrzeug.dGeschwindigkeit() * dZeitIntervall;// Berechnet man die maximale Entfernung, die das Fahrzeug in der vorgegebenen Zeit zurücklegen kann
    double dStreckeRest = p_rWeg.getLaenge() - fahrzeug.getAbschnittStrecke(); // Berechnet man die verbleibende Distanz auf dem aktuellen Pfad
    // Wenn die verbleibende Distanz größer als 0 ist, berechne das Minimum zwischen der maximalen und der verbleibenden Distanz
	if (dStreckeRest > 0) {
		return std::min(dMaxStrecke, dStreckeRest);
	} else {
		// Benachrichtigen, dass das Fahrzeug das Ende der Straße erreicht hat
		std::cout << "Der Fahrzeug" << fahrzeug.getName() << "ist am Ende des Weges angekommen: "
				  << p_rWeg.getName() << std::endl;
		return 0.0;
	}
}


