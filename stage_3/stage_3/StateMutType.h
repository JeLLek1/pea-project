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

	// obecnie wyró¿niony typ mutacji
	MutationTypes currentStatus;
	// mapowanie typów mutacji i nazw wyœwietlanych na ekranie
	static const std::map<MutationTypes, std::string> crossTypesNames;

	StateMutType();

	// przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
	virtual void process();
	// przetwarzanie wciœniêtych klawiszy
	virtual bool handleInput(char key);
	//wyberanie opcji w menu
	bool selectOtption();
};

