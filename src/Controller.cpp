#include "Controller.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

// 생성자 구현
Controller::Controller(Database *database, View *view) : database(database), view(view) {}

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
            break;
        case 5:
            return;
        default:
            cout << "Invalid choice\n";
        }
    }
}

void Controller::enterCar()
{
    while (true)
    {
        string carID = view->getInput("차량 ID를 입력하세요: ");
        cout << "입력한 차량 ID: " << carID << endl;
        string confirm = view->getInput("맞습니까? (예/아니오): ");
        if (confirm == "예")
        {
            if (database->isMember(carID))
            {
                cout << "PASS 가입자 입니다." << endl;
                // 현재 시간 출력
                auto now = chrono::system_clock::now();
                auto now_c = chrono::system_clock::to_time_t(now);
                std::cout << "현재 시간: " << ctime(&now_c) << endl;
                // Parking 데이터베이스에 값 저장
                database->enterCar(carID, "Member");
            }
            else
            {
                cout << "GUEST 입니다." << endl;
                // 현재 시간 출력
                auto now = chrono::system_clock::now();
                auto now_c = chrono::system_clock::to_time_t(now);
                cout << "현재 시간: " << ctime(&now_c) << endl;
                // Guest 데이터베이스에 값 저장
                database->enterCar(carID, "Guest");
            }
            break;
        }
        else if (confirm == "아니오")
        {
            continue;
        }
        else
        {
            cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
        }
    }
}

// 차량 출차 처리 메소드 구현
void Controller::exitCar()
{
    string car_id = view->getInput("Enter car ID: ");                 // 차량 ID 입력 받음
    string payment_method = view->getInput("Enter payment method: "); // 결제 방법 입력 받음
    if (database->exitCar(car_id, payment_method))
    {                           // 차량 출차 처리
        cout << "Car exited\n"; // 출차 성공 메시지 출력
    }
    else
    {
        cout << "Error exiting car\n"; // 출차 실패 메시지 출력
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
