#pragma once
#include <vector>
struct JobsOrder
{
	unsigned int totalLoos;

	JobsOrder();
	std::vector<size_t>* order=nullptr;
	void setOrder(std::vector<size_t>* order, unsigned int loos);
	void display();
};

