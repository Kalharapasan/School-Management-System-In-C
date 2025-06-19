#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int student_id;
    char first_name[50];
    char last_name[50];
    char email[100];
    char phone[20];
    char address[200];
    char date_of_birth[15];
    char enrollment_date[15];
    int class_id;
    char class_name[50];
    char guardian_name[100];
    char guardian_phone[20];
    float fees_paid;
    float total_fees;
    char status[20]; // Active, Inactive, Suspended
} Student;

// Function declarations
void register_student();
void display_all_students();
void search_student();
void update_student();
void delete_student();
void manage_attendance();
int get_next_student_id();
void save_student_to_file(Student student);
Student* load_students_from_file(int* count);
int find_student_by_id(int id);
void display_student_details(Student student);

#endif