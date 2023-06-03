#include "View.h"
#include <iostream>

int View::showMenu() {
    int choice;
    std::cout << "1. 입차\n";
    std::cout << "2. 출차\n";
    std::cout << "3. 데이터 관리\n";
    std::cout << "4. 종료\n";
    std::cout << "선택: ";
    std::cin >> choice;
    return choice;
}

std::string View::getInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::cin >> input;
    return input;
}
