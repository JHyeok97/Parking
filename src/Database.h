#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <memory>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

class Database
{
private:
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

public:
    Database(const std::string &db_name, const std::string &db_user, const std::string &db_pass);
    ~Database();

    bool isMember(const std::string &carID, std::string& memberID); // 차량 ID가 Member에 있는지 확인하는 메소드
    void addGuest(const std::string &guestID, const std::string &carID);
    std::string generateGuestID();                                       // Guest ID를 생성하는 메소드
    void enterCar(const std::string &carID, const std::string &carType); // 차량 입차 정보를 데이터베이스에 저장하는 메소드
    void enterParking(const std::string &guestID, const std::time_t &enterTime, const std::string &parkingStatus);
    bool exitCar(const std::string &car_id, const std::string &payment_method);
    std::vector<std::vector<std::string>> queryData(const std::string &table_name);
    bool addMembers(std::string &member_id, std::string &car_id, std::string &member_name, std::string &address, std::string &phone_number, std::string &expiration_date);
    sql::ResultSet *showMembers(const std::string &query);
    bool deleteMembers(std::string &car_id);
    bool deleteData(const std::string &table_name, const std::string &attribute, const std::string &value);
};

#endif // DATABASE_H
