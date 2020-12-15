#pragma once
#include "AState.h"
#include <chrono>
/*
Klasa stanu aplikacji odpowiedzialnego za testy czasowe
*/
class StateRunAlgorithm : public AState
{
	//zegar do pomiaru czasu
	std::chrono::high_resolution_clock::time_point start;

	bool canBeRunned = true;

	//reset czasu
	void resetTimer();
	//czas od ostatniego restartu
	long long returnTime();
public:
	//przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
	virtual void process();
	//przetwarzanie wci�ni�tych klawiszy
	virtual bool handleInput(char key);

	void runAlgorithm(size_t choose);
};
