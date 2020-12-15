/*===============================
* Autor: Maciej Bronikowski
* Numer indeksu: 248838
* Teamat: Jednoprocesorowy problem szeregowania zadań przy kryterium minimalizacji ważonej sumy opóźnień zadań
* Etap: 2
* ===============================*/

#include <iostream>
#include "App.h"
#include "StateMainMenu.h"

int main() {

	App* app = App::getInstance();
	app->pushState(new StateMainMenu());
	app->loop();

	return 0;
}
