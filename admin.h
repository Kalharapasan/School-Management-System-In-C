#ifndef ADMIN_H
#define ADMIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int admin_id;
    char username[50];
    char password[100];
    char first_name[50];
    char last_name[50];
    char email[100];
    char phone[20];
    char role[50]; // Super Admin, Admin, Assistant
    char created_date[15];
    char last_login[20];
    char status[20]; // Active, Inactive
} Admin;

// Function declarations
void add_admin();
void display_all_admins();
void update_admin();
void delete_admin();
void create_system_backup();
int get_next_admin_id();
void save_admin_to_file(Admin admin);
Admin* load_admins_from_file(int* count);
int find_admin_by_id(int id);
void display_admin_details(Admin admin);

#endif