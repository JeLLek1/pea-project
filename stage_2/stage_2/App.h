#pragma once
#include <stack>
#include "AState.h"
#include "WeightedTardiness.h"
/*
Klasa odpowiada za g³ówne dzia³anie aplikacji (zosta³a storzona jako singleton dla u³atwionego dostêpu)
Zapewnia funkcjonalnoœæ zmiany statusu programu (jak poruszanie siê po menu),
dodatkowo przechowywana jest g³ówna instancja problemu szeregowania zadañ dla póŸniejszych operacji

Dodatkowo zawiera dwie metody statyczne czêsto wykorzystywane w aplikacji.
*/
class App
{
private:
	// instancja singletonu
	static App* instance;
	// prywatny konstruktor singletonu
	App();
	// stos stanów aplickacji
	std::stack<AState*> states;
	// zdjêcie ze stosu aktualnie wykonywanej akcji
	void popState();
	// pobranie aktualnego stanu ze stosu
	AState* getCurrentState();
	// instancja problemu szeregowania zadañ
	WeightedTardiness* weightedTardiness = nullptr;
	// dodanie instancji klasy jobSequencing
	void setWeightedTardiness(WeightedTardiness* weightedTardiness);
public:
	//pobranie instancji klasy jobSequencing
	WeightedTardiness* getWeightedTardiness();
	//usuwanie funkcjonalnoœci niepotrzebnych dla singletounu
	App(App& other) = delete;
	void operator=(const App&) = delete;
	//pobranie instancji singletonu
	static App* getInstance();
	//dodanie nowego stanu aplikacji do stosu
	void pushState(AState* state);
	//wyœwietlanie informacji o programie
	void displayAppInfo();
	//pêtla g³ówna programu
	void loop();

	//zwraca liczbê cyfr w liczbie
	static unsigned int countDigits(unsigned int number);
	//wszytywanie liczby unsigned int z konsoli
	static unsigned int cinLine(unsigned int min);
};
