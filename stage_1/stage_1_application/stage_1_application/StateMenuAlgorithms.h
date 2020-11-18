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
		B_AND_B_DFS_1,			//algorytm B&B strategia przeszukiwania wszerz z pierwsz¹ funkcj¹ ograniczaj¹c¹ doln¹
		B_AND_B_DFS_2,			//algorytm B&B strategia przeszukiwania wszerz z drug¹ funkcj¹ ograniczaj¹c¹ doln¹
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

