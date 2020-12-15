#pragma once
#include <stack>
#include "AState.h"
#include "WeightedTardiness.h"
/*
Klasa odpowiada za g��wne dzia�anie aplikacji (zosta�a storzona jako singleton dla u�atwionego dost�pu)
Zapewnia funkcjonalno�� zmiany statusu programu (jak poruszanie si� po menu),
dodatkowo przechowywana jest g��wna instancja problemu szeregowania zada� dla p�niejszych operacji

Dodatkowo zawiera dwie metody statyczne cz�sto wykorzystywane w aplikacji.
*/
class App
{
private:
	// instancja singletonu
	static App* instance;
	// prywatny konstruktor singletonu
	App();
	// stos stan�w aplickacji
	std::stack<AState*> states;
	// zdj�cie ze stosu aktualnie wykonywanej akcji
	void popState();
	// pobranie aktualnego stanu ze stosu
	AState* getCurrentState();
	// instancja problemu szeregowania zada�
	WeightedTardiness* weightedTardiness = nullptr;
	// dodanie instancji klasy jobSequencing
	void setWeightedTardiness(WeightedTardiness* weightedTardiness);
public:
	//pobranie instancji klasy jobSequencing
	WeightedTardiness* getWeightedTardiness();
	//usuwanie funkcjonalno�ci niepotrzebnych dla singletounu
	App(App& other) = delete;
	void operator=(const App&) = delete;
	//pobranie instancji singletonu
	static App* getInstance();
	//dodanie nowego stanu aplikacji do stosu
	void pushState(AState* state);
	//wy�wietlanie informacji o programie
	void displayAppInfo();
	//p�tla g��wna programu
	void loop();

	//zwraca liczb� cyfr w liczbie
	static unsigned int countDigits(unsigned int number);
	//wszytywanie liczby unsigned int z konsoli
	static unsigned int cinLine(unsigned int min);
};
