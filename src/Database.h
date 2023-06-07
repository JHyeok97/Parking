#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <memory>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

class Database {
private:
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

public:
    Database(const std::string& db_name, const std::string& db_user, const std::string& db_pass);
    ~Database();

    bool isMember(const std::string& carID);  // 차량 ID가 Member에 있는지 확인하는 메소드
    void enterCar(const std::string& carID, const std::string& carType);  // 차량 입차 정보를 데이터베이스에 저장하는 메소드
    bool exitCar(const std::string& car_id, const std::string& payment_method);
    std::vector<std::vector<std::string>> queryData(const std::string& table_name);
    bool deleteData(const std::string& table_name, const std::string& attribute, const std::string& value);
};

#endif  // DATABASE_H
