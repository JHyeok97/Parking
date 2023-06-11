#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Database.h"
#include "View.h"

class Controller
{
public:
    // 생성자: Database 객체와 View 객체를 인자로 받음
    Controller(Database *db, View *v);

    // 주 로직을 실행하는 메소드
    void run();

private:
    Database *database; // Database 객체를 가리키는 포인터
    View *view;         // View 객체를 가리키는 포인터
    void enterCar();    // 차량 입차를 처리하는 메소드
    void calculate();   // 차량 출차 시 요금 계산
    void manageData();  // 데이터를 관리하는 메소드
};

#endif