#pragma once
#include "Admin.h"
#include "Calculate.h"
#include "Enter.h"
#include "Exit.h"
#include "Database.h"
#include "View.h"
#include "Controller.h"

class Manager
{
    Admin admin;
    Enter enter;
    Exit exit;
    Calculate calculate;

public:
    Manager();
    ~Manager();
    void show();
    void front();
};