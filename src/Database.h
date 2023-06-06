#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include <vector>
#include <memory>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

// Database 클래스 정의
class Database {
private:
  sql::mysql::MySQL_Driver* driver; // MySQL 드라이버를 가리키는 포
  sql::Connection* con; // 데이터베이스 연결을 가리키는 포인터

public:
  // 생성자: 데이터베이스 이름, 사용자 이름, 비밀번호를 인자로 받음
  Database(const std::string& db_name, const std::string& db_user, const std::string& db_pass);

  // 소멸자
  ~Database();

  // 차량 입차를 처리하는 메소드
  bool enterCar(const std::string& car_id);

  // 차량 출차와 결제를 처리하는 메소드
  bool exitCar(const std::string& car_id, const std::string& payment_method);

  // 특정 테이블에서 데이터를 조회하는 메소드
  std::vector<std::vector<std::string>> queryData(const std::string& table_name);

  // 특정 테이블에서 데이터를 삭제하는 메소드
  bool deleteData(const std::string& table_name, const std::string& attribute, const std::string& value);
};

#endif // DATABASE_H
