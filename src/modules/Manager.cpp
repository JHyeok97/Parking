#include "Manager.h"
#include <iostream>
using namespace std;

Manager::Manager()
{
}

Manager::~Manager()
{
}

void Manager::show()
{
    int num = 1;

    while (num > 0 && num < 5)
    {
        front();
        cin >> num;
        switch (num)
        {
        case 0:
            break;
        case 1:
            enter.show();
            break;
        case 2:
            exit.show();
            break;
        case 3:
            calculate.show();
            break;
        case 4:
            admin.show();
            break;
        default:
            cout << "다시 입력하세요." << endl;
            break;
        }
    }
}

void Manager::front()
{
    system("clear");
    cout << "【\t주차 관리 시스템\t】" << endl;
    cout << endl;
    cout << "1. 입차" << endl;
    cout << "2. 출차" << endl;
    cout << "3. 정산하기" << endl;
    cout << "4. 회원 관리" << endl;
    cout << "* 다른 키 입력 시 종료 *" << endl;
}
