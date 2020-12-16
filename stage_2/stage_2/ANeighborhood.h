#pragma once
#include <map>
#include <string>
#include <vector>

class WeightedTardiness;

// mo�liwe typy s�siedztwa
enum class NeigborhoodTypes : size_t {
	EXCHANGE,			// zamiana dw�ch indeks�w
	INSERT,				// �ci�gni�cie indeksu i wstawienie w inne miejsce
};
// klasa abstrakcyjna s�siedztwa
class ANeighborhood
{
public:
	// nazwy s�siedztw dla menu
	static const std::map<NeigborhoodTypes, std::string> typeNames;
	virtual NeigborhoodTypes getType() = 0; // zwaraca obecny typ s�siedztwa
	virtual unsigned int getLoos() = 0; // zwraca wyliczone op�nienie

	// specyficzne dla SA
	// losowanie s�siada (parametrami s� kolejno�� kt�rej s�siedztwo jest losowane, oraz instancja problemu potrzebna do wyliczenia op�nie�)
	virtual void draw(std::vector<size_t>* order, WeightedTardiness* problem) = 0;
	// przypisanie wylosowanej warto�ci do przekazanego wektora
	virtual void applyChanges(std::vector<size_t>*& order) = 0;
	// zwara z�o�ono�� s�siedztwa
	virtual unsigned int assignComplexity(unsigned int n) = 0;

	// specyficzne dla TS
	// przypisanie warto�ci pocz�tkowych s�siedztwa
	virtual void init() = 0;
	// przypisywanie kolejnych s�siad�w
	// je�eli nie ma ju� s�siad�w zostanie zwr�cony fa�sz
	virtual bool getNext(std::vector<size_t>* order, WeightedTardiness* problem) = 0;
	// zapisanie obecnego s�siada jako najlepszego s�siada znalezionego
	virtual void saveCurrent() = 0;
	// zmniejszenie warto�ci wszystkich element�w listy zakaz�w
	virtual void refreaschTabu(std::vector<std::vector<unsigned>> &tabu) = 0;
	// zwi�kszenie warto�ci najlepszego znalezionego s�siada w li�cie zakaz�w
	virtual void increaseTabu(std::vector<std::vector<unsigned>>& tabu, unsigned iters) = 0;
	// zwi�kszenie kary w li�cie kar za pogarszanie wynik�w (dywersyfikacja)
	virtual void increasePunishment(std::vector<std::vector<unsigned>>& punishment, unsigned punish) = 0;
	// zwraca kar� dla najlepszego przechowywanego s�siada, bior�c pod uwag� kar� za pogarszanie (dywersyfikacja)
	virtual unsigned int getLoosWithPunish(std::vector<std::vector<unsigned>>& punishment) = 0;
	// ustawienie najlepszego s�siedztwa do wektora order
	virtual void applyBest(std::vector<size_t>*& order, WeightedTardiness* problem) = 0;
	// sprawdzenie, czy obecnie przetwarzany s�siad jest w li�cie tabu
	virtual bool notInTabu(std::vector<std::vector<unsigned>>& tabu) = 0;

	virtual ~ANeighborhood();
};

