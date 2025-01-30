/*
 * Fahrzeug.cpp
 *
 *  Created on: Nov 1, 2024
 *      Author: Karime Soriano
 *
 *
 */

#include "Fahrzeug.h"
#include <iostream>
#include <memory> //Für die Zeigerverwaltung
#include <vector>
#include <iomanip>
#include <algorithm>
#include "Fahrrad.h"
#include "PKW.h"
#include "Weg.h"
#include "Tempolimit.h"
#include "Parkend.h"
#include "Losfahren.h"
#include "Fahrausnahme.h"
#include "Streckende.h"
#include "SimuClient.h"
//#include "Verhalten.h"
#include "Fahrend.h"
#include "Kreuzung.h"
#include <cmath> // Fúr std::fabs()
#include <random>
#include "vertagt_aktion - Vorlage.h"
#include "vertagt_liste - Vorlage.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::make_unique;
using std::make_shared;
using namespace std;

double dGlobaleZeit = 0.0; //4.2.6
//Globale Variable für die Simulationszeit

void vAufgabe_3(){ //4.4.6
	dGlobaleZeit=0.0; //Startzeit für Simulationen
	// Fahrzeuginstanzen erstellen
	Fahrzeug Auto1("BMW", 120.0);
	Fahrzeug Auto2("Audi", 100.0);
	Fahrzeug Auto3("Tesla", 150.0);
	cout << "Ausgangszustand der Fahrzeuge" << endl;
	Fahrzeug::vKopf(std::cout);
	// Den Exit-Operator testen
	cout << Auto1 << endl; //Testoperator <<
	cout << Auto2 << endl; //Testoperator <<
	cout << Auto3 << endl;//Testoperator <<
	// Verschiedene Zeiten simulieren, um Zuweisungsoperatoren und < zu testen
	cout << "\nEntfernungen simulieren"<<endl;
	dGlobaleZeit = 2.0; // 2 Stunden simulieren
	Auto1.vSimulieren(); // Auto1 fährt 2 * 120 = 240 km
	dGlobaleZeit = 1.0; // 1 Stunde simulieren
	Auto3.vSimulieren(); // Auto3 fährt 1 * 150 = 150 km
	cout << "Status der Fahrzeuge nach Simulationen" << endl;
	Fahrzeug::vKopf(std::cout);
	cout << Auto1 << endl;
	cout << Auto2 << endl;
	cout << Auto3 << endl;
	cout << "Testen des Zuweisungsoperators durch Kopieren von Daten von Auto1 nach Auto2:\n";
	Auto2 = Auto1; // Testoperator, um Auto1 Auto2 zuzuweisen
	Fahrzeug::vKopf(std::cout);
	cout << Auto1 << endl;
	cout << Auto2 << endl;
	cout << Auto3 << endl;
	cout << "Prüfung des Vergleichsoperators (<) zwischen Auto1 und Auto3:"<<endl;
	if (Auto1 < Auto3) {  //Testoperator <
		cout << Auto1.getName() << " hat weniger Abstand als " << Auto3.getName() << endl;
	} else {
		cout << Auto1.getName() << " hat mehr oder den gleichen Abstand wie " << Auto3.getName() << endl;
	}
}

void vAufgabe_53_1(){
	dGlobaleZeit=0.0; //Iniciar tiempo para simulaciones
	Fahrzeug Auto1("BMW", 120.0); //Prueba constructor vehículo con parámetros
	Fahrzeug Auto2("Audi", 100.0);
	PKW Auto3("Tesla", 150.0, 5.0, 50.0);
	Fahrzeug Auto4("VW"); //Prueba constructor vehículo con parámetro de nombre
	Fahrzeug Auto5; //Prueba constructor vehículo por default
	Fahrrad bici("MountainB", 25.0); //Prueba constructor Farrad
	std::cout << "Initiale Zustand der Fahrzeuge" << std::endl;
	Fahrzeug::vKopf(std::cout);
	std::cout << Auto1 << std::endl;
	std::cout << Auto2 << std::endl;
	std::cout << Auto3 << std::endl;
	std::cout << Auto4 << std::endl;
	std::cout << Auto5 << std::endl;
	std::cout << bici << std::endl;
	// Simular 1 hora
	std::cout << "1 Stunde simulieren"<<std::endl;
	dGlobaleZeit = 1.0; // Simular 1 hora
	Auto1.vSimulieren(); // Auto1 recorre 1 * 120 = 120 km
	Auto2.vSimulieren(); // Auto2 recorre 1 * 100 = 100 km
	Auto3.vSimulieren(); // Auto3 recorre 1 * 150 = 150 km
	bici.vSimulieren();
	std::cout << "Estado de vehículos después de simulaciones" << std::endl;
	Fahrzeug::vKopf(std::cout);
	std::cout << Auto1 << std::endl;
	std::cout << Auto2 << std::endl;
	std::cout << Auto3 << std::endl;
	std::cout << bici << std::endl;
	// Prueba de Weg
	auto weg = std::make_shared<Weg>("Ruta1", 520.0, Tempolimit::Innerorts); // Camino de 50 km
	weg->vSimulieren(); // Simulación del camino
	weg->vAusgeben(std::cout); // Mostrar el estado del camino

}

