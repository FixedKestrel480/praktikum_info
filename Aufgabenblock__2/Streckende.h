/*
 * Streckende.h
 *
 *  Created on: Dec 31, 2024
 *      Author: Karime Soriano
 */

#ifndef STRECKENDE_H_
#define STRECKENDE_H_
#include "Fahrausnahme.h"

class Streckende : public Fahrausnahme {
public:
	Streckende(Fahrzeug& fahrzeug, Weg& weg);
	virtual ~Streckende();
	void vBearbeiten()const override;
};

#endif /* STRECKENDE_H_ */
