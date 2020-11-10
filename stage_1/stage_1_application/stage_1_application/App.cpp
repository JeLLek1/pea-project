#include "App.h"
#include <conio.h>
#include <iostream>
#include <Windows.h>

App* App::instance = nullptr;

App::App()
{

}

void App::popState()
{
	if (this->states.empty()) return;

	delete this->states.top();
	this->states.pop();
}

AState* App::getCurrentState()
{
	if (this->states.empty()) return nullptr;

	return this->states.top();
}

void App::setWeightedTardiness(WeightedTardiness* weightedTardiness)
{
	if (this->weightedTardiness != nullptr) {
		delete this->weightedTardiness;
	}
	this->weightedTardiness = weightedTardiness;
}

WeightedTardiness* App::getWeightedTardiness(WeightedTardiness* weightedTardiness)
{
	return this->weightedTardiness;
}

App* App::getInstance()
{
	if (App::instance == nullptr) {
		App::instance = new App();
	}
	return App::instance;
}

void App::pushState(AState* state)
{
	this->states.push(state);
}

void App::displayAppInfo()
{
	std::cout << "=================================="	<< std::endl;
	std::cout << "          PEA - Projekt"				<< std::endl;
	std::cout << "       Zadanie projektowe 1"			<< std::endl;
	std::cout << "    Autor: Maciej Bronikowski"		<< std::endl;
	std::cout << "     Klawisze: [W,S] [enter]"			<< std::endl;
	std::cout << "=================================="	<< std::endl << std::endl;
}

void App::loop()
{
	while (!this->states.empty()) {
		system("CLS");
		this->displayAppInfo();
		this->getCurrentState()->process();
		if (!this->getCurrentState()->handleInput(_getch())) {
			this->popState();
		}
	}
}
