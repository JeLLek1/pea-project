#include "WeightedTardiness.h"

void WeightedTardiness::pushJob(Job* job)
{
	this->jobs.push_back(job);
}

size_t WeightedTardiness::countJobs()
{
	return this->jobs.size();
}

void WeightedTardiness::display()
{
	for (auto const& value : this->jobs) {

	}
}

WeightedTardiness::~WeightedTardiness()
{
	while (!this->jobs.empty()) {
		delete this->jobs.back();
		this->jobs.pop_back();
	}
}
