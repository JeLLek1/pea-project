#include "JobsOrder.h"
#include <iostream>
#include "App.h"
#include "WeightedTardiness.h"

JobsOrder::JobsOrder()
{
	this->totalLoos = UINT_MAX;
}

void JobsOrder::setOrder(std::vector<size_t>* order, unsigned int loos)
{
	if (this->order != nullptr) {
		delete this->order;
	}
	this->order = new std::vector<size_t>(*order);
	this->totalLoos = loos;
}

void JobsOrder::display()
{
	if (this->order == nullptr) return;
	std::cout << "Sumaryczne wazone opoznienie: " << this->totalLoos << std::endl;
	std::cout << "Kolejnosc wykonywania zadan: " << std::endl;
	WeightedTardiness* problem = App::getInstance()->getWeightedTardiness();
	for (auto const& jobIndex : *this->order) {
		std::cout << problem->getJob(jobIndex)->number << " ";
	}
	std::cout << std::endl;
}
