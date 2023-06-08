#include "Database.h"
#include <sstream> // std::stringstream을 사용하기 위한 헤더 파일
#include <iomanip> // std::put_time을 사용하기 위한 헤더 파일
#include <ctime>   // std::localtime을 사용하기 위한 헤더 파일
#include <chrono>

using namespace std;

Database::Database(const std::string &db_name, const std::string &db_user, const std::string &db_pass)
{
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", db_user, db_pass);
    con->setSchema(db_name);
}

Database::~Database()
{
    delete con;
}

bool Database::isMember(const std::string& carID, std::string& memberID)
{
    std::string query = "SELECT * FROM Members WHERE car_id = '" + carID + "';";
    std::unique_ptr<sql::Statement> stmt(con->createStatement());
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
    
    if (res->next())
    {
        memberID = res->getString("member_id");
        return true;
    }
    
    return false;
}

void Database::addGuest(const std::string& guestID, const std::string& carID)
{
    std::string query = "INSERT INTO Guest (guest_id, car_id) VALUES ('" + guestID + "', '" + carID + "');";
    std::unique_ptr<sql::Statement> stmt(con->createStatement());
    stmt->execute(query);
}

std::string Database::generateGuestID()
{
    std::string query = "SELECT MAX(guest_id) AS guest_id FROM Guest;";
    std::unique_ptr<sql::Statement> stmt(con->createStatement());
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

    std::string lastGuestID = "g0";  // Default value
    if (res->next())
    {
        std::string result = res->getString("guest_id");
        if (!result.empty())    // Check if the result is not NULL
        {
            lastGuestID = result;
        }
    }

    int guestNum = std::stoi(lastGuestID.substr(1));  // "g" 다음의 숫자를 추출
    guestNum++;  // 숫자를 1 증가

    return "g" + std::to_string(guestNum);  // 새로운 Guest ID 생성
}

void Database::enterCar(const std::string& carID, const std::string& carType)
{
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_c);
    std::stringstream ss;
    ss << std::put_time(now_tm, "%F %T");
    std::string currentTime = ss.str();
    
    if (carType == "Member")
    {
        std::string memberID;
        if (isMember(carID, memberID))
        {
            // Member일 경우에도 Parking 테이블에 parking_status를 "IN"으로 설정
            std::string query = "INSERT INTO Parking (member_id, enter_time, parking_status) VALUES ('" + memberID + "', '" + currentTime + "', 'IN');";
            std::unique_ptr<sql::Statement> stmt(con->createStatement());
            stmt->execute(query);
        }
    }
    else if (carType == "Guest")
    {
        // Guest ID 생성
        std::string guestID = generateGuestID();  // generateGuestID()는 새로운 Guest ID를 생성하는 메소드

        // Guest 테이블에 차량 ID와 Guest ID 저장
        std::string query = "INSERT INTO Guest (guest_id, car_id) VALUES ('" + guestID + "', '" + carID + "');";
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        stmt->execute(query);

        // Parking 테이블에 guest_id, enter_time, parking_status 값 저장
        enterParking(guestID, now_c, "IN");
    }
}

void Database::enterParking(const std::string& guestID, const std::time_t& enterTime, const std::string& parkingStatus)
{
    std::tm* enterTime_tm = std::localtime(&enterTime);
    std::stringstream ss;
    ss << std::put_time(enterTime_tm, "%F %T");
    std::string enterTimeString = ss.str();

    std::string query = "INSERT INTO Parking (guest_id, enter_time, parking_status) VALUES ('" + guestID + "', '" + enterTimeString + "', '" + parkingStatus + "');";
    std::unique_ptr<sql::Statement> stmt(con->createStatement());
    stmt->execute(query);
}



bool Database::exitCar(const std::string &car_id, const std::string &payment_method)
{
    unique_ptr<sql::Statement> stmt(con->createStatement());
    stmt->execute("INSERT INTO Pay (car_id, payment, exit_time) VALUES ('" + car_id + "', '" + payment_method + "', NOW())");
    return true;
}

vector<std::vector<std::string>> Database::queryData(const std::string &table_name)
{
    vector<vector<string>> data;
    unique_ptr<sql::Statement> stmt(con->createStatement());
    unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM " + table_name));
    while (res->next())
    {
        // 각 행의 데이터를 벡터에 추가하는 코드
    }
    return data;
}

bool Database::addMembers(string &member_id, string &car_id, string &member_name, string &address, string &phone_number, string &expiration_date)
{
    unique_ptr<sql::Statement> stmt(con->createStatement());
    stmt->execute("INSERT INTO Members (member_id, car_id, member_name, address, phone_number, expiration_date) VALUES ('" + member_id + "', '" + car_id + "', '" + member_name + "', '" + address + "', '" + phone_number + "', '" + expiration_date + "');");

    return true;
}

bool Database::deleteData(const string &table_name, const string &attribute, const string &value)
{
    unique_ptr<sql::Statement> stmt(con->createStatement());
    stmt->execute("DELETE FROM " + table_name + " WHERE " + attribute + " = '" + value + "';");
    return true;
}
