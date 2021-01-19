#include "StateCrossRate.h"
#include <iostream>
#include "App.h"

void StateCrossRate::process()
{
    std::cout << "Podaj wspolczynnik krzyzowania [0;1]:";
    App::getInstance()->getWeightedTardiness()->crossoverRatio = App::cinFloat(0.f, 1.f);
    std::cout << "\nNacisnij dowolny klawisz by zakonczyc...";
}

bool StateCrossRate::handleInput(char key)
{
    return false;
}
