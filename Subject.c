#include "subject.h"
#include "utils.h"



void class_management_menu() {
    printf("\n===== CLASS MANAGEMENT =====\n");
    printf("This feature will be implemented in the next version.\n");
    printf("Features will include:\n");
    printf("- Create and manage classes\n");
    printf("- Assign subjects to classes\n");
    printf("- View class schedules\n");
    printf("- Manage class capacity\n");
}

void add_subject() {
    Subject new_subject;

    printf("\n===== ADD NEW SUBJECT =====\n");

    new_subject.subject_id = get_next_subject_id();
    printf("Subject ID (Auto-generated): %d\n", new_subject.subject_id);

    printf("Enter Subject Name: ");
    fgets(new_subject.subject_name, sizeof(new_subject.subject_name), stdin);
    remove_newline(new_subject.subject_name);

    printf("Enter Subject Code: ");
    fgets(new_subject.subject_code, sizeof(new_subject.subject_code), stdin);
    remove_newline(new_subject.subject_code);

    printf("Enter Description: ");
    fgets(new_subject.description, sizeof(new_subject.description), stdin);
    remove_newline(new_subject.description);

    printf("Enter Credits: ");
    scanf("%d", &new_subject.credits);

    printf("Enter Class ID: ");
    scanf("%d", &new_subject.class_id);
    clear_input_buffer();

    printf("Enter Class Name: ");
    fgets(new_subject.class_name, sizeof(new_subject.class_name), stdin);
    remove_newline(new_subject.class_name);

    printf("Enter Teacher ID (0 for unassigned): ");
    scanf("%d", &new_subject.teacher_id);
    clear_input_buffer();

    if (new_subject.teacher_id > 0) {
        printf("Enter Teacher Name: ");
        fgets(new_subject.teacher_name, sizeof(new_subject.teacher_name), stdin);
        remove_newline(new_subject.teacher_name);
    } else {
        strcpy(new_subject.teacher_name, "Unassigned");
    }

    strcpy(new_subject.status, "Active");

    save_subject_to_file(new_subject);

    printf("\n✓ Subject added successfully!\n");
    printf("Subject ID: %d\n", new_subject.subject_id);
    printf("Subject: %s (%s)\n", new_subject.subject_name, new_subject.subject_code);
}

void display_all_subjects() {
    int count = 0;
    Subject* subjects = load_subjects_from_file(&count);

    if (count == 0) {
        printf("\nNo subjects found in database.\n");
        return;
    }

    printf("\n===== ALL SUBJECTS =====\n");
    printf("%-5s %-20s %-10s %-15s %-8s %-20s %-10s\n",
           "ID", "Subject Name", "Code", "Class", "Credits", "Teacher", "Status");
    printf("===================================================================================\n");

    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-10s %-15s %-8d %-20s %-10s\n",
               subjects[i].subject_id,
               subjects[i].subject_name,
               subjects[i].subject_code,
               subjects[i].class_name,
               subjects[i].credits,
               subjects[i].teacher_name,
               subjects[i].status);
    }

    printf("\nTotal Subjects: %d\n", count);
    free(subjects);
}

