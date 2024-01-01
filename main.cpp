#include <iostream>
#include "FlightNetworkManager.h"
#include "Airport.h"
#include "Menu.h"

int main() {
    FlightNetworkManager manager;
    manager.readFiles();
    Menu menu(manager);
    menu.displayMainMenu();
    return 0;
}
