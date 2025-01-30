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
#include "Fahrrad.h"
#include "PKW.h"
#include <cmath> // Fúr std::fabs()
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::make_unique;
using std::make_shared;


double dGlobaleZeit = 0.0; //4.2.6
//Globale Variable für die Simulationszeit

//Funktion die man es benutzt um verschiedene Instancias von Fahrzeug zu erstellen
//4.2.4
void vAufgabe1(){ //4.2.9
	//Statische Fahrzeuge erstellen mit den default Konstruktor
	Fahrzeug Auto1;////Fahrrad1-Objekt statisch und mit dem Standardkonstruktor erstellen
	Fahrzeug Auto2("Auto 1");//Auto1-Objekt statisch und den Konstruktor mit Namensparameter erstellen

	//Dynamische Fahrzeuge erzeugen
	Fahrzeug* pFahrzeug1 = new Fahrzeug();//pFahrzeug1-Objekt dynamisch mit new und dem Standardkonstruktor erstellen
	Fahrzeug* pFahrzeug2 = new Fahrzeug("auto 3"); //pFahrzeug2-Objekt dynamisch mit new und dem Konstruktor mit Namensparameter erstellen

	delete pFahrzeug1;//pFahrzeug1-Objekt löschen, um Speicher freizugeben
	delete pFahrzeug2;//pFahrzeug2-Objekt löschen, um Speicher freizugeben


	//Erstellung einen einzelnen Smart-Pointer mit dem Konstruktor von defualt
	auto pPointerFahrzeug1 = make_unique<Fahrzeug>(); //aqui es un puntero inteligente, que hace que sea unico, unico dueño del objeto, cuando ya no se usa, se libera la memoria automaticamente
	//con el make unique estamos creando un nuevo objeto en la memoria, hacer que el unique apunte a el, se encarga de administrar la memoria, osea cuando se destruye, memoria se libera
	auto pPointerFahrzeug4= make_unique<Fahrzeug>("Auto4"); //Erstellung einen eindeutigen intelligenten Zeiger mit dem Konstruktor mit Namensparameter, Form 1
	auto pPointerFahrzeug2 = make_shared<Fahrzeug>();//Erstelle standardmäßig einen eindeutigen gemeinsamen Zeiger mit dem Konstruktor
	auto pPointerFahrzeug3 = make_shared<Fahrzeug>("Auto5");//Erstellung einen gemeinsamen Smart-Pointer mit dem Konstruktor mit Namensparameter

	//Kopiert den gemeinsamen Zeiger nach pAuto5 und die Anzahl der Zeiger, die dasselbe Objekt teilen, wird erhöht. Die erste Ausgabe von pAuto4.use_count()
		//Zuerst ist es 1 und nach der Zuweisung oder dem Kopieren wird es auf 2 erhöht
	cout << "Count für Auto5 vor der Zuweisung: " << pPointerFahrzeug3.use_count() << endl; //Wie viel Zeiger gibt es in den Objekt
	auto pPointerFahrzeug3Copy = pPointerFahrzeug3;
	cout << " Count für Auto6 nach der Zuweisung:: " << pPointerFahrzeug3Copy.use_count() << endl;// Wie viel jetzt
	cout<<"Zeiger auf den Speicher von pPointerFahrzeug3 nach der Zuweisung: "<<pPointerFahrzeug3<<"Und Referenznummer zu pPointerFahrzeug3Copy: "<<pPointerFahrzeug3Copy<<endl;


//if pPointerFahrzeug != Nullptr
	//Die Funktion pAuto3.use_count() ist für einzelne Zeiger nicht möglich und es ist auch nicht möglich, diese zu kopieren. Es kann nur verschoben werden. Nach dem Verschieben wird pAuto3 zu nullptr
	cout<<"Zeiger von pPointerFahrzeug4 vor die Modifikation: "<<(pPointerFahrzeug4?"Ja":"Nein")<<endl;//Hier ist Ja, weil der Zeiger zeigt zu dieser OBjekt
	auto pPointerFahrzeug5 = move(pPointerFahrzeug4);
	cout<<"Zeiger von pPointerFahrzeug4 nach die Aktivation von pPointerFahrzeug5"<<(pPointerFahrzeug4?"Ja":"Nein")<<endl;//Hier Nein, weil Zeiger zu den anderen Objekt zeigt, weil wir es bewegt haben


	// <vector> wird eingefügt, um dieses Element verwenden zu können, das einzelne Smart-Pointer-Objekte vom Typ Fahrzeug speichert.
	std::vector<std::unique_ptr<Fahrzeug>> vUniqueFahrzeuge; //deklariert einen Vektor, der eindeutig verwaltete Fahrzeugobjekte speichert, wobei jedes Objekt das ausschließliche Eigentum an dem Objekt hat, über das es verfügt
	vUniqueFahrzeuge.push_back(move(pPointerFahrzeug1));
	vUniqueFahrzeuge.push_back(move(pPointerFahrzeug5));

	//Der Vektor wird gelöscht und die Destruktoren, die auf pPointerFahrzeug1 und pPointerFahrzeug5 zeigen, werden ausgeführt.
    vUniqueFahrzeuge.clear(); //destructor

	    // Crear vector de shared_ptr
   std::vector<std::shared_ptr<Fahrzeug>> vSharedFahrzeuge;
    vSharedFahrzeuge.push_back(pPointerFahrzeug2); // ohne move
    vSharedFahrzeuge.push_back(move(pPointerFahrzeug3)); // Mit move

    // Zeigt die Anzahl der Referenzen der Objekte im Vektor an
    cout << "count für pPointerFahrzeug2: " << pPointerFahrzeug2.use_count() << endl;
    cout << "count für pPointerFahrzeug3: " << pPointerFahrzeug3Copy.use_count() << endl;

    vSharedFahrzeuge.clear();

    Fahrzeug::vKopf();
    Auto1.vAusgeben();
    cout<<endl;
    Auto2.vAusgeben();
    cout<<endl;
    pPointerFahrzeug1->vAusgeben(); // Fahrzeugdaten drucken „Auto4“ (unique_ptr)
    cout << std::endl;
    pPointerFahrzeug2->vAusgeben();//Fahzeugdaten von Auto5 (shared_ptr) drucken
    cout << std::endl;

}
void vAufgabe1a(){
	dGlobaleZeit=0.0;
	std::vector<std::unique_ptr<Fahrzeug>> vUniqueFahrzeuge; //Vektor um die Fahrzeuge zu speichern
	for(int i = 1; i<=3;i++){
		string sName; //Name der Fahrzeuge
		double dMaxGe; //Geschwindigkeit der Fahrzeuge
		cout<<"Name der Fahrzeug: "<<i<<endl;cin>>sName; //Damit der Benutzer die Name der Fahrzeug schreiben kann
		cout<<"Maximal Geschwindigkeit der Fahrzeug: "<<i<<endl;cin>>dMaxGe;// Damit der Benutzer die Maximal Geschwindigkeit schreiben kann
		vUniqueFahrzeuge.push_back(make_unique<Fahrzeug>(sName,dMaxGe));// Speicherung von Fahrzeugdaten
	}

	// Simulation: Erhöhen Sie die globale Zeit bei jedem Zeitschritt
	const double dZeitschrittweite=0.5; // Zeitinkrement in Bruchteilen einer Stunde
	const int iSchritte=10; // Anzahl der Zeitschritte für die Simulation
	for(int j=0;j<=iSchritte;j++)
		//globale Zeit erhöhen
	{
		dGlobaleZeit += dZeitschrittweite;
		cout<<"Globale Zeit: "<<dGlobaleZeit<<"Stunde(n)"<<endl;
		Fahrzeug::vKopf(); //tabelle
		for(auto&fahrzeug:vUniqueFahrzeuge){ //Daten drucken
			fahrzeug->vSimulieren();
			fahrzeug->vAusgeben();
			cout<<endl;
		}
	}



}
//Um die Funktion zu testen

