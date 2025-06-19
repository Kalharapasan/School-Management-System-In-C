#include "school_management.h"

sqlite3 *db;

int initialize_database() {
    int rc = sqlite3_open("school_management.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    create_tables();
    printf("Database initialized successfully!\n");
    return 1;
}

void create_tables() {
    char *sql;
    char *err_msg = 0;
    int rc;

    // Create Students table
    sql = "CREATE TABLE IF NOT EXISTS students ("
          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
          "name TEXT NOT NULL,"
          "email TEXT UNIQUE,"
          "phone TEXT,"
          "address TEXT,"
          "enrollment_date TEXT,"
          "class_id INTEGER);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    // Create Teachers table
    sql = "CREATE TABLE IF NOT EXISTS teachers ("
          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
          "name TEXT NOT NULL,"
          "email TEXT UNIQUE,"
          "phone TEXT,"
          "subject TEXT,"
          "qualification TEXT,"
          "salary REAL,"
          "join_date TEXT);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    // Create Admins table
    sql = "CREATE TABLE IF NOT EXISTS admins ("
          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
          "username TEXT UNIQUE NOT NULL,"
          "password TEXT NOT NULL,"
          "name TEXT NOT NULL,"
          "email TEXT,"
          "role TEXT);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    // Create Classes table
    sql = "CREATE TABLE IF NOT EXISTS classes ("
          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
          "name TEXT NOT NULL,"
          "grade INTEGER,"
          "section TEXT,"
          "teacher_id INTEGER);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    // Create Subjects table
    sql = "CREATE TABLE IF NOT EXISTS subjects ("
          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
          "name TEXT NOT NULL,"
          "code TEXT UNIQUE,"
          "credits INTEGER,"
          "teacher_id INTEGER);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    // Create Exams table
    sql = "CREATE TABLE IF NOT EXISTS exams ("
          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
          "name TEXT NOT NULL,"
          "date TEXT,"
          "subject_id INTEGER,"
          "class_id INTEGER,"
          "total_marks INTEGER);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    // Create Student Exam Marks table
    sql = "CREATE TABLE IF NOT EXISTS student_exam_marks ("
          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
          "student_id INTEGER,"
          "exam_id INTEGER,"
          "marks_obtained REAL,"
          "grade TEXT);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    // Create Student Test Marks table
    sql = "CREATE TABLE IF NOT EXISTS student_test_marks ("
          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
          "student_id INTEGER,"
          "subject_id INTEGER,"
          "test_type TEXT,"
          "marks_obtained REAL,"
          "total_marks REAL,"
          "date TEXT);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    // Insert default admin if not exists
    sql = "INSERT OR IGNORE INTO admins (username, password, name, email, role) "
          "VALUES ('admin', 'admin123', 'System Administrator', 'admin@school.com', 'Super Admin');";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}
