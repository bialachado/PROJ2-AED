//
// Created by Francisca Fernandes on 28/12/2023.
//

#ifndef PROJ2_MENU_H
#define PROJ2_MENU_H


#include "FlightNetworkManager.h"

class Menu {
public:
    Menu(FlightNetworkManager& manager) : manager(manager) {}
    void displayMainMenu();
    void displayMenu2();
    void displayMenu3();
    void processChoice1(int choice);
    void processChoice2(int choice);

private:
    FlightNetworkManager& manager;
    string airlineCode;
    string airportCode;

};


#endif //PROJ2_MENU_H