void search_subject() {
    int search_choice;
    int count = 0;
    Subject* subjects = load_subjects_from_file(&count);

    if (count == 0) {
        printf("\nNo subjects found in database.\n");
        return;
    }

    printf("\n===== SEARCH SUBJECT =====\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("3. Search by Code\n");
    printf("4. Search by Class\n");
    printf("Enter choice: ");
    scanf("%d", &search_choice);
    clear_input_buffer();

    switch(search_choice) {
        case 1: {
            int id;
            printf("Enter Subject ID: ");
            scanf("%d", &id);
            clear_input_buffer();

            for (int i = 0; i < count; i++) {
                if (subjects[i].subject_id == id) {
                    display_subject_details(subjects[i]);
                    free(subjects);
                    return;
                }
            }
            printf("Subject with ID %d not found.\n", id);
            break;
        }
        case 2: {
            char name[100];
            printf("Enter subject name: ");
            fgets(name, sizeof(name), stdin);
            remove_newline(name);

            int found = 0;
            for (int i = 0; i < count; i++) {
                if (strstr(subjects[i].subject_name, name)) {
                    if (!found) {
                        printf("\n===== SEARCH RESULTS =====\n");
                        found = 1;
                    }
                    display_subject_details(subjects[i]);
                    printf("----------------------------\n");
                }
            }
            if (!found) {
                printf("No subjects found with name containing '%s'.\n", name);
            }
            break;
        }
        case 3: {
            char code[20];
            printf("Enter subject code: ");
            fgets(code, sizeof(code), stdin);
            remove_newline(code);

            int found = 0;
            for (int i = 0; i < count; i++) {
                if (strcmp(subjects[i].subject_code, code) == 0) {
                    display_subject_details(subjects[i]);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("No subject found with code '%s'.\n", code);
            }
            break;
        }
        case 4: {
            char class_name[50];
            printf("Enter class name: ");
            fgets(class_name, sizeof(class_name), stdin);
            remove_newline(class_name);

            int found = 0;
            for (int i = 0; i < count; i++) {
                if (strstr(subjects[i].class_name, class_name)) {
                    if (!found) {
                        printf("\n===== SUBJECTS IN CLASS '%s' =====\n", class_name);
                        found = 1;
                    }
                    printf("ID: %d | Subject: %s | Code: %s | Credits: %d\n",
                           subjects[i].subject_id,
                           subjects[i].subject_name,
                           subjects[i].subject_code,
                           subjects[i].credits);
                }
            }
            if (!found) {
                printf("No subjects found for class '%s'.\n", class_name);
            }
            break;
        }
        default:
            printf("Invalid choice!\n");
    }

    free(subjects);
}

void update_subject() {
    int id;
    printf("\nEnter Subject ID to update: ");
    scanf("%d", &id);
    clear_input_buffer();

    int index = find_subject_by_id(id);
    if (index == -1) {
        printf("Subject with ID %d not found.\n", id);
        return;
    }

    int count = 0;
    Subject* subjects = load_subjects_from_file(&count);

    printf("\n===== UPDATE SUBJECT (ID: %d) =====\n", id);
    display_subject_details(subjects[index]);

    printf("\nWhat do you want to update?\n");
    printf("1. Subject Name\n");
    printf("2. Subject Code\n");
    printf("3. Description\n");
    printf("4. Credits\n");
    printf("5. Class Information\n");
    printf("6. Status\n");
    printf("Enter choice: ");

    int choice;
    scanf("%d", &choice);
    clear_input_buffer();

    switch(choice) {
        case 1:
            printf("Enter new Subject Name (current: %s): ", subjects[index].subject_name);
            fgets(subjects[index].subject_name, sizeof(subjects[index].subject_name), stdin);
            remove_newline(subjects[index].subject_name);
            break;

        case 2:
            printf("Enter new Subject Code (current: %s): ", subjects[index].subject_code);
            fgets(subjects[index].subject_code, sizeof(subjects[index].subject_code), stdin);
            remove_newline(subjects[index].subject_code);
            break;

        case 3:
            printf("Enter new Description (current: %s): ", subjects[index].description);
            fgets(subjects[index].description, sizeof(subjects[index].description), stdin);
            remove_newline(subjects[index].description);
            break;

        case 4:
            printf("Enter new Credits (current: %d): ", subjects[index].credits);
            scanf("%d", &subjects[index].credits);
            clear_input_buffer();
            break;

        case 5:
            printf("Enter new Class ID (current: %d): ", subjects[index].class_id);
            scanf("%d", &subjects[index].class_id);
            clear_input_buffer();

            printf("Enter new Class Name (current: %s): ", subjects[index].class_name);
            fgets(subjects[index].class_name, sizeof(subjects[index].class_name), stdin);
            remove_newline(subjects[index].class_name);
            break;

        case 6:
            printf("Enter new Status (current: %s): ", subjects[index].status);
            fgets(subjects[index].status, sizeof(subjects[index].status), stdin);
            remove_newline(subjects[index].status);
            break;

        default:
            printf("Invalid choice!\n");
            free(subjects);
            return;
    }

    // Save updated data
    FILE* file = fopen("data/subjects.txt", "w");
    if (file) {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%d|%s|%s|%s|%d|%d|%s|%d|%s|%s\n",
                    subjects[i].subject_id, subjects[i].subject_name, subjects[i].subject_code,
                    subjects[i].description, subjects[i].credits, subjects[i].class_id,
                    subjects[i].class_name, subjects[i].teacher_id, subjects[i].teacher_name,
                    subjects[i].status);
        }
        fclose(file);
        printf("\n✓ Subject information updated successfully!\n");
    } else {
        printf("Error updating subject information.\n");
    }

    free(subjects);
}

