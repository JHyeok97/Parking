#include "Controller.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <iomanip>
#include <sstream>
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
            calculate();
            break;
        case 3:
            manageData();
            break;
        case 4:
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
        string carID = view->getInput("차량 번호를 입력하세요: ");
        cout << "입력한 차량 번호: " << carID << endl;
        string confirm = view->getInput("맞습니까? (예/아니오): ");
        if (confirm == "예")
        {
            string memberID; // 멤버 ID를 저장할 변수를 추가합니다.
            if (database->isMember(carID, memberID))
            {
                cout << "PASS 가입자 입니다." << endl;
                // 현재 시간 출력
                auto now = chrono::system_clock::now();
                auto now_c = chrono::system_clock::to_time_t(now);
                tm *ltm = localtime(&now_c);
                cout << "현재 시간: " << 1900 + ltm->tm_year << "년 " << 1 + ltm->tm_mon << "월 " << ltm->tm_mday << "일 " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl;
                // Parking 데이터베이스에 값 저장
                database->enterCar(carID, "Member");
                cout << "\n메뉴로 돌아가려면 엔터를 누르세요." << endl;
                cin.ignore();
                cin.ignore();
            }
            else
            {
                cout << "GUEST 입니다." << endl;
                // 현재 시간 출력
                auto now = chrono::system_clock::now();
                auto now_c = chrono::system_clock::to_time_t(now);
                tm *ltm = localtime(&now_c);
                cout << "현재 시간: " << 1900 + ltm->tm_year << "년 " << 1 + ltm->tm_mon << "월 " << ltm->tm_mday << "일 " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl;
                // Guest ID 생성
                std::string guestID = database->generateGuestID(); // generateGuestID()는 새로운 Guest ID를 생성하는 메소드
                // Guest 테이블에 차량 ID와 Guest ID 저장
                database->addGuest(guestID, carID);
                // Parking 테이블에 값 저장
                database->enterCar(carID, "Guest");
                // Parking 테이블에 guest_id, enter_time, parking_status 값 저장
                database->enterParking(guestID, now_c, "IN");

                cout << "\n메뉴로 돌아가려면 엔터를 누르세요." << endl;
                cin.ignore();
                cin.ignore();
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



std::chrono::system_clock::time_point parseDateTime(const string dateTimeStr)
{
    std::tm tm = {};
    std::istringstream ss(dateTimeStr);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
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
    else if(check == 0)
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
        int parkingFee = parkingDuration * parkingRate + 3000;
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
                cout << "카드결제 되었습니다.좋은 하루 되세요." << endl;
                cin.ignore();
                cin.ignore();
            }
            else if (payment == "현금")
            {
                database->out_time(exit_time, car_id);
                database->Pay(exit_time, car_id, enter_time, payment, parkingFee);
                cout << "현금결제 되었습니다.좋은 하루 되세요." << endl;
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
            vector<string> header = {"회원 ID", "차량 번호", "이름", "주소", "전화번호", "종료일"};
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
            ftxui::Table ftable = table;
            view->printTable(ftable);

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
