/*
 * Fahrend.cpp
 *
 *  Created on: Dec 21, 2024
 *      Author: Karime Soriano
 */

#include "Fahrend.h"
#include "Fahrzeug.h"
#include "Streckende.h"
#include "PKW.h"
using std::cout;

Fahrend::Fahrend(const Weg& weg):Verhalten(weg){

}

Fahrend::~Fahrend(){

}

//5.4.2
double Fahrend::dStrecke(Fahrzeug& fahrzeug, double dZeitIntervall){
	//5.1.4
	double dMaxStrecke = fahrzeug.dGeschwindigkeit() * dZeitIntervall;
    double dStreckeRest = p_rWeg.getLaenge() - fahrzeug.getAbschnittStrecke(); // Berechnen Sie die verbleibende Distanz auf dem aktuellen Pfad
	if(dStreckeRest <= dMaxStrecke){
		//cout<<"Der Fahrzeug "<<fahrzeug.getName()<<"Ha llegado al final del camino: "<<p_rWeg.getName()<<std::endl;
		// Zurückgelegte Distanzen aktualisieren/////////////
			fahrzeug.setGesamtStrecke(fahrzeug.getGesamtStrecke() + dStreckeRest);
			fahrzeug.setAbschnittStrecke(fahrzeug.getAbschnittStrecke() + dStreckeRest);
			//Gesamtfahrzeit aktualisieren
			fahrzeug.setGesamtZeit(fahrzeug.getGesamtZeit()+dZeitIntervall);

			// Prüfen, ob das Fahrzeug ein PKW ist, um den Kraftstoffverbrauch zu aktualisieren
			auto* pkw = dynamic_cast<PKW*>(&fahrzeug);
			if (pkw) {
				double dCombustibleConsumido = (dStreckeRest / 100) * pkw->getVerbrauch();
				pkw->setGesamtVerbrauch(pkw->getGesamtVerbrauch()+dCombustibleConsumido);
				pkw->setTankinhalt(pkw->getTankinhalt() - dCombustibleConsumido);
			}

		throw Streckende(fahrzeug, const_cast<Weg&>(p_rWeg));
	}
	return std::min(dMaxStrecke,dStreckeRest);
}

