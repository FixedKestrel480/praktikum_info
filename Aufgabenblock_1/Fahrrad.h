/*
 * Fahrrad.h
 *
 *  Created on: Nov 14, 2024
 *      Author: Karime Soriano
 */

#ifndef FAHRRAD_H_
#define FAHRRAD_H_
#include "Fahrzeug.h"
using namespace std;

class Fahrrad: public Fahrzeug{
public:
	Fahrrad(string sName, double dMaxGeschwindigkeit);
	//virtual ~Fahrrad();

	void vSimulieren() override;   // Sobreescribe la simulación específica para Fahrrad
	void vAusgeben() const override; // Sobreescribe la salida específica para Fahrrad

};



#endif /* FAHRRAD_H_ */
