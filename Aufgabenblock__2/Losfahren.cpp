/*
 * Losfahren.cpp
 *
 *  Created on: Dec 31, 2024
 *      Author: Karime Soriano
 */

#include "Losfahren.h"
#include"Weg.h"
#include "Fahrzeug.h"

Losfahren::Losfahren(Fahrzeug& fahrzeug, Weg& weg)
    : Fahrausnahme(fahrzeug, weg) {}

Losfahren::~Losfahren() {
    // Leere Destruktor
}

void Losfahren::vBearbeiten() const {
    //std::cout << "Exception: Losfahren. "
      //        << "Fahrzeug: " << p_fahrzeug.getName()
        //      << ", Strecke: " << p_weg.getName() << std::endl;
	auto pFzg= p_weg.pAbgabe(p_fahrzeug);
	if(pFzg){
		p_weg.vAnnahme(std::move(pFzg));
		std::cout << "Das Fahrzeug" << p_fahrzeug.getName()
		<< " fang an, auf der Straße zu fahren" << p_weg.getName() << ".\n";
	}

}


