#pragma once
#include <vector>
#include "Job.h"

class WeightedTardiness
{
private:
	std::vector<Job*> jobs;
public:
	void pushJob(Job* job);
	size_t countJobs();
	void display();
	~WeightedTardiness();
};