void vAufgabe2(){ //4.3.4
	int inumPKW,inumFahrrad;
	dGlobaleZeit=0.0;
	// Lesen Sie die Anzahl der zu erstellenden Autos und Fahrräder ab
	cout<<"Wie viele autos erzeugen: ";
	cin>>inumPKW;
	cout<<"Wie viele Fahrrad erzeugen: ";
	cin>>inumFahrrad;
	// Erstelle den Vektor zum Speichern der Auto- und Fahrradfahrzeugobjekte
	std::vector<std::unique_ptr<Fahrzeug>>fahrzeuge;
	for(int i=0;i<inumPKW;i++){ //Autos erzeugen
		fahrzeuge.push_back(make_unique<PKW>("Auto"+std::to_string(i+1),100.0+i*5,10));
	}
	for(int i=0;i<inumFahrrad;i++){ //Fahrrad erzeugen
		fahrzeuge.push_back(make_unique<Fahrrad>("Fahrrad"+std::to_string(i+1),15.0+i*1));
	}
//Start drucken
	cout<<"In Zustand: ";
	Fahrzeug::vKopf();
	for(const auto&fahrzeug:fahrzeuge){
		fahrzeug->vAusgeben();
		cout<<endl;
	}
	cout<<"---------------------------------------------------------------------------"<<endl;

	//5 Male simulieren
	for(int iSchritt=1; iSchritt<=6;iSchritt++){
		dGlobaleZeit+=1;
		cout<<"Simulation-Globale Zeit: "<<dGlobaleZeit<<" Stunden"<<endl;
		for(auto& fahrzeug:fahrzeuge){
			fahrzeug->vSimulieren();
		}

		//Zustand nach die Simulation
		Fahrzeug::vKopf();
		for(const auto&fahrzeug:fahrzeuge){
			fahrzeug->vAusgeben();
			//std::cout << *fahrzeug;
			cout<<endl;
		}
		cout<<"------------------------------------------------------------------------"<<endl;
		// Prüfen Sie, ob es Zeit ist, PKWs aufzutanken
		double dresidual=std::fmod(dGlobaleZeit,3.0); // Berechnen Sie das Residuum der Division von dGlobaleZeit durch 3, um zu bestimmen, dass dGlobaleZeit ein Vielfaches von 3 war
		double dToleranz = 0.001; // Akzeptable Toleranz
		if(std::fabs(dresidual)<dToleranz||std::fabs(dresidual-3.0)<dToleranz){ //Stellen Sie sicher, dass der Restwert nahe bei Null oder 3 Stunden liegt
			cout<<"Auto alle 3 Stunden nachfüllen"<<endl; /////
			for(auto& fahrzeug:fahrzeuge){
				auto pkw = dynamic_cast<PKW*>(fahrzeug.get());
				if(pkw){
					pkw->dTanken();
				}
			}
		}

	}
}

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

