#include "StateMainMenu.h"
#include <iostream>
#include "App.h"
#include "StateLoadFile.h"
#include "StateRandom.h"
#include "StateDisplay.h"
#include "StateMenuAlgorithms.h"

const std::map<StateMainMenu::MenuStatuses, std::string> StateMainMenu::menuStatusesNames = {
	{MenuStatuses::LOAD_FILE, "Wczytaj plik"},
	{MenuStatuses::RANDOM_GENERATE, "Wygeneruj losowe dane"},
	{MenuStatuses::DISPLAY_DATA, "Wyswietl dane na ekranie"},
	{MenuStatuses::RUN_ALGORITHM, "Wybierz i wykonaj algorytm"},
	{MenuStatuses::TIME_TESTS, "Uruchom testy czasu dzialania"},
	{MenuStatuses::EXIT, "Zakoncz program"}
};

void StateMainMenu::process()
{
	for (size_t i = 0; i < StateMainMenu::menuStatusesNames.size(); i++) {
		MenuStatuses state = static_cast<MenuStatuses>(i);
		if (this->currentStatus == state) {
			std::cout << " -> ";
		}
		else {
			std::cout << "    ";
		}
		std::cout << StateMainMenu::menuStatusesNames.at(state) << std::endl;
	}
}

bool StateMainMenu::handleInput(char key)
{
	switch (key)
	{
	case 13:
		return this->selectOtption();
		break;
	case 'w':
		{
			size_t currentState = static_cast<size_t>(this->currentStatus) - 1;
			if (currentState >= StateMainMenu::menuStatusesNames.size()) currentState = StateMainMenu::menuStatusesNames.size() - 1;
			this->currentStatus = static_cast<MenuStatuses>(currentState);
		}
		break;
	case 's':
		{
			size_t currentState = static_cast<size_t>(this->currentStatus) + 1;
			if (currentState >= StateMainMenu::menuStatusesNames.size()) currentState = 0;
			this->currentStatus = static_cast<MenuStatuses>(currentState);
		}
		break;
	}
	return true;
}

bool StateMainMenu::selectOtption()
{
	switch (this->currentStatus)
	{
	case MenuStatuses::LOAD_FILE:
		App::getInstance()->pushState(new StateLoadFile());
		break;
	case MenuStatuses::RANDOM_GENERATE:
		App::getInstance()->pushState(new StateRandom());
		break;
	case MenuStatuses::DISPLAY_DATA:
		App::getInstance()->pushState(new StateDisplay());
		break;
	case MenuStatuses::RUN_ALGORITHM:
		App::getInstance()->pushState(new StateMenuAlgorithms());
		break;
	case MenuStatuses::TIME_TESTS:
		break;
	case MenuStatuses::EXIT:
		return false;
	}
	return true;
}
