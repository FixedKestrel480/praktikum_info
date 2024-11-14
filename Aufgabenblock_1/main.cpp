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
#include <memory>
#include <vector>
#include <iomanip>
#include "Fahrrad.h"
using namespace std;

double dGlobaleZeit = 0.0;

//Funktion die man es benutzt um verschiedene Instancias von Fahrzeug zu erstellen
void vAufgabe1(){
	//Statische Fahrzeuge erstellen mit den default Konstruktor
	//static object is an object than does not move when forces are applied to it, perform early run time at compiletime, happens by default
	Fahrzeug Auto1;// mit den default Konstruktor//-----------------
	Fahrzeug Auto2("Auto 1");// mit parameter Konstruktor///---------------

	//dynamic will move with forces and other, perform during run time, dynamic binding
	//Dynamische Fahrzeuge crear
	Fahrzeug* pFahrzeug1 = new Fahrzeug();//Mit default Konstruktor//-------------
	Fahrzeug* pFahrzeug2 = new Fahrzeug("auto 3");

	//liberar memoria de los dinámicos
	delete pFahrzeug1;
	delete pFahrzeug2;

	// Crear vehículos usando smart pointers
	// en vez de escribir esto: std::unique_ptr<Fahrzeug> pSmartFahrzeug1 = std::make_unique<Fahrzeug>("Auto4");
	//el auto funciona a partir de que este sabe cual es el tipo de la variable que se está utilizando, lo deduce
	//---------
	auto pPointerFahrzeug1 = make_unique<Fahrzeug>(); //aqui es un puntero inteligente, que hace que sea unico, unico dueño del objeto, cuando ya no se usa, se libera la memoria automaticamente
	//con el make unique estamos creando un nuevo objeto en la memoria, hacer que el unique apunte a el, se encarga de administrar la memoria, osea cuando se destruye, memoria se libera
	auto pPointerFahrzeug4= make_unique<Fahrzeug>("Auto4");
	auto pPointerFahrzeug2 = make_shared<Fahrzeug>();//shared permite que multiples punteros  apunten al mismo objeto
	auto pPointerFahrzeug3 = make_shared<Fahrzeug>("Auto5");

	 // Compartir el puntero shared_ptr
//--------------------------
	cout << "Use count for Auto5 before assignment: " << pPointerFahrzeug3.use_count() << endl; //cuantos punteros están apuntando al mismo objeto
	auto pPointerFahrzeug3Copy = pPointerFahrzeug3;
	cout << "Use count for Auto6 after assignment: " << pPointerFahrzeug3Copy.use_count() << endl;// cuantos ahora
	cout<<"Puntero a  memoria de pPointerFahrzeug3 despues asignacion: "<<pPointerFahrzeug3<<"Y num de ref a pPointerFahrzeug3Copy: "<<pPointerFahrzeug3Copy<<endl;
	//se usa para asegurarse que el objeto no se elimine mientras todavía hayn un puntero apuntando a él.

	cout<<"Puntero von pPointerFahrzeug4 vor die Modifikation: "<<(pPointerFahrzeug4?"Ja":"Nein")<<endl;//Hier ist Ja, weil der Zeiger apunta zu dieser OBjekt
	auto pPointerFahrzeug5 = move(pPointerFahrzeug4);
	cout<<"Zeiger von pPointerFahrzeug4 nach die Aktivation von pPointerFahrzeug5"<<(pPointerFahrzeug4?"Ja":"Nein")<<endl;//Hier Nein, weil Zeiger zu den anderen Objekt apunta, weil wir es bewegt haben

	    // Crear vector de unique_ptr
	//crear vector como si fuera nuestra caja para guardar, y el push_back es el brazo mecanico que mueve los objetos y los guarda en la caja
	// <vector> wird eingefügt, um dieses Element verwenden zu können, das einzelne Smart-Pointer-Objekte vom Typ Fahrzeug speichert.
	vector<unique_ptr<Fahrzeug>> vUniqueFahrzeuge; //declara vector que almacenará objetos Fahrzeug gestionados por unique, cada uno tiene la propiedad exclusiva sobre el objeto que tien
	vUniqueFahrzeuge.push_back(move(pPointerFahrzeug1));
	vUniqueFahrzeuge.push_back(move(pPointerFahrzeug5));

    //vUniqueFahrzeuge.push_back(std::make_unique<Fahrzeug>("Auto7"));//Añade objeto Fahrzeug al vector, que crea objeto en memoria dinamica
    //vUniqueFahrzeuge.push_back(std::make_unique<Fahrzeug>("Auto8")); //otro objeto

	//Der Vektor wird gelöscht und die Destruktoren, die auf pPointerFahrzeug1 und pPointerFahrzeug5 zeigen, werden ausgeführt.
    vUniqueFahrzeuge.clear(); //destructor

	    // Crear vector de shared_ptr
    vector<shared_ptr<Fahrzeug>> vSharedFahrzeuge;
    vSharedFahrzeuge.push_back(pPointerFahrzeug2); // Sin move
    vSharedFahrzeuge.push_back(move(pPointerFahrzeug3)); // Con move

	    // Mostrar la cantidad de referencias de los objetos en el vector
    cout << "Use count for pPointerFahrzeug2: " << pPointerFahrzeug2.use_count() << endl;
    cout << "Use count for pPointerFahrzeug3 after move: " << pPointerFahrzeug3Copy.use_count() << endl;

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
	vector<unique_ptr<Fahrzeug>> vUniqueFahrzeuge; //Vektor um die Fahrzeuge zu speichern
	for(int i = 1; i<=3;i++){
		string sName; //Name der Fahrzeuge
		double dMaxGe; //Geschwindigkeit der Fahrzeuge
		cout<<"Name der Fahrzeug: "<<i<<endl;cin>>sName; //Damit der Benutzer die Name der Fahrzeug schreiben kann
		cout<<"Maximal Geschwindigkeit der Fahrzeug: "<<i<<endl;cin>>dMaxGe;// Damit der Benutzer die Maximal Geschwindigkeit schreiben kann
		vUniqueFahrzeuge.push_back(make_unique<Fahrzeug>(sName,dMaxGe));// Speicherung von Fahrzeugdaten
	}
	double dZeitschrittweite=0.5;
	int iSchritte=10;
	for(int j=0;j<=iSchritte;j++)
	{
		dGlobaleZeit += dZeitschrittweite;
		cout<<"Globale Zeit: "<<dGlobaleZeit<<"Stunde(n)"<<endl;
		Fahrzeug::vKopf();
		for(auto&fahrzeug:vUniqueFahrzeuge){
			fahrzeug->vSimulieren();
			fahrzeug->vAusgeben();
			cout<<endl;
		}
	}



}
//Um die Funktion zu testen
void vAufgabe1_5_6(){
	Fahrzeug v1 = Fahrzeug("volkswagen",180);
	auto v2 = make_unique<Fahrzeug>("Hyundai",-20);
	auto v3 = make_shared<Fahrzeug>("Toyota",150);
	 Fahrzeug::vKopf();
	v1.vAusgeben();
	cout<<endl;
	v2->vAusgeben();
	cout<<endl;
	v3->vAusgeben();
	cout<<endl;

	auto v4 = move(v2);
	v4->vAusgeben();
	cout<<endl;
	auto v5 = v3;
	v5->vAusgeben();
	cout<<endl;

	vector<unique_ptr<Fahrzeug>> uniqueFahrzeuge; //Se crea vector de punteros unicos
	uniqueFahrzeuge.push_back(move(v4)); //Se mueve y anexa al vector el puntero de Vehiculo4 que antes era vehiculo2
	uniqueFahrzeuge.push_back(make_unique<Fahrzeug>("Kia",180)); //Se crea nuevo puntero único en el vector
	Fahrzeug::vKopf(); //Cabecera
	for (const auto& fahrzeug : uniqueFahrzeuge) { //Muestra los datos de los elementos del vector
		fahrzeug->vAusgeben();
		cout << endl;
	}
	vector<shared_ptr<Fahrzeug>>sharedFahrzeuge;
	sharedFahrzeuge.push_back(v5);
	sharedFahrzeuge.push_back(make_shared<Fahrzeug>("Ferrari",220));
	Fahrzeug::vKopf(); //cabecera
	for (const auto& fahrzeug : sharedFahrzeuge) { //Muestra los datos de los elementos del vector
		fahrzeug->vAusgeben();
		cout << endl;
	}

}

