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
	//b��d je�eli nie uda�o si� otworzy�
	if (!file.is_open()) {
		std::cout << std::endl << "Nie udalo sie otworzyc pliku!";
		return false;
	}
	//wczytanie pierwszej linii - wielko�ci problemu
	std::string line;
	size_t size;
	std::getline(file, line);
	std::istringstream is_ss(line);
	is_ss >> size;
	//b��d je�eli nie uda�o si� wczyta�
	if (file.fail() || line.empty() || is_ss.fail()) {
		std::cout << std::endl << "Nie udalo sie odczytac wielkosci struktury!";
		file.close();
		return false;
	}
	//instancja problemu szeregowania zada�
	WeightedTardiness* weightedTardiness = new WeightedTardiness();
	size_t i = 0;
	//wczytywanie kolejnych zada�
	while (i < size) {
		//pobranie linii
		std::getline(file, line);
		//b��d podczas pobierania linii
		if (file.fail() || line.empty()) {
			break;
		}
		is_ss = std::istringstream(line);
		//pobieranie czasu przetwarzania zadania
		unsigned int processingTime;
		is_ss >> processingTime;
		//b�ad pobierania
		if (is_ss.fail()) {
			break;
		}
		//pobieranie priorytetu zadania
		unsigned int priority;
		is_ss >> priority;
		//b��d pobierania
		if (is_ss.fail()) {
			break;
		}
		//pobieranie oczekwianego czasu zako�czenia zadania
		unsigned int expectedEnd;
		is_ss >> expectedEnd;
		//b��d przetwarzania
		if (is_ss.fail()) {
			break;
		}
		//je�eli uda�o si� wczyta� elementy, dodawanie zadania (zadania maj� indeks 1 wi�kszy ni� indeks w tablicy)
		weightedTardiness->pushJob(new Job(i + 1, processingTime, expectedEnd, priority));
		i++;
	}
	//zamkni�cie pliku
	file.close();
	//je�eli nie uda�o si� wczyta� pliku to komunikat o b�edzie
	if (weightedTardiness->countJobs() < size) {
		delete weightedTardiness;
		std::cout << std::endl << "Nie udalo sie odczytac danych!";
		return false;
	}
	//wy�wietlenie wczytanej struktury
	weightedTardiness->display();
	//ustawienie jej jako struktura przetwarzana w aplikacji
	App::getInstance()->setWeightedTardiness(weightedTardiness);
	return true;
}

//przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
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
//przetwarzanie wci�ni�tych klawiszy
bool StateLoadFile::handleInput(char key)
{
	//po wci�ni�ciu klawisza powr�t do poprzedniego stanu
	return false;
}