void delete_subject() {
    int id;
    printf("\nEnter Subject ID to delete: ");
    scanf("%d", &id);
    clear_input_buffer();

    int index = find_subject_by_id(id);
    if (index == -1) {
        printf("Subject with ID %d not found.\n", id);
        return;
    }

    int count = 0;
    Subject* subjects = load_subjects_from_file(&count);

    printf("\n===== CONFIRM DELETION =====\n");
    display_subject_details(subjects[index]);

    printf("\nAre you sure you want to delete this subject? (y/N): ");
    char confirm = getchar();
    clear_input_buffer();

    if (confirm == 'y' || confirm == 'Y') {
        FILE* file = fopen("data/subjects.txt", "w");
        if (file) {
            for (int i = 0; i < count; i++) {
                if (i != index) {
                    fprintf(file, "%d|%s|%s|%s|%d|%d|%s|%d|%s|%s\n",
                            subjects[i].subject_id, subjects[i].subject_name, subjects[i].subject_code,
                            subjects[i].description, subjects[i].credits, subjects[i].class_id,
                            subjects[i].class_name, subjects[i].teacher_id, subjects[i].teacher_name,
                            subjects[i].status);
                }
            }
            fclose(file);
            printf("\n✓ Subject deleted successfully!\n");
        } else {
            printf("Error deleting subject.\n");
        }
    } else {
        printf("Deletion cancelled.\n");
    }

    free(subjects);
}

void assign_teacher_to_subject() {
    int subject_id, teacher_id;

    printf("\nEnter Subject ID: ");
    scanf("%d", &subject_id);

    printf("Enter Teacher ID: ");
    scanf("%d", &teacher_id);
    clear_input_buffer();

    int index = find_subject_by_id(subject_id);
    if (index == -1) {
        printf("Subject with ID %d not found.\n", subject_id);
        return;
    }

    int count = 0;
    Subject* subjects = load_subjects_from_file(&count);

    subjects[index].teacher_id = teacher_id;

    printf("Enter Teacher Name: ");
    fgets(subjects[index].teacher_name, sizeof(subjects[index].teacher_name), stdin);
    remove_newline(subjects[index].teacher_name);

    // Save updated data
    FILE* file = fopen("data/subjects.txt", "w");
    if (file) {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%d|%s|%s|%s|%d|%d|%s|%d|%s|%s\n",
                    subjects[i].subject_id, subjects[i].subject_name, subjects[i].subject_code,
                    subjects[i].description, subjects[i].credits, subjects[i].class_id,
                    subjects[i].class_name, subjects[i].teacher_id, subjects[i].teacher_name,
                    subjects[i].status);
        }
        fclose(file);
        printf("\n✓ Teacher assigned to subject successfully!\n");
    } else {
        printf("Error assigning teacher to subject.\n");
    }

    free(subjects);
}

