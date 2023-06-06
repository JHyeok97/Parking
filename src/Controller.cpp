#include "Controller.h"
#include <iostream>

// 생성자 구현
Controller::Controller(Database* db, View* view) : db(db), view(view) {}

// 주 로직 실행 메소드 구현
void Controller::run() {
  while (true) {
    int choice = view->showMenu(); // 메뉴를 보여주고 사용자의 선택을 받음
    switch (choice) {
      case 1:
        enterCar(); // 차량 입차 처리
        break;
      case 2:
        exitCar(); // 차량 출차 처리
        break;
      case 3:
        manageData(); // 데이터 관리
        break;
      case 4:
        return; // 프로그램 종료
      default:
        std::cout << "Invalid choice\n"; // 잘못된 선택을 했을 경우 메시지 출력
    }
  }
}

// 차량 입차 처리 메소드 구현
void Controller::enterCar() {
  std::string car_id = view->getInput("Enter car ID: "); // 차량 ID 입력 받음
  if (db->enterCar(car_id)) { // 차량 입차 처리
    std::cout << "Car entered\n"; // 입차 성공 메시지 출력
  } else {
    std::cout << "Error entering car\n"; // 입차 실패 메시지 출력
  }
}

// 차량 출차 처리 메소드 구현
void Controller::exitCar() {
  std::string car_id = view->getInput("Enter car ID: "); // 차량 ID 입력 받음
  std::string payment_method = view->getInput("Enter payment method: "); // 결제 방법 입력 받음
  if (db->exitCar(car_id, payment_method)) { // 차량 출차 처리
    std::cout << "Car exited\n"; // 출차 성공 메시지 출력
  } else {
    std::cout << "Error exiting car\n"; // 출차 실패 메시지 출력
  }
}

// 데이터 관리 메소드 구현
void Controller::manageData() {
  // 데이터 관리 코드
  // 이 부분은 구현이 누락되어 있습니다.
}
