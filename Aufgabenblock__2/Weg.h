/*
 * Weg.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Karime Soriano
 */

#ifndef WEG_H_
#define WEG_H_

#include "Simulationsobjekt.h"
//#include "Fahrzeug.h" Para evitar dependencias circulares se comenta
#include "Tempolimit.h"
//#include "Kreuzung.h"
#include <list>
#include <memory>
#include <vector>
#include "vertagt_liste - Vorlage.h" // Incluir la plantilla VListe


//5.3.2
class Kreuzung;
class Fahrzeug;
class Weg:public Simulationsobjekt{
public:
	Weg(); // Constructor estándar
	Weg(const std::string& sname, double dlaenge, Tempolimit tempolimit = Tempolimit::Autobahn,std::shared_ptr<Kreuzung> pZiel = nullptr); //Konstruktor zum Erstellen eines Pfads mit Namensparameter, Pfadlänge und Maximalgeschwindigkeit
	~Weg() override = default;// Standarddestruktor für Simulationsobjekt
	void vSimulieren() override; //Override ist für reine Simulationsobjekt-Methoden gesetzt
	void vAusgeben(std::ostream& os) const override; //Override ist für reine Simulationsobjekt-Methoden gesetzt
	double getTempolimit() const;// Funktion zum Abrufen der Geschwindigkeitsbegrenzung als Double
	void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug); //5.4.2, ermöglicht das Hinzufügen eines Fahrzeugs zur Fahrzeugliste (p_pFahrzeuge() auf einem Wegpfad
	void vAnnahme(std::unique_ptr<Fahrzeug>fahrzeug, double dStartzeit);
	void Fahrzeughinfuegen(std::unique_ptr<Fahrzeug> fahrzeug);
	static void vKopf(std::ostream& os);
	double getLaenge() const { return p_dLaenge; }; // Funktion zum Ermitteln der Länge des Pfades
	const vertagt::VListe<std::unique_ptr<Fahrzeug>>& getFahrzeuge() const { return p_pFahrzeuge; }
	//const std::list<std::unique_ptr<Fahrzeug>>& getFahrzeuge() const { //Holen Sie sich die Liste der Fahrzeuge auf der Straße
	  //  return p_pFahrzeuge;
	//}
	std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& fahrzeug); //Fahrzeug suchen und aus der Liste entfernen, Zeiger zur Wiederverwendung zurückgeben
	// Methoden zum Herstellen von Verbindungen
	void setRueckweg(std::shared_ptr<Weg> rueckweg); //Wir weisen dem schwachen Zeiger einen Pfad zurück zu (mithilfe eines shared_ptr).
	void setZiel(std::shared_ptr<Kreuzung> ziel);
	std::shared_ptr<Weg> getRueckweg() const { return p_rueckweg.lock(); }// Konvertiere weak_ptr in shared_ptr, rufe den Zeiger auf den Pfad zurück ab
	std::shared_ptr<Kreuzung> getZiel() const { return p_zielKreuzung.lock(); } // Konvertiere weak_ptr in shared_ptr
	void vAktualisierenFahrzeuge();


private:
	//5.3.2
    double p_dLaenge; //Straßenlängenattribut in km
    //std::list<std::unique_ptr<Fahrzeug>> p_pFahrzeuge; //Vektor, der die Fahrzeuge innerhalb des Pfades verwaltet
    vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge; // Liste der zurückgestellten Fahrzeuge////////////////7
    Tempolimit p_eTempolimit; //Geschwindigkeitsbegrenzung auflisten///////////////////////////7



    std::weak_ptr<Weg> p_rueckweg;       // Rückweg, es ist schwach für den Rückweg, um zirkuläre Abhängigkeiten zwischen Pfaden zu vermeiden
    std::weak_ptr<Kreuzung> p_zielKreuzung; // Kreuzung des Schicksals
};

// Überladen des <<-Operators (außerhalb der Klasse)
std::ostream& operator<<(std::ostream& os, const Weg& weg);

#endif /* WEG_H_ */
