#include "Controller.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;
// 생성자 구현
Controller::Controller(Database* database, View* view) : database(database), view(view) {}

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
            return ;        
        default:
            cout << "Invalid choice\n";
        }
    }
}

void Controller::enterCar() {
    while (true) {
        std::string carID = view->getInput("차량 ID를 입력하세요: ");
        std::cout << "입력한 차량 ID: " << carID << std::endl;
        std::string confirm = view->getInput("맞습니까? (예/아니오): ");
        if (confirm == "예") {
            if (database->isMember(carID)) {
                std::cout << "PASS 가입자 입니다." << std::endl;
                // 현재 시간 출력
                auto now = std::chrono::system_clock::now();
                auto now_c = std::chrono::system_clock::to_time_t(now);
                std::cout << "현재 시간: " << std::ctime(&now_c) << std::endl;
                // Parking 데이터베이스에 값 저장
                database->enterCar(carID, "Member");
            } else {
                std::cout << "GUEST 입니다." << std::endl;
                // 현재 시간 출력
                auto now = std::chrono::system_clock::now();
                auto now_c = std::chrono::system_clock::to_time_t(now);
                std::cout << "현재 시간: " << std::ctime(&now_c) << std::endl;
                // Guest 데이터베이스에 값 저장
                database->enterCar(carID, "Guest");
            }
            break;
        } else if (confirm == "아니오") {
            continue;
        } else {
            std::cout << "잘못된 입력입니다. 다시 입력해주세요." << std::endl;
        }
    }
}


// 차량 출차 처리 메소드 구현
void Controller::exitCar() {
  std::string car_id = view->getInput("Enter car ID: "); // 차량 ID 입력 받음
  std::string payment_method = view->getInput("Enter payment method: "); // 결제 방법 입력 받음
  if (database->exitCar(car_id, payment_method)) { // 차량 출차 처리
    std::cout << "Car exited\n"; // 출차 성공 메시지 출력
  } else {
    std::cout << "Error exiting car\n"; // 출차 실패 메시지 출력
  }
}


void Controller::calculate()
{
    // 정산 코드
    
    // 입차 시간 입력
    time_t enterTime;
    cout << "입차 시간을 입력하세요 (예: 2023-06-07 10:30:00): "; // 이거 db에서 값 빼오는걸로 수정해야함
    string enterTimeString;
    cin.ignore();  // 이전 입력 버퍼 비우기
    getline(cin, enterTimeString);
    struct tm enterTM;
    strptime(enterTimeString.c_str(), "%Y-%m-%d %H:%M:%S", &enterTM);
    enterTime = mktime(&enterTM);

    // 출차 시간 입력
    time_t exitTime;
    cout << "출차 시간을 입력하세요 (예: 2023-06-07 14:45:00): "; // 이거 db에서 값 빼오는걸로 수정해야함
    string exitTimeString;
    getline(cin, exitTimeString);
    struct tm exitTM;
    strptime(exitTimeString.c_str(), "%Y-%m-%d %H:%M:%S", &exitTM);
    exitTime = mktime(&exitTM);

    // 주차 시간 계산
    double parkingDuration = difftime(exitTime, enterTime) / 3600.0;  // 시간 단위로 변환

    // 주차 요금 계산
    double parkingRate = 3000.0;  // 시간당 요금 (3000원)
    double parkingFee = parkingDuration * parkingRate;

    // 출차 정보 출력
    cout << "출차 시간: " << exitTimeString << endl;
    cout << "주차 시간: " << parkingDuration << "시간" << endl;
    cout << "주차 요금: " << parkingFee << "원" << endl;

    // db데이터 연결해야함
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
