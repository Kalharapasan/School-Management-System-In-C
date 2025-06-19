#ifndef TEACHER_H
#define TEACHER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int teacher_id;
    char first_name[50];
    char last_name[50];
    char email[100];
    char phone[20];
    char address[200];
    char qualification[100];
    char specialization[100];
    char hire_date[15];
    float salary;
    char subjects[200]; // Comma-separated list
    char status[20]; // Active, Inactive, On Leave
    int experience_years;
} Teacher;

// Function declarations
void add_teacher();
void display_all_teachers();
void search_teacher();
void update_teacher();
void delete_teacher();
void assign_subjects_to_teacher();
int get_next_teacher_id();
void save_teacher_to_file(Teacher teacher);
Teacher* load_teachers_from_file(int* count);
int find_teacher_by_id(int id);
void display_teacher_details(Teacher teacher);

#endif