void vAufgabe_53_2(){
	// Crear caminos con diferentes límites de velocidad
	Weg standardWeg; // Constructor estándar
	Weg innerorts("Urbano", 5.0, Tempolimit::Innerorts);
	Weg autobahn("Autopista", 50.0); // Límite por defecto: Autobahn

	// Crear vehículos y añadirlos a los caminos
	auto auto1 = std::make_unique<Fahrzeug>("BMW", 120.0);
	auto auto2 = std::make_unique<Fahrzeug>("Audi", 100.0);

	innerorts.Fahrzeughinfuegen(std::move(auto1));
	autobahn.Fahrzeughinfuegen(std::move(auto2));

	// Simulación
	innerorts.vSimulieren();
	autobahn.vSimulieren();

	// Imprimir resultados
	Fahrzeug::vKopf(std::cout);
	innerorts.vAusgeben(std::cout);
	autobahn.vAusgeben(std::cout);
}



void vAufgabe_54_1(){
	dGlobaleZeit=0.0;
	// Crear caminos
	Weg autobahn("Autobahn", 150.0);
	// Crear vehículos
	auto bmw = std::make_unique<Fahrzeug>("BMW", 120.0);
	auto audi = std::make_unique<Fahrzeug>("Audi", 100.0);
	// Asignar comportamiento inicial (Parkend y fahrend) y agregar los vehículos al camino
	bmw->setVerhalten(std::make_unique<Parkend>(autobahn)); //Este vehículo está estacionado y no debería moverse
	audi->setVerhalten(std::make_unique<Fahrend>(autobahn)); //Este vehículo está en movimiento ////////////
	autobahn.Fahrzeughinfuegen(std::move(bmw));
	autobahn.Fahrzeughinfuegen(std::move(audi));
	// Imprimir cabecera y estado inicial
	Weg::vKopf(std::cout);
	std::cout << autobahn << std::endl;
	Fahrzeug::vKopf(std::cout);
	for (const auto& fahrzeug : autobahn.getFahrzeuge()) {
		std::cout << *fahrzeug << std::endl;
	}
	// Simular 1 hora
	dGlobaleZeit += 1.0;
	std::cout << "Simulation nach einer Stunde:"<< std::endl;
	autobahn.vSimulieren();
	for (const auto& fahrzeug : autobahn.getFahrzeuge()) {
		std::cout << *fahrzeug << std::endl;
	}
}

void vAufgabe_54_1a(){
	//Prueba p_dAbschnittStrecke
	// Crear caminos
	Weg autobahn("Autobahn", 100.0);
	Weg landstrasse("LandstraBe", 50.0);
	Fahrzeug bmw("BMW", 120.0); // Crear vehículo
	bmw.vNeueStrecke(autobahn);// Asignar el vehículo a la autopista
	// Simular 1 hora
	dGlobaleZeit += 1.0;
	bmw.vSimulieren();
	// Mostrar estado
	Fahrzeug::vKopf(std::cout);
	std::cout << bmw << std::endl;
	// Cambiar el vehículo a la Landstrasse
	bmw.vNeueStrecke(landstrasse);
	// Simular otra hora
	dGlobaleZeit += 1.0;
	bmw.vSimulieren();
	// Mostrar estado nuevamente
	std::cout << bmw << std::endl;
	// Simular otra hora
	dGlobaleZeit += 1.0;
	bmw.vSimulieren();
	// Mostrar estado nuevamente
	std::cout << bmw << std::endl;
}



void vAufgabe_54_4(){
	Weg autobahn("Autobahn",150.0);
	auto Tesla = make_unique<Fahrzeug>("Tesla",200.0);
	auto Bmw = make_unique<Fahrzeug>("BMW",100.0);
	auto Audi = make_unique<Fahrzeug>("Audi",150.0);

	autobahn.vAnnahme(std::move(Tesla));
	autobahn.vAnnahme(std::move(Bmw),1.0); //Estacionado y lo pone al inicio del camino
	autobahn.vAnnahme(std::move(Audi));

	std::cout << "Estado inicial del camino y vehículos:\n";
	Weg::vKopf(std::cout);
	std::cout << autobahn << std::endl;
	Fahrzeug::vKopf(std::cout);
	for (const auto& fahrzeug : autobahn.getFahrzeuge()) {
		std::cout << *fahrzeug << std::endl;
	}

// Incrementar el tiempo global y simular el camino
	for (int i = 0; i < 3; ++i) {
		dGlobaleZeit += 1.0; // Incrementar en 1 hora
		// Mostrar estado después de cada simulación
		std::cout << "Estado del camino y vehículos después de " << dGlobaleZeit << " horas:"<< std::endl;
		autobahn.vSimulieren();
		Weg::vKopf(std::cout);
		std::cout << autobahn << std::endl;
		Fahrzeug::vKopf(std::cout);
		for (const auto& fahrzeug : autobahn.getFahrzeuge()) {
			std::cout << *fahrzeug << std::endl;
				}
		    }

}

