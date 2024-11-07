/*
 * Fahrzeug.h
 *
 *  Created on: Nov 9, 2024
 *      Author: Karime Soriano
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_
#include <iostream> //Für output und input
#include <string> // Für std::string
using namespace std;


class Fahrzeug { //Klasse Fahrzeug mit ein Name und eine unique ID
private:
	//valor compartido entre todas las instancias de la clase
//Su propósito es generar una ID única para cada objeto Fahrzeug. Cada vez que se crea un nuevo objeto,
// se incrementa el valor de p_iMaxID, lo que garantiza que cada vehículo tenga un ID único.
	//Bloque de tarea 1. Inicio punto 3
    static int p_iMaxID;  // Statische Variable, die benutzt wird um ein einzigartiges ID zu jedes Item der Klass Fahrzeug zu geben
// p_iID almacena el ID único del vehículo específico y se asigna en el momento en que se crea el objeto, se toma el valor de p_iMaxID
    const int p_iID;            // Einzigartiges ID jedes Fahrzeug, kann nicht modifiziert werden
    string p_sName;  // Name der Fahrzeug

protected:// Atributos que se consideran accesible para subclases para cálculos o simulaciones particulares. Tarea 1 sección 4.3 punto 1
    //Inicio Tarea 1 punto 4
    double p_dMaxGeschwindigkeit; //Maximum Geschwindigkeit der Fahrzeug
    double p_dGesamtStrecke;         // Totale strecke der Fahrzeug
    double p_dGesamtZeit;            // Totale zeit
    double p_dZeit; //Zeit der letzte Simulation



public:
    //Bloque de tarea 1. Fin 4.4 punto 3
    //Konstruktor
    Fahrzeug();           // Constructor por defecto
	Fahrzeug(const string& sName);  // Constructor con nombre, este tiene la velocidad por defecto de 0
	Fahrzeug(const string& sName, double dMaxGeschwindigkeit); // Constructor con nombre y velocidad máxima, este le puedes poner la velocidad que quieras
	void vOutput();

	//Destruktor
    virtual ~Fahrzeug();  // Destructor virtual

    //Inicio tarea 1 punto 6
    //Funktion
    virtual void vAusgeben()const; //Funktion um INfo der Fahrzeug zu drucken
    static void vKopf(); //Funktion für die cabecera der Tabelle
    virtual void vSimulieren();

};




#endif /* FAHRZEUG_H_ */
