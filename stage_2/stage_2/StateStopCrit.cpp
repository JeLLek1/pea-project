#include "StateStopCrit.h"
#include <iostream>
#include "App.h"

void StateStopCrit::process()
{
    std::cout << "Podaj kryterium stopu [s]:";
    unsigned int stop = App::cinLine(1);
    App::getInstance()->getWeightedTardiness()->setStopSeconds(stop);
    std::cout << "\nNacisnij dowolny klawisz by zakonczyc...";
}

bool StateStopCrit::handleInput(char key)
{
    return false;
}
