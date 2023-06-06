#include "View.h"
#include <iostream>

// 메뉴 보여주기 메소드 구현
int View::showMenu() {
  int choice;
  std::cout << "1. 입차\n"; // 1번 선택지: 입차
  std::cout << "2. 출차\n"; // 2번 선택지: 출차
  std::cout << "3. 데이터 관리\n"; // 3번 선택지: 데이터 관리
  std::cout << "4. 종료\n"; // 4번 선택지: 프로그램 종료
  std::cout << "선택: ";
  std::cin >> choice; // 사용자의 선택 입력 받기
  return choice; // 사용자의 선택 반환
}

// 사용자 입력 받기 메소드 구현
std::string View::getInput(const std::string& prompt) {
  std::string input;
  std::cout << prompt; // 입력 요청 메시지 출력
  std::cin >> input; // 사용자 입력 받기
  return input; // 사용자 입력 반환
}