void vAufgabe1_5_6(){
	//Test von Aufgabe 4.2.5-6
	Fahrzeug v1 = Fahrzeug("volkswagen",180);
	//cuando recomiendo hacerun unique y un shared puntero
	auto v2 = std::make_unique<Fahrzeug>("Hyundai",-20);
	auto v3 = std::make_shared<Fahrzeug>("Toyota",150);
	 Fahrzeug::vKopf(); //Tabelle
	v1.vAusgeben(); //Daten v1 //para que le pueda seguir agregando datos al tipo de ob
	cout<<endl;
	v2->vAusgeben(); //Daten v2
	cout<<endl;
	v3->vAusgeben(); //Daten v3
	cout<<endl;

	auto v4 = move(v2); //Einzelnen Zeiger von v4 nach v2 bewegen
	v4->vAusgeben();// v4-Daten, die von v2 stammen
	cout<<endl;
	auto v5 = v3;//Zeiger wird zwischen v5 und v3 geteilt
	v5->vAusgeben();
	cout<<endl;

	//puedo meter el shared en el unique??
	std::vector<std::unique_ptr<Fahrzeug>> uniqueFahrzeuge; //Es wird ein Vektor eindeutiger Zeiger erstellt
	uniqueFahrzeuge.push_back(move(v4)); //Der Zeiger von v4, der zuvor v2 war, wird verschoben und an den Vektor angehängt
	uniqueFahrzeuge.push_back(make_unique<Fahrzeug>("Kia",180)); //Neuer eindeutiger Zeiger wird im Vektor erstellt
	Fahrzeug::vKopf(); //Tabelle
	for (const auto& fahrzeug : uniqueFahrzeuge) { //Zeigt die Daten der Vektorelemente
		fahrzeug->vAusgeben();
		cout << endl;
	}
	std::vector<std::shared_ptr<Fahrzeug>>sharedFahrzeuge; //Vektor gemeinsam genutzter Zeiger wird erstellt
	sharedFahrzeuge.push_back(v5);//Kopie von v3 ist im Vektor enthalten
	sharedFahrzeuge.push_back(make_shared<Fahrzeug>("Ferrari",220)); //Kopie von v5 ist im Vektor enthalten
	Fahrzeug::vKopf(); //Tabelle
	for (const auto& fahrzeug : sharedFahrzeuge) { //Zeigt die Daten der Vektorelemente
		fahrzeug->vAusgeben();
		cout << endl;
	}

}

