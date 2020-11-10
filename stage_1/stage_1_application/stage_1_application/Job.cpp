#include "Job.h"

Job::Job(unsigned int number, unsigned int processingTime, unsigned int expectedEnd, unsigned int priority)
{
	this->number = number;
	this->processingTime = processingTime;
	this->expectedEnd = expectedEnd;
	this->priority = priority;
}

unsigned int Job::getWeightedDelay(unsigned int calculationEnd)
{
	if (calculationEnd <= this->expectedEnd) {
		return 0;
	}
	else {
		return this->priority * (calculationEnd - this->expectedEnd);
	}
}
