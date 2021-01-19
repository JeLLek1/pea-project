#pragma once
#include "AState.h"
#include <string>
#include <map>
/*
Klasa stanu aplikacji odpowiedzialnego za g³ówne menu programu
*/
class StateMainMenu : public AState
{
	//mo¿liwe akcja w menu (opcje musz¹ mieæ wartoœci 0,1,2...)
	enum class MenuStatuses : size_t {
		LOAD_FILE,			// wczytywanie pliku
		SHOW_PROBLEM,		// wyœwietlenie problemu
		STOP_CRIT,			// Kryterium stopu w sekundach
		POP_SIZE,			// wielkoœæ populacji
		MUT_RATE,			// wspó³czybnnik mutacji
		CROSS_RATE,			// Wspó³czynnik krzy¿owania
		MUT_TYPE,			// typu mutacji
		CROS_TYPE,			// typ krzy¿owania
		RUN_ALGORITHM,		// uruchom algorytm
		EXIT				// zakoñczenie stanu
	};
	// obecnie wyró¿niony typ akcji
	MenuStatuses currentStatus = MenuStatuses::LOAD_FILE;
	// mapowanie typów akcji i nazw wyœwietlanych na ekranie
	static const std::map<MenuStatuses, std::string> menuStatusesNames;
public:
	//przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
	virtual void process();
	//przetwarzanie wciœniêtych klawiszy
	virtual bool handleInput(char key);
	//wyberanie opcji w menu
	bool selectOtption();
};

