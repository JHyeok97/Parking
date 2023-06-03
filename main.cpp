#include "Database.h"
#include "View.h"
#include "Controller.h"

int main() {
    Database db("db_name", "parkingman123", "test123");
    View view;
    Controller controller(&db, &view);
    controller.run();
    return 0;
}
