#include "Enter.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

Enter::~Enter()
{
}

Enter::Enter()
{
}

void Enter::show()
{
    system("clear");
    cout << "차량 번호를 입력하세요 : ";
    cin >> Car_number;
    cout << "차량 번호는 : " << Car_number << std::endl;
}