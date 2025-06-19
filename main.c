#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "student.h"
#include "teacher.h"
#include "admin.h"
#include "subject.h"
#include "exam.h"
#include "utils.h"

void display_main_menu() {
    printf("\n");
    printf("========================================\n");
    printf("    SCHOOL MANAGEMENT SYSTEM v2.0\n");
    printf("========================================\n");
    printf("1.  Student Management\n");
    printf("2.  Teacher Management\n");
    printf("3.  Admin Management\n");
    printf("4.  Subject Management\n");
    printf("5.  Class Management\n");
    printf("6.  Exam Management\n");
    printf("7.  Marks & Results\n");
    printf("8.  Reports & Analytics\n");
    printf("9.  System Settings\n");
    printf("0.  Exit\n");
    printf("========================================\n");
    printf("Enter your choice: ");
}

void student_menu() {
    int choice;
    do {
        printf("\n");
        printf("===== STUDENT MANAGEMENT =====\n");
        printf("1. Register New Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Student Attendance\n");
        printf("0. Back to Main Menu\n");
        printf("==============================\n");
        printf("Enter choice: ");
        
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch(choice) {
            case 1: register_student(); break;
            case 2: display_all_students(); break;
            case 3: search_student(); break;
            case 4: update_student(); break;
            case 5: delete_student(); break;
            case 6: manage_attendance(); break;
            case 0: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 0);
}

void teacher_menu() {
    int choice;
    do {
        printf("\n");
        printf("===== TEACHER MANAGEMENT =====\n");
        printf("1. Add New Teacher\n");
        printf("2. View All Teachers\n");
        printf("3. Search Teacher\n");
        printf("4. Update Teacher\n");
        printf("5. Delete Teacher\n");
        printf("6. Assign Subjects\n");
        printf("0. Back to Main Menu\n");
        printf("==============================\n");
        printf("Enter choice: ");
        
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch(choice) {
            case 1: add_teacher(); break;
            case 2: display_all_teachers(); break;
            case 3: search_teacher(); break;
            case 4: update_teacher(); break;
            case 5: delete_teacher(); break;
            case 6: assign_subjects_to_teacher(); break;
            case 0: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 0);
}

void admin_menu() {
    int choice;
    do {
        printf("\n");
        printf("===== ADMIN MANAGEMENT =====\n");
        printf("1. Add New Admin\n");
        printf("2. View All Admins\n");
        printf("3. Update Admin\n");
        printf("4. Delete Admin\n");
        printf("5. System Backup\n");
        printf("0. Back to Main Menu\n");
        printf("============================\n");
        printf("Enter choice: ");
        
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch(choice) {
            case 1: add_admin(); break;
            case 2: display_all_admins(); break;
            case 3: update_admin(); break;
            case 4: delete_admin(); break;
            case 5: create_system_backup(); break;
            case 0: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 0);
}

void exam_menu() {
    int choice;
    do {
        printf("\n");
        printf("===== EXAM & MARKS MANAGEMENT =====\n");
        printf("1. Create New Exam\n");
        printf("2. View All Exams\n");
        printf("3. Enter Student Marks\n");
        printf("4. Update Student Marks\n");
        printf("5. View Student Results\n");
        printf("6. Generate Report Cards\n");
        printf("7. Class Performance Analysis\n");
        printf("0. Back to Main Menu\n");
        printf("===================================\n");
        printf("Enter choice: ");
        
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch(choice) {
            case 1: create_exam(); break;
            case 2: display_all_exams(); break;
            case 3: enter_student_marks(); break;
            case 4: update_student_marks(); break;
            case 5: view_student_results(); break;
            case 6: generate_report_cards(); break;
            case 7: class_performance_analysis(); break;
            case 0: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 0);
}

int main() {
    int choice;
    
    // Initialize data files
    initialize_system();
    
    printf("Welcome to Advanced School Management System!\n");
    printf("Initializing system...\n");
    
    do {
        display_main_menu();
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch(choice) {
            case 1: student_menu(); break;
            case 2: teacher_menu(); break;
            case 3: admin_menu(); break;
            case 4: subject_management_menu(); break;
            case 5: class_management_menu(); break;
            case 6: exam_menu(); break;
            case 7: marks_results_menu(); break;
            case 8: reports_analytics_menu(); break;
            case 9: system_settings_menu(); break;
            case 0: 
                printf("Thank you for using School Management System!\n");
                printf("Goodbye!\n");
                break;
            default: 
                printf("Invalid choice! Please enter a number between 0-9.\n");
        }
    } while(choice != 0);
    
    return 0;
}