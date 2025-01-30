/*
 * Simulationsobjekt.cpp
 *
 *  Created on: Dec 5, 2024
 *      Author: Karime Soriano
 */

#include "Simulationsobjekt.h"
#include <iostream>
#include <iomanip>
using std::cout;

int Simulationsobjekt::p_iMaxID = 0;
Simulationsobjekt::Simulationsobjekt() : p_sName("-"), p_iID(++p_iMaxID), p_dZeit(0.0) {
	std::cout << "Objekt "<<p_sName<<" mit ID " << p_iID << " war erstellt." << std::endl;
}

Simulationsobjekt::Simulationsobjekt(const std::string& sName) : p_sName(sName), p_iID(++p_iMaxID), p_dZeit(0.0) {
	std::cout << "Objekt "<<p_sName<<" mit ID " << p_iID << " war erstellt." << std::endl;
}

Simulationsobjekt::~Simulationsobjekt() {
    cout << "Simulationsobjekt \"" << p_sName << "\" mit ID "
              << p_iID << " gelöscht.\n";
}

void Simulationsobjekt::vAusgeben(std::ostream& os) const {
	os << std::left << std::setw(19) << p_iID <<
		  std::left << std::setw(9) << p_sName;
}

bool Simulationsobjekt::operator==(const Simulationsobjekt& other) const {
    return this->p_iID == other.p_iID;
}

std::ostream& operator<<(std::ostream& os, const Simulationsobjekt& obj) {
    obj.vAusgeben(os); // Ruft man  die spezifische Version der Klasse auf
    return os;
}