void vAufgabe_55_2(){
	dGlobaleZeit = 0.0;
	// Crear un camino con un límite de velocidad (Landstrasse: 100 km/h)
	Weg landstrasse("Carretera", 200.0, Tempolimit::LandstraBe);

	// Crear un PKW con una velocidad máxima mayor al Tempolimit, rendimiento de 10L/100 km, tanque máximo de 50 L y en consecuencia se inicia con 25 L en el tanque
	auto audi = std::make_unique<PKW>("Audi", 120.0, 10.0, 50.0);

	// Agregar el PKW al camino
	landstrasse.vAnnahme(std::move(audi));

	//Estado inicial
	std::cout << "Estado inicial del camino y vehículos:\n";
	Weg::vKopf(cout);
	std::cout << landstrasse << std::endl;
	Fahrzeug::vKopf(std::cout);
	for (const auto& fahrzeug : landstrasse.getFahrzeuge()) {
		std::cout << *fahrzeug << std::endl;
	}

	// Simular pasos
	for (int i = 0; i < 3; ++i) {
		dGlobaleZeit += 1.0;
		std::cout << "\nEstado después de " << dGlobaleZeit << " horas:\n";
		landstrasse.vSimulieren(); // Simular el camino

		Weg::vKopf(std::cout);
		std::cout << landstrasse << std::endl;
		Fahrzeug::vKopf(std::cout);
		for (const auto& fahrzeug : landstrasse.getFahrzeuge()) {
			std::cout << *fahrzeug << std::endl;
		}
	}
}

void vAufgabe_6_58(){
	dGlobaleZeit = 0.0;
	auto kreuzungA = std::make_shared<Kreuzung>("Kreuzung A", 500.0);
	auto kreuzungB = std::make_shared<Kreuzung>("Kreuzung B", 300.0);

	Kreuzung::vVerbinde("Hinweg", "Ruckweg", 200.0, kreuzungA, kreuzungB, Tempolimit::LandstraBe);

	auto audi = std::make_unique<PKW>("Audi", 120.0, 10.0, 50.0);
	auto bmw = std::make_unique<PKW>("BMW", 150.0, 8.0, 60.0);

	//kreuzungA->vTanken(*audi);
	kreuzungA->vAnnahme(std::move(audi)); //Llena el tanque con 25 L y se los resta a la gasolinera del CRUCE A
	kreuzungB->vAnnahme(std::move(bmw), 1.0); // Estacionado inicialmente. Llena el tanque con 25 L y se los resta a la gasolinera del CRUCE B
	// Simular ambos cruceros
	//kreuzungA->vSimulieren();
	//kreuzungB->vSimulieren();
	// Mostrar estado inicial
	std::cout << "Initiale Zustand\n";
	Kreuzung::vKopf(std::cout);
	std::cout << *kreuzungA << "\n";
	std::cout << *kreuzungB << "\n";
	std::cout << "Aktuelle Zustand der Wege:\n";
	Weg::vKopf(std::cout);
	for (const auto& weg : kreuzungA->getWege()) {
		std::cout << *weg << "\n";
		// Mostrar vehículos en el camino
		Fahrzeug::vKopf(std::cout);
		for (const auto& fahrzeug : weg->getFahrzeuge()) {
			std::cout << *fahrzeug << "\n";
		}
	}
	for (const auto& weg : kreuzungB->getWege()) {
		std::cout << *weg << "\n";
		// Mostrar vehículos en el camino
		Fahrzeug::vKopf(std::cout);
		for (const auto& fahrzeug : weg->getFahrzeuge()) {
			std::cout << *fahrzeug << "\n";
		}
	}

	 for (int i = 0; i < 5; ++i) {
		dGlobaleZeit += 1.0;

		std::cout << "\nGlobalezeit: " << dGlobaleZeit << " Stunden\n";
		std::cout << "--------------------------------------------\n";

		// Simular ambos cruceros
		kreuzungA->vSimulieren();
		kreuzungB->vSimulieren();

		// Mostrar estado de los cruceros
		Kreuzung::vKopf(std::cout);
		std::cout << *kreuzungA << "\n";
		std::cout << *kreuzungB << "\n";

		// Mostrar estado de los caminos y vehículos en ellos
		std::cout << "Aktuelle Zustand der Wege:\n";
		for (const auto& weg : kreuzungA->getWege()) {
			std::cout << *weg << "\n";
			Fahrzeug::vKopf(std::cout);
			for (const auto& fahrzeug : weg->getFahrzeuge()) {
				std::cout << *fahrzeug << "\n";
			}
		}

		for (const auto& weg : kreuzungB->getWege()) {
			std::cout << *weg << "\n";
			Fahrzeug::vKopf(std::cout);
			for (const auto& fahrzeug : weg->getFahrzeuge()) {
				std::cout << *fahrzeug << "\n";
			}
		}
	}
}