int get_next_subject_id() {
    FILE* file = fopen("data/subjects.txt", "r");
    int max_id = 3000; // Starting ID for subjects

    if (file) {
        char line[300];
        while (fgets(line, sizeof(line), file)) {
            int id;
            sscanf(line, "%d|", &id);
            if (id > max_id) {
                max_id = id;
            }
        }
        fclose(file);
    }

    return max_id + 1;
}

void save_subject_to_file(Subject subject) {
    FILE* file = fopen("data/subjects.txt", "a");
    if (file) {
        fprintf(file, "%d|%s|%s|%s|%d|%d|%s|%d|%s|%s\n",
                subject.subject_id, subject.subject_name, subject.subject_code,
                subject.description, subject.credits, subject.class_id,
                subject.class_name, subject.teacher_id, subject.teacher_name,
                subject.status);
        fclose(file);
    } else {
        printf("Error: Could not save subject data.\n");
    }
}

Subject* load_subjects_from_file(int* count) {
    FILE* file = fopen("data/subjects.txt", "r");
    Subject* subjects = NULL;
    *count = 0;

    if (!file) {
        return NULL;
    }

    char line[400];
    int capacity = 10;
    subjects = malloc(capacity * sizeof(Subject));

    while (fgets(line, sizeof(line), file)) {
        if (*count >= capacity) {
            capacity *= 2;
            subjects = realloc(subjects, capacity * sizeof(Subject));
        }

        sscanf(line, "%d|%99[^|]|%19[^|]|%199[^|]|%d|%d|%49[^|]|%d|%99[^|]|%19[^|\n]",
               &subjects[*count].subject_id,
               subjects[*count].subject_name,
               subjects[*count].subject_code,
               subjects[*count].description,
               &subjects[*count].credits,
               &subjects[*count].class_id,
               subjects[*count].class_name,
               &subjects[*count].teacher_id,
               subjects[*count].teacher_name,
               subjects[*count].status);

        (*count)++;
    }

    fclose(file);
    return subjects;
}

int find_subject_by_id(int id) {
    int count = 0;
    Subject* subjects = load_subjects_from_file(&count);

    if (!subjects) return -1;

    for (int i = 0; i < count; i++) {
        if (subjects[i].subject_id == id) {
            free(subjects);
            return i;
        }
    }

    free(subjects);
    return -1;
}

void display_subject_details(Subject subject) {
    printf("\n===== SUBJECT DETAILS =====\n");
    printf("Subject ID: %d\n", subject.subject_id);
    printf("Subject Name: %s\n", subject.subject_name);
    printf("Subject Code: %s\n", subject.subject_code);
    printf("Description: %s\n", subject.description);
    printf("Credits: %d\n", subject.credits);
    printf("Class: %s (ID: %d)\n", subject.class_name, subject.class_id);
    printf("Teacher: %s (ID: %d)\n", subject.teacher_name, subject.teacher_id);
    printf("Status: %s\n", subject.status);
    printf("===========================\n");
}

void subject_management_menu() {
    int choice;
    do {
        printf("\n===== SUBJECT MANAGEMENT =====\n");
        printf("1. Add New Subject\n");
        printf("2. View All Subjects\n");
        printf("3. Search Subject\n");
        printf("4. Update Subject\n");
        printf("5. Delete Subject\n");
        printf("6. Assign Teacher to Subject\n");
        printf("0. Back to Main Menu\n");
        printf("==============================\n");
        printf("Enter choice: ");

        scanf("%d", &choice);
        clear_input_buffer();

        switch(choice) {
            case 1: add_subject(); break;
            case 2: display_all_subjects(); break;
            case 3: search_subject(); break;
            case 4: update_subject(); break;
            case 5: delete_subject(); break;
            case 6: assign_teacher_to_subject(); break;
            case 0: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 0);
}
