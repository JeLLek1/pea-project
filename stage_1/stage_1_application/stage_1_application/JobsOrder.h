#pragma once
#include <vector>
#include <list>
/*
struktura przechowuje informacje o kolejno�ci zada� i ca�kowitej stracie wyliczonych przez algorytmy
*/
struct JobsOrder
{
	//ca�kowita strata
	unsigned int totalLoos;
	//lista kolejno�ci zada�
	std::vector<size_t>* order = nullptr;
	
	//konstruktor
	JobsOrder();
	//kopiowanie kolejno�ci zada� i obecnej straty
	void setOrder(std::vector<size_t>* order, unsigned int loos);
	//kopiowanie kolejno�ci zada� i obecnej straty z listy
	void setOrder(std::list<size_t>* order, unsigned int loos);
	//kopiowanie kolejno�ci zada� i obecnej straty z listy z dodatkowym wynikiem
	void setOrder(std::list<size_t>* order, unsigned int loos, size_t index);
	//wy�wietlanie
	void display();
	//destruktor
	~JobsOrder();
};

