#include "Database.h"
#include "View.h"
#include "Controller.h"

int main()
{
    Database db("park_db", "parkingman123", "test123");
    View v;
    Controller controller(&db, &v);
    controller.run();
    return 0;
}
