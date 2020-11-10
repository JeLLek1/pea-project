#include "StateLoadFile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "WeightedTardiness.h"
#include "Job.h"
#include "App.h"

bool StateLoadFile::loadFile(std::string name)
{
	std::fstream file = std::fstream(name, std::ios::in);
	if (!file.is_open()) {
		std::cout << std::endl << "Nie uda³o siê otworzyæ pliku!";
		return false;
	}
	size_t size;
	file >> size;
	if (file.fail()) {
		std::cout << std::endl << "Nie uda³o siê odczytaæ wielkoœci struktury!";
		file.close();
		return false;
	}
	WeightedTardiness* weightedTardiness = new WeightedTardiness();
	size_t i = 0;
	std::string line;
	while (i < size) {
		std::getline(file, line);
		if (file.fail() || line.empty()) {
			break;
		}
		std::istringstream is_ss(line);
		unsigned int processingTime;
		is_ss >> processingTime;
		if (is_ss.fail()) {
			break;
		}
		unsigned int priority;
		is_ss >> priority;
		if (is_ss.fail()) {
			break;
		}
		unsigned int expectedEnd;
		is_ss >> expectedEnd;
		if (is_ss.fail()) {
			break;
		}
		weightedTardiness->pushJob(new Job(i + 1, processingTime, expectedEnd, priority));
		i++;
	}
	file.close();
	if (weightedTardiness->countJobs() < size) {
		delete weightedTardiness;
		std::cout << std::endl << "Nieuda³o siê odczytaæ danych!";
		return false;
	}
	App::getInstance()->setWeightedTardiness(weightedTardiness);
	return true;
}

void StateLoadFile::process()
{
	std::cout << "Podaj nazwe pliku: ";
	std::string fileName;
	std::getline(std::cin, fileName);
	if (this->loadFile(fileName)) {
		std::cout << std::endl << "Pomyslnie zakonczono wczytywanie pliku";
	}
	else {
		std::cout << std::endl << "Wczytywanie pliku zakonczone niepowodzeniem";
	}
	std::cout << std::endl << "Nacisnij dowolny przycisk by pwrocic...";
}

bool StateLoadFile::handleInput(char key)
{
	return false;
}
