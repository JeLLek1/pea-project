#include "StateShowProblem.h"
#include <iostream>
#include "App.h"

void StateShowProblem::process()
{
    WeightedTardiness* problem =  App::getInstance()->getWeightedTardiness();
    if (problem == nullptr || problem->countJobs()<1) {
        std::cout << "Nalezy najpierw wczytac problem z pliku";
    } else {
        problem->display();
    }


    std::cout << "\n\nNacisnij dowolny klawisz by zakonczyc...";
}

bool StateShowProblem::handleInput(char key)
{
    return false;
}
