#pragma once
#include "AState.h"
#include <map>
#include <string>

class StateCrossType : public AState
{
public:
	// typy krzy�owania
	enum class CrossTypes : size_t {
		PMX,			// krzy�owanie typu PMX
		OX,				// krzy�owanie typu OX
	};

	// obecnie wyr�niony typ krzy�owania
	CrossTypes currentStatus;
	// mapowanie typ�w krzy�owa� i nazw wy�wietlanych na ekranie
	static const std::map<CrossTypes, std::string> crossTypesNames;

	StateCrossType();

	// przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
	virtual void process();
	// przetwarzanie wci�ni�tych klawiszy
	virtual bool handleInput(char key);
	//wyberanie opcji w menu
	bool selectOtption();
};

