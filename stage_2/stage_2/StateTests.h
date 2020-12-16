#pragma once
#include "AState.h"
#include <chrono>
#include <list>
#include <string>
// struktura wyniku (numer, opóŸnienie)
struct Result{
	unsigned int nr, tardiness;
};
/*
Klasa stanu aplikacji odpowiedzialnego za testy algorytmów
*/
class StateTests : public AState
{
	//zegar do pomiaru czasu
	std::chrono::high_resolution_clock::time_point start;

	// lista wyników kolejnych algorytmów
	std::list<Result*>* results = nullptr;

	// œcie¿ka z problemami wybranej wielkoœci
	std::string nameProblems;

	//reset czasu
	void resetTimer();
	//czas od ostatniego restartu
	long long returnTime();
	// wczytanie pliku wyników (wa¿ne jest aby by³o tyle samo instancji nazwanych wed³ug opisów 
	bool loadFile(std::string filename);
public:
	//przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
	virtual void process();
	//przetwarzanie wciœniêtych klawiszy
	virtual bool handleInput(char key);

	// metoda uruchamiaj¹ca algorytm wed³ug wybranych parametrów
	unsigned runAlgorithms();

	~StateTests();
};

