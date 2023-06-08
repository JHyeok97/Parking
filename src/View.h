#ifndef VIEW_H
#define VIEW_H

#include <string>
#include <vector>

class View
{
public:
    int showMenu();
    std::string getInput(const std::string &prompt);
    void printTable(const std::vector<std::vector<std::string>> &table);
};

#endif
