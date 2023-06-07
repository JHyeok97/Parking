#include "Controller.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

Controller::Controller(Database *db, View *view) : db(db), view(view) {}

void Controller::run()
{
    while (true)
    {
        int choice = view->showMenu();

        switch (choice)
        {
        case 1:
            enterCar();
            break;
        case 2:
            exitCar();
            break;
        case 3:
            calculate();
            break;
        case 4:
            manageData();
            return;
        default:
            cout << "Invalid choice\n";
        }
    }
}

void Controller::enterCar()
{
    string car_id = view->getInput("Enter car ID: ");
    if (db->enterCar(car_id))
    {
        cout << "Car entered\n";
    }
    else
    {
        cout << "Error entering car\n";
    }
}

void Controller::exitCar()
{
    string car_id = view->getInput("Enter car ID: ");
    string payment_method = view->getInput("Enter payment method: ");
    if (db->exitCar(car_id, payment_method))
    {
        cout << "Car exited\n";
    }
    else
    {
        cout << "Error exiting car\n";
    }
}

void Controller::calculate()
{
    // 정산 코드
}

void Controller::manageData()
{
    // 데이터 관리 코드
    string password;

    system("clear");
    cout << "Password : ";
    cin >> password;

    if (password == "1234") // 비밀 번호가 맞으면 실행
    {
        // 회원 관리(삭제/추가)
    }
    else
    {
        cout << "Wrong Password!\n";
        this_thread::sleep_for(chrono::seconds(1));
    }
}
