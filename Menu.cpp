#include <iostream>
#include <string>
#include "Airport.h"
#include "Menu.h"

void Menu::displayMainMenu() {
    int choice = 0;
    while (true) {
        std::cout << "\033[1;34m";
        std::cout << "\n********************** ✈ FLIGHT MANAGEMENT SYSTEM ✈ **********************\n";

        std::cout << "****** 1.";
        std::cout << "\033[0m";
        std::cout << " Statistics of the air travel network                      ";
        std::cout << "\033[1;34m";
        std::cout << "******\n";

        std::cout << "****** 2.";
        std::cout << "\033[0m";
        std::cout << " Best flight option                                        ";
        std::cout << "\033[1;34m";
        std::cout << "******\n";


        std::cout << "******";
        std::cout << "\033[1;31m";
        std::cout << " 3. Exit                                                      ";
        std::cout << "\033[0;31m";
        std::cout << "\033[1;34m";
        std::cout << "******\n";

        std::cout << "**************************************************************************\n";
        std::cout << "\033[0m";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        if (choice == 3) { break; }
        processChoice1(choice);
        break;
    }
}

void Menu::processChoice1(int choice) {
    switch (choice) {
        case 1: {
            displayMenu2();
            break;
        }
        case 2:{
            displayMenu3();
            break;
        }
        default:
            std::cout << "\033[1;31m";
            cout << "\nInvalid option. Try again\n";
            std::cout << "\033[0;31m";
            displayMainMenu();
    }
}

void Menu::displayMenu2() {
    int choice = 0;
    while (true) {
        std::cout << "\033[1;34m";
        std::cout << "\n**************************      ✈ FLIGHT MANAGEMENT SYSTEM ✈      **************************\n";
        std::cout << "****** 1.";
        std::cout << "\033[0m";
        std::cout << " Global number of airports and number of available flights                   ";
        std::cout << "\033[1;34m";
        std::cout << "******\n";

        std::cout << "****** 2.";
        std::cout << "\033[0m";
        std::cout << " Number of flights of an airport and from how many different airlines        ";
        std::cout << "\033[1;34m";
        std::cout << "******\n";

        std::cout << "****** 3.";
        std::cout << "\033[0m";
        std::cout << " Number of flights per city/airline                                          ";
        std::cout << "\033[1;34m";
        std::cout << "******\n";

        std::cout << "****** 4.";
        std::cout << "\033[0m";
        std::cout << " Number of different countries that an airport/city flies to                 ";
        std::cout << "\033[1;34m";
        std::cout << "******\n";

        std::cout << "****** 5.";
        std::cout << "\033[0m";
        std::cout << " Number of destinations (airports, cities or countries)                      ";
        std::cout << "\033[1;34m";
        std::cout << "******\n";
        std::cout << "******   ";
        std::cout << "\033[0m";
        std::cout << " available for an airport                                                    ";
        std::cout << "\033[1;34m";
        std::cout << "******\n";

        std::cout << "****** 6.";
        std::cout << "\033[0m";
        std::cout << " Number of reachable destinations (airports, cities or countries)            ";
        std::cout << "\033[1;34m";
        std::cout << "******\n";
        std::cout << "******   ";
        std::cout << "\033[0m";
        std::cout << " from a given airport in a maximum number of X stops (lay-overs)             ";
        std::cout << "\033[1;34m";
        std::cout << "******\n";

        std::cout << "****** 7.";
        std::cout << "\033[0m";
        std::cout << " The light trip(s) with the greatest number of stops in between them         ";
        std::cout << "\033[1;34m";
        std::cout << "******\n";

        std::cout << "****** 8.";
        std::cout << "\033[0m";
        std::cout << " The top-k airport with the greatest number of flights                       ";
        std::cout << "\033[1;34m";
        std::cout << "******\n";

        std::cout << "****** 9.";
        std::cout << "\033[0m";
        std::cout << " The airports that are essential to the network’s circulation capability     ";
        std::cout << "\033[1;34m";
        std::cout << "******\n";

        std::cout << "******";
        std::cout << "\033[1;32m";
        std::cout << " 10. Back to Main Menu                                                          ";
        std::cout << "\033[0;32m";
        std::cout << "\033[1;34m";
        std::cout << "******\n";

        std::cout << "******";
        std::cout << "\033[1;31m";
        std::cout << " 11. Exit                                                                       ";
        std::cout << "\033[0;31m";
        std::cout << "\033[1;34m";
        std::cout << "******\n";
        std::cout << "********************************************************************************************\n";
        std::cout << "\033[0m";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        if (choice == 11) { break; }
        processChoice2(choice);
        break;
    }
}

