#ifndef SUBJECT_H
#define SUBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int subject_id;
    char subject_name[100];
    char subject_code[20];
    char description[200];
    int credits;
    int class_id;
    char class_name[50];
    int teacher_id;
    char teacher_name[100];
    char status[20]; // Active, Inactive
} Subject;

// Function declarations
void subject_management_menu();
void add_subject();
void display_all_subjects();
void search_subject();
void update_subject();
void delete_subject();
void class_management_menu();
int get_next_subject_id();
void save_subject_to_file(Subject subject);
Subject* load_subjects_from_file(int* count);
int find_subject_by_id(int id);
void display_subject_details(Subject subject);

#endif