void vSimulieren1_7(){
	Fahrzeug f1 = Fahrzeug("Tesla",25.5);
	f1.vSimulieren();

}

void vSimuFahrzeuge1_8(double Zeitinc, vector<shared_ptr<Fahrzeug>>&fahrzeuge){
	dGlobaleZeit += Zeitinc;
	cout<<"Globale Zeit: "<<dGlobaleZeit<<"Stunden"<<endl;
	for(auto& fahrzeug:fahrzeuge){
		fahrzeug->vSimulieren();
	}
	for(const auto&fahrzeug:fahrzeuge){
		fahrzeug->vAusgeben();
		cout<<endl;
	}

}

void vAufgaben1_8(){

	dGlobaleZeit =0.0;
	vector<shared_ptr<Fahrzeug>> sharedFahrzeuge; //Se crea vector de punteros compartidos para probar con varios vehículos
	sharedFahrzeuge.push_back(make_shared<Fahrzeug>("B_Giant",5.1)); //Se crea un elemento nuevo en vector
	sharedFahrzeuge.push_back(make_shared<Fahrzeug>("A_Acura",165.2)); //Se crea un elemento nuevo en vector
	sharedFahrzeuge.push_back(make_shared<Fahrzeug>("A_Volvo",235.6)); //Se crea un elemento nuevo en vector
	sharedFahrzeuge.push_back(make_shared<Fahrzeug>("B_Carrera",23.41)); //Se crea un elemento nuevo en vector
	sharedFahrzeuge.push_back(make_shared<Fahrzeug>("B_Orbea",-2)); //Se crea un elemento nuevo en vector y se prueba con una velocidad máxima negativa
	sharedFahrzeuge.push_back(make_shared<Fahrzeug>("A_Descom",0)); //Se crea un elemento nuevo en vector

	vSimuFahrzeuge1_8(1.0,sharedFahrzeuge);
	vSimuFahrzeuge1_8(0.5,sharedFahrzeuge);
	vSimuFahrzeuge1_8(1.0,sharedFahrzeuge);
}

void vAufgabe1_4_3_1(){
	auto Fahrrad1 = Fahrrad("Nike",23);
	Fahrrad1.vSimulieren();
	Fahrrad1.vAusgeben();
}
int main() {
	//vAufgabe1_5_6();
	//vSimulieren1_7();
	//vAufgaben1_8();
	//vAufgabe1();
	//vAufgabe1a();
	vAufgabe1_4_3_1();

    return 0;
}
