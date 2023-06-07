#include "Database.h"
#include <sstream>  // std::stringstream을 사용하기 위한 헤더 파일
#include <iomanip>  // std::put_time을 사용하기 위한 헤더 파일
#include <ctime>    // std::localtime을 사용하기 위한 헤더 파일
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

bool Database::isMember(const std::string& carID) {
    std::string query = "SELECT * FROM Members WHERE car_id = '" + carID + "';";
    std::unique_ptr<sql::Statement> stmt(con->createStatement()); // SQL 문을 실행할 Statement 객체 생성
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query)); // 쿼리를 실행하고 결과를 받습니다.
    return res->next(); // 결과가 있으면 true, 없으면 false를 반환합니다.
}

void Database::enterCar(const std::string& carID, const std::string& carType) {
    // 현재 시간을 얻습니다.
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_c);
    std::stringstream ss;
    ss << std::put_time(now_tm, "%F %T");
    std::string currentTime = ss.str();

    // carType에 따라 적절한 데이터베이스에 carID와 현재 시간을 저장합니다.
    if (carType == "Member") {
        std::string query = "INSERT INTO Parking (member_id, enter_time) VALUES ('" + carID + "', '" + currentTime + "');";
        // 쿼리를 실행합니다.
    } else if (carType == "Guest") {
        std::string query = "INSERT INTO Guest (car_id) VALUES ('" + carID + "');";
        // 쿼리를 실행합니다.
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
