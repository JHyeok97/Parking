#pragma once;
#include "Admin.h"
#include <string>

class ParkingLot : Admin
{
protected:
    string parking_slot;
    int rate;
};