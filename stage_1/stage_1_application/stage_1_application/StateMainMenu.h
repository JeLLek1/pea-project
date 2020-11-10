#pragma once
#include "AState.h"
#include <string>
#include <map>

class StateMainMenu : public AState
{
	enum class MenuStatuses : size_t {
		LOAD_FILE		= 0,
		RANDOM_GENERATE = 1,
		DISPLAY_DATA	= 2,
		RUN_ALGORITHM	= 3,
		TIME_TESTS		= 4,
		EXIT			= 5
	};

	MenuStatuses currentStatus = MenuStatuses::LOAD_FILE;
	static std::map<MenuStatuses, std::string> menuStatusesNames;
public:
	virtual void process();
	virtual bool handleInput(char key);
	bool selectOtption();
};

