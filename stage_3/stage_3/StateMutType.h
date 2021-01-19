#pragma once
#include "AState.h"
#include <map>
#include <string>

class StateMutType : public AState
{
public:
	// typy mutacji
	enum class MutationTypes : size_t {
		INSERT,			// mutacja typu insert
		TRANSPOSITION,	// mutacja typu transposition
	};

	// obecnie wyr�niony typ mutacji
	MutationTypes currentStatus;
	// mapowanie typ�w mutacji i nazw wy�wietlanych na ekranie
	static const std::map<MutationTypes, std::string> crossTypesNames;

	StateMutType();

	// przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
	virtual void process();
	// przetwarzanie wci�ni�tych klawiszy
	virtual bool handleInput(char key);
	//wyberanie opcji w menu
	bool selectOtption();
};

