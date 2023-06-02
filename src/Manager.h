#pragma once
#include "Admin.h"
#include "Calculate.h"
#include "Enter.h"
#include "Exit.h"

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