void vAufgabe_6_58_2(){
	dGlobaleZeit = 0.0;

	// Crear tres cruces
	auto kreuzungA = std::make_shared<Kreuzung>("CRUCE A", 500.0);
	auto kreuzungB = std::make_shared<Kreuzung>("CRUCE B", 400.0);
	auto kreuzungC = std::make_shared<Kreuzung>("CRUCE C", 300.0);

	// Conectar los cruces con caminos (ida y vuelta)
	Kreuzung::vVerbinde("A->B", "B->A", 200.0, kreuzungA, kreuzungB, Tempolimit::LandstraBe); //Límite velocidad: 100 km/h y 200 km de longitud
	Kreuzung::vVerbinde("B->C", "C->B", 200.0, kreuzungB, kreuzungC, Tempolimit::Autobahn);	//Sin límite de velocidad y 200 km de longitud
	Kreuzung::vVerbinde("C->A", "A->C", 250.0, kreuzungC, kreuzungA, Tempolimit::LandstraBe); //Límite velocidad: 100 km/h y 250 km de longitud

	// Crear vehículos
	auto audi = std::make_unique<PKW>("Audi", 120.0, 10.0, 50.0); //Máxima velcidad 120 km/h, rendimiento 10 L/100 Km y tanque máximo de 50L que al crearse quedan 25
	auto bmw = std::make_unique<PKW>("BMW", 100.0, 8.0, 60.0); //Máxima velcidad 100 km/h, rendimiento 8 L/100 Km y tanque máximo de 60L que al crearse quedan 30
	auto tesla = std::make_unique<PKW>("Tesla", 150.0, 5.0, 70.0); //Máxima velcidad 150 km/h, rendimiento 5 L/100 Km y tanque máximo de 70L que al crearse quedan 35

	// Agregar 2 vehículos al cruce A y al agregarlos se les llena el tanque de gasolina
	kreuzungA->vAnnahme(std::move(audi));
	kreuzungA->vAnnahme(std::move(bmw));

	// Agregar un vehículo al cruce B y al agregarlo se les llena el tanque de gasolina
	kreuzungB->vAnnahme(std::move(tesla), 1.0); // Estacionado una hora inicialmente

	// Mostrar el estado inicial antes de la simulación, después de agregar los autos y llenarles el tanque
	std::cout << "Estado inicial de los cruces:\n";
	Kreuzung::vKopf(std::cout);
	std::cout << *kreuzungA << "\n"; //500L - 25L - 30L = 445L al abastecer al Audi y BMW
	std::cout << *kreuzungB << "\n"; //440L - 35 = 365L al abastecer al Tesla
	std::cout << *kreuzungC << "\n"; //300L en la estación del cruce

	// Mostrar vehículos en los caminos de cada cruce. Aun no se asigna un vehículo a los caminos
	std::cout << "Estado de los caminos del CRUCE A:\n";
	for (const auto& weg : kreuzungA->getWege()) {
		std::cout << *weg << "\n";
		Fahrzeug::vKopf(std::cout);
		for (const auto& fahrzeug : weg->getFahrzeuge()) {
			std::cout << *fahrzeug << "\n";
		}
	}
	std::cout << "Estado de los caminos del CRUCE B:\n";
	for (const auto& weg : kreuzungB->getWege()) {
		std::cout << *weg << "\n";
		Fahrzeug::vKopf(std::cout);
		for (const auto& fahrzeug : weg->getFahrzeuge()) {
			std::cout << *fahrzeug << "\n";
		}
	}
	std::cout << "Estado de los caminos del CRUCE C:\n";
	for (const auto& weg : kreuzungC->getWege()) {
		std::cout << *weg << "\n";
		Fahrzeug::vKopf(std::cout);
		for (const auto& fahrzeug : weg->getFahrzeuge()) {
			std::cout << *fahrzeug << "\n";
		}
	}
	// Simulación de 6 horas
	for (int i = 1; i <= 6; ++i) {
		dGlobaleZeit += 1.0;

		std::cout << "\nTiempo global: " << dGlobaleZeit << " horas\n";
		std::cout << "--------------------------------------------\n";

		// Simular los cruces
		kreuzungA->vSimulieren();
		kreuzungB->vSimulieren();
		kreuzungC->vSimulieren();

		// Mostrar estado de los cruces
		std::cout << "Estado actual de los cruces:\n";
		Kreuzung::vKopf(std::cout);
		std::cout << *kreuzungA << "\n";
		std::cout << *kreuzungB << "\n";
		std::cout << *kreuzungC << "\n";

		// Mostrar vehículos en los caminos de cada cruce
		std::cout << "Estado de los caminos del CRUCE A:\n";
		for (const auto& weg : kreuzungA->getWege()) {
			std::cout << *weg << "\n";
			Fahrzeug::vKopf(std::cout);
			for (const auto& fahrzeug : weg->getFahrzeuge()) {
				std::cout << *fahrzeug << "\n";
			}
		}

		std::cout << "Estado de los caminos del CRUCE B:\n";
		for (const auto& weg : kreuzungB->getWege()) {
			std::cout << *weg << "\n";
			Fahrzeug::vKopf(std::cout);
			for (const auto& fahrzeug : weg->getFahrzeuge()) {
				std::cout << *fahrzeug << "\n";
			}
		}
		std::cout << "Estado de los caminos del CRUCE C:\n";
		for (const auto& weg : kreuzungC->getWege()) {
			std::cout << *weg << "\n";
			Fahrzeug::vKopf(std::cout);
			for (const auto& fahrzeug : weg->getFahrzeuge()) {
				std::cout << *fahrzeug << "\n";
			}
		}

	}
}




