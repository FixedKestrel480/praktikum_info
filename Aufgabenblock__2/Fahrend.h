/*
 * Fahrend.h
 *
 *  Created on: Dec 21, 2024
 *      Author: Karime Soriano
 */

#ifndef FAHREND_H_
#define FAHREND_H_
#include "Verhalten.h"
class Fahrend: public Verhalten{
public:
	Fahrend(const Weg&weg);
	virtual ~Fahrend();
	double dStrecke(Fahrzeug& fahrzeug, double dZeitIntervall) override;

};



#endif /* FAHREND_H_ */
