/*
 * Streckende.cpp
 *
 *  Created on: Dec 31, 2024
 *      Author: Karime Soriano
 */

#include "Streckende.h"
#include "Kreuzung.h"
#include "Fahrzeug.h"
#include <iostream>
using std::cout;
using std:: endl;
extern double dGlobaleZeit;


Streckende::Streckende(Fahrzeug& fahrzeug, Weg& weg)
		:Fahrausnahme(fahrzeug, weg) {}

Streckende::~Streckende() {
    // Destructor vacío
}

void Streckende::vBearbeiten() const {
    /*cout << "Exception: Streckende. "
              << "Fahrzeug: " << p_fahrzeug.getName()
              << ", Strecke: " << p_weg.getName() << endl;
	auto pFzg=  p_weg.pAbgabe(p_fahrzeug);
	if (pFzg) {
		std::cout << "El vehículo " << p_fahrzeug.getName()
				  << " llegó al final del camino " << p_weg.getName()
				  << " y se ha eliminado.\n";*/
	//}
	auto kreuzung = p_weg.getZiel(); // Ziel Kreuzung abrufen
	if (!kreuzung) {
		std::cerr << "Fehler: Das Ziel Kreuzung ist nicht festgelegt.\n";
		return;
	}
	// Wähle einen neuen Weg ab der Kreuzung
	auto neuesWeg = kreuzung->pZufaelligerWeg(p_weg);

	// Hol das Fahrzeug vom aktuellen Weg
	auto fahrz = p_weg.pAbgabe(p_fahrzeug);

	if(fahrz){
		kreuzung->vTanken(*fahrz);
		// Bewegt man das Fahrzeug auf den neuen Weg
		neuesWeg->vAnnahme(std::move(fahrz));
		neuesWeg->vAktualisierenFahrzeuge(); // Sofort aktualisieren, um Änderungen widerzuspiegeln
	}
	// Details der Bewegung ausdrucken
		std::cout << "ZEIT: [" << dGlobaleZeit << "]\n"
				  << "KREUZUNG: [" << kreuzung->getName()
				  << "] [Tank: " << kreuzung->getTankstelle() << " liter]\n"
				  << "WECHSEL: [" << p_weg.getName() << "] -> [" << neuesWeg->getName() << "]\n"
				  << "FAHRZEUG:\n" << p_fahrzeug
				  << "\n";

}


