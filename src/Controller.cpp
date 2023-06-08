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
        int mem;
        string member_id, car_id, member_name, address, phone_number;

        system("clear");
        cout << "1. 회원 추가" << endl;
        cout << "2. 회원 목록" << endl;
        cout << "3. 회원 찾기" << endl;
        cout << "4. 회원 삭제" << endl;
        cout << "\n선택 : ";
        cin >> mem;

        switch (mem)
        {
        case 1:
        { // 회원 추가

            // 현재 날짜 정보 가져오기
            time_t now = time(nullptr);
            tm *localTime = localtime(&now);

            // 1달을 더한 날짜 계산
            localTime->tm_mon += 1;
            mktime(localTime);

            // YYYY-MM-DD 형식 변환
            char expiration_date[11];
            strftime(expiration_date, sizeof(expiration_date), "%Y-%m-%d", localTime);

            string expiration_date_str(expiration_date);
            cin.ignore(); // 버퍼 초기화

            cout << "member id : ";
            getline(cin, member_id);
            cout << "car id : ";
            getline(cin, car_id);
            cout << "member name : ";
            getline(cin, member_name);
            cout << "address : ";
            getline(cin, address);
            cout << "phone number : ";
            getline(cin, phone_number);

            if (database->addMembers(member_id, car_id, member_name, address, phone_number, expiration_date_str))
            {
                cout << car_id << " 차량 회원 등록이 완료되었습니다." << endl;
                cout << "Enter 입력 시 처음 화면으로..." << endl;
                cin.ignore();
                cin.ignore();
            };

            break;
        }
        case 2:
        { // 회원 목록
            system("clear");
            sql::ResultSet *res = database->showMembers("SELECT * FROM Members");
            vector<vector<string>> table;
            vector<string> header = {"  회원 ID", "   차량 번호", "이름", "주소", "전화번호", "종료일"};
            table.push_back(header);
            while (res->next())
            {
                vector<std::string> row = {
                    res->getString("member_id"),
                    res->getString("car_id"),
                    res->getString("member_name"),
                    res->getString("address"),
                    res->getString("phone_number"),
                    res->getString("expiration_date")};

                table.push_back(row);
            }

            view->printTable(table);

            cout << "\nEnter 입력 시 처음 화면으로..." << endl;
            cin.ignore();
            cin.ignore();

            break;
        }
        case 3:
        { // 회원 찾기
            system("clear");
            cout << "차량 번호 : ";
            cin.ignore();
            getline(cin, car_id);
            sql::ResultSet *res = database->showMembers("SELECT * FROM Members WHERE car_id = '" + car_id + "'");

            // 결과 확인
            if (res->next())
            {
                // 결과 출력
                system("clear");
                cout << "회원 ID\t\t: " << res->getString("member_id") << std::endl;
                cout << "차량 번호\t: " << res->getString("car_id") << std::endl;
                cout << "회원 이름\t: " << res->getString("member_name") << std::endl;
                cout << "주소\t\t: " << res->getString("address") << std::endl;
                cout << "전화번호\t: " << res->getString("phone_number") << std::endl;
                cout << "종료일\t\t: " << res->getString("expiration_date") << std::endl;
                cout << endl;
            }
            else
            {
                cout << "회원을 찾을 수 없습니다." << endl;
                cout << endl;
            }

            cout << "Enter 입력 시 처음 화면으로..." << endl;
            cin.ignore();
            break;
        }
        case 4:
        { // 회원 삭제
            cout << "차량 번호 :";
            cin.ignore();
            getline(cin, car_id);
            if (database->deleteMembers(car_id))
                cout << "삭제 완료" << endl;

            cout << "Enter 입력 시 처음 화면으로..." << endl;
            cin.ignore();
            break;
        default:
            break;
        }
        }
    }
    else
    {
        cout << "Wrong Password!\n";
        cout << "Enter 입력 시 처음 화면으로..." << endl;
        cin.ignore();
        cin.ignore();
    }
}