void vAufgabe_4(){
	Weg autobahn("Autobahn", 150.0);
	autobahn.Fahrzeughinfuegen(std::make_unique<Fahrzeug>("BMW", 120.0));
	autobahn.Fahrzeughinfuegen(std::make_unique<PKW>("Audi", 100.0, 10.0));
	autobahn.Fahrzeughinfuegen(std::make_unique<Fahrrad>("Bici1", 20.0));

	// Header und Pfad drucken
	Weg::vKopf(std::cout);
	std::cout << autobahn << std::endl;
}

void vAufgabe5(){
	Weg autobahn("Autobahn",100.0);
	auto Tesla = make_unique<Fahrzeug>("Tesla",200.0);
	auto Bmw = make_unique<Fahrzeug>("BMW",120.0);
	auto Audi = make_unique<Fahrzeug>("Audi",150.0);
	//Fahrzeuge zur Straße hinzufügen
	autobahn.vAnnahme(std::move(Tesla));
	autobahn.vAnnahme(std::move(Bmw));
	autobahn.vAnnahme(std::move(Audi));

	//Simulieren und der
	cout<<"Initiele Zustand:\n";
	Weg::vKopf(cout);
	cout<<autobahn<<endl;
	Fahrzeug::vKopf(cout);
	for(const auto& fahrzeug:autobahn.getFahrzeuge()){
		cout<<*fahrzeug<<endl;
	}

	for(int i=0;i<3;i++){
		dGlobaleZeit +=1.0;
		autobahn.vSimulieren();
		cout<<"Straßen- und Fahrzeugzustand nach: "<<dGlobaleZeit<<"Stunden"<<endl;
		Weg::vKopf(cout);
		cout<<autobahn<<endl;
		Fahrzeug::vKopf(cout);
		for(const auto& fahrzeug:autobahn.getFahrzeuge()){
			cout<<*fahrzeug<<endl;
		}

	}


}

void vAufgabe6(){
	dGlobaleZeit = 0.0;
	Weg landstrasse("Landstrasse", 120.0, Tempolimit::LandstraBe); //100 km/std grenzwert
	Weg autobahn("Autobahn",300.0,Tempolimit::Autobahn); //Ohne Grenz

	auto bmw = make_unique<PKW>("BMW",150.0, 10.0,50.0); //Geschwindigkeit max 150
	auto audi = make_unique<PKW>("Audi",120.0, 5.0,60.0);
    auto tesla = std::make_unique<Fahrzeug>("Tesla", 100.0); // Velocidad de limitada por LandstraBe

	auto bici = make_unique<Fahrrad>("Bici",25.0); //velo

	//Fahrzeuge addieren
	landstrasse.vAnnahme(std::move(bmw)); //Fahrzeug bewegt sich
    landstrasse.vAnnahme(std::move(tesla), 1.0); // Geparkt, Abfahrt in 1 Stunde
	autobahn.vAnnahme(std::move(bici),2.0); //Velo parkend und beginnt in 2 Stunden
	autobahn.vAnnahme(std::move(audi)); //Fahrzeug bewegt sich

	cout<<"Initiale Zustand der Fahrzeug:\n";
	Weg::vKopf(cout);
	cout << landstrasse << std::endl;
	Fahrzeug::vKopf(std::cout);
	for (const auto& fahrzeug : landstrasse.getFahrzeuge()) {
			std::cout << *fahrzeug << std::endl;
		}

	std::cout << autobahn << std::endl;
	Fahrzeug::vKopf(std::cout);
	for (const auto& fahrzeug : autobahn.getFahrzeuge()) {
		std::cout << *fahrzeug << std::endl;
	}


	//Simulation
	for(int i= 0;i<5;i++){
		dGlobaleZeit +=1.0;
		cout<<"Globale Zeit: "<<dGlobaleZeit<<"Stunde(n)"<<endl;
		//Simulation landstrasse
		landstrasse.vSimulieren();
		//Simulation autobahn
		autobahn.vSimulieren();
		cout << "\nAktueller Straßenstatus:\n";
		Weg::vKopf(cout);
		cout << landstrasse <<endl;
		Fahrzeug::vKopf(cout);
		cout<<endl;
		for(const auto& fahrzeug : landstrasse.getFahrzeuge()){
			cout<<*fahrzeug<<endl;
		}
	}

}


