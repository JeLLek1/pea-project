#pragma once
#include <vector>
#include <list>
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
	//kopiowanie kolejnoœci zadañ i obecnej straty z listy
	void setOrder(std::list<size_t>* order, unsigned int loos);
	//kopiowanie kolejnoœci zadañ i obecnej straty z listy z dodatkowym wynikiem
	void setOrder(std::list<size_t>* order, unsigned int loos, size_t index);
	//wyœwietlanie
	void display();
	//destruktor
	~JobsOrder();
};

