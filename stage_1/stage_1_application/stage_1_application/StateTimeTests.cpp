#include "StateTimeTests.h"
#include <iostream>
#include "App.h"
#include "RandomGenerator.h"
#include "WeightedTardiness.h"

int StateTimeTests::test_count = 100;

//reset czasu
void StateTimeTests::resetTimer()
{
	this->start = std::chrono::high_resolution_clock::now();
}
//czas od ostatniego restartu
long long StateTimeTests::returnTime()
{
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(end - this->start).count();
}
//testy czasowe bruteforce
void StateTimeTests::testsBruteForce(size_t maxSize)
{
	std::numeric_limits< double > dbl;
	std::cout.precision(dbl.max_digits10);
	std::cout << "rozmiar;czas[ms]" << std::endl;
	long long time = 0;
	for (size_t i = 1; i <= maxSize; i++) {
		double time = 0;
		for (size_t j = 0; j < StateTimeTests::test_count; j++) {
			WeightedTardiness* problem = RandomGenerator::getInstance()->generateWeightedTardiness(i);
			this->resetTimer();
			JobsOrder* tmp = problem->bruteforce();
			time += this->returnTime();
			delete tmp;
			delete problem;
		}
		std::cout << std::fixed << i << ";" << static_cast<double>(time) / StateTimeTests::test_count * 0.001 << std::endl;
	}
}
//testy czasowe dynamic programming
void StateTimeTests::testsDP(size_t maxSize)
{
	std::numeric_limits< double > dbl;
	std::cout.precision(dbl.max_digits10);
	std::cout << "rozmiar;czas[ms]" << std::endl;
	for (size_t i = 1; i <= maxSize; i++) {
		double time = 0;
		for (size_t j = 0; j < StateTimeTests::test_count; j++) {
			WeightedTardiness* problem = RandomGenerator::getInstance()->generateWeightedTardiness(i);
			this->resetTimer();
			JobsOrder* tmp = problem->dynamicProgramming();
			time += (static_cast<double>(this->returnTime()) / StateTimeTests::test_count);
			delete tmp;
			delete problem;
		}
		std::cout << std::fixed << i << ";" << time * 0.001 << std::endl;
	}
}
//testy czasowe B&B BFT
void StateTimeTests::testsBandBBFT(size_t maxSize)
{
	std::numeric_limits< double > dbl;
	std::cout.precision(dbl.max_digits10);
	std::cout << "rozmiar;czas[ms]" << std::endl;
	for (size_t i = 1; i <= maxSize; i++) {
		double time = 0;
		for (size_t j = 0; j < StateTimeTests::test_count; j++) {
			WeightedTardiness* problem = RandomGenerator::getInstance()->generateWeightedTardiness(i);
			this->resetTimer();
			JobsOrder* tmp = problem->BandBDFS(WeightedTardiness::BandBlower1);
			time += (static_cast<double>(this->returnTime()) / StateTimeTests::test_count);
			delete tmp;
			delete problem;
		}
		std::cout << std::fixed << i << ";" << time * 0.001 << std::endl;
	}
}
//testy czasowe B&B Best First
void StateTimeTests::testsBandBBestFirst(size_t maxSize)
{
	std::numeric_limits< double > dbl;
	std::cout.precision(dbl.max_digits10);
	std::cout << "rozmiar;czas[ms]" << std::endl;
	for (size_t i = 1; i <= maxSize; i++) {
		double time = 0;
		for (size_t j = 0; j < StateTimeTests::test_count; j++) {
			WeightedTardiness* problem = RandomGenerator::getInstance()->generateWeightedTardiness(i);
			this->resetTimer();
			JobsOrder* tmp = problem->BandBDFS(WeightedTardiness::BandBlower2);
			time += (static_cast<double>(this->returnTime()) / StateTimeTests::test_count);
			delete tmp;
			delete problem;
		}

		std::cout << std::fixed << i << ";" << time*0.001 << std::endl;
	}
}

//przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
void StateTimeTests::process()
{
	std::cout << "Podaj maksymalna ilosc elementow do testowania: ";
	size_t maxSize = App::cinLine(1);
	std::cout << "Wybierz algorytm (1-Przeglad zupelny, 2-DP, 3-B&B DFS - lower bound 1, 4-B&B DFS - lower bound 2): ";
	size_t algorithm = App::cinLine(1);
	switch (algorithm) {
	case 1:
		this->testsBruteForce(maxSize);
		break;
	case 2:
		this->testsDP(maxSize);
		break;
	case 3:
		this->testsBandBBFT(maxSize);
		break;
	case 4:
		this->testsBandBBestFirst(maxSize);
		break;
	}
	std::cout << std::endl <<std::endl << "Zakonczono testy. Nacisnij dowolny klawisz by powrocic...";
}

//przetwarzanie wciœniêtych klawiszy
bool StateTimeTests::handleInput(char key)
{
	//dowolny klawisz ma zakoñczyæ stan
	return false;
}
