#include "StateMainMenu.h"
#include <iostream>
#include "App.h"
#include "StateLoadFile.h"
#include "StateRandom.h"
#include "StateDisplay.h"
#include "StateMenuAlgorithms.h"
#include "StateTimeTests.h"

//mapowanie typ�w akcji i nazw wy�wietlanych na ekranie
const std::map<StateMainMenu::MenuStatuses, std::string> StateMainMenu::menuStatusesNames = {
	{MenuStatuses::LOAD_FILE, "Wczytaj plik"},
	{MenuStatuses::RANDOM_GENERATE, "Wygeneruj losowe dane"},
	{MenuStatuses::DISPLAY_DATA, "Wyswietl dane na ekranie"},
	{MenuStatuses::RUN_ALGORITHM, "Wybierz i wykonaj algorytm"},
	{MenuStatuses::TIME_TESTS, "Uruchom testy czasu dzialania"},
	{MenuStatuses::EXIT, "Zakoncz program"}
};

//przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
void StateMainMenu::process()
{
	//dla wszystkich opcji
	for (size_t i = 0; i < StateMainMenu::menuStatusesNames.size(); i++) {
		//zmiana size_t na enum
		MenuStatuses state = static_cast<MenuStatuses>(i);
		//wy�wietlanie wyr�nienia
		if (this->currentStatus == state) {
			std::cout << " -> ";
		}
		else {
			std::cout << "    ";
		}
		//wy�wietlanie tre�ci elementu
		std::cout << StateMainMenu::menuStatusesNames.at(state) << std::endl;
	}
}
//przetwarzanie wci�ni�tych klawiszy
bool StateMainMenu::handleInput(char key)
{
	switch (key)
	{
	//enter -> wykonanie wyr�nionej akcji
	case 13:
		return this->selectOtption();
		break;
	case 'w':
		{
			//przej�cie w g�r� menu
			size_t currentState = static_cast<size_t>(this->currentStatus) - 1;
			if (currentState >= StateMainMenu::menuStatusesNames.size()) currentState = StateMainMenu::menuStatusesNames.size() - 1;
			this->currentStatus = static_cast<MenuStatuses>(currentState);
		}
		break;
	case 's':
		{
			//przej�cie w g� menu
			size_t currentState = static_cast<size_t>(this->currentStatus) + 1;
			if (currentState >= StateMainMenu::menuStatusesNames.size()) currentState = 0;
			this->currentStatus = static_cast<MenuStatuses>(currentState);
		}
		break;
	}
	return true;
}
//akcja po wybraniu opcji
bool StateMainMenu::selectOtption()
{
	switch (this->currentStatus)
	{
	case MenuStatuses::LOAD_FILE:
		//stan wczytywania pliku
		App::getInstance()->pushState(new StateLoadFile());
		break;
	case MenuStatuses::RANDOM_GENERATE:
		//stan generowania struktury
		App::getInstance()->pushState(new StateRandom());
		break;
	case MenuStatuses::DISPLAY_DATA:
		//stan wy�wietlania struktury
		App::getInstance()->pushState(new StateDisplay());
		break;
	case MenuStatuses::RUN_ALGORITHM:
		//stan menu algorytmu
		App::getInstance()->pushState(new StateMenuAlgorithms());
		break;
	case MenuStatuses::TIME_TESTS:
		//stan test�w czasowych
		App::getInstance()->pushState(new StateTimeTests());
		break;
	case MenuStatuses::EXIT:
		//zako�czenie obecnego stanu
		return false;
	}
	//stan nie jest zaka�czany
	return true;
}
