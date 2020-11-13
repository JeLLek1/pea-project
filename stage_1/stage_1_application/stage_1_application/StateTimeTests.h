#pragma once
#include "AState.h"
#include <chrono>
/*
Klasa stanu aplikacji odpowiedzialnego za testy czasowe
*/
class StateTimeTests : public AState
{
	//ilosc testow
	static int test_count;
	//zegar do pomiaru czasu
	std::chrono::high_resolution_clock::time_point start;

	//reset czasu
	void resetTimer();
	//czas od ostatniego restartu
	long long returnTime();
	//testy czasowe bruteforce
	void testsBruteForce(size_t maxSize);
	//testy czasowe dynamic programming
	void testsDP(size_t maxSize);
	//testy czasowe B&B BFT
	void testsBandBBFT(size_t maxSize);
	//testy czasowe B&B Best First
	void testsBandBBestFirst(size_t maxSize);
public:
	//przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
	virtual void process();
	//przetwarzanie wci�ni�tych klawiszy
	virtual bool handleInput(char key);
};