void vSimulieren1_7(){ //Test 4.2.7
	Fahrzeug f1 = Fahrzeug("Tesla",25.5);
	f1.vSimulieren();

}

void vSimuFahrzeuge1_8(double dZeitstei, std::vector<std::shared_ptr<Fahrzeug>>&fahrzeuge){ //Daten für alle Fahrzeuge in einem gemeinsamen Fahrzeugvektor simulieren und anzeigen
	dGlobaleZeit += dZeitstei; //Inkrementiert man die globale Zeit in dZeitstei
	cout<<"Globale Zeit: "<<dGlobaleZeit<<"Stunden"<<endl; //Zeigt die globale Zeit
	Fahrzeug::vKopf();
	for(auto& fahrzeug:fahrzeuge){//Zeigt die Daten der Vektorelemente an.
		fahrzeug->vSimulieren();
		fahrzeug->vAusgeben();
		cout<<endl;
	}

}

void vAufgaben1_8(){

	dGlobaleZeit =0.0;
	std::vector<std::shared_ptr<Fahrzeug>> sharedFahrzeuge; //Vektor gemeinsam genutzter Zeiger wird zum Testen mit mehreren Fahrzeugen erstellt
	sharedFahrzeuge.push_back(make_shared<Fahrzeug>("B_Giant",5.1)); //Ein neues Element wird im Vektor erstellt
	sharedFahrzeuge.push_back(make_shared<Fahrzeug>("A_Acura",165.2)); //Ein neues Element wird im Vektor erstellt
	sharedFahrzeuge.push_back(make_shared<Fahrzeug>("A_Volvo",235.6)); //Ein neues Element wird im Vektor erstellt
	sharedFahrzeuge.push_back(make_shared<Fahrzeug>("B_Carrera",23.41)); //Ein neues Element wird im Vektor erstellt
	sharedFahrzeuge.push_back(make_shared<Fahrzeug>("B_Orbea",-2)); //Ein neues Element wird im Vektor erstellt und mit einer negativen Maximalgeschwindigkeit getestet
	sharedFahrzeuge.push_back(make_shared<Fahrzeug>("A_Descom",0));

	vSimuFahrzeuge1_8(1.0,sharedFahrzeuge);
	vSimuFahrzeuge1_8(0.5,sharedFahrzeuge);
	vSimuFahrzeuge1_8(1.0,sharedFahrzeuge);
}

