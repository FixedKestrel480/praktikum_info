/*
 * Parkend.h
 *
 *  Created on: Dec 15, 2024
 *      Author: Karime Soriano
 */

#ifndef PARKEND_H_
#define PARKEND_H_

#include "Verhalten.h"

class Parkend: public Verhalten {
public:
	Parkend(const Weg& weg);
	Parkend(const Weg& weg, double dStartzeit);
	virtual ~Parkend();
	double dStrecke(Fahrzeug& fahrzeug, double dZeitIntervall) override;
private:
	double p_dStartzeit;
};





#endif /* PARKEND_H_ */
