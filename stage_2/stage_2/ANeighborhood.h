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
// klasa abstrakcyjna s¹siedztwa
class ANeighborhood
{
public:
	// nazwy s¹siedztw dla menu
	static const std::map<NeigborhoodTypes, std::string> typeNames;
	virtual NeigborhoodTypes getType() = 0; // zwaraca obecny typ s¹siedztwa
	virtual unsigned int getLoos() = 0; // zwraca wyliczone opóŸnienie

	// specyficzne dla SA
	// losowanie s¹siada (parametrami s¹ kolejnoœæ której s¹siedztwo jest losowane, oraz instancja problemu potrzebna do wyliczenia opóŸnieñ)
	virtual void draw(std::vector<size_t>* order, WeightedTardiness* problem) = 0;
	// przypisanie wylosowanej wartoœci do przekazanego wektora
	virtual void applyChanges(std::vector<size_t>*& order) = 0;
	// zwara z³o¿onoœæ s¹siedztwa
	virtual unsigned int assignComplexity(unsigned int n) = 0;

	// specyficzne dla TS
	// przypisanie wartoœci pocz¹tkowych s¹siedztwa
	virtual void init() = 0;
	// przypisywanie kolejnych s¹siadów
	// je¿eli nie ma ju¿ s¹siadów zostanie zwrócony fa³sz
	virtual bool getNext(std::vector<size_t>* order, WeightedTardiness* problem) = 0;
	// zapisanie obecnego s¹siada jako najlepszego s¹siada znalezionego
	virtual void saveCurrent() = 0;
	// zmniejszenie wartoœci wszystkich elementów listy zakazów
	virtual void refreaschTabu(std::vector<std::vector<unsigned>> &tabu) = 0;
	// zwiêkszenie wartoœci najlepszego znalezionego s¹siada w liœcie zakazów
	virtual void increaseTabu(std::vector<std::vector<unsigned>>& tabu, unsigned iters) = 0;
	// zwiêkszenie kary w liœcie kar za pogarszanie wyników (dywersyfikacja)
	virtual void increasePunishment(std::vector<std::vector<unsigned>>& punishment, unsigned punish) = 0;
	// zwraca karê dla najlepszego przechowywanego s¹siada, bior¹c pod uwagê karê za pogarszanie (dywersyfikacja)
	virtual unsigned int getLoosWithPunish(std::vector<std::vector<unsigned>>& punishment) = 0;
	// ustawienie najlepszego s¹siedztwa do wektora order
	virtual void applyBest(std::vector<size_t>*& order, WeightedTardiness* problem) = 0;
	// sprawdzenie, czy obecnie przetwarzany s¹siad jest w liœcie tabu
	virtual bool notInTabu(std::vector<std::vector<unsigned>>& tabu) = 0;

	virtual ~ANeighborhood();
};