void vAufgab6graph(){
	dGlobaleZeit = 0.0;
	//Grafische Oberfläche initialisieren
	if(!bInitialisiereGrafik(800,500)){
		std::cerr<<"Error"<<endl;
		return;
	}

	// Pfade erstellen (Hin- und Rückweg)
	Weg landstrasse("LANDSTRASSE", 500.0, Tempolimit::LandstraBe);
	Weg autobahn("Autobahn", 500.0, Tempolimit::Autobahn);
	// Zeichne die Straße (Hinweg und Rückweg)
	int coords[]={100,250,700,250};
	if(!bZeichneStrasse("Autobahn","Auto",500,2,coords)){
		std::cerr<<"Error"<<endl;
		return;
	}

	// Autos und Fahrzeuge erstellen
	auto audi = std::make_unique<PKW>("Audi", 120.0, 10.0, 50.0);//Geschwindigkeit von 120 km/h, die auf der Autobahn auf 100 km/h begrenzt wird
	auto bmw = std::make_unique<PKW>("BMW", 140.0, 5.0, 60.0);//Nach 2 Stunden erreichen Sie das Ende der Autobahn
	auto orbea = std::make_unique<Fahrrad>("Orbea", 18.0);
	auto tesla = std::make_unique<PKW>("Tesla", 100.0); // Geschwindigkeitsbegrenzung durch Landstraße
	auto bici = std::make_unique<Fahrrad>("Bici", 25.0); // Zunächst geparkt
	auto lazer = std::make_unique<Fahrrad>("lazer", 30.0);
	// Fahrzeuge zu Straßen hinzufügen
	landstrasse.vAnnahme(std::move(audi)); // Unterwegs
	landstrasse.vAnnahme(std::move(tesla), 1.0); // Geparkt, Abfahrt in 1 Stunde
	landstrasse.vAnnahme(std::move(orbea)); // Unterwegs
	autobahn.vAnnahme(std::move(bmw));// Unterwegs
	autobahn.vAnnahme(std::move(bici), 2.0); // Geparkt, Abfahrt in 2 Stunden
	autobahn.vAnnahme(std::move(lazer)); // Unterwegs

	//Fahrzeuge auf „Straße“ zeichnen

/*
	for(const auto& fahrzeug : landstrasse.getFahrzeuge()){
		if(auto pkw = dynamic_cast<PKW*>(fahrzeug.get())){
			bZeichnePKW(pkw->getName(), std::string("Autobahn"),
						pkw->getAbschnittStrecke() / landstrasse.getLaenge(),
						pkw->dGeschwindigkeit(),
						pkw->getTankinhalt());
		}else {
			bZeichneFahrrad(fahrzeug->getName(), "Autobahn",
							fahrzeug->getAbschnittStrecke() / landstrasse.getLaenge(),
							fahrzeug->dGeschwindigkeit());
		}

		vSleep(1000); // Retraso 1 seg para visualización
	}*/
	vSetzeZeit(dGlobaleZeit);
	landstrasse.vSimulieren();
	autobahn.vSimulieren();
	vSleep(1000);
	for(int i =0;i<5;i++){
		dGlobaleZeit +=1.0;
		vSetzeZeit(dGlobaleZeit);
		landstrasse.vSimulieren();
		autobahn.vSimulieren();
		vSleep(1000);

	}
	vSleep(5000);
	vBeendeGrafik();

}

