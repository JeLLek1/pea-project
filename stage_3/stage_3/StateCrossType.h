#pragma once
#include "AState.h"
#include <map>
#include <string>

class StateCrossType : public AState
{
public:
	// typy krzy¿owania
	enum class CrossTypes : size_t {
		PMX,			// krzy¿owanie typu PMX
		OX,				// krzy¿owanie typu OX
	};

	// obecnie wyró¿niony typ krzy¿owania
	CrossTypes currentStatus;
	// mapowanie typów krzy¿owañ i nazw wyœwietlanych na ekranie
	static const std::map<CrossTypes, std::string> crossTypesNames;

	StateCrossType();

	// przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
	virtual void process();
	// przetwarzanie wciœniêtych klawiszy
	virtual bool handleInput(char key);
	//wyberanie opcji w menu
	bool selectOtption();
};

