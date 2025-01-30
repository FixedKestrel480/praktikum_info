/*
 * Weg.cpp
 *
 *  Created on: Dec 7, 2024
 *      Author: Karime Soriano
 */

#include "Weg.h"
#include "Fahrzeug.h" //Um zirkuläre Abhängigkeiten zu vermeiden
#include "Fahrausnahme.h"
#include <iostream>
#include <iomanip>
#include "vertagt_liste - Vorlage.h" // Fügt man die VListe-Vorlage ein
#include "vertagt_aktion - Vorlage.h" // Fügt man die VListe-Vorlage ein



Weg::Weg() //Standardkonstruktor, unbenannt, 0 km lang und keine Geschwindigkeitsbeschränkungen
    : Simulationsobjekt(""), p_dLaenge(0.0), p_eTempolimit(Tempolimit::Autobahn) {
}

Weg::Weg(const std::string& sname, double dlaenge, Tempolimit tempolimit, std::shared_ptr<Kreuzung> pZiel)
: Simulationsobjekt(sname), p_dLaenge(dlaenge), p_eTempolimit(tempolimit){

}

void Weg::vSimulieren() { ////
	//std::cout<<"Simulation Strecke:"<<p_sName<<std::endl;
	// Simuliert jedes Fahrzeug auf der Straße
	p_pFahrzeuge.vAktualisieren(); //5.7.3
	for (auto& fahrzeug : p_pFahrzeuge) {
		try{ //5.5.1
			fahrzeug->vSimulieren();
			fahrzeug->vZeichnen(*this);
		}catch(Fahrausnahme& ex){
			ex.vBearbeiten();
		}
    }
	p_pFahrzeuge.vAktualisieren();
}

void Weg::vAusgeben(std::ostream& os) const {
	Simulationsobjekt::vAusgeben(os);
	// Drucke die Länge des Pfades
	os <<  std::setw(6) << p_dLaenge ;
	// Drucke die Namen der Fahrzeuge auf dem Weg in Klammern
	os << " (";
	bool erste = true;
	for (const auto& fahrzeug : p_pFahrzeuge) {
		if (!erste) { //prüft, ob ein Fahrzeug gedruckt wurde, wenn es bereits gedruckt wurde, wird beim nächsten ein Komma hinzugefügt
			os << ", ";
		}
		os << fahrzeug->getName();
		erste = false;
	}
	os << ")";
}

double Weg::getTempolimit() const {
    switch (p_eTempolimit) {
        case Tempolimit::Innerorts:
            return 50.0;
        case Tempolimit::LandstraBe:
            return 100.0;
        case Tempolimit::Autobahn:
            return std::numeric_limits<double>::max(); //Gibt die größte positive endliche Zahl zurück, die einen doppelten Wert hat
        default:
        	return 0.0;
    }
}


void Weg::Fahrzeughinfuegen(std::unique_ptr<Fahrzeug> fahrzeug) {
    p_pFahrzeuge.push_back(std::move(fahrzeug));
}

void Weg::vKopf(std::ostream& os){
	//os << std::setiosflags(std::ios::left);
	os 	<< std::setw(9) << "ID" << "|"
		<< std::setw(17) << "Name" << "|"
		<< std::setw(12) << "Laenge" << "|"
		<< "Fahrzeuge" << std::endl;
	 os << "-----------------------------------------------" << std::endl;
}


//5.4.2
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug) {//------------------------------------
	// Benachrichtigt das Fahrzeug, dass es sich auf einem neuen Weg befindet
    fahrzeug->vNeueStrecke(*this);
    p_pFahrzeuge.push_back(std::move(fahrzeug)); // Fahrzeug mit std::move zur Fahrzeugliste hinzufügen

}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug,double dStartzeit){
	fahrzeug->vNeueStrecke(*this, dStartzeit);
	p_pFahrzeuge.push_front(std::move(fahrzeug));
}

std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fahrzeug){
	for(auto it= p_pFahrzeuge.begin(); it!=p_pFahrzeuge.end();++it){
		if(*it &&**it == fahrzeug){
			//*it: Abres la caja que estás revisando (esto te da el puntero único a la caja actual).
			//**it: Sacas el juguete de la caja para mirar si es el que estás buscando.
			std::unique_ptr<Fahrzeug> pFzg = std::move(*it); // Bewegt man den einzelnen Zeiger
			p_pFahrzeuge.erase(it); //Entfernt man das Element aus der Liste
			return pFzg; // Gelöschtes Fahrzeug zurückgeben
		}
	}
	return nullptr;
}

void Weg::setRueckweg(std::shared_ptr<Weg> rueckweg) {
    p_rueckweg = rueckweg;
}

void Weg::setZiel(std::shared_ptr<Kreuzung> ziel) {
    p_zielKreuzung = ziel;
}

// werden ausgeführt, bevor die Simulation oder andere Vorgänge fortgesetzt werden.
void Weg::vAktualisierenFahrzeuge() {
    p_pFahrzeuge.vAktualisieren();
}

// Überladen des <<-Operators (außerhalb der Klasse)
std::ostream& operator<<(std::ostream& os, const Weg& weg) {
    weg.vAusgeben(os); // Methode vAusgeben aufrufen
    return os;
}
