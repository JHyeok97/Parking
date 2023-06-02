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
    while (1)
    {
        cout << "1. 관리자" << endl;
        cout << "2. 회원" << endl;
    }
}