void vAufgabe_6a(){
	vertagt::VListe<int>lista;
	static std::mt19937 device(0);
	std::uniform_int_distribution<int> dist(1, 10);
	for(int i =0;i<10;i++){//Liste mit Zufallszahlen füllen
		lista.push_back(dist(device));
	}
	//Anfangsliste drucken
	lista.vAktualisieren();
	cout<<"Initiale Liste:\n ";
	for(const auto& val: lista){
		cout<<val<<" ";
	}
	//Elemente größer als 5 entfernen
	for(auto it=lista.begin();it!=lista.end();it++){
		if(*it>5){
			lista.erase(it);
		}
	}
	// Drucken Sie die Liste vor dem Aktualisieren
	std::cout << "\nListe nach dem Markieren von Löschungen (nicht aktualisiert):\n";
	for (const auto& val : lista) {
		std::cout << val << " ";
	}
    lista.vAktualisieren(); //Updates anwenden
    //Drucke die Liste nach dem Update
	std::cout << "\nListe nach Update:\n";
	for (const auto& val : lista) {
		std::cout << val << " ";
	}
	//neue Elemente hinzufügen
	lista.push_front(0);
	lista.push_back(11);
	lista.vAktualisieren();
	// Drucke die endgültige Liste
	std::cout << "\nEndgültige Liste nach Neuaufnahmen:\n";
	for (const auto& val : lista) {
		std::cout << val << " ";
	}
	std::cout << std::endl;
}


void vAufgabe_7(){

	// Initialisiere die grafische Oberfläche
	if (!bInitialisiereGrafik(1200, 1000)) {
		std::cerr << "Fehler beim Initialisieren der grafischen Benutzeroberfläche.\n";
		return;
	}

	//Kreuze erstellen
	auto kreuzung1 = std::make_shared<Kreuzung>("Kr1", 0.0);     // Ohne Tank
	bZeichneKreuzung(680, 40);
	auto kreuzung2 = std::make_shared<Kreuzung>("Kr2", 1000.0);  // 1000L Tank
	bZeichneKreuzung(680, 300);
	auto kreuzung3 = std::make_shared<Kreuzung>("Kr3", 0.0);     // Ohne Tank
	bZeichneKreuzung(680, 570);
	auto kreuzung4 = std::make_shared<Kreuzung>("Kr4", 0.0);     // Ohne Tank
	bZeichneKreuzung(320, 300);

	//Pfade erstellen und zeichnen
	//Straße erstellen und zeichnen1
	Kreuzung::vVerbinde("W12", "W21", 40.0, kreuzung1, kreuzung2, Tempolimit::Innerorts); //Geschwindigkeitsbegrenzung: 50 km/h und 40 km Länge
	int coords1[] = {680, 40, 680, 300};
	if (!bZeichneStrasse("W12", "W21", 40, 2, coords1)) {
		std::cerr << "Error al dibujar la carretera 1.\n";
		return;
	}
		//Crear y dibujar Strasse 2
		Kreuzung::vVerbinde("W23a", "W32a", 115.0, kreuzung2, kreuzung3, Tempolimit::Autobahn); //Keine Geschwindigkeitsbegrenzung und 115 km lang
		int coords2[] = {680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570};
		if (!bZeichneStrasse("W23a", "W32a", 115.0, 6, coords2)) {
			std::cerr << "Error al dibujar la carretera 2.\n";
			return;
		}

		//Crear y dibujar Strasse 3
		Kreuzung::vVerbinde("W23b", "W32b", 40.0, kreuzung2, kreuzung3, Tempolimit::Innerorts); //Geschwindigkeitsbegrenzung: 50 km/h und 40 km Länge
		int coords3[] = {680, 300, 680, 570};
		if (!bZeichneStrasse("W23b", "W32b", 40.0, 2, coords3)) {
			std::cerr << "Error al dibujar la carretera 3.\n";
			return;
		}

		//Crear y dibujar Strasse 4
		Kreuzung::vVerbinde("W24", "W42", 55.0, kreuzung2, kreuzung4, Tempolimit::Innerorts); //Geschwindigkeitsbegrenzung: 50 km/h und 55 km Länge
		int coords4[] = {680, 300, 320, 300};
		if (!bZeichneStrasse("W24", "W42", 55.0, 2, coords4)) {
			std::cerr << "Error al dibujar la carretera 4.\n";
			return;
		}

		//Crear y dibujar Strasse 5
		Kreuzung::vVerbinde("W34", "W43", 85.0, kreuzung3, kreuzung4, Tempolimit::Autobahn); //Keine Geschwindigkeitsbegrenzung und 85 km lang
		int coords5[] = {680, 570, 500, 570, 350, 510, 320, 420, 320, 300};
		if (!bZeichneStrasse("W34", "W43", 85.0, 5, coords5)) {
			std::cerr << "Error al dibujar la carretera 5.\n";
			return;
		}

		//Straße 6 anlegen und einzeichnen
		Kreuzung::vVerbinde("W44a", "W44b", 130.0, kreuzung4, kreuzung4, Tempolimit::LandstraBe); //Geschwindigkeitsbegrenzung: 100 km/h und 130 km Länge
		int coords6[] = {320, 300, 170, 300, 70, 250, 80, 90, 200, 60, 320, 150, 320, 300};
		if (!bZeichneStrasse("W44a", "W44b", 130.0, 7, coords6)) {
			std::cerr << "Error al dibujar la carretera 6.\n";
			return;
		}

		// Fahrzeuge erstellen
		auto audi = std::make_unique<PKW>("Audi", 120.0, 10.0, 50.0);//Höchstgeschwindigkeit 120 km/h, Leistung 10 L/100 Km und maximaler Tankinhalt 50L, was bei der Erstellung 25
		auto bmw = std::make_unique<PKW>("BMW", 100.0, 8.0, 60.0);//Höchstgeschwindigkeit 100 km/h, Leistung 8 L/100 Km und maximaler Tankinhalt 60L, was bei der Erstellung 30
		auto tesla = std::make_unique<PKW>("Tesla", 150.0, 5.0, 70.0); //Höchstgeschwindigkeit 150 km/h, Leistung 5 L/100 Km und maximaler Tank von 70L, was bei der Erstellung 35
		auto orbea = std::make_unique<Fahrrad>("Orbea", 18.0);
		auto bici = std::make_unique<Fahrrad>("Bici", 25.0);
		auto lazer = std::make_unique<Fahrrad>("lazer", 30.0);
		// Fahrzeuge zu KR1 hinzufügen
		kreuzung1->vAnnahme(std::move(audi));
		kreuzung1->vAnnahme(std::move(bmw), 0.5); // Zunächst 30 Minuten geparkt
		kreuzung1->vAnnahme(std::move(tesla), 1.0);// Zunächst für eine Stunde geparkt
		kreuzung1->vAnnahme(std::move(orbea));
		kreuzung1->vAnnahme(std::move(bici));
		kreuzung1->vAnnahme(std::move(lazer),1.0);
		// Zunächst für eine Stunde geparkt
		dGlobaleZeit = 0.0;
		vSetzeZeit(dGlobaleZeit);
		kreuzung1->vSimulieren();
		kreuzung2->vSimulieren();
		kreuzung3->vSimulieren();
		kreuzung4->vSimulieren();

		// Simular varios pasos
		for (int i = 0; i < 40; ++i) {
			dGlobaleZeit += 0.10;
			std::cout << "\nGlobale Zeit: " << dGlobaleZeit << " Stunden \n";
			vSetzeZeit(dGlobaleZeit);// Aktualisiere die Zeit im Diagramm
			kreuzung1->vSimulieren();
			kreuzung2->vSimulieren();
			kreuzung3->vSimulieren();
			kreuzung4->vSimulieren();
			vSleep(500); // 1 Sekunde Verzögerung für die Anzeige
		}

		vSleep(3000);
		// Beende den Graphen
		vBeendeGrafik();
}


