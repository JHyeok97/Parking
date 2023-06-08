#include "View.h"
#include <iostream>
using namespace std;

int View::showMenu()
{
    int choice;
    system("clear");
    cout << "1. 입차" << endl;
    cout << "2. 출차" << endl;
    cout << "3. 회원 관리" << endl;
    cout << "4. 종료" << endl;
    cout << "\n선택: ";
    cin >> choice;

    return choice;
}

string View::getInput(const std::string &prompt)
{
    string input;

    cout << prompt;
    cin >> input;

    return input;
}
