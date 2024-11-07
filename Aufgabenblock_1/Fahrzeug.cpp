/*
 * Fahrzeug.cpp
 *
 *  Created on: Nov 9, 2024
 *      Author: Karime Soriano
 */

#include "Fahrzeug.h"
#include <iostream>
#include <iomanip>
using namespace std;

extern double dGlobaleZeit;

// Inicialización de la variable estática
int Fahrzeug::p_iMaxID = 0;

// Constructor por defecto
//Bloque de tarea 1 punto 3
Fahrzeug::Fahrzeug()
: p_iID(++p_iMaxID), p_sName("?"), p_dMaxGeschwindigkeit(0.0), p_dGesamtStrecke(0.0), p_dGesamtZeit(0.0), p_dZeit(0.0) { //Standardkonstruktor eines Fahrzeugs, der dem Namen „“ zuweist, der ID den Wert von p_iMaxID zuweist und p_iMaxID um 1 inkrementiert
	vOutput();
    //std::cout << "Fahrzeug [ID: " << p_iID << "] \"" << p_sName << "\" erstellt." << std::endl;
}

//en este caso utilizas & porque estas pasando una referencia no solo una copia del std::string, el constructor utilizará una referencia al objeto, es más eficiente, y evita las duplicaciones
//con constante evitas que se cambie el valor y es más seguro
//otra forma de escribirlo es  Fahrzeug(std::string sName) : p_iID(++p_iMaxID), p_sName(std::move(sName)) {
//std::cout << "Fahrzeug [ID: " << p_iID << "] \"" << p_sName << "\" erstellt." << std::endl;
//}
/*Fahrzeug::Fahrzeug(const std::string& sName) {--> se podría escribir así
    p_iID = ++p_iMaxID;
    p_sName = sName;
    p_dMaxGeschwindigkeit = 0.0;
    p_dGesamtStrecke = 0.0;
    p_dGesamtZeit = 0.0;
    p_dZeit = 0.0;

    std::cout << "Fahrzeug [ID: " << p_iID << "] \"" << p_sName << "\" erstellt." << std::endl;
}*/
//Konstruktor mit Name als Parameter
//Bloque de tarea 1 punto 3
Fahrzeug::Fahrzeug(const std::string& sName)
: p_iID(++p_iMaxID), p_sName(sName), p_dMaxGeschwindigkeit(0.0), p_dGesamtStrecke(0.0), p_dGesamtZeit(0.0), p_dZeit(0.0) {
    vOutput();
	//std::cout << "Fahrzeug [ID: " << p_iID << "] \"" << p_sName << "\" erstellt." << std::endl;
}
// Konstruktor mit Name und max Geschwindigkeit
//Constructor Tarea 1 punto 5
Fahrzeug::Fahrzeug(const std::string& sName, double dMaxGeschwindigkeit)
: p_iID(++p_iMaxID), p_sName(sName), p_dMaxGeschwindigkeit(dMaxGeschwindigkeit > 0 ? dMaxGeschwindigkeit : 0.0), p_dGesamtStrecke(0.0), p_dGesamtZeit(0.0), p_dZeit(0.0) {
	//checar si la velocidad es mayor que 0 si si, usa el valor que pusieron, sino pone el valor el 0
    std::cout << "Fahrzeug [ID: " << p_iID << "] \"" << p_sName << "\" mit Maximalgeschwindigkeit " << p_dMaxGeschwindigkeit << " erstellt." << std::endl;
}
//Bloque de tarea 1 punto 3
//Destruktor
Fahrzeug::~Fahrzeug() {
    std::cout << "Fahrzeug [ID: " << p_iID << "] \"" << p_sName << "\" gelöscht." << std::endl;
}
void Fahrzeug::vOutput()	{ //Función que imprime los datos del objeto vehículo
	cout << "Fahrzeug "<<p_sName<<" mit ID " << p_iID << " war erstellt." << endl;
}

//Inicio Tarea 1 punto 6

// Funktion zum Drucken des Tabellenkopfes
void Fahrzeug::vKopf(){
	cout << std::setiosflags(std::ios::left);
	cout << std::setw(5) << "ID" <<
			std::setw(10) << "Name";
	cout << std::resetiosflags(std::ios::left);
	cout << std::setw(20) << "MaxGeschwindigkeit" <<
			std::setw(20) << "Gesamtstrecke" << endl;
	cout << "--------------------------------------------------------" << endl;

	/*
	cout<<std::left; //asegura que todo lo que se imprima quede alineado a la izquierda
	cout<<setw(5)<<"ID"<<setw(15)<<"Name"<<setw(20)<<"Max Geschwindigkeit"<<setw(20)<<"Gesamtstrecke"<<endl; //setw = set width, que ancho tiene que tener
	//se asegura que si la palabra tiene de por ejemplo menos de 5 caracteres, el espacio lo llenara en blanco
	cout<<"-------------------------------------"<<endl;*/
}

//Funktion um die Daten zu drucken
void Fahrzeug::vAusgeben() const{//-----------------------
	cout<<std::left<<std::setw(5)<<p_iID<<
		  std::left << std::setw(10) << p_sName <<
		  std::right << std::setw(20) << std::fixed << std::setprecision(2) << p_dMaxGeschwindigkeit <<
		  std::right << std::setw(20) << std::fixed << std::setprecision(2) << p_dGesamtStrecke;

}

// Función para simular el avance del vehículo
void Fahrzeug::vSimulieren() {
	if (dGlobaleZeit <= p_dZeit) { //Se compara el tiempo Global de la simulación respecto al tiempo de la última simulación
			return;  // Si este es menor o igual, significa que ya se simuló y sale de la función sin hacer más cálculos
		}
	double dDifZeit = dGlobaleZeit - p_dZeit; //Se calcula la diferencia del tiempo global con el tiempo de la última simulación del vehículo
	p_dGesamtStrecke += (p_dMaxGeschwindigkeit * dDifZeit); //Se calcula la distancia recorrida respecto a la diferencia de tiempo y considerando la máxima velocidad del vehiculo
	p_dGesamtZeit += dDifZeit; //Al tiempo total de conducción se acumula la diferencia del tiempo
	p_dZeit = dGlobaleZeit; //S

    /*if (p_dZeit < dGlobaleZeit) {
        double dZeitdifferenz = dGlobaleZeit - p_dZeit;
        double dStrecke = p_dMaxGeschwindigkeit * dZeitdifferenz;
        p_dGesamtStrecke += dStrecke;
        p_dGesamtZeit += dZeitdifferenz;
        p_dZeit = dGlobaleZeit;*/
    }



