/*
 * Fahrzeug.cpp
 *
 *  Created on: Nov 1, 2024
 *      Author: Karime Soriano
 *
 *
 */

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <iomanip>

#include <limits>
//cbasfg
class Fahrzeug {
protected:
    static int p_iMaxID;  // Klassenvariable für eindeutige ID-Zuweisung
    int p_iID;
    std::string p_sName;
    double p_dMaxGeschwindigkeit;
    double p_dGesamtStrecke;
    double p_dGesamtZeit;
    double p_dZeit;

public:
    // Konstruktor mit Name und optionaler Maximalgeschwindigkeit
    Fahrzeug(const std::string& name, double maxGeschwindigkeit = 0.0)
        : p_sName(name), p_dMaxGeschwindigkeit(maxGeschwindigkeit),
          p_dGesamtStrecke(0.0), p_dGesamtZeit(0.0), p_dZeit(0.0), p_iID(++p_iMaxID) {
        if (p_dMaxGeschwindigkeit < 0) {
            p_dMaxGeschwindigkeit = 0.0;
        }
        std::cout << "Fahrzeug " << p_sName << " mit ID " << p_iID << " erstellt.\n";
    }

    virtual ~Fahrzeug() {
        std::cout << "Fahrzeug " << p_sName << " mit ID " << p_iID << " gelöscht.\n";
    }

    // Statische Funktion für Überschrift
    static void vKopf() {
        std::cout << "ID    Name       MaxGeschwindigkeit  Gesamtstrecke\n"
                  << "---------------------------------------------\n";
    }

    // Ausgabe der Fahrzeugdaten
    virtual void vAusgeben() const {
        std::cout << std::setw(4) << p_iID << "  "
                  << std::setw(10) << p_sName << "  "
                  << std::setw(16) << p_dMaxGeschwindigkeit << "  "
                  << std::setw(14) << p_dGesamtStrecke << "\n";
    }

    // Dummy-Simulationsfunktion, um später erweitert zu werden
    virtual void vSimulieren(double dGlobaleZeit) {
        double dDeltaZeit = dGlobaleZeit - p_dZeit;
        p_dGesamtStrecke += dDeltaZeit * p_dMaxGeschwindigkeit;
        p_dGesamtZeit += dDeltaZeit;
        p_dZeit = dGlobaleZeit;
    }
};

class PKW : public Fahrzeug {
private:
    double p_dVerbrauch;         // Verbrauch in Liter/100 km
    double p_dTankvolumen;       // Tankvolumen in Liter
    double p_dTankinhalt;        // Aktueller Tankinhalt in Liter

public:
    // Konstruktor mit zusätzlichen PKW-spezifischen Parametern
    PKW(const std::string& name, double maxGeschwindigkeit, double verbrauch, double tankvolumen = 55.0)
        : Fahrzeug(name, maxGeschwindigkeit), p_dVerbrauch(verbrauch), p_dTankvolumen(tankvolumen),
          p_dTankinhalt(tankvolumen / 2) {  // Tankinhalt auf Hälfte des Tankvolumens gesetzt
    }

    // Tanken-Funktionhttps://marketplace.eclipse.org/marketplace-client-intro?mpc_install=1336
    double dTanken(double menge = std::numeric_limits<double>::infinity()) {
        double getankteMenge = std::min(menge, p_dTankvolumen - p_dTankinhalt);
        p_dTankinhalt += getankteMenge;
        return getankteMenge;
    }

    // Simulation mit Verbrauch
    void vSimulieren(double dGlobaleZeit) override {
        double dDeltaZeit = dGlobaleZeit - p_dZeit;
        double gefahreneStrecke = dDeltaZeit * p_dMaxGeschwindigkeit;

        // Verbrauch berechnen und Tankinhalt aktualisieren
        double benoetigteMenge = gefahreneStrecke * (p_dVerbrauch / 100.0);
        if (p_dTankinhalt >= benoetigteMenge) {
            p_dGesamtStrecke += gefahreneStrecke;
            p_dGesamtZeit += dDeltaZeit;
            p_dTankinhalt -= benoetigteMenge;
        } else {
            std::cout << "PKW " << p_sName << " hat keinen Kraftstoff mehr und bleibt stehen.\n";
        }
        p_dZeit = dGlobaleZeit;
    }

    // Ausgabe der PKW-spezifischen Daten
    void vAusgeben() const override {
        Fahrzeug::vAusgeben();
        std::cout << "  Tankinhalt: " << p_dTankinhalt << " L, Verbrauch: " << p_dVerbrauch << " L/100km\n";
    }
};

class Fahrrad : public Fahrzeug {
public:
    // Konstruktor für Fahrrad
    Fahrrad(const std::string& name, double maxGeschwindigkeit)
        : Fahrzeug(name, maxGeschwindigkeit) {}

    // Geschwindigkeit, die mit zunehmender Strecke sinkt
    double dGeschwindigkeit() const {
        double geschwindigkeit = p_dMaxGeschwindigkeit * std::max(0.12, 1.0 - 0.1 * (p_dGesamtStrecke / 20.0));
        return std::max(geschwindigkeit, 12.0);  // Minimale Geschwindigkeit: 12 km/h
    }

    // Simulation, die die sinkende Geschwindigkeit berücksichtigt
    void vSimulieren(double dGlobaleZeit) override {
        double dDeltaZeit = dGlobaleZeit - p_dZeit;
        double aktuelleGeschwindigkeit = dGeschwindigkeit();
        p_dGesamtStrecke += dDeltaZeit * aktuelleGeschwindigkeit;
        p_dGesamtZeit += dDeltaZeit;
        p_dZeit = dGlobaleZeit;
    }

    // Ausgabe der Fahrrad-spezifischen Daten
    void vAusgeben() const override {
        Fahrzeug::vAusgeben();
        std::cout << "  Aktuelle Geschwindigkeit: " << dGeschwindigkeit() << " km/h\n";
    }
};


// Initialisieren der statischen Variable für die ID-Vergabe
int Fahrzeug::p_iMaxID = 0;

int main() {
    Fahrzeug::vKopf();  // Überschrift für die Ausgabe

    // Fahrzeuge erstellen und simulieren
    auto fahrzeug1 = std::make_unique<Fahrzeug>("PKW1", 40.0);
    auto fahrzeug2 = std::make_unique<Fahrzeug>("Auto3", 30.0);

    // Ausgabe der Fahrzeuge
    fahrzeug1->vAusgeben();
    fahrzeug2->vAusgeben();
    Fahrzeug::vKopf();  // Überschrift für die Ausgabe

     // PKWs und Fahrräder erstellen
     auto pkw1 = std::make_unique<PKW>("Audi", 120.0, 8.5);
     auto fahrrad1 = std::make_unique<Fahrrad>("MountainBike", 25.0);

     // Simulationszeitpunkt einstellen und simulieren
     double dGlobaleZeit = 0.0;
     for (int i = 0; i < 5; ++i) {
         dGlobaleZeit += 1.0;  // Erhöht die globale Zeit jeweils um 1 Stunde
         pkw1->vSimulieren(dGlobaleZeit);
         fahrrad1->vSimulieren(dGlobaleZeit);

         // Ausgabe des Zustands
         pkw1->vAusgeben();
         fahrrad1->vAusgeben();
         std::cout << "---------------------------------------------\n";
     }

    return 0;
}


