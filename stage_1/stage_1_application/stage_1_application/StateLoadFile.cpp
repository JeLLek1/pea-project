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
		std::cout << std::endl << "Nie udalo sie otworzyc pliku!";
		return false;
	}
	std::string line;
	size_t size;
	std::getline(file, line);
	std::istringstream is_ss(line);
	is_ss >> size;
	if (file.fail() || line.empty() || is_ss.fail()) {
		std::cout << std::endl << "Nie udalo sie odczytac wielkosci struktury!";
		file.close();
		return false;
	}
	WeightedTardiness* weightedTardiness = new WeightedTardiness();
	size_t i = 0;
	while (i < size) {
		std::getline(file, line);
		if (file.fail() || line.empty()) {
			break;
		}
		is_ss = std::istringstream(line);
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
		std::cout << std::endl << "Nie udalo sie odczytac danych!";
		return false;
	}
	weightedTardiness->display();
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
	std::cout << std::endl << std::endl << "Nacisnij dowolny przycisk by powrocic...";
}

bool StateLoadFile::handleInput(char key)
{
	return false;
}
