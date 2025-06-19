#include <stdio.h>
#include <stdlib.h>
#include "school_management.h"

int main() {
    // Initialize the database
    if (!initialize_database()) {
        fprintf(stderr, "Failed to initialize database.\n");
        return 1;
    }

    // Show main menu
    main_menu();

    // Close DB connection when done
    sqlite3_close(db);
    return 0;
}