void Menu::processChoice2(int choice) {
    switch (choice) {
        case 1: {
                manager.DisplayNumberAirportsAirlinesFlights();
                displayMenu2();
                break;
        }
        case 2: {
                cout << "Enter the Airport Code: ";
                cin >> airportCode;
                manager.DirectFlightsCountFromAirport(airportCode);
                displayMenu2();
                break;
        }
        case 3: {
                string city;
                cout << "Enter the City: ";
                cin >> city;
                manager.getFlightsByCity(city);
                cout << "Enter the Airline Code: ";
                cin >> airlineCode;
                manager.getFlightsByAirline(airlineCode);
                displayMenu2();
                break;
        }
        case 4: {
            cout << "Enter the Airport Code: ";
            cin >> airportCode;
            manager.DisplayAirportDestinationCountries(airportCode);
            manager.DisplayAirlinesOperatingFromAirport(airportCode);
            cout << endl;
            displayMenu2();
            break;
        }
        case 5: {
            cout << "Enter the Airport Code: ";
            cin >> airportCode;
            manager.ReachableDestinations(airportCode);
            displayMenu2();
            break;
        }
        case 6: {
            cout << "Enter the Airport Code: ";
            cin >> airportCode;
            int maxStops;
            cout << "Enter the maximum number of stops: ";
            cin >> maxStops;
            manager.CountFlightsWithStopsFromAirport(airportCode, maxStops);
            manager.CountReachableCitiesFromAirport(airportCode, maxStops);
            manager.CountReachableAirportsFromAirport(airportCode, maxStops);
            manager.CountReachableCountriesFromAirport(airportCode, maxStops);
            displayMenu2();
            break;
        }
        case 7: {
            cout << "Calculating the diameter of the flight network...\n";
            manager.findDiameterAndCorrespondingNodes();
            displayMenu2();
            break;
        }
        case 8: {
            int k;
            cout << "Enter the top-k: ";
            cin >> k;
            manager.DisplayTopKAirports(k);
            displayMenu2();
            break;
        }
        case 9: {
            manager.DisplayNumberOfArticulationPoints();
            manager.DisplayArticulationAirports();
            displayMenu2();
            break;
        }
        case 10: {
            displayMainMenu();
        }
        default:
            std::cout << "\033[1;31m";
            cout << "\nInvalid option. Try again\n";
            std::cout << "\033[0;31m";
            displayMenu2();

        }
}

void Menu::displayMenu3() {
    int choice = 0;
    while (true) {
        std::cout << "\033[1;34m";
        std::cout << "\n********************** ✈ FLIGHT MANAGEMENT SYSTEM ✈ **********************\n";
        std::cout << "****** 1.";
        std::cout << "\033[0m";
        std::cout << " By Airport Code                                           ";
        std::cout << "\033[1;34m";
        std::cout << "******\n";

        std::cout << "****** 2.";
        std::cout << "\033[0m";
        std::cout << " By City                                                   ";
        std::cout << "\033[1;34m";
        std::cout << "******\n";

        std::cout << "****** 3.";
        std::cout << "\033[0m";
        std::cout << " By Geographical Coordinates                               ";
        std::cout << "\033[1;34m";
        std::cout << "******\n";

        std::cout << "******";
        std::cout << "\033[1;32m";
        std::cout << " 4. Back to Main Menu                                         ";
        std::cout << "\033[0;32m";
        std::cout << "\033[1;34m";
        std::cout << "******\n";

        std::cout << "******";
        std::cout << "\033[1;31m";
        std::cout << " 5. Exit                                                      ";
        std::cout << "\033[0;31m";
        std::cout << "\033[1;34m";
        std::cout << "******\n";

        std::cout << "**************************************************************************\n";
        std::cout << "\033[0m";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        if (choice == 5) { break; }
        processChoice3(choice);
        break;
    }
}

