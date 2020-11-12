#pragma once
#include <vector>
#include "Job.h"
#include "JobsOrder.h"
#include "IndexMask.h"

class WeightedTardiness
{
private:
	void bruteforceGenerate(size_t size, std::vector<size_t>* order, JobsOrder* best);
	void dpSubsets(
		std::vector<std::vector<unsigned int>>& punishment,
		std::vector<std::vector<unsigned int>>& totalTime,
		std::vector<std::vector<IndexMask>>& jobIndexes,
		size_t subsetSize, size_t end, size_t start = 0, size_t index = 0, size_t mask=0
	);
public:
	std::vector<Job*> jobs;
	void pushJob(Job* job);
	size_t countJobs();
	void display();
	JobsOrder* bruteforce();
	JobsOrder* dynamicProgramming();
	Job* getJob(size_t index);
	unsigned int getTotalWeightedLoos(std::vector<size_t>* order);
	~WeightedTardiness();
};

