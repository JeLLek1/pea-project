#pragma once
#include "AState.h"
#include <chrono>
#include <list>
#include <string>
// struktura wyniku (numer, op�nienie)
struct Result{
	unsigned int nr, tardiness;
};
/*
Klasa stanu aplikacji odpowiedzialnego za testy algorytm�w
*/
class StateTests : public AState
{
	//zegar do pomiaru czasu
	std::chrono::high_resolution_clock::time_point start;

	// lista wynik�w kolejnych algorytm�w
	std::list<Result*>* results = nullptr;

	// �cie�ka z problemami wybranej wielko�ci
	std::string nameProblems;

	//reset czasu
	void resetTimer();
	//czas od ostatniego restartu
	long long returnTime();
	// wczytanie pliku wynik�w (wa�ne jest aby by�o tyle samo instancji nazwanych wed�ug opis�w 
	bool loadFile(std::string filename);
public:
	//przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
	virtual void process();
	//przetwarzanie wci�ni�tych klawiszy
	virtual bool handleInput(char key);

	// metoda uruchamiaj�ca algorytm wed�ug wybranych parametr�w
	unsigned runAlgorithms();

	~StateTests();
};

