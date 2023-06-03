#include "Database.h"

Database::Database(const std::string& db_name, const std::string& db_user, const std::string& db_pass) {
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", db_user, db_pass);
    con->setSchema(db_name);
}

Database::~Database() {
    delete con;
}

bool Database::enterCar(const std::string& car_id) {
    std::unique_ptr<sql::Statement> stmt(con->createStatement());
    stmt->execute("INSERT INTO Parking (car_id, enter_time) VALUES ('" + car_id + "', NOW())");
    return true;
}

bool Database::exitCar(const std::string& car_id, const std::string& payment_method) {
    std::unique_ptr<sql::Statement> stmt(con->createStatement());
    stmt->execute("INSERT INTO Pay (car_id, payment, exit_time) VALUES ('" + car_id + "', '" + payment_method + "', NOW())");
    return true;
}

std::vector<std::vector<std::string>> Database::queryData(const std::string& table_name) {
    std::vector<std::vector<std::string>> data;
    std::unique_ptr<sql::Statement> stmt(con->createStatement());
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM " + table_name));
    while (res->next()) {
        // 각 행의 데이터를 벡터에 추가하는 코드
    }
    return data;
}

bool Database::deleteData(const std::string& table_name, const std::string& attribute, const std::string& value) {
    std::unique_ptr<sql::Statement> stmt(con->createStatement());
    stmt->execute("DELETE FROM " + table_name + " WHERE " + attribute + " = '" + value + "'");
    return true;
}
