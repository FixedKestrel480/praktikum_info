/*
 * Fahrausnahme.h
 *
 *  Created on: Dec 31, 2024
 *      Author: Karime Soriano
 */

#ifndef FAHRAUSNAHME_H_
#define FAHRAUSNAHME_H_

#include <string>
#include <exception>
#include "Fahrzeug.h"
#include "Weg.h"

//5.5.1

class Fahrausnahme : public std::exception {
protected:
	Fahrzeug& p_fahrzeug;
	Weg& p_weg;

public:
	Fahrausnahme(Fahrzeug& fahrzeug, Weg& weg);
	virtual ~Fahrausnahme();
	virtual void vBearbeiten() const = 0;
};

#endif /* FAHRAUSNAHME_H_ */
