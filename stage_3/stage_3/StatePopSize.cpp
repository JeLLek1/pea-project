#include "StatePopSize.h"
#include <iostream>
#include "App.h"

void StatePopSize::process()
{
    std::cout << "Podaj wielkosc populacji:";
    unsigned int popSize = App::cinUInt(1);
    while (popSize % 2 == 1) {
        std::cout << "Wielkosc populacji musi byc parzysta. Podaj wartosc ponownie: ";
        popSize = App::cinUInt(1);
    }
    App::getInstance()->getWeightedTardiness()->stopSeconds = popSize;
    std::cout << "\nNacisnij dowolny klawisz by zakonczyc...";
}

bool StatePopSize::handleInput(char key)
{
    return false;
}
