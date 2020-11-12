#pragma once
#include <vector>
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
	//wy�wietlanie
	void display();
};

