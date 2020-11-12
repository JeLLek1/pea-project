#pragma once
class Job
{
public:
	unsigned int	number,
					processingTime,
					expectedEnd,
					priority;

	Job(unsigned int number, unsigned int processingTime, unsigned int expectedEnd, unsigned int priority);
	unsigned int getWeightedDelay(unsigned int calculationEnd);
};

