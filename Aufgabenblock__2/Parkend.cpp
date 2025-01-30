/*
 * Parkend.cpp
 *
 *  Created on: Dec 15, 2024
 *      Author: Karime Soriano
 */
#include "Parkend.h"
#include "Fahrzeug.h" //Inkludiert, damit die aus Fahrzeug bekannten Methoden und Attribute zugänglich sind
#include "Fahrend.h"
#include "Verhalten.h"
#include "Losfahren.h"
extern double dGlobaleZeit; //Globale Simulationszeitvariable, deklariert in main.cpp


Parkend::Parkend(const Weg& weg) : Verhalten(weg), p_dStartzeit(0.0) {
	// TODO Auto-generated constructor stub

}

Parkend::Parkend(const Weg& weg, double dStartzeit) : Verhalten(weg), p_dStartzeit(dStartzeit) {
	// TODO Auto-generated constructor stub
}


Parkend::~Parkend() {
	// TODO Auto-generated destructor stub
}

double Parkend::dStrecke(Fahrzeug& fahrzeug, double dZeitIntervall) {
	if(dGlobaleZeit<p_dStartzeit){
		 return 0.0; // Geparkte Fahrzeuge legen keine Strecke zurück
	}else{
		/*std::cout << "El vehículo " << fahrzeug.getName()
				  << " ha comenzado a moverse en el camino " << p_rWeg.getName() << std::endl;
		// Cambiar el comportamiento del vehículo a Fahrend
		fahrzeug.setVerhalten(std::make_unique<Fahrend>(p_rWeg));
		// Delegar el cálculo de la distancia al nuevo comportamiento Fahrend
		//return fahrzeug.getVerhalten()->dStrecke(fahrzeug, dZeitIntervall);
		return 0.0;*/
		throw Losfahren(fahrzeug, const_cast<Weg&>(p_rWeg)); // const_cast wird verwendet, um die Konstante in p_rWeg vorübergehend zu entfernen. Dadurch kann der Pfad beim Auslösen der Ausnahme geändert werden.

	}

}



