#include "Job.h"
//konstruktor (przypisanie wszystkich elementów)
Job::Job(unsigned int number, unsigned int processingTime, unsigned int expectedEnd, unsigned int priority)
{
	this->number = number;
	this->processingTime = processingTime;
	this->expectedEnd = expectedEnd;
	this->priority = priority;
}
//obliczanie wa¿onej straty danego zadania na podstawie podanego czasu przetworzenia
unsigned int Job::getWeightedDelay(unsigned int calculationEnd)
{
	//je¿eli przetworzono szybciej ni¿ spodziewanie to wa¿one opóŸnienie 0
	if (calculationEnd <= this->expectedEnd) {
		return 0;
	}
	//w przeciwnym wypadku priorytet*(czas_przetworzenia - oczekiwany_czas_przetworzenia)
	else {
		return this->priority * (calculationEnd - this->expectedEnd);
	}
}
