#include "school_management.h"

void main_menu() {
    int choice;
    char username[50], password[50];
    Admin *admin;

    while (1) {
        printf("\n========================================\n");
        printf("    SCHOOL MANAGEMENT SYSTEM\n");
        printf("========================================\n");
        printf("1. Admin Login\n");
        printf("2. Exit\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);

                admin = authenticate_admin(username, password);
                if (admin) {
                    printf("\nWelcome, %s!\n", admin->name);
                    admin_menu();
                    free(admin);
                } else {
                    printf("Invalid credentials!\n");
                }
                break;
            case 2:
                printf("Thank you for using School Management System!\n");
                sqlite3_close(db);
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void admin_menu() {
    int choice;

    while (1) {
        printf("\n========================================\n");
        printf("           ADMIN PANEL\n");
        printf("========================================\n");
        printf("1. Student Management\n");
        printf("2. Teacher Management\n");
        printf("3. Class Management\n");
        printf("4. Subject Management\n");
        printf("5. Exam Management\n");
        printf("6. Marks Management\n");
        printf("7. Reports\n");
        printf("8. System Settings\n");
        printf("9. Logout\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                student_menu();
                break;
            case 2:
                teacher_menu();
                break;
            case 3:
                class_menu();
                break;
            case 4:
                subject_menu();
                break;
            case 5:
                exam_menu();
                break;
            case 6:
                marks_menu();
                break;
            case 7:
                reports_menu();
                break;
            case 8:
                system_menu();
                break;
            case 9:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void student_menu() {
    int choice, id, class_id;
    Student student;
    char search_term[100];

    while (1) {
        printf("\n========================================\n");
        printf("        STUDENT MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Student\n");
        printf("2. Update Student\n");
        printf("3. Delete Student\n");
        printf("4. View All Students\n");
        printf("5. Search Students\n");
        printf("6. View Student Details\n");
        printf("7. Back to Main Menu\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter student name: ");
                scanf(" %[^\n]", student.name);
                printf("Enter email: ");
                scanf("%s", student.email);
                printf("Enter phone: ");
                scanf("%s", student.phone);
                printf("Enter address: ");
                scanf(" %[^\n]", student.address);
                printf("Enter class ID: ");
                scanf("%d", &student.class_id);
                get_current_date(student.enrollment_date);
                add_student(student);
                break;

            case 2:
                printf("Enter student ID to update: ");
                scanf("%d", &id);
                Student *existing = get_student(id);
                if (existing) {
                    student.id = id;
                    printf("Enter new name (current: %s): ", existing->name);
                    scanf(" %[^\n]", student.name);
                    printf("Enter new email (current: %s): ", existing->email);
                    scanf("%s", student.email);
                    printf("Enter new phone (current: %s): ", existing->phone);
                    scanf("%s", student.phone);
                    printf("Enter new address (current: %s): ", existing->address);
                    scanf(" %[^\n]", student.address);
                    printf("Enter new class ID (current: %d): ", existing->class_id);
                    scanf("%d", &student.class_id);
                    strcpy(student.enrollment_date, existing->enrollment_date);
                    update_student(student);
                    free(existing);
                } else {
                    printf("Student not found!\n");
                }
                break;

            case 3:
                printf("Enter student ID to delete: ");
                scanf("%d", &id);
                delete_student(id);
                break;

            case 4:
                display_all_students();
                break;

            case 5:
                printf("Enter search term (name or email): ");
                scanf(" %[^\n]", search_term);
                search_students(search_term);
                break;

            case 6:
                printf("Enter student ID: ");
                scanf("%d", &id);
                Student *s = get_student(id);
                if (s) {
                    printf("\n=== STUDENT DETAILS ===\n");
                    printf("ID: %d\n", s->id);
                    printf("Name: %s\n", s->name);
                    printf("Email: %s\n", s->email);
                    printf("Phone: %s\n", s->phone);
                    printf("Address: %s\n", s->address);
                    printf("Enrollment Date: %s\n", s->enrollment_date);
                    printf("Class ID: %d\n", s->class_id);
                    free(s);
                } else {
                    printf("Student not found!\n");
                }
                break;

            case 7:
                return;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void teacher_menu() {
    int choice, id;
    Teacher teacher;

    while (1) {
        printf("\n========================================\n");
        printf("        TEACHER MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Teacher\n");
        printf("2. Update Teacher\n");
        printf("3. Delete Teacher\n");
        printf("4. View All Teachers\n");
        printf("5. View Teacher Details\n");
        printf("6. Back to Main Menu\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter teacher name: ");
                scanf(" %[^"]", teacher.name);
                printf("Enter email: ");
                scanf("%s", teacher.email);
                printf("Enter phone: ");
                scanf("%s", teacher.phone);
                printf("Enter subject: ");
                scanf(" %[^"]", teacher.subject);
                printf("Enter qualification: ");
                scanf(" %[^"]", teacher.qualification);
                printf("Enter salary: ");
                scanf("%f", &teacher.salary);
                get_current_date(teacher.join_date);
                add_teacher(teacher);
                break;

            case 2:
                printf("Enter teacher ID to update: ");
                scanf("%d", &id);
                Teacher *existing = get_teacher(id);
                if (existing) {
                    teacher.id = id;
                    printf("Enter new name (current: %s): ", existing->name);
                    scanf(" %[^"]", teacher.name);
                    printf("Enter new email (current: %s): ", existing->email);
                    scanf("%s", teacher.email);
                    printf("Enter new phone (current: %s): ", existing->phone);
                    scanf("%s", teacher.phone);
                    printf("Enter new subject (current: %s): ", existing->subject);
                    scanf(" %[^"]", teacher.subject);
                    printf("Enter new qualification (current: %s): ", existing->qualification);
                    scanf(" %[^"]", teacher.qualification);
                    printf("Enter new salary (current: %.2f): ", existing->salary);
                    scanf("%f", &teacher.salary);
                    strcpy(teacher.join_date, existing->join_date);
                    update_teacher(teacher);
                    free(existing);
                } else {
                    printf("Teacher not found!\n");
                }
                break;

            case 3:
                printf("Enter teacher ID to delete: ");
                scanf("%d", &id);
                delete_teacher(id);
                break;

            case 4:
                display_all_teachers();
                break;

            case 5:
                printf("Enter teacher ID: ");
                scanf("%d", &id);
                Teacher *t = get_teacher(id);
                if (t) {
                    printf("\n=== TEACHER DETAILS ===\n");
                    printf("ID: %d\n", t->id);
                    printf("Name: %s\n", t->name);
                    printf("Email: %s\n", t->email);
                    printf("Phone: %s\n", t->phone);
                    printf("Subject: %s\n", t->subject);
                    printf("Qualification: %s\n", t->qualification);
                    printf("Salary: %.2f\n", t->salary);
                    printf("Join Date: %s\n", t->join_date);
                    free(t);
                } else {
                    printf("Teacher not found!\n");
                }
                break;

            case 6:
                return;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void class_menu() {
    int choice;
    Class class_data;

    while (1) {
        printf("\n======== CLASS MANAGEMENT ========\n");
        printf("1. Add Class\n");
        printf("2. View All Classes\n");
        printf("3. Back to Admin Menu\n");
        printf("==================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter class name: ");
                scanf(" %[^\n]", class_data.name);
                printf("Enter grade (1-13): ");
                scanf("%d", &class_data.grade);
                printf("Enter section: ");
                scanf(" %[^\n]", class_data.section);
                printf("Enter class teacher ID: ");
                scanf("%d", &class_data.teacher_id);
                add_class(class_data);
                break;

            case 2:
                display_all_classes();
                break;

            case 3:
                return;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

void subject_menu() {
    int choice;
    Subject subject;

    while (1) {
        printf("\n======== SUBJECT MANAGEMENT ========\n");
        printf("1. Add Subject\n");
        printf("2. View All Subjects\n");
        printf("3. Back to Admin Menu\n");
        printf("====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter subject name: ");
                scanf(" %[^\n]", subject.name);
                printf("Enter subject code: ");
                scanf(" %[^\n]", subject.code);
                printf("Enter credits: ");
                scanf("%d", &subject.credits);
                printf("Enter teacher ID: ");
                scanf("%d", &subject.teacher_id);
                add_subject(subject);
                break;

            case 2:
                display_all_subjects();
                break;

            case 3:
                return;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

void exam_menu() {
    int choice;
    Exam exam;

    while (1) {
        printf("\n========== EXAM MANAGEMENT ==========\n");
        printf("1. Add Exam\n");
        printf("2. View All Exams\n");
        printf("3. Back to Admin Menu\n");
        printf("=====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter exam name: ");
                scanf(" %[^\n]", exam.name);
                printf("Enter exam date (YYYY-MM-DD): ");
                scanf("%s", exam.date);
                printf("Enter subject ID: ");
                scanf("%d", &exam.subject_id);
                printf("Enter class ID: ");
                scanf("%d", &exam.class_id);
                printf("Enter total marks: ");
                scanf("%d", &exam.total_marks);
                add_exam(exam);
                break;

            case 2:
                display_all_exams();
                break;

            case 3:
                return;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

void marks_menu() {
    int choice;
    StudentExamMark exam_mark;
    StudentTestMark test_mark;

    while (1) {
        printf("\n=========== MARKS MANAGEMENT ===========\n");
        printf("1. Add Exam Mark\n");
        printf("2. Add Test Mark\n");
        printf("3. View Student Exam Marks\n");
        printf("4. View Student Test Marks\n");
        printf("5. Back to Admin Menu\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter student ID: ");
                scanf("%d", &exam_mark.student_id);
                printf("Enter exam ID: ");
                scanf("%d", &exam_mark.exam_id);
                printf("Enter marks obtained: ");
                scanf("%f", &exam_mark.marks_obtained);
                strcpy(exam_mark.grade, get_grade(calculate_percentage(exam_mark.marks_obtained, 100)));
                add_student_exam_mark(exam_mark);
                break;

            case 2:
                printf("Enter student ID: ");
                scanf("%d", &test_mark.student_id);
                printf("Enter subject ID: ");
                scanf("%d", &test_mark.subject_id);
                printf("Enter test type (e.g., Quiz/Midterm): ");
                scanf(" %[^\n]", test_mark.test_type);
                printf("Enter marks obtained: ");
                scanf("%f", &test_mark.marks_obtained);
                printf("Enter total marks: ");
                scanf("%f", &test_mark.total_marks);
                get_current_date(test_mark.date);
                add_student_test_mark(test_mark);
                break;

            case 3:
                printf("Enter student ID: ");
                scanf("%d", &exam_mark.student_id);
                display_student_exam_marks(exam_mark.student_id);
                break;

            case 4:
                printf("Enter student ID: ");
                scanf("%d", &test_mark.student_id);
                display_student_test_marks(test_mark.student_id);
                break;

            case 5:
                return;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

void reports_menu() {
    int student_id;

    while (1) {
        printf("\n============= REPORTS =============\n");
        printf("1. Generate Student Report Card\n");
        printf("2. Back to Admin Menu\n");
        printf("===================================\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter student ID: ");
                scanf("%d", &student_id);
                generate_report_card(student_id);
                break;

            case 2:
                return;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

void system_menu() {
    int choice;

    while (1) {
        printf("\n========== SYSTEM SETTINGS ==========\n");
        printf("1. Backup Database\n");
        printf("2. Back to Admin Menu\n");
        printf("=====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                backup_database();
                break;

            case 2:
                return;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
