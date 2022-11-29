#include <iostream>
#include "libs/sqlite3/sqlite3.h"
#include "DbConnection.h"

#include "App.h"

int main()
{
    App app("test.db");
    app.Start();
    return 0;
}
