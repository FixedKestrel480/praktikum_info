/*
 * Kreuzung.h
 *
 *  Created on: Jan 15, 2025
 *      Author: Karime Soriano
 */

#ifndef KREUZUNG_H_
#define KREUZUNG_H_
#include "Simulationsobjekt.h"
//#include "Weg.h"
#include <list>
#include <memory>
//#include "Fahrzeug.h"
#include "Tempolimit.h"

class Weg;
class Fahrzeug;
using namespace std;

class Kreuzung: public Simulationsobjekt {
private:
	std::list<std::shared_ptr<Weg>> p_pWege;
    double p_dTankstelle; // Menge an Kraftstoff, die zum Betanken von durchfahrenden PKW-Fahrzeugen zur Verfügung steht.

public:

	Kreuzung(const std::string& name, double tankstelle=0.0);
	virtual ~Kreuzung();
	void vTanken(Fahrzeug& fahrzeug);
	static void vVerbinde(const string& sNameHinweg,
			const string& sNameRueckweg,
			double dLaenge,
			std::shared_ptr<Kreuzung> pStart,
			std::shared_ptr<Kreuzung> pZiel,
			Tempolimit eTempolimit);
	void vAusgeben(std::ostream& os) const override;
	void vSimulieren() override;
	static void vKopf(std::ostream& os);

	// Zugriff auf die Liste der Pfade
	const std::list<std::shared_ptr<Weg>>& getWege() const { return p_pWege; }
	//Fahrzeuge auf dem ersten verfügbaren Weg platzieren
	void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double startzeit = 0.0);
	std::shared_ptr<Weg> pZufaelligerWeg(Weg& vorherigerWeg);
	double getTankstelle() const { return p_dTankstelle; }

};
// Überladen des <<-Operators (außerhalb der Klasse)
std::ostream& operator<<(std::ostream& os, const Kreuzung& kz);
#endif /* KREUZUNG_H_ */