void vAufgabe_8(){
	dGlobaleZeit = 0.0;
	// Zwei Straßen erstellen, eine mit Geschwindigkeitsbegrenzung
	    Weg landstrasse("Landstrasse", 120.0, Tempolimit::LandstraBe);//Höchstgeschwindigkeit 100 km/h

	    // Crear autos y vehículos

	    auto tesla = std::make_unique<Fahrzeug>("Tesla", 100.0); // Velocidad de limitada por LandstraBe

	    // Añadir vehículos a los caminos

	    landstrasse.vAnnahme(std::move(tesla), 3.0); // Estacionado, comienza a moverse en 1 hora

		std::cout << "Ausgangszustand von Straßen und Fahrzeugen:\n";
		Weg::vKopf(std::cout);
		std::cout << landstrasse << std::endl;
		Fahrzeug::vKopf(std::cout);
		for (const auto& fahrzeug : landstrasse.getFahrzeuge()) {
			std::cout << *fahrzeug << std::endl;
		}

		// Mehrere Schritte simulieren
	    for (int i = 0; i < 16; ++i) {
	        dGlobaleZeit += 0.4;
	        std::cout << "\nGlobale Zeit: " << dGlobaleZeit << " Stunden\n";
	        // Straße simulieren
	        landstrasse.vSimulieren();
	        // Autobahn simulieren

	        // Zeige den Status nach jeder Simulation
	       	        std::cout << "\nAktueller Straßenstatus:Aktueller Straßenstatus:\n";
	       	        Weg::vKopf(std::cout);
	       	        std::cout << landstrasse << std::endl;
	       	        Fahrzeug::vKopf(std::cout);
	       			for (const auto& fahrzeug : landstrasse.getFahrzeuge()) {
	       				std::cout << *fahrzeug << std::endl;
	       			}

	       }

	     }

int main() {
	//vAufgabe1();
	//vAufgabe1a();
	//vAufgabe2();
	//vAufgabe_3();
	//vAufgabe_53_1();
	//vAufgabe_53_2();
	//vAufgabe_54_1a();
	//vAufgabe_54_1();
	//vAufgabe_4();
	//vAufgabe5();
	//vAufgabe_55_2();
	//vAufgabe_54_4();
	//vAufgabe6();
	//vDepurador();
	//vAufgab6graph();
	//vAufgabe_6a();
	vAufgabe_7();
	//vAufgabe_8();
    return 0;
}
