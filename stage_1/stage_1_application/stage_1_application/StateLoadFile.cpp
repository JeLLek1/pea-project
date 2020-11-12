#include "StateLoadFile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "WeightedTardiness.h"
#include "Job.h"
#include "App.h"

//wczytywanie pliku
bool StateLoadFile::loadFile(std::string name)
{
	//otwarcie pliku o podanej nazwie
	std::fstream file = std::fstream(name, std::ios::in);
	//b³¹d je¿eli nie uda³o siê otworzyæ
	if (!file.is_open()) {
		std::cout << std::endl << "Nie udalo sie otworzyc pliku!";
		return false;
	}
	//wczytanie pierwszej linii - wielkoœci problemu
	std::string line;
	size_t size;
	std::getline(file, line);
	std::istringstream is_ss(line);
	is_ss >> size;
	//b³¹d je¿eli nie uda³o siê wczytaæ
	if (file.fail() || line.empty() || is_ss.fail()) {
		std::cout << std::endl << "Nie udalo sie odczytac wielkosci struktury!";
		file.close();
		return false;
	}
	//instancja problemu szeregowania zadañ
	WeightedTardiness* weightedTardiness = new WeightedTardiness();
	size_t i = 0;
	//wczytywanie kolejnych zadañ
	while (i < size) {
		//pobranie linii
		std::getline(file, line);
		//b³¹d podczas pobierania linii
		if (file.fail() || line.empty()) {
			break;
		}
		is_ss = std::istringstream(line);
		//pobieranie czasu przetwarzania zadania
		unsigned int processingTime;
		is_ss >> processingTime;
		//b³ad pobierania
		if (is_ss.fail()) {
			break;
		}
		//pobieranie priorytetu zadania
		unsigned int priority;
		is_ss >> priority;
		//b³¹d pobierania
		if (is_ss.fail()) {
			break;
		}
		//pobieranie oczekwianego czasu zakoñczenia zadania
		unsigned int expectedEnd;
		is_ss >> expectedEnd;
		//b³¹d przetwarzania
		if (is_ss.fail()) {
			break;
		}
		//je¿eli uda³o siê wczytaæ elementy, dodawanie zadania (zadania maj¹ indeks 1 wiêkszy ni¿ indeks w tablicy)
		weightedTardiness->pushJob(new Job(i + 1, processingTime, expectedEnd, priority));
		i++;
	}
	//zamkniêcie pliku
	file.close();
	//je¿eli nie uda³o siê wczytaæ pliku to komunikat o b³edzie
	if (weightedTardiness->countJobs() < size) {
		delete weightedTardiness;
		std::cout << std::endl << "Nie udalo sie odczytac danych!";
		return false;
	}
	//wyœwietlenie wczytanej struktury
	weightedTardiness->display();
	//ustawienie jej jako struktura przetwarzana w aplikacji
	App::getInstance()->setWeightedTardiness(weightedTardiness);
	return true;
}

//przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
void StateLoadFile::process()
{
	std::cout << "Podaj nazwe pliku: ";
	//pobranie nazwy pliku
	std::string fileName;
	std::getline(std::cin, fileName);
	//powodzenie wczytywania danych
	if (this->loadFile(fileName)) {
		std::cout << std::endl << "Pomyslnie zakonczono wczytywanie pliku";
	}
	//niepowodzenie wczytywania danych
	else {
		std::cout << std::endl << "Wczytywanie pliku zakonczone niepowodzeniem";
	}
	std::cout << std::endl << std::endl << "Nacisnij dowolny przycisk by powrocic...";
}
//przetwarzanie wciœniêtych klawiszy
bool StateLoadFile::handleInput(char key)
{
	//po wciœniêciu klawisza powrót do poprzedniego stanu
	return false;
}
