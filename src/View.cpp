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

void View::printTable(ftxui::Table &ftable)
{
    ftable.SelectAll().Border(ftxui::BorderStyle::LIGHT);

    // Add border around the first column
    ftable.SelectColumn(0).Border(ftxui::BorderStyle::LIGHT);

    // Make first row bold with a double border.
    ftable.SelectRow(0).Decorate(ftxui::bold);
    ftable.SelectRow(0).SeparatorVertical(ftxui::BorderStyle::LIGHT);
    ftable.SelectRow(0).Border(ftxui::DOUBLE);

    // Align right the "Release date" column.
    ftable.SelectColumn(2).DecorateCells(ftxui::align_right);

    // Select row from the second to the last.
    auto content = ftable.SelectRows(1, -1);
    // Alternate in between 3 colors.
    content.DecorateCellsAlternateColumn(ftxui::color(ftxui::Color::Green), 6, 0);
    content.DecorateCellsAlternateColumn(ftxui::color(ftxui::Color::RedLight), 6, 1);
    content.DecorateCellsAlternateColumn(ftxui::color(ftxui::Color::White), 6, 2);
    content.DecorateCellsAlternateColumn(ftxui::color(ftxui::Color::White), 6, 3);
    content.DecorateCellsAlternateColumn(ftxui::color(ftxui::Color::White), 6, 4);
    content.DecorateCellsAlternateColumn(ftxui::color(ftxui::Color::White), 6, 5);

    auto document = ftable.Render();
    auto screen = ftxui::Screen::Create(ftxui::Dimension::Fit(document));
    Render(screen, document);
    screen.Print();
    std::cout << std::endl;
}