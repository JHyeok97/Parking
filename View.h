#ifndef VIEW_H
#define VIEW_H

#include <string>

class View {
public:
    int showMenu();
    std::string getInput(const std::string& prompt);
};

#endif
