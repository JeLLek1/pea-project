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
	//mo�liwe akcja w menu (opcje musz� mie� warto�ci 0,1,2...)
	enum class MenuStatuses : size_t {
		BRUTE_FORCE,			//algorytm przegl�du zupe�nego
		DYNAMIC_PROGRAMMING,	//algorytm dynamicznego programowania
		B_AND_B_DFS_1,			//algorytm B&B strategia przeszukiwania wszerz z pierwsz� funkcj� ograniczaj�c� doln�
		B_AND_B_DFS_2,			//algorytm B&B strategia przeszukiwania wszerz z drug� funkcj� ograniczaj�c� doln�
		BACK					//powr�t
	};
private:
	//obecnie wyr�niony typ akcji
	MenuStatuses currentStatus = MenuStatuses::BRUTE_FORCE;
	//mapowanie typ�w akcji i nazw wy�wietlanych na ekranie
	static const std::map<MenuStatuses, std::string> menuStatusesNames;
public:
	//przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
	virtual void process();
	//przetwarzanie wci�ni�tych klawiszy
	virtual bool handleInput(char key);
	//wyberanie opcji w menu
	bool selectOtption();
};

