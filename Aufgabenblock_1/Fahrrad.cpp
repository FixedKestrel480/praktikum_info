/*
 * Fahrrad.cpp
 *
 *  Created on: Nov 14, 2024
 *      Author: Karime Soriano
 */
#include "Fahrrad.h"
#include<iostream>
#include<iomanip>

Fahrrad::Fahrrad(string sName,double dmaxGeschwindigkeit)
	:Fahrzeug(sName,dmaxGeschwindigkeit){
	cout<<"Fahrrad: "<<sName<<"mit einer Geschwindigkeit von: "<<dmaxGeschwindigkeit<<"km/s"<<endl;
}

void Fahrrad::vSimulieren(){
	cout<<"Test von vSimulieren: "<<endl;
}
void Fahrrad::vAusgeben() const{
	cout<<"Test von vAusgeben"<<endl;
}

