/*
 * Tempolimit.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Karime Soriano
 */

#ifndef TEMPOLIMIT_H_
#define TEMPOLIMIT_H_

#include <limits>

//5.3.2
enum class Tempolimit {
    Innerorts,   // 50 km/h urban
    LandstraBe,  // 100 km/h Landstraße
    Autobahn     // Autobahn ohne Begrenzung
};




#endif /* TEMPOLIMIT_H_ */
