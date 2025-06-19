#include "school_management.h"

// Exam Management Functions
int add_exam(Exam exam) {
    char *sql = "INSERT INTO exams (name, date, subject_id, class_id, total_marks) "
                "VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, exam.name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, exam.date, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, exam.subject_id);
    sqlite3_bind_int(stmt, 4, exam.class_id);
    sqlite3_bind_int(stmt, 5, exam.total_marks);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    printf("Exam added successfully!\n");
    return 1;
}

int update_exam(Exam exam) {
    char *sql = "UPDATE exams SET name=?, date=?, subject_id=?, class_id=?, total_marks=? WHERE id=?;";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, exam.name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, exam.date, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, exam.subject_id);
    sqlite3_bind_int(stmt, 4, exam.class_id);
    sqlite3_bind_int(stmt, 5, exam.total_marks);
    sqlite3_bind_int(stmt, 6, exam.id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Update failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    printf("Exam updated successfully!\n");
    return 1;
}

void display_all_exams() {
    char *sql = "SELECT e.*, s.name as subject_name, c.name as class_name FROM exams e "
                "LEFT JOIN subjects s ON e.subject_id = s.id "
                "LEFT JOIN classes c ON e.class_id = c.id ORDER BY e.
