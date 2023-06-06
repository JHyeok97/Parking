#ifndef VIEW_H
#define VIEW_H
#include <string>

// View 클래스 정의
class View {
public:
  // 메뉴를 보여주고 사용자의 선택을 반환하는 메소드
  int showMenu();

  // 사용자에게 입력을 요청하고 입력받은 값을 반환하는 메소드
  std::string getInput(const std::string& prompt);
};

#endif