void Menu::processChoice3(int choice) {
    switch (choice) {
        case 1: {
            cout << endl;
            string source;
            string target;
            cout << "Enter source airport code: ";
            cin >> source;
            cout << endl;
            cout << "Enter target airport code: ";
            cin >> target;
            cout << endl;
            string answer;
            vector<string> airlines;
            cout << "Do you want to specify airlines? (Y/N) ";
            cin >> answer;
            if (answer == "Y"){
                cout << endl;
                while (true) {
                    string airline;
                    cout << "Enter the desired airline(s) (if you want to stop enter 'q'): ";
                    cin >> airline;
                    if (airline == "q") {
                        break;
                    } else {
                        airlines.push_back(airline);
                    }
                }
            }
            manager.findFlightRoutesAirportToAirport(source, target, airlines);
            displayMenu3();
            break;
        }
        case 2: {
            string line;
            getline(cin, line);
            cout << "Enter source country name: ";
            string sourcecountry;
            getline(cin,sourcecountry);
            cout << endl;
            cout << "Enter source city name: ";
            string sourcecity;
            getline(cin,sourcecity);
            cout << endl;
            cout << "Enter target country name: ";
            string targetcountry;
            getline(cin,targetcountry);
            cout << endl;
            cout << "Enter target city name: ";
            string targetcity;
            getline(cin,targetcity);
            cout << endl;
            string answer;
            vector<string> airlines;
            cout << "Do you want to specify airlines? (Y/N) ";
            cin >> answer;
            if (answer == "Y"){
                cout << endl;
                while (true) {
                    string airline;
                    cout << "Enter the desired airline(s) (if you want to stop enter 'q'): ";
                    cin >> airline;
                    if (airline == "q") {
                        break;
                    } else {
                        airlines.push_back(airline);
                    }
                }
            }
            manager.findFlightRoutesCityToCity(sourcecountry, sourcecity, targetcountry, targetcity, airlines);
            displayMenu3();
            break;
        }
        case 3: {
            cout << endl;
            double sourceLongitude;
            double targetLongitude;
            cout << "Enter source longitude: ";
            cin >> sourceLongitude;
            cout << endl;
            double sourceLatitude;
            cout << "Enter source latitude: ";
            cin >> sourceLatitude;
            cout << endl;
            cout << "Enter target longitude: ";
            cin >> targetLongitude;
            cout << endl;
            double targetLatitude;
            cout << "Enter target latitude: ";
            cin >> targetLatitude;
            cout << endl;
            double radius;
            cout << "Enter the desired radius: ";
            cin >> radius;
            cout << endl;
            string answer;
            vector<string> airlines;
            cout << "Do you want to specify airlines? (Y/N) ";
            cin >> answer;
            if (answer == "Y"){
                cout << endl;
                while (true) {
                    string airline;
                    cout << "Enter the desired airline(s) (if you want to stop enter 'q'): ";
                    cin >> airline;
                    if (airline == "q") {
                        break;
                    } else {
                        airlines.push_back(airline);
                    }
                }
            }
            manager.findFlightRoutesCoordinates(sourceLongitude, sourceLatitude, targetLongitude, targetLatitude, radius, airlines);
            displayMenu3();
            break;
        }
        case 4: {
            displayMainMenu();
        }
        default:
            std::cout << "\033[1;31m";
            cout << "\nInvalid option. Try again\n";
            std::cout << "\033[0;31m";
            displayMenu2();

    }
}