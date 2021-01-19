#include "StateMutRate.h"
#include <iostream>
#include "App.h"

void StateMutRate::process()
{
    std::cout << "Podaj wspolczynnik mutacji [0;1]:";
    App::getInstance()->getWeightedTardiness()->mutationRatio = App::cinFloat(0,1);
    std::cout << "\nNacisnij dowolny klawisz by zakonczyc...";
}

bool StateMutRate::handleInput(char key)
{
    return false;
}
