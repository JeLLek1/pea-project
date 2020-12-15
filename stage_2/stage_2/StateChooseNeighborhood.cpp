#include "StateChooseNeighborhood.h"
#include <iostream>
#include "App.h"
#include "ExchangeNeighborhood.h"
#include "InsertNeigborhood.h"


StateChooseNeighborhood::StateChooseNeighborhood() : AState()
{
	ANeighborhood* current = App::getInstance()->getWeightedTardiness()->getNeighborhood();
	if (current == nullptr) return;

	this->currentType = current->getType();
}

void StateChooseNeighborhood::process()
{
	std::cout << "Wybierz typ sasiedztwa:\n\n";
	// dla wszystkich opcji
	for (size_t i = 0; i < ANeighborhood::typeNames.size(); i++) {
		//zmiana size_t na enum
		NeigborhoodTypes type = static_cast<NeigborhoodTypes>(i);
		//wy�wietlanie wyr�nienia
		if (this->currentType == type) {
			std::cout << " -> ";
		}
		else {
			std::cout << "    ";
		}
		//wy�wietlanie tre�ci elementu
		std::cout << ANeighborhood::typeNames.at(type) << std::endl;
	}
}

bool StateChooseNeighborhood::handleInput(char key)
{
	switch (key)
	{
		//enter -> wykonanie wyr�nionej akcji
	case 13:
		this->selectOption();
		return false;
		break;
	case 'w':
	{
		//przej�cie w g�r� menu
		size_t currentState = static_cast<size_t>(this->currentType) - 1;
		if (currentState >= ANeighborhood::typeNames.size()) currentState = ANeighborhood::typeNames.size() - 1;
		this->currentType = static_cast<NeigborhoodTypes>(currentState);
	}
	break;
	case 's':
	{
		//przej�cie w g� menu
		size_t currentState = static_cast<size_t>(this->currentType) + 1;
		if (currentState >= ANeighborhood::typeNames.size()) currentState = 0;
		this->currentType = static_cast<NeigborhoodTypes>(currentState);
	}
	break;
	}
	return true;
}

void StateChooseNeighborhood::selectOption()
{
	switch (this->currentType)
	{
	case NeigborhoodTypes::EXCHANGE:
		App::getInstance()->getWeightedTardiness()->setNeighborhood(new ExchangeNeighborhood());
		break;
	case NeigborhoodTypes::INSERT:
		App::getInstance()->getWeightedTardiness()->setNeighborhood(new InsertNeigborhood());
		break;
	}
}