void vAufgabe1_4_3_1(){
//Test 4.3.2
	std::vector<std::unique_ptr<Fahrzeug>>fahrzeuge;
	fahrzeuge.push_back(std::make_unique<PKW>("Auto1", 150.0, 8.5));    // Verbrauch: 8,5 L/100km, Tank: 55 L (Standard)
	fahrzeuge.push_back(std::make_unique<PKW>("Auto2", 120.0, 6.0, 60.0)); // Verbrauch: 6,0 L/100km, Tank: 60 L
	fahrzeuge.push_back(std::make_unique<PKW>("Auto3", 100.0, 12.0, 50.0)); // Verbrauch: 12,0 L/100km, Tank: 50 L

	// Zeigt den Ausgangsstatus der Fahrzeuge an
	cout << "Ausgangszustand" << endl;
	Fahrzeug::vKopf();
	for (const auto& fahrzeug : fahrzeuge) {
		fahrzeug->vAusgeben();
		cout << endl;
	}
	cout << "-------------------------------------------------------------"  << endl;

	// 5 Zeitschritte lang simulieren
	for(int iSchritte=1;iSchritte<=5;iSchritte++){
		dGlobaleZeit +=1; // Erhöht die globale Zeit um 1 Stunde
		cout<<"Globale Zeit: "<<dGlobaleZeit<<"Stunden"<<endl;
		for(auto& fahrzeug:fahrzeuge){
			fahrzeug->vSimulieren(); // Man ruft die Simulation jedes Fahrzeugs auf
		}
		// Status nach jedem Simulationsschritt anzeigen
		Fahrzeug::vKopf();
		for (const auto& fahrzeug : fahrzeuge) {
			fahrzeug->vAusgeben();
			cout << endl;
		}
		cout << "-------------------------------------------------------------"  << endl;
	}

	dynamic_cast<PKW*>(fahrzeuge[0].get())->dTanken(20.0); //20 Liter werden in den Tank gefüllt
	dynamic_cast<PKW*>(fahrzeuge[1].get())->dTanken(); //Tank füllen
	dynamic_cast<PKW*>(fahrzeuge[2].get())->dTanken(60.0); // Es kommen 60 Liter hinzu, aber der Tank ist kleiner und muss gefüllt werden
	cout << "Status nach Betankung der Fahrzeuge:" << endl;
	Fahrzeug::vKopf();
	for (const auto& fahrzeug : fahrzeuge) {
		fahrzeug->vAusgeben();
		cout << std::endl;
	}
	cout << "-------------------------------------------------------------" << endl;
	//
	// 5 Zeitschritte lang simulieren
	for (int iSchritte = 1; iSchritte <= 5; ++iSchritte) {
		dGlobaleZeit += 1;  // Erhöht die globale Zeit um 1 Stunde
		cout << "Simulation - Globale Zeit: " << dGlobaleZeit << " Stunden" << endl;
		for (auto& fahrzeug : fahrzeuge) {
			fahrzeug->vSimulieren();  // Man ruft die Simulation jedes Fahrzeugs auf
		}
		// Status nach jedem Simulationsschritt anzeigen
		Fahrzeug::vKopf();
		for (const auto& fahrzeug : fahrzeuge) {
			fahrzeug->vAusgeben();
			cout << endl;
		}
		cout << "-------------------------------------------------------------"  << endl;
	}
}

