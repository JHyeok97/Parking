#include "Database.h"

// 생성자 구현
Database::Database(const std::string& db_name, const std::string& db_user, const std::string& db_pass) {
  driver = sql::mysql::get_mysql_driver_instance(); // MySQL 드라이버 인스턴스를 가져옴
  con = driver->connect("tcp://127.0.0.1:3306", db_user, db_pass); // 데이터베이스에 연결
  con->setSchema(db_name); // 사용할 데이터베이스 스키마 설정
}

// 소멸자 구현
Database::~Database() {
  delete con; // 데이터베이스 연결 해제
}

// 차량 입차 처리 메소드 구현
bool Database::enterCar(const std::string& car_id) {
  std::unique_ptr<sql::Statement> stmt(con->createStatement()); // SQL 문을 실행할 Statement 객체 생성
  stmt->execute("INSERT INTO Parking (car_id, enter_time) VALUES ('" + car_id + "', NOW())"); // 차량 입차 정보를 Parking 테이블에 추가
  return true;
}

// 차량 출차 및 결제 처리 메소드 구현
bool Database::exitCar(const std::string& car_id, const std::string& payment_method) {
  std::unique_ptr<sql::Statement> stmt(con->createStatement()); // SQL 문을 실행할 Statement 객체 생성
  stmt->execute("INSERT INTO Pay (car_id, payment, exit_time) VALUES ('" + car_id + "', '" + payment_method + "', NOW())"); // 차량 출차 및 결제 정보를Pay 테이블에 추가
  return true;
}

// 데이터 조회 메소드 구현
std::vector<std::vector<std::string>> Database::queryData(const std::string& table_name) {
  std::vector<std::vector<std::string>> data; // 조회 결과를 저장할 벡터
  std::unique_ptr<sql::Statement> stmt(con->createStatement()); // SQL 문을 실행할 Statement 객체 생성
  std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM " + table_name)); // 테이블에서 모든 데이터 조회

  while (res->next()) {
    // 각 행의 데이터를 벡터에 추가하는 코드
    // 이 부분은 구현이 누락되어 있음
  }

  return data; // 조회 결과 반환
}

// 데이터 삭제 메소드 구현
bool Database::deleteData(const std::string& table_name, const std::string& attribute, const std::string& value) {
  std::unique_ptr<sql::Statement> stmt(con->createStatement()); // SQL 문을 실행할 Statement 객체 생성
  stmt->execute("DELETE FROM " + table_name + " WHERE " + attribute + " = '" + value + "'"); // 테이블에서 특정 조건에 맞는 데이터 삭제
  return true;
}
