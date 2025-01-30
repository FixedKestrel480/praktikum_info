/*
 * Fahrrad.cpp
 *
 *  Created on: Nov 14, 2024
 *      Author: Karime Soriano
 */
#include "Fahrrad.h"
#include "SimuClient.h"
#include "Fahrzeug.h"
#include<iostream>
#include<iomanip>
using std::cout;
using std::string;
using std::endl;
//4.3.1
Fahrrad::Fahrrad(const string sName,double dmaxGeschwindigkeit)
	:Fahrzeug(sName,dmaxGeschwindigkeit){
	cout<<"Fahrrad: "<<sName<<"mit einer Geschwindigkeit von: "<<dmaxGeschwindigkeit<<"km/std"<<endl;
}

//4.3.3
void Fahrrad::vSimulieren(){
	Fahrzeug::vSimulieren();
	//cout<<"Test von vSimulieren: "<<endl;
}
void Fahrrad::vAusgeben() const{
	Fahrzeug::vAusgeben();
	//cout<<"Test von vAusgeben"<<endl;
}

void Fahrrad::vAusgeben(std::ostream& os)const{ //Modifiziert zur Unterstützung von ostream
	Fahrzeug::vAusgeben(os); //Prüfung aus der Fahrradklasse
	os<<"(Fahrrad)";
}

//4.3.3
double Fahrrad::dGeschwindigkeit()const{ //Berechnung der Höchstgeschwindigkeit überschreiben
	int iabgeschlosseneAbschnitte = static_cast<int>(p_dGesamtStrecke/20); // Man ermittelt, wie viele 20-km-Abschnitte vollständig zurückgelegt wurden
	// Man reduziert die Geschwindigkeit für jede vollständig zurückgelegte Strecke von 20 km um 10 %
	double dReduzieren =1.0-(iabgeschlosseneAbschnitte*0.1);
	double dAktuelGeschwindigkeit = p_dMaxGeschwindigkeit*dReduzieren;
	// Die Mindestgeschwindigkeit beträgt 12 km/std
	return std::max(dAktuelGeschwindigkeit,12.0);//////

}

void Fahrrad::vZeichnen(const Weg& weg) const {
    bZeichneFahrrad(
        getName(), // Fahrzeugname
        weg.getName(), // Name der Straße
        getAbschnittStrecke() / weg.getLaenge(), // Relative Position
        dGeschwindigkeit() // Aktuelle Geschwindigkeit
    );
}
