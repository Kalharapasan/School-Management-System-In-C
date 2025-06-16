
#ifndef SCHOOL_MANAGEMENT_H
#define SCHOOL_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>

// Structure definitions
typedef struct {
    int id;
    char name[100];
    char email[100];
    char phone[20];
    char address[200];
    char enrollment_date[20];
    int class_id;
} Student;

typedef struct {
    int id;
    char name[100];
    char email[100];
    char phone[20];
    char subject[50];
    char qualification[100];
    float salary;
    char join_date[20];
} Teacher;

typedef struct {
    int id;
    char username[50];
    char password[50];
    char name[100];
    char email[100];
    char role[20];
} Admin;

typedef struct {
    int id;
    char name[50];
    int grade;
    char section[10];
    int teacher_id;
} Class;

typedef struct {
    int id;
    char name[100];
    char code[20];
    int credits;
    int teacher_id;
} Subject;

typedef struct {
    int id;
    char name[100];
    char date[20];
    int subject_id;
    int class_id;
    int total_marks;
} Exam;

typedef struct {
    int id;
    int student_id;
    int exam_id;
    float marks_obtained;
    char grade[5];
} StudentExamMark;

typedef struct {
    int id;
    int student_id;
    int subject_id;
    char test_type[50];
    float marks_obtained;
    float total_marks;
    char date[20];
} StudentTestMark;

// Function declarations
int initialize_database();
void create_tables();

// Student functions
int add_student(Student student);
int update_student(Student student);
int delete_student(int id);
Student* get_student(int id);
void display_all_students();
void search_students(char* search_term);

// Teacher functions
int add_teacher(Teacher teacher);
int update_teacher(Teacher teacher);
int delete_teacher(int id);
Teacher* get_teacher(int id);
void display_all_teachers();

// Admin functions
int add_admin(Admin admin);
int update_admin(Admin admin);
int delete_admin(int id);
Admin* authenticate_admin(char* username, char* password);
void display_all_admins();

// Class functions
int add_class(Class class);
int update_class(Class class);
int delete_class(int id);
Class* get_class(int id);
void display_all_classes();

// Subject functions
int add_subject(Subject subject);
int update_subject(Subject subject);
int delete_subject(int id);
Subject* get_subject(int id);
void display_all_subjects();

// Exam functions
int add_exam(Exam exam);
int update_exam(Exam exam);
int delete_exam(int id);
Exam* get_exam(int id);
void display_all_exams();

// Student Exam Mark functions
int add_student_exam_mark(StudentExamMark mark);
int update_student_exam_mark(StudentExamMark mark);
int delete_student_exam_mark(int id);
void display_student_exam_marks(int student_id);
void display_exam_results(int exam_id);

// Student Test Mark functions
int add_student_test_mark(StudentTestMark mark);
int update_student_test_mark(StudentTestMark mark);
int delete_student_test_mark(int id);
void display_student_test_marks(int student_id);

// Utility functions
void get_current_date(char* date_str);
float calculate_percentage(float obtained, float total);
char* get_grade(float percentage);
void generate_report_card(int student_id);
void backup_database();
void restore_database();

// Menu functions
void main_menu();
void student_menu();
void teacher_menu();
void admin_menu();
void class_menu();
void subject_menu();
void exam_menu();
void marks_menu();
void reports_menu();

// Global database connection
extern sqlite3 *db;

#endif
