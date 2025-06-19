#include "school_management.h"

int add_student(Student student) {
    char *sql = "INSERT INTO students (name, email, phone, address, enrollment_date, class_id) "
                "VALUES (?, ?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, student.name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, student.email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, student.phone, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, student.address, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, student.enrollment_date, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, student.class_id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    printf("Student added successfully!\n");
    return 1;
}

int update_student(Student student) {
    char *sql = "UPDATE students SET name=?, email=?, phone=?, address=?, class_id=? WHERE id=?;";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, student.name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, student.email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, student.phone, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, student.address, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, student.class_id);
    sqlite3_bind_int(stmt, 6, student.id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Update failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    printf("Student updated successfully!\n");
    return 1;
}

int delete_student(int id) {
    char *sql = "DELETE FROM students WHERE id=?;";
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
    printf("Student deleted successfully!\n");
    return 1;
}

Student* get_student(int id) {
    char *sql = "SELECT * FROM students WHERE id=?;";
    sqlite3_stmt *stmt;
    int rc;
    Student *student = NULL;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    sqlite3_bind_int(stmt, 1, id);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        student = malloc(sizeof(Student));
        student->id = sqlite3_column_int(stmt, 0);
        strcpy(student->name, (char*)sqlite3_column_text(stmt, 1));
        strcpy(student->email, (char*)sqlite3_column_text(stmt, 2));
        strcpy(student->phone, (char*)sqlite3_column_text(stmt, 3));
        strcpy(student->address, (char*)sqlite3_column_text(stmt, 4));
        strcpy(student->enrollment_date, (char*)sqlite3_column_text(stmt, 5));
        student->class_id = sqlite3_column_int(stmt, 6);
    }

    sqlite3_finalize(stmt);
    return student;
}

void display_all_students() {
    char *sql = "SELECT s.*, c.name as class_name FROM students s "
                "LEFT JOIN classes c ON s.class_id = c.id ORDER BY s.id;";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    printf("\n=== ALL STUDENTS ===\n");
    printf("%-5s %-20s %-25s %-15s %-15s %-15s\n",
           "ID", "Name", "Email", "Phone", "Class", "Enrollment");
    printf("================================================================================\n");

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        printf("%-5d %-20s %-25s %-15s %-15s %-15s\n",
               sqlite3_column_int(stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_text(stmt, 2),
               sqlite3_column_text(stmt, 3),
               sqlite3_column_text(stmt, 7) ? (char*)sqlite3_column_text(stmt, 7) : "N/A",
               sqlite3_column_text(stmt, 5));
    }

    sqlite3_finalize(stmt);
}

void search_students(char* search_term) {
    char *sql = "SELECT s.*, c.name as class_name FROM students s "
                "LEFT JOIN classes c ON s.class_id = c.id "
                "WHERE s.name LIKE ? OR s.email LIKE ? ORDER BY s.id;";
    sqlite3_stmt *stmt;
    int rc;
    char search_pattern[200];

    sprintf(search_pattern, "%%%s%%", search_term);

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, search_pattern, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, search_pattern, -1, SQLITE_STATIC);

    printf("\n=== SEARCH RESULTS ===\n");
    printf("%-5s %-20s %-25s %-15s %-15s %-15s\n",
           "ID", "Name", "Email", "Phone", "Class", "Enrollment");
    printf("================================================================================\n");

    int found = 0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        found = 1;
        printf("%-5d %-20s %-25s %-15s %-15s %-15s\n",
               sqlite3_column_int(stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_text(stmt, 2),
               sqlite3_column_text(stmt, 3),
               sqlite3_column_text(stmt, 7) ? (char*)sqlite3_column_text(stmt, 7) : "N/A",
               sqlite3_column_text(stmt, 5));
    }

    if (!found) {
        printf("No students found matching '%s'\n", search_term);
    }

    sqlite3_finalize(stmt);
}
