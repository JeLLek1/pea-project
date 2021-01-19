#include "App.h"
#include <conio.h>
#include <iostream>
#include <Windows.h>
#include "RandomGenerator.h"
//usuniêcie dyrektywy max (k³óci siê z std::numeric_limits<>::max())
#undef max

//instancja singletonu
App* App::instance = nullptr;

//konstruktor
App::App(){
	// tworzenie instancji generatora liczb losowych
	// z uwagi, ¿e jest tworzony tylko raz (singleton)
	// to móg³by pogorszyæ wynik pierwszego uruchomionego algorytmu
	RandomGenerator::getInstance();

	this->setWeightedTardiness(new WeightedTardiness());
}

//zdjêcie ze stosu aktualnie wykonywanej akcji
void App::popState()
{
	if (this->states.empty()) return;

	delete this->states.top();
	this->states.pop();
}

//pobranie aktualnego stanu ze stosu
AState* App::getCurrentState()
{
	if (this->states.empty()) return nullptr;

	return this->states.top();
}

//dodanie instancji klasy jobSequencing
void App::setWeightedTardiness(WeightedTardiness* weightedTardiness)
{
	//usuniêcie starego problemu je¿eli istnia³
	if (this->weightedTardiness != nullptr) {
		delete this->weightedTardiness;
	}
	this->weightedTardiness = weightedTardiness;
}

//pobranie instancji klasy jobSequencing
WeightedTardiness* App::getWeightedTardiness()
{
	return this->weightedTardiness;
}

//pobranie instancji singletonu aplikacji
App* App::getInstance()
{
	if (App::instance == nullptr) {
		App::instance = new App();
	}
	return App::instance;
}

//dodanie nowego stanu aplikacji do stosu
void App::pushState(AState* state)
{
	this->states.push(state);
}

//wyœwietlanie informacji o programie dla ka¿dego stanu
void App::displayAppInfo()
{
	std::cout << "=================================="	<< std::endl;
	std::cout << "          PEA - Projekt"				<< std::endl;
	std::cout << "       Zadanie projektowe 1"			<< std::endl;
	std::cout << "    Autor: Maciej Bronikowski"		<< std::endl;
	std::cout << "     Klawisze: [W,S] [enter]"			<< std::endl;
	std::cout << "=================================="	<< std::endl << std::endl;
}

//pêtla g³ówna programu
void App::loop()
{
	//dopuki kolejka stanów aplikacji nie jest pusta
	while (!this->states.empty()) {
		//czyszczenie ekranu
		system("CLS");
		//wyœwietlenie informacji o programie
		this->displayAppInfo();
		//wyœwietlenie i rpzetworzenie obednego stanu aplikacji
		this->getCurrentState()->process();
		//przetwarzanie pobranych znaków u¿ytych w konsoli dla danego stanu
		if (!this->getCurrentState()->handleInput(_getch())) {
			//je¿eli stan zwróci³ informacjê o tym ¿e ma byæ zakoñczony to zdjêcie ze stosu
			this->popState();
		}
	}
}

//zwraca liczbê cyfr w liczbie
unsigned int App::countDigits(unsigned int number)
{
	unsigned int digits = 0;
	do{
		digits++;
		number /= 10;
	}while (number);

	return digits;
}

float App::cinFloat(float min, float max)
{
	float value;
	//pobranie wartoœci
	std::cin >> value;
	//powtarzanie pobrania wartoœci dopuki nie jest zgodna z za³o¿eniami
	while (std::cin.good() == false || value < min ||  value > max)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << std::endl << "Podaj wartosc zmiennoprzecinkowa w zakresie [" << min << ";" << max << "]:";
		std::cin >> value;
	}
	std::cin.ignore();
	return value;
}

void App::swap(std::vector<size_t>* vec, size_t fisrt, size_t second)
{
	size_t tmp = (*vec)[fisrt];
	(*vec)[fisrt] = (*vec)[second];
	(*vec)[second] = tmp;
}

//wszytywanie liczby unsigned int z konsoli
unsigned int App::cinUInt(unsigned int min)
{
	unsigned int value;
	//pobranie wartoœci
	std::cin >> value;
	//powtarzanie pobrania wartoœci dopuki nie jest zgodna z za³o¿eniami
	while (std::cin.good() == false || value < min)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << std::endl << "Podaj wartosc naturalna rowna conajmniej " << min << ": ";
		std::cin >> value;
	}
	std::cin.ignore();
	return value;
}
