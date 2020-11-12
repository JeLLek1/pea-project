#pragma once
#include <map>
#include <string>
#include "AState.h"

class StateMenuAlgorithms : public AState
{
public:
	enum class MenuStatuses : size_t {
		BRUTE_FORCE,
		DYNAMIC_PROGRAMMING,
		B_AND_B_1,
		B_AND_B_2,
		BACK
	};
private:

	MenuStatuses currentStatus = MenuStatuses::BRUTE_FORCE;
	static const std::map<MenuStatuses, std::string> menuStatusesNames;
public:
	virtual void process();
	virtual bool handleInput(char key);
	bool selectOtption();
};

