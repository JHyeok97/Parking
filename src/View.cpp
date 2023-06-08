#include "View.h"
#include <iostream>
#include <iomanip>

using namespace std;

int View::showMenu()
{
    int choice;
    system("clear");
    cout << "1. 입차" << endl;
    cout << "2. 출차" << endl;
    cout << "3. 정산하기" << endl;
    cout << "4. 회원 관리" << endl;
    cout << "5. 종료" << endl;
    cout << "\n선택: ";
    cin >> choice;

    return choice;
}

string View::getInput(const std::string &prompt)
{
    string input;

    cout << prompt;
    cin >> input;

    return input;
}

void View::printTable(const std::vector<std::vector<std::string>> &table)
{
    if (table.empty())
    {
        std::cout << "Table is empty." << std::endl;
        return;
    }

    // 열의 너비 계산
    std::vector<size_t> colWidths(table[0].size());
    for (const auto &row : table)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            if (row[i].length() > colWidths[i])
            {
                colWidths[i] = row[i].length();
            }
        }
    }

    // 표 출력
    for (const auto &row : table)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            std::cout << std::setw(colWidths[i]) << std::left << std::setfill(' ') << row[i] << " | ";
        }
        std::cout << std::endl;

        // 구분선 출력
        for (size_t i = 0; i < colWidths.size(); ++i)
        {
            std::cout << std::setw(colWidths[i]) << std::left << std::setfill('-') << ""
                      << "-";
        }
        std::cout << std::endl;
    }
}