#pragma once;
#include "Member.h"
#include <string>

class Parking : Member
{
protected:
    int parking_id;
    string in_time;
    string out_time;
};
