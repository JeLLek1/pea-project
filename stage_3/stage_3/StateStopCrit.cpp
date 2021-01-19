#include "StateStopCrit.h"
#include <iostream>
#include "App.h"

void StateStopCrit::process()
{
    std::cout << "Podaj kryterium stopu [s]:";
    unsigned int stop = App::cinUInt(1);
    App::getInstance()->getWeightedTardiness()->stopSeconds = stop;
    std::cout << "\nNacisnij dowolny klawisz by zakonczyc...";
}

bool StateStopCrit::handleInput(char key)
{
    return false;
}