void vAufgabe2_1_2_3(){
	std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge;
	fahrzeuge.push_back(std::make_unique<PKW>("Auto1", 120.0, 8.5));
	fahrzeuge.push_back(std::make_unique<Fahrrad>("Bici1", 25.0));
	fahrzeuge.push_back(std::make_unique<PKW>("Auto2",100.0,6.0,60.0));
	// Tabelle Drucken
	Fahrzeug::vKopf(std::cout);
	// Den operator << um die Fahrzeuge zu drucken
	for (const auto& fahrzeug : fahrzeuge) {
		std::cout << *fahrzeug << endl;
	}
	// Individuelle PKW- und Fahrrad-Instanzen erstellen
	auto pPKW = make_unique<PKW>("Auto3", 110.0, 9.0);
	auto pFahrrad = make_unique<Fahrrad>("Bici2", 20.0);
	// Tabelle Drucken
	Fahrzeug::vKopf(std::cout);
	// Drucken mit dem <<-Operator
	cout << *pPKW << endl;
	cout << *pFahrrad << endl;


	//Testen Sie die Funktionsweise der <-Operatorüberladung
	dGlobaleZeit+=1.0;
	for (auto& fahrzeug : fahrzeuge) {
		fahrzeug->vSimulieren(); // Rufen Sie die Simulation jedes Fahrzeugs auf
	}
	// Simulation für individuell erstellte Objekte durchführen
	pPKW->vSimulieren();
	pFahrrad->vSimulieren();
	// Tabelle drucken
	Fahrzeug::vKopf(std::cout);
	// Verwenden Sie den <<-Operator, um Fahrzeuge anzuzeigen
	for (const auto& fahrzeug : fahrzeuge) {
		std::cout << *fahrzeug << endl;
	}
	// Mit dem <<-Operator jeder Unterklasse drucken
	cout << *pPKW << endl;
	cout << *pFahrrad << endl;
	cout << "Vergleich von Fahrzeugen nach zurückgelegter Strecke:"<<endl;

	for (size_t i = 0; i < fahrzeuge.size(); ++i) {
		for (size_t j = i + 1; j < fahrzeuge.size(); ++j) {
			const auto& fahrzeug1 = fahrzeuge[i]; //copia deinformacion, sobrecargandoel operado =, sino sobrecargara el este comolo estoy haciendo daría error,porque el vector es con unique
			const auto& fahrzeug2 = fahrzeuge[j];

			if (*fahrzeug1 < *fahrzeug2) {
				cout << fahrzeug1->getName() << " hat eine geringere zurückgelegte Strecke als " << fahrzeug2->getName() << endl;
			} else {
				cout << fahrzeug1->getName() << " mehr oder die gleiche Strecke zurückgelegt hat wie " << fahrzeug2->getName() << endl;
			}
		}
	}
	cout << "Vergleich von Fahrzeugen nach zurückgelegter Strecke von individuell erstellten Objekten:"<<endl;
	if (*pPKW < *pFahrrad) {
		cout << pPKW->getName() << " hat eine geringere zurückgelegte Strecke als" << pFahrrad->getName() << endl;
	} else {
		cout << pPKW->getName() << " mehr oder die gleiche Strecke zurückgelegt hat wie " << pFahrrad->getName() << endl;
	}
}

void vAufgabe2_5(){
	// Zwei Fahrzeugobjekte testen, ohne dass Daten wie p_iID kopiert werden
	Fahrzeug Auto1 = Fahrzeug("BM",120);
	Fahrzeug Auto2 = Fahrzeug("Tesla",220);
	cout<<"Daten vorher: "<<endl;
	Fahrzeug::vKopf();
	cout<<Auto1<<endl;
	cout<<Auto2<<endl;
	Auto2 = Auto1;
	cout<<"Daten nacher: "<<endl;
	Fahrzeug::vKopf();
	cout<<Auto1<<endl;
	cout<<Auto2<<endl;

}

int main() {
	//vAufgabe1_5_6();
	//vSimulieren1_7();
	//vAufgaben1_8();
	//vAufgabe1();
	//vAufgabe1a();
	//vAufgabe1_4_3_1();
	vAufgabe2();
	//vAufgabe2_1_2_3();
	//vAufgabe2_5();
	//vAufgabe_3();
    return 0;
}
