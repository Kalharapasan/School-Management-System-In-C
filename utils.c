#include "school_management.h"

void get_current_date(char* date_str) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date_str, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

float calculate_percentage(float obtained, float total) {
    if (total == 0) return 0;
    return (obtained / total) * 100;
}

char* get_grade(float percentage) {
    if (percentage >= 90) return "A+";
    else if (percentage >= 85) return "A";
    else if (percentage >= 80) return "A-";
    else if (percentage >= 75) return "B+";
    else if (percentage >= 70) return "B";
    else if (percentage >= 65) return "B-";
    else if (percentage >= 60) return "C+";
    else if (percentage >= 55) return "C";
    else if (percentage >= 50) return "C-";
    else if (percentage >= 45) return "D";
    else return "F";
}

void generate_report_card(int student_id) {
    Student *student = get_student(student_id);
    if (!student) {
        printf("Student not found!\n");
        return;
    }

    printf("\n" "=".repeat(60) "\n");
    printf("                    REPORT CARD\n");
    printf("=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "\n");
    printf("Student Name: %s\n", student->name);
    printf("Student ID: %d\n", student->id);
    printf("Email: %s\n", student->email);
    printf("Enrollment Date: %s\n", student->enrollment_date);
    printf("=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "\n");

    // Display exam marks
    display_student_exam_marks(student_id);

    // Display test marks
    display_student_test_marks(student_id);

    printf("=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "\n");

    free(student);
}

void backup_database() {
    char backup_filename[100];
    char current_date[20];
    get_current_date(current_date);
    sprintf(backup_filename, "school_backup_%s.db", current_date);

    char command[200];
    sprintf(command, "cp school_management.db %s", backup_filename);

    if (system(command) == 0) {
        printf("Database backed up successfully to %s\n", backup_filename);
    } else {
        printf("Backup failed!\n");
    }
}

// Class Management Functions
int add_class(Class class) {
    char *sql = "INSERT INTO classes (name, grade, section, teacher_id) VALUES (?, ?, ?, ?);";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, class.name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, class.grade);
    sqlite3_bind_text(stmt, 3, class.section, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, class.teacher_id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    printf("Class added successfully!\n");
    return 1;
}

void display_all_classes() {
    char *sql = "SELECT c.*, t.name as teacher_name FROM classes c "
                "LEFT JOIN teachers t ON c.teacher_id = t.id ORDER BY c.grade, c.section;";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    printf("\n=== ALL CLASSES ===\n");
    printf("%-5s %-15s %-8s %-10s %-20s\n",
           "ID", "Class Name", "Grade", "Section", "Class Teacher");
    printf("================================================================\n");

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        printf("%-5d %-15s %-8d %-10s %-20s\n",
               sqlite3_column_int(stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_int(stmt, 2),
               sqlite3_column_text(stmt, 3),
               sqlite3_column_text(stmt, 5) ? (char*)sqlite3_column_text(stmt, 5) : "N/A");
    }

    sqlite3_finalize(stmt);
}

// Subject Management Functions
int add_subject(Subject subject) {
    char *sql = "INSERT INTO subjects (name, code, credits, teacher_id) VALUES (?, ?, ?, ?);";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, subject.name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, subject.code, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, subject.credits);
    sqlite3_bind_int(stmt, 4, subject.teacher_id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    printf("Subject added successfully!\n");
    return 1;
}

void display_all_subjects() {
    char *sql = "SELECT s.*, t.name as teacher_name FROM subjects s "
                "LEFT JOIN teachers t ON s.teacher_id = t.id ORDER BY s.name;";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    printf("\n=== ALL SUBJECTS ===\n");
    printf("%-5s %-20s %-10s %-8s %-20s\n",
           "ID", "Subject Name", "Code", "Credits", "Teacher");
    printf("================================================================\n");

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        printf("%-5d %-20s %-10s %-8d %-20s\n",
               sqlite3_column_int(stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_text(stmt, 2),
               sqlite3_column_int(stmt, 3),
               sqlite3_column_text(stmt, 5) ? (char*)sqlite3_column_text(stmt, 5) : "N/A");
    }

    sqlite3_finalize(stmt);
}

// Admin Management Functions
int add_admin(Admin admin) {
    char *sql = "INSERT INTO admins (username, password, name, email, role) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, admin.username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, admin.password, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, admin.name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, admin.email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, admin.role, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    printf("Admin added successfully!\n");
    return 1;
}

Admin* authenticate_admin(char* username, char* password) {
    char *sql = "SELECT * FROM admins WHERE username=? AND password=?;";
    sqlite3_stmt *stmt;
    int rc;
    Admin *admin = NULL;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        admin = malloc(sizeof(Admin));
        admin->id = sqlite3_column_int(stmt, 0);
        strcpy(admin->username, (char*)sqlite3_column_text(stmt, 1));
        strcpy(admin->password, (char*)sqlite3_column_text(stmt, 2));
        strcpy(admin->name, (char*)sqlite3_column_text(stmt, 3));
        strcpy(admin->email, (char*)sqlite3_column_text(stmt, 4));
        strcpy(admin->role, (char*)sqlite3_column_text(stmt, 5));
    }

    sqlite3_finalize(stmt);
    return admin;
}
