#include "Controller.h"
#include <iostream>

Controller::Controller(Database* db, View* view) : db(db), view(view) {}

void Controller::run() {
    while (true) {
        int choice = view->showMenu();
        switch (choice) {
            case 1:
                enterCar();
                break;
            case 2:
                exitCar();
                break;
            case 3:
                manageData();
                break;
            case 4:
                return;
            default:
                std::cout << "Invalid choice\n";
        }
    }
}

void Controller::enterCar() {
    std::string car_id = view->getInput("Enter car ID: ");
    if (db->enterCar(car_id)) {
        std::cout << "Car entered\n";
    } else {
        std::cout << "Error entering car\n";
    }
}

void Controller::exitCar() {
    std::string car_id = view->getInput("Enter car ID: ");
    std::string payment_method = view->getInput("Enter payment method: ");
    if (db->exitCar(car_id, payment_method)) {
        std::cout << "Car exited\n";
    } else {
        std::cout << "Error exiting car\n";
    }
}

void Controller::manageData() {
    // 데이터 관리 코드
}
