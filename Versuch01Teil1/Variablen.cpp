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
    int iSumme, iQuotient;
    double dSumme=0;
    double dQuotient =0;
    
    // Hier folgt Ihr eigener Code
    cout<<"Give 1 integer number: "; cin>>iErste;
    cout<<"Give another integer number: "; cin>>iZweite;
    iSumme = iErste +iZweite;
    iQuotient = iErste/iZweite;
    
    cout<<"The sum is: "<<iSumme<<endl;
    cout<<"The quotient is: "<<iQuotient<<endl;

    //calculate with double
    dSumme = static_cast<double>(iErste)+iZweite;
    dQuotient = static_cast<double>(iErste)/iZweite;
    cout<<"Result: "<<endl;
    cout<<"The result is: "<<iSumme<<endl;
    cout<<"The Quotient is: "<<dQuotient<<endl;

    return 0;
    
}
