#pragma once
#include "AState.h"
#include <string>
#include <map>
/*
Klasa stanu aplikacji odpowiedzialnego za g��wne menu programu
*/
class StateMainMenu : public AState
{
	//mo�liwe akcja w menu (opcje musz� mie� warto�ci 0,1,2...)
	enum class MenuStatuses : size_t {
		LOAD_FILE,			// wczytywanie pliku
		SHOW_PROBLEM,		// wy�wietlenie problemu
		STOP_CRIT,			// Kryterium stopu w sekundach
		DIVERSIFI,			// w��czenie / wy��czenie dywersyfikacji
		NEIGHORHOOD,		// wyb�r s�siedztwa
		RUN_ALGORITHM,		// testy czas�w wykonywania
		EXIT				// zako�czenie stanu
	};
	// obecnie wyr�niony typ akcji
	MenuStatuses currentStatus = MenuStatuses::LOAD_FILE;
	// mapowanie typ�w akcji i nazw wy�wietlanych na ekranie
	static const std::map<MenuStatuses, std::string> menuStatusesNames;
public:
	//przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
	virtual void process();
	//przetwarzanie wci�ni�tych klawiszy
	virtual bool handleInput(char key);
	//wyberanie opcji w menu
	bool selectOtption();
};

