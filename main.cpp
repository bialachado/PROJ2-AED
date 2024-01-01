#include <iostream>
#include "FlightNetworkManager.h"
#include "Airport.h"
#include "Menu.h"

int main() {
    FlightNetworkManager manager;
    Menu menu(manager);
    manager.readFiles();
    menu.displayMainMenu();
    return 0;
}
