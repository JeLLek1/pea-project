#pragma once
#include <vector>
/*
struktura przechowuje informacje o kolejnoœci zadañ i ca³kowitej stracie wyliczonych przez algorytmy
*/
struct JobsOrder
{
	//ca³kowita strata
	unsigned int totalLoos;
	//lista kolejnoœci zadañ
	std::vector<size_t>* order = nullptr;
	
	//konstruktor
	JobsOrder();
	//kopiowanie kolejnoœci zadañ i obecnej straty
	void setOrder(std::vector<size_t>* order, unsigned int loos);
	//wyœwietlanie
	void display();
};

