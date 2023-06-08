#include "Controller.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <iomanip>
#include <ctime>

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

std::chrono::system_clock::time_point parseDateTime(const string dateTimeStr)
{
    std::tm tm = {};
    std::istringstream ss(dateTimeStr);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

void Controller::enterCar()
{
    while (true)
    {
        std::string carID = view->getInput("차량 ID를 입력하세요: ");
        std::cout << "입력한 차량 ID: " << carID << std::endl;
        std::string confirm = view->getInput("맞습니까? (예/아니오): ");
        if (confirm == "예")
        {
            if (database->isMember(carID))
            {
                std::cout << "PASS 가입자 입니다." << std::endl;
                // 현재 시간 출력
                auto now = std::chrono::system_clock::now();
                auto now_c = std::chrono::system_clock::to_time_t(now);
                std::cout << "현재 시간: " << std::ctime(&now_c) << std::endl;
                // Parking 데이터베이스에 값 저장
                database->enterCar(carID, "Member");
            }
            else
            {
                std::cout << "GUEST 입니다." << std::endl;
                // 현재 시간 출력
                auto now = std::chrono::system_clock::now();
                auto now_c = std::chrono::system_clock::to_time_t(now);
                std::cout << "현재 시간: " << std::ctime(&now_c) << std::endl;
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
            std::cout << "잘못된 입력입니다. 다시 입력해주세요." << std::endl;
        }
    }
}

// 차량 출차 처리 메소드 구현
void Controller::exitCar()
{
    std::string car_id = view->getInput("Enter car ID: ");                 // 차량 ID 입력 받음
    std::string payment_method = view->getInput("Enter payment method: "); // 결제 방법 입력 받음
    if (database->exitCar(car_id, payment_method))
    {                                // 차량 출차 처리
        std::cout << "Car exited\n"; // 출차 성공 메시지 출력
    }
    else
    {
        std::cout << "Error exiting car\n"; // 출차 실패 메시지 출력
    }
}

void Controller::calculate()
{
    // 차량번호 입력
    string car_id;
    cout << "차량번호를 입력하세요: ";
    cin >> car_id;

    // 출차 시간 확인
    auto now = chrono::system_clock::now();
    auto now_c = chrono::system_clock::to_time_t(now);
    tm *current_time = localtime(&now_c);
    ostringstream oss;
    oss << std::put_time(current_time, "%Y-%m-%d %H:%M:%S");
    string exit_time = oss.str();

    string enter_time = database->calculate(car_id);

    int check = database->check(car_id);

    if (check == 1)
    {
        database->out_time(exit_time, car_id);
        cout << "정기차량입니다. 안녕히 가십시오." << endl;

        cin.ignore();
        cin.ignore();
    }
    else
    {

        // 입차시간, 출차시간(현재시간) 출력
        cout << "방문차량입니다." << endl;
        cout << "입차 시간: " << enter_time << endl;
        cout << "현재 시간: " << exit_time << endl;

        chrono::system_clock::time_point time1 = parseDateTime(enter_time);
        chrono::system_clock::time_point time2 = parseDateTime(exit_time);

        chrono::duration<double> duration = time2 - time1;
        double timeDiff = duration.count();

        int parkingDuration = timeDiff / 3600.0; // 시간 단위로 변환
        cout << "사용시간 : " << parkingDuration << "시간 입니다." << endl;

        // 주차 요금 계산
        int parkingRate = 5000.0; // 시간당 요금 (3000원)
        int parkingFee = parkingDuration * parkingRate;
        cout << "사용요금 : " << parkingFee << "원 입니다." << endl;

        string out;
        cout << "출차 하시겠습니까?? (예/아니오) " << endl;
        cin >> out;
        if (out == "예")
        {
            string payment;
            cout << "결제방식 (카드/현금) " << endl;
            cin >> payment;
            if (payment == "카드")
            {
                database->out_time(exit_time, car_id);
                database->Pay(exit_time, car_id, enter_time, payment, parkingFee);
                cout << "카드결제되었습니다.좋은하루되세요." << endl;
                cin.ignore();
                cin.ignore();
            }
            else if (payment == "현금")
            {
                database->out_time(exit_time, car_id);
                database->Pay(exit_time, car_id, enter_time, payment, parkingFee);
                cout << "현금결제되었습니다.좋은하루되세요." << endl;
                cin.ignore();
                cin.ignore();
            }
        }
        else if (out == "아니오")
        {
            cout << "나가실때 정산 부탁드립니다." << endl;
            cin.ignore();
            cin.ignore();
        }
    }
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
