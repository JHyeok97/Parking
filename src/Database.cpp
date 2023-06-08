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

bool Database::isMember(const std::string &carID)
{
    std::string query = "SELECT * FROM Members WHERE car_id = '" + carID + "';";
    std::unique_ptr<sql::Statement> stmt(con->createStatement());   // SQL 문을 실행할 Statement 객체 생성
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query)); // 쿼리를 실행하고 결과를 받습니다.
    return res->next();                                             // 결과가 있으면 true, 없으면 false를 반환합니다.
}

void Database::enterCar(const std::string &carID, const std::string &carType)
{
    // 현재 시간을 얻습니다.
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::tm *now_tm = std::localtime(&now_c);
    std::stringstream ss;
    ss << std::put_time(now_tm, "%F %T");
    std::string currentTime = ss.str();
    // carType에 따라 적절한 데이터베이스에 carID와 현재 시간을 저장합니다.
    if (carType == "Member")
    {
        std::string query = "INSERT INTO Parking (member_id, enter_time) VALUES ('" + carID + "', '" + currentTime + "');";
        // 쿼리를 실행합니다.
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        stmt->execute(query);
    }
    else if (carType == "Guest")
    {
        std::string query = "INSERT INTO Guest (car_id) VALUES ('" + carID + "');";
        // 쿼리를 실행합니다.
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        stmt->execute(query);
    }
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

bool Database::deleteData(const string &table_name, const string &attribute, const string &value)
{
    unique_ptr<sql::Statement> stmt(con->createStatement());
    stmt->execute("DELETE FROM " + table_name + " WHERE " + attribute + " = '" + value + "'");
    return true;
}

// guest_id의 입차시간 반환 이거 삭제해도됨
string Database::guest_id(const string &guest_id)
{
    string enter_time;

    unique_ptr<sql::Statement> stmt(con->createStatement());
    unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT enter_time FROM Parking WHERE guest_id = '" + guest_id + "'"));

    if (res->next())
    {
        enter_time = res->getString("enter_time");
    }

    return enter_time;
}

// member_id의 입차시간 반환 이거 삭제해도됨
string Database::member_id(const string &member_id)
{
    string enter_time;

    unique_ptr<sql::Statement> stmt(con->createStatement());
    unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT enter_time FROM Parking WHERE member_id = '" + member_id + "'"));

    if (res->next())
    {
        enter_time = res->getString("enter_time");
    }

    return enter_time;
}

string Database::calculate(const string &car_id)
{
    string guest_id;
    string member_id;

    // Guest 테이블에서 car_id 검색
    unique_ptr<sql::Statement> stmt(con->createStatement());
    unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT guest_id FROM Guest WHERE car_id = '" + car_id + "'"));

    if (res->next())
    {
        // car_id가 Guest 테이블에 존재하는 경우
        guest_id = res->getString("guest_id");
        string enter_time;

        unique_ptr<sql::Statement> stmt(con->createStatement());
        unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT enter_time FROM Parking WHERE guest_id = '" + guest_id + "'"));

        if (res->next())
        {
            enter_time = res->getString("enter_time");
        }

        return enter_time;
    }
    else
    {
        // car_id가 Guest 테이블에 없는 경우, Members 테이블에서 찾기
        unique_ptr<sql::ResultSet> res2(stmt->executeQuery("SELECT member_id FROM Members WHERE car_id = '" + car_id + "'"));

        if (res2->next())
        {
            // car_id가 Members 테이블에 존재하는 경우
            member_id = res2->getString("member_id");
            string enter_time;

            unique_ptr<sql::Statement> stmt(con->createStatement());
            unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT enter_time FROM Parking WHERE member_id = '" + member_id + "'"));

            if (res->next())
            {
                enter_time = res->getString("enter_time");
            }

            return enter_time;
        }
        else
        {
            // car_id가 Guest 테이블 및 Members 테이블에 모두 존재하지 않는 경우
            cout << "해당 차량조회에 실패하였습니다. 다시 입력해 주세요." << endl;
            return "";
        }
    }
}

int Database::check(const string &car_id)
{
    string guest_id;
    string member_id;

    // Guest 테이블에서 car_id 검색
    unique_ptr<sql::Statement> stmt(con->createStatement());
    unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT guest_id FROM Guest WHERE car_id = '" + car_id + "'"));

    if (res->next())
    {
        // car_id가 Guest 테이블에 존재하는 경우
        guest_id = res->getString("guest_id");

        return 0;
    }
    else
    {
        // car_id가 Guest 테이블에 없는 경우, Members 테이블에서 찾기
        unique_ptr<sql::ResultSet> res2(stmt->executeQuery("SELECT member_id FROM Members WHERE car_id = '" + car_id + "'"));

        if (res2->next())
        {
            member_id = res2->getString("member_id");
            return 1;
        }
        else
        {
            return -1; // Guests 및 Members 테이블에 car_id가 존재하지 않는 경우
        }
    }
}

// 나갈때 Parking테이블의 parking_status와 exit_time을 변경
bool Database::out_time(const string& exit_time, const string& car_id) {
    string guest_id;
    string member_id;

    // Guest 테이블에서 car_id 검색
    unique_ptr<sql::Statement> stmt(con->createStatement());
    unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT guest_id FROM Guest WHERE car_id = '" + car_id + "'"));

    string query; // query 변수를 선언하여 범위를 변경함

    if (res->next()) {
        // car_id가 Guest 테이블에 존재하는 경우
        guest_id = res->getString("guest_id");
        query = "UPDATE Parking SET parking_status = 'OUT', exit_time = '" + exit_time + "' WHERE guest_id = '" + guest_id + "'";
    } else {
        // car_id가 Guest 테이블에 없는 경우, Members 테이블에서 찾기
        unique_ptr<sql::ResultSet> res2(stmt->executeQuery("SELECT member_id FROM Members WHERE car_id = '" + car_id + "'"));

        if (res2->next()) {
            member_id = res2->getString("member_id");
            cout << member_id << endl;
            query = "UPDATE Parking SET parking_status = 'OUT', exit_time = '" + exit_time + "' WHERE member_id = '" + member_id + "'";
        }
    }

    if (!query.empty()) {
        unique_ptr<sql::Statement> updateStmt(con->createStatement());
        updateStmt->executeUpdate(query);
    }

    return true;
}

bool Database::Pay(const string& exit_time, const string& car_id, const string& enter_time, const string& payment, const int& parking_fee)
{
    string guest_id;
    unique_ptr<sql::Statement> stmt(con->createStatement());
    unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT guest_id FROM Guest WHERE car_id = '" + car_id + "'"));
    if (res->next()) {
        guest_id = res->getString("guest_id");
        string query = "INSERT INTO Pay (guest_id, parking_fee, payment, enter_time, exit_time) VALUES ('" + guest_id + "', '" + to_string(parking_fee) + "' , '" + payment + "', '" + enter_time + "', '" + exit_time + "');";

        unique_ptr<sql::Statement> updateStmt(con->createStatement());
        updateStmt->executeUpdate(query);

        return true;
    }
    return false;
}

