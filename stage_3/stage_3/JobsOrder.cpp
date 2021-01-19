#include "JobsOrder.h"
#include <iostream>
#include "App.h"
#include "WeightedTardiness.h"
//konstruktor
JobsOrder::JobsOrder()
{
	//pocz�tkowo maksymalna strata to oo
	this->totalLoos = UINT_MAX;
}
//kopiowanie kolejno�ci zada� i obecnej straty
void JobsOrder::setOrder(std::vector<size_t>* order, unsigned int loos)
{
	//je�eli by�a ju� jaka� lista trzeba j� usun��
	if (this->order != nullptr) {
		delete this->order;
	}
	//kopiowanie zawarto�ci przekazanej tablicy kolejno�ci
	this->order = new std::vector<size_t>(*order);
	//strata
	this->totalLoos = loos;
}

//wy�wietlanie
void JobsOrder::display()
{
	if (this->order == nullptr) return;
	//kara
	std::cout << "Sumaryczne wazone opoznienie: " << this->totalLoos << std::endl;
	std::cout << "Kolejnosc wykonywania zadan: " << std::endl;
	//lista zada�
	WeightedTardiness* problem = App::getInstance()->getWeightedTardiness();
	for (auto const& jobIndex : *this->order) {
		std::cout << problem->getJob(jobIndex)->number << " ";
	}
	std::cout << std::endl;
}

JobsOrder::~JobsOrder()
{
	delete order;
}
