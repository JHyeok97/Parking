#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Database.h" // Database 클래스를 사용하기 위한 헤더 파일 포함
#include "View.h" // View 클래스를 사용하기 위한 헤더 파일 포함

// Controller 클래스 정의
class Controller {
public:
  // 생성자: Database 객체와 View 객체를 인자로 받음
  Controller(Database* db, View* view);

  // 주 로직을 실행하는 메소드
  void run();

private:
  Database* db; // Database 객체를 가리키는 포인터
  View* view; // View 객체를 가리키는 포인터

  // 차량 입차를 처리하는 메소드
  void enterCar();

  // 차량 출차를 처리하는 메소드
  void exitCar();

  // 데이터를 관리하는 메소드
  void manageData();
};

#endif
