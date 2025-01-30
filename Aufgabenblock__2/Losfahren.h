/*
 * Losfahren.h
 *
 *  Created on: Dec 31, 2024
 *      Author: Karime Soriano
 */

#ifndef LOSFAHREN_H_
#define LOSFAHREN_H_
#include "Fahrausnahme.h"

//5.5
class Losfahren : public Fahrausnahme{
public:
	Losfahren(Fahrzeug& fahrzeug, Weg& weg);
	virtual ~Losfahren();
	void vBearbeiten()const override;
};

#endif /* LOSFAHREN_H_ */
