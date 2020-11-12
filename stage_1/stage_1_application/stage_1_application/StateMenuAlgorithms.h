#pragma once
#include <map>
#include <string>
#include "AState.h"
/*
Klasa stanu aplikacji odpowiedzialnego za menu wyboru algorytmu
*/
class StateMenuAlgorithms : public AState
{
public:
	//mo¿liwe akcja w menu (opcje musz¹ mieæ wartoœci 0,1,2...)
	enum class MenuStatuses : size_t {
		BRUTE_FORCE,			//algorytm przegl¹du zupe³nego
		DYNAMIC_PROGRAMMING,	//algorytm dynamicznego programowania
		B_AND_B_BFS,			//algorytm B&B strategia przeszukiwania wszerz
		B_AND_B_BEST_FIRST,		//algorytm B&B strategia przeszukiwania najpierw najlepszy
		BACK					//powrót
	};
private:
	//obecnie wyró¿niony typ akcji
	MenuStatuses currentStatus = MenuStatuses::BRUTE_FORCE;
	//mapowanie typów akcji i nazw wyœwietlanych na ekranie
	static const std::map<MenuStatuses, std::string> menuStatusesNames;
public:
	//przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
	virtual void process();
	//przetwarzanie wciœniêtych klawiszy
	virtual bool handleInput(char key);
	//wyberanie opcji w menu
	bool selectOtption();
};

