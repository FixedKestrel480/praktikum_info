/*
 * Kreuzung.cpp
 *
 *  Created on: Jan 15, 2025
 *      Author: Karime Soriano
 */

#include "Kreuzung.h"
#include "PKW.h"
#include <iostream>
#include "Weg.h"
#include <random>
Kreuzung::Kreuzung(const std::string& name, double tankstelle)
 : Simulationsobjekt(name), p_dTankstelle(tankstelle) {}

void Kreuzung::vTanken(Fahrzeug& fahrzeug){
    auto pPKW = dynamic_cast<PKW*>(&fahrzeug);
    if (pPKW && p_dTankstelle > 0.0) {
           double dGetankt = pPKW->dTanken(); //PKW-Tank füllen
           p_dTankstelle -= dGetankt; //Die Stationskapazität wird reduziert
           std::cout << "El PKW " << fahrzeug.getName() << " le abastecieron " << dGetankt
                     << " litros en el cruce " << getName() << ".\n";
       }
}
Kreuzung::~Kreuzung() {
	// TODO Auto-generated destructor stub
}

void Kreuzung::vSimulieren(){
	 for (const auto& weg : p_pWege) {
	        weg->vSimulieren();
	    }
}
////

void Kreuzung::vVerbinde(const std::string& sNameHinweg,
        const std::string& sNameRueckweg,
        double  dLaenge,
        std::shared_ptr<Kreuzung> pStart,
        std::shared_ptr<Kreuzung> pZiel,
        Tempolimit eTempolimit){

	//Erstelle zwei Pfade
	auto hinWeg = std::make_shared<Weg>(sNameHinweg,dLaenge,eTempolimit);
	auto rueckWeg = std::make_shared<Weg>(sNameRueckweg,dLaenge,eTempolimit);


	// Pfade müssen einander bekannt sein (direkter Verweis auf den Gegenpfad).
	hinWeg->setRueckweg(rueckWeg);
	rueckWeg->setRueckweg(hinWeg);

	// Zuordnung der Wege zu den Kreuzungen
	pStart->p_pWege.push_back(hinWeg);
	pZiel->p_pWege.push_back(rueckWeg);

	// Zielkreuzung setzen
	hinWeg->setZiel(pZiel);
	rueckWeg->setZiel(pStart);
}

void Kreuzung::vAusgeben(std::ostream& os) const {
    Simulationsobjekt::vAusgeben(os);
    os << " | " << p_dTankstelle << " litros | ";
    //os << "Camino: ";
    for (const auto& weg : p_pWege) {
        os << weg->getName() << " ";
    }
    //os << "\n";
}

void Kreuzung::vKopf(std::ostream& os) {
    os << "Cruce | Gasolinera | Camino(s)\n";
    os << "----------------------------------\n";
}
/////
void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double startzeit) {
    vTanken(*fahrzeug);// Versucht man, das Fahrzeug aufzutanken

    if (!p_pWege.empty()) {
    	// In den ersten Pfad der Liste einfügen
    	if (auto primerWeg = p_pWege.front()) {
    		if (startzeit>0.0) {
    			primerWeg->vAnnahme(std::move(fahrzeug), startzeit);
    		}
			else {
				primerWeg->vAnnahme(std::move(fahrzeug));
			}
    	} else {
    	    std::cerr << "Fehler: Der Pfad ist nicht richtig konfiguriert.\n";
    	}
    }
}
////
std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& vorherigerWeg){
	std::list<std::shared_ptr<Weg>> moglicheWege;
	for(const auto& weg:p_pWege){
		if(weg != vorherigerWeg.getRueckweg()){
			moglicheWege.push_back(weg);
		}

	}
	if(moglicheWege.empty()){
		return vorherigerWeg.getRueckweg();
	}
	// Wähle einen zufälligen Pfad
	static std::mt19937 rng(0);
	std::uniform_int_distribution<size_t> distribucion(0, moglicheWege.size() - 1);
	auto it = moglicheWege.begin();
	std::advance(it, distribucion(rng));
	return *it;
}

std::ostream& operator<<(std::ostream& os, const Kreuzung& kz) {
	kz.vAusgeben(os); 	// Methode vAusgeben aufrufen
    return os;
}

