#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Database.h"
#include "View.h"

class Controller
{
public:
    Controller(Database *db, View *view);
    void run();

private:
    Database *db;
    View *view;

    void enterCar();
    void exitCar();
    void manageData();
    void calculate();
};

#endif