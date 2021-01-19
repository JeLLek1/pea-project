/*===============================
* Autor: Maciej Bronikowski
* Numer indeksu: 248838
* Teamat: Jednoprocesorowy problem szeregowania zadañ przy kryterium minimalizacji wa¿onej sumy opóŸnieñ zadañ
* Etap: 3
* ===============================*/

#include <iostream>
#include "App.h"
#include "StateMainMenu.h"

#include "GeneticAlgorithm.h"
#include "WeightedTardiness.h"
#include <vector>
#include <utility>
int main() {

	App* app = App::getInstance();
	app->pushState(new StateMainMenu());
	app->loop();

	return 0;
}
