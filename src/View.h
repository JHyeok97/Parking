#ifndef VIEW_H
#define VIEW_H

#include <ftxui/dom/elements.hpp>  // for color, Fit, LIGHT, align_right, bold, DOUBLE
#include <ftxui/dom/table.hpp>     // for Table, TableSelection
#include <ftxui/screen/screen.hpp> // for Screen
#include "ftxui/dom/node.hpp"      // for Render
#include "ftxui/screen/color.hpp"  // for Color, Color::Blue, Color::Cyan, Color::White, ftxui
#include <string>
#include <vector>

class View
{
public:
    int showMenu();
    std::string getInput(const std::string &prompt);
    void printTable(ftxui::Table &ftable);
};

#endif
