#include "StateCrossType.h"
#include <iostream>
#include <map>
#include "App.h"
#include "GeneticAlgorithm.h"

#include "App.h"
//mapowanie typ�w akcji i nazw wy�wietlanych na ekranie
const std::map<StateCrossType::CrossTypes, std::string> StateCrossType::crossTypesNames = {
	{CrossTypes::PMX, "partially matched crossover"},
	{CrossTypes::OX, "Order crossover"},
};


StateCrossType::StateCrossType()
{
	this->currentStatus = (App::getInstance()->getWeightedTardiness()->crossFunction == GeneticAlgorithm::PMX) ?
		CrossTypes::PMX : CrossTypes::OX;
}

//przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
void StateCrossType::process()
{
	//dla wszystkich opcji
	for (size_t i = 0; i < StateCrossType::crossTypesNames.size(); i++) {
		//zmiana size_t na enum
		CrossTypes state = static_cast<CrossTypes>(i);
		//wy�wietlanie wyr�nienia
		if (this->currentStatus == state) {
			std::cout << " -> ";
		}
		else {
			std::cout << "    ";
		}
		//wy�wietlanie tre�ci elementu
		std::cout << StateCrossType::crossTypesNames.at(state) << std::endl;
	}
}

//przetwarzanie wci�ni�tych klawiszy
bool StateCrossType::handleInput(char key)
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
		if (currentState >= StateCrossType::crossTypesNames.size()) currentState = StateCrossType::crossTypesNames.size() - 1;
		this->currentStatus = static_cast<CrossTypes>(currentState);
	}
	break;
	case 's':
	{
		//przej�cie w g� menu
		size_t currentState = static_cast<size_t>(this->currentStatus) + 1;
		if (currentState >= StateCrossType::crossTypesNames.size()) currentState = 0;
		this->currentStatus = static_cast<CrossTypes>(currentState);
	}
	break;
	}
	return true;
}

//akcja po wybraniu opcji
bool StateCrossType::selectOtption()
{
	switch (this->currentStatus)
	{
	case CrossTypes::PMX:
		App::getInstance()->getWeightedTardiness()->crossFunction = GeneticAlgorithm::PMX;
		break;
	case CrossTypes::OX:
		App::getInstance()->getWeightedTardiness()->crossFunction = GeneticAlgorithm::OX;
		break;
	}
	//stan nie jest zaka�czany

	return false;
}
