#ifndef EXAM_H
#define EXAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int exam_id;
    char exam_name[100];
    char exam_type[50]; // Midterm, Final, Quiz, Assignment
    int subject_id;
    char subject_name[100];
    int class_id;
    char class_name[50];
    char exam_date[15];
    char start_time[10];
    char end_time[10];
    int total_marks;
    char status[20]; // Scheduled, Completed, Cancelled
} Exam;

typedef struct {
    int mark_id;
    int student_id;
    char student_name[100];
    int exam_id;
    char exam_name[100];
    int subject_id;
    char subject_name[100];
    float marks_obtained;
    float total_marks;
    float percentage;
    char grade[5];
    char remarks[200];
    char entry_date[15];
} ExamMark;

// Function declarations
void create_exam();
void display_all_exams();
void enter_student_marks();
void update_student_marks();
void view_student_results();
void generate_report_cards();
void class_performance_analysis();
void marks_results_menu();
void reports_analytics_menu();
void system_settings_menu();
int get_next_exam_id();
int get_next_mark_id();
void save_exam_to_file(Exam exam);
void save_mark_to_file(ExamMark mark);
Exam* load_exams_from_file(int* count);
ExamMark* load_marks_from_file(int* count);
void display_exam_details(Exam exam);
char* calculate_grade(float percentage);

#endif