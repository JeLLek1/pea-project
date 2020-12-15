#pragma once
#include <map>
#include <string>
#include <vector>

class WeightedTardiness;

// mo¿liwe typy s¹siedztwa
enum class NeigborhoodTypes : size_t {
	EXCHANGE,			// zamiana dwóch indeksów
	INSERT,				// œci¹gniêcie indeksu i wstawienie w inne miejsce
};

class ANeighborhood
{
public:
	static const std::map<NeigborhoodTypes, std::string> typeNames;
	virtual NeigborhoodTypes getType() = 0;
	virtual unsigned int getLoos() = 0;

	// specyficzne dla SA
	virtual void draw(std::vector<size_t>* order, WeightedTardiness* problem) = 0;
	virtual void applyChanges(std::vector<size_t>* &order) = 0;
	virtual unsigned int assignComplexity(unsigned int n) = 0;

	// specyficzne dla TS
	virtual void init() = 0;
	virtual void getNext() = 0;
	virtual void saveCurrent() = 0;
	virtual void refreaschTabu(std::vector<std::vector<unsigned>> &tabu) = 0;
	virtual void increaseTabu(std::vector<std::vector<unsigned>>& tabu, unsigned iters) = 0;
	virtual void increasePunishment(std::vector<std::vector<unsigned>>& punishment) = 0;
	virtual unsigned int getLoos(std::vector<std::vector<unsigned>>& punishment) = 0;
	virtual unsigned int getLoos() = 0;
};

