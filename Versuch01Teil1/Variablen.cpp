//////////////////////////////////////////////////////////////////////////////
// Praktikum Informatik 1 
// 
// Versuch 1.1: Datentypen und Typumwandlung
//
// Datei:  Variablen.cpp
// Inhalt: Hauptprogramm
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
int main()
{
    int iErste = 0;
    int iZweite = 0;
    int iSumme=0;
    int iQuotient =0;
    
    // Hier folgt Ihr eigener Code
    cout<<"Give 1 integer number: "; cin>>iErste;
    cout<<"Give another integer number: "; cin>>iZweite;
    iSumme = iErste +iZweite;
    iQuotient = iErste/iZweite;
    
    cout<<"The sum is: "<<iSumme<<endl;
    cout<<"The quotient is: "<<iQuotient<<endl;
    return 0;
    
}
