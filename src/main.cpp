#include "Database.h" // Database 클래스를 사용하기 위한 헤더 파일 포함
#include "View.h" // View 클래스를 사용하기 위한 헤더 파일 포함
#include "Controller.h" // Controller 클래스를 사용하기 위한 헤더 파일 포함

int main()
{
  // Database 객체 생성. 데이터베이스 이름, 사용자 이름, 비밀번호를 인자로 전달
  Database db("park_db", "parkingman123", "test123");

  // View 객체 생성
  View view;

  // Controller 객체 생성. Database 객체와 View 객체를 인자로 전달
  Controller controller(&db, &view);

  // Controller의 run 메소드 실행. 이 메소드에서는 주로 프로그램의 주 로직이 실행됩니다.
  controller.run();

  // 프로그램이 정상적으로 종료되었음을 시스템에 알림
  return 0;
}
