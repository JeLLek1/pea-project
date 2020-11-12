#pragma once
#include "AState.h"
#include <string>
#include <map>

class StateMainMenu : public AState
{
	enum class MenuStatuses : size_t {
		LOAD_FILE,
		RANDOM_GENERATE,
		DISPLAY_DATA,
		RUN_ALGORITHM,
		TIME_TESTS,
		EXIT
	};

	MenuStatuses currentStatus = MenuStatuses::LOAD_FILE;
	static const std::map<MenuStatuses, std::string> menuStatusesNames;
public:
	virtual void process();
	virtual bool handleInput(char key);
	bool selectOtption();
};

