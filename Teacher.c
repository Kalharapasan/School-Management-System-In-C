#include "school_management.h"

int add_teacher(Teacher teacher) {
    char *sql = "INSERT INTO teachers (name, email, phone, subject, qualification, salary, join_date) "
                "VALUES (?, ?, ?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, teacher.name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, teacher.email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, teacher.phone, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, teacher.subject, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, teacher.qualification, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 6, teacher.salary);
    sqlite3_bind_text(stmt, 7, teacher.join_date, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    printf("Teacher added successfully!\n");
    return 1;
}

int update_teacher(Teacher teacher) {
    char *sql = "UPDATE teachers SET name=?, email=?, phone=?, subject=?, qualification=?, salary=? WHERE id=?;";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, teacher.name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, teacher.email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, teacher.phone, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, teacher.subject, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, teacher.qualification, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 6, teacher.salary);
    sqlite3_bind_int(stmt, 7, teacher.id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Update failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    printf("Teacher updated successfully!\n");
    return 1;
}

int delete_teacher(int id) {
    char *sql = "DELETE FROM teachers WHERE id=?;";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_int(stmt, 1, id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Delete failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    printf("Teacher deleted successfully!\n");
    return 1;
}

Teacher* get_teacher(int id) {
    char *sql = "SELECT * FROM teachers WHERE id=?;";
    sqlite3_stmt *stmt;
    int rc;
    Teacher *teacher = NULL;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    sqlite3_bind_int(stmt, 1, id);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        teacher = malloc(sizeof(Teacher));
        teacher->id = sqlite3_column_int(stmt, 0);
        strcpy(teacher->name, (char*)sqlite3_column_text(stmt, 1));
        strcpy(teacher->email, (char*)sqlite3_column_text(stmt, 2));
        strcpy(teacher->phone, (char*)sqlite3_column_text(stmt, 3));
        strcpy(teacher->subject, (char*)sqlite3_column_text(stmt, 4));
        strcpy(teacher->qualification, (char*)sqlite3_column_text(stmt, 5));
        teacher->salary = sqlite3_column_double(stmt, 6);
        strcpy(teacher->join_date, (char*)sqlite3_column_text(stmt, 7));
    }

    sqlite3_finalize(stmt);
    return teacher;
}

void display_all_teachers() {
    char *sql = "SELECT * FROM teachers ORDER BY id;";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    printf("\n=== ALL TEACHERS ===\n");
    printf("%-5s %-20s %-25s %-15s %-15s %-20s %-10s\n",
           "ID", "Name", "Email", "Phone", "Subject", "Qualification", "Salary");
    printf("======================================================================================\n");

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        printf("%-5d %-20s %-25s %-15s %-15s %-20s $%-9.2f\n",
               sqlite3_column_int(stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_text(stmt, 2),
               sqlite3_column_text(stmt, 3),
               sqlite3_column_text(stmt, 4),
               sqlite3_column_text(stmt, 5),
               sqlite3_column_double(stmt, 6));
    }

    sqlite3_finalize(stmt);
}
