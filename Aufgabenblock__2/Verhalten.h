/*
 * Verhalten.h
 *
 *  Created on: Dec 11, 2024
 *      Author: Karime Soriano
 */

#ifndef VERHALTEN_H_
#define VERHALTEN_H_
#include "Weg.h"

//5.4.1
class Fahrzeug;
class Verhalten{
public:
	Verhalten(const Weg& weg);
	virtual ~Verhalten();
	virtual double dStrecke(Fahrzeug& fahrzeug, double dZeitIntervall); // Berechnet man die maximale Entfernung, die das Fahrzeug auf diesem Weg zurücklegen kann
	const Weg& getWeg()const{
	    return p_rWeg; // Konstante Referenz auf den zugehörigen Pfad
	    }
protected:
	const Weg& p_rWeg;


};



#endif /* VERHALTEN_H_ */
