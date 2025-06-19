#include "teacher.h"
#include "utils.h"

void add_teacher() {
    Teacher new_teacher;
    
    printf("\n===== ADD NEW TEACHER =====\n");
    
    new_teacher.teacher_id = get_next_teacher_id();
    printf("Teacher ID (Auto-generated): %d\n", new_teacher.teacher_id);
    
    printf("Enter First Name: ");
    fgets(new_teacher.first_name, sizeof(new_teacher.first_name), stdin);
    remove_newline(new_teacher.first_name);
    
    printf("Enter Last Name: ");
    fgets(new_teacher.last_name, sizeof(new_teacher.last_name), stdin);
    remove_newline(new_teacher.last_name);
    
    printf("Enter Email: ");
    fgets(new_teacher.email, sizeof(new_teacher.email), stdin);
    remove_newline(new_teacher.email);
    
    printf("Enter Phone Number: ");
    fgets(new_teacher.phone, sizeof(new_teacher.phone), stdin);
    remove_newline(new_teacher.phone);
    
    printf("Enter Address: ");
    fgets(new_teacher.address, sizeof(new_teacher.address), stdin);
    remove_newline(new_teacher.address);
    
    printf("Enter Qualification: ");
    fgets(new_teacher.qualification, sizeof(new_teacher.qualification), stdin);
    remove_newline(new_teacher.qualification);
    
    printf("Enter Specialization: ");
    fgets(new_teacher.specialization, sizeof(new_teacher.specialization), stdin);
    remove_newline(new_teacher.specialization);
    
    printf("Enter Years of Experience: ");
    scanf("%d", &new_teacher.experience_years);
    
    printf("Enter Salary: ");
    scanf("%f", &new_teacher.salary);
    clear_input_buffer();
    
    get_current_date(new_teacher.hire_date);
    
    printf("Enter Subjects (comma-separated): ");
    fgets(new_teacher.subjects, sizeof(new_teacher.subjects), stdin);
    remove_newline(new_teacher.subjects);
    
    strcpy(new_teacher.status, "Active");
    
    save_teacher_to_file(new_teacher);
    
    printf("\n✓ Teacher added successfully!\n");
    printf("Teacher ID: %d\n", new_teacher.teacher_id);
    printf("Name: %s %s\n", new_teacher.first_name, new_teacher.last_name);
}

void display_all_teachers() {
    int count = 0;
    Teacher* teachers = load_teachers_from_file(&count);
    
    if (count == 0) {
        printf("\nNo teachers found in database.\n");
        return;
    }
    
    printf("\n===== ALL TEACHERS =====\n");
    printf("%-5s %-15s %-15s %-25s %-15s %-20s %-10s\n", 
           "ID", "First Name", "Last Name", "Email", "Phone", "Specialization", "Status");
    printf("=======================================================================================\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-5d %-15s %-15s %-25s %-15s %-20s %-10s\n",
               teachers[i].teacher_id,
               teachers[i].first_name,
               teachers[i].last_name,
               teachers[i].email,
               teachers[i].phone,
               teachers[i].specialization,
               teachers[i].status);
    }
    
    printf("\nTotal Teachers: %d\n", count);
    free(teachers);
}

void search_teacher() {
    int search_choice;
    int count = 0;
    Teacher* teachers = load_teachers_from_file(&count);
    
    if (count == 0) {
        printf("\nNo teachers found in database.\n");
        return;
    }
    
    printf("\n===== SEARCH TEACHER =====\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("3. Search by Subject\n");
    printf("Enter choice: ");
    scanf("%d", &search_choice);
    clear_input_buffer();
    
    switch(search_choice) {
        case 1: {
            int id;
            printf("Enter Teacher ID: ");
            scanf("%d", &id);
            clear_input_buffer();
            
            for (int i = 0; i < count; i++) {
                if (teachers[i].teacher_id == id) {
                    display_teacher_details(teachers[i]);
                    free(teachers);
                    return;
                }
            }
            printf("Teacher with ID %d not found.\n", id);
            break;
        }
        case 2: {
            char name[50];
            printf("Enter teacher name (first or last): ");
            fgets(name, sizeof(name), stdin);
            remove_newline(name);
            
            int found = 0;
            for (int i = 0; i < count; i++) {
                if (strstr(teachers[i].first_name, name) || strstr(teachers[i].last_name, name)) {
                    if (!found) {
                        printf("\n===== SEARCH RESULTS =====\n");
                        found = 1;
                    }
                    display_teacher_details(teachers[i]);
                    printf("----------------------------\n");
                }
            }
            if (!found) {
                printf("No teachers found with name containing '%s'.\n", name);
            }
            break;
        }
        case 3: {
            char subject[50];
            printf("Enter subject name: ");
            fgets(subject, sizeof(subject), stdin);
            remove_newline(subject);
            
            int found = 0;
            for (int i = 0; i < count; i++) {
                if (strstr(teachers[i].subjects, subject)) {
                    if (!found) {
                        printf("\n===== TEACHERS FOR SUBJECT '%s' =====\n", subject);
                        found = 1;
                    }
                    printf("ID: %d | Name: %s %s | Phone: %s\n",
                           teachers[i].teacher_id,
                           teachers[i].first_name,
                           teachers[i].last_name,
                           teachers[i].phone);
                }
            }
            if (!found) {
                printf("No teachers found for subject '%s'.\n", subject);
            }
            break;
        }
        default:
            printf("Invalid choice!\n");
    }
    
    free(teachers);
}

void update_teacher() {
    int id;
    printf("\nEnter Teacher ID to update: ");
    scanf("%d", &id);
    clear_input_buffer();
    
    int index = find_teacher_by_id(id);
    if (index == -1) {
        printf("Teacher with ID %d not found.\n", id);
        return;
    }
    
    int count = 0;
    Teacher* teachers = load_teachers_from_file(&count);
    
    printf("\n===== UPDATE TEACHER (ID: %d) =====\n", id);
    display_teacher_details(teachers[index]);
    
    printf("\nWhat do you want to update?\n");
    printf("1. Personal Information\n");
    printf("2. Contact Information\n");
    printf("3. Professional Information\n");
    printf("4. Salary\n");
    printf("5. Status\n");
    printf("Enter choice: ");
    
    int choice;
    scanf("%d", &choice);
    clear_input_buffer();
    
    switch(choice) {
        case 1:
            printf("Enter new First Name (current: %s): ", teachers[index].first_name);
            fgets(teachers[index].first_name, sizeof(teachers[index].first_name), stdin);
            remove_newline(teachers[index].first_name);
            
            printf("Enter new Last Name (current: %s): ", teachers[index].last_name);
            fgets(teachers[index].last_name, sizeof(teachers[index].last_name), stdin);
            remove_newline(teachers[index].last_name);
            break;
            
        case 2:
            printf("Enter new Email (current: %s): ", teachers[index].email);
            fgets(teachers[index].email, sizeof(teachers[index].email), stdin);
            remove_newline(teachers[index].email);
            
            printf("Enter new Phone (current: %s): ", teachers[index].phone);
            fgets(teachers[index].phone, sizeof(teachers[index].phone), stdin);
            remove_newline(teachers[index].phone);
            break;
            
        case 3:
            printf("Enter new Qualification (current: %s): ", teachers[index].qualification);
            fgets(teachers[index].qualification, sizeof(teachers[index].qualification), stdin);
            remove_newline(teachers[index].qualification);
            
            printf("Enter new Specialization (current: %s): ", teachers[index].specialization);
            fgets(teachers[index].specialization, sizeof(teachers[index].specialization), stdin);
            remove_newline(teachers[index].specialization);
            break;
            
        case 4:
            printf("Enter new Salary (current: %.2f): ", teachers[index].salary);
            scanf("%f", &teachers[index].salary);
            clear_input_buffer();
            break;
            
        case 5:
            printf("Enter new Status (Active/Inactive/On Leave) (current: %s): ", teachers[index].status);
            fgets(teachers[index].status, sizeof(teachers[index].status), stdin);
            remove_newline(teachers[index].status);
            break;
            
        default:
            printf("Invalid choice!\n");
            free(teachers);
            return;
    }
    
    // Save updated data
    FILE* file = fopen("data/teachers.txt", "w");
    if (file) {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%d|%s|%s|%s|%s|%s|%s|%s|%s|%.2f|%s|%s|%d\n",
                    teachers[i].teacher_id, teachers[i].first_name, teachers[i].last_name,
                    teachers[i].email, teachers[i].phone, teachers[i].address,
                    teachers[i].qualification, teachers[i].specialization,
                    teachers[i].hire_date, teachers[i].salary, teachers[i].subjects,
                    teachers[i].status, teachers[i].experience_years);
        }
        fclose(file);
        printf("\n✓ Teacher information updated successfully!\n");
    } else {
        printf("Error updating teacher information.\n");
    }
    
    free(teachers);
}

void delete_teacher() {
    int id;
    printf("\nEnter Teacher ID to delete: ");
    scanf("%d", &id);
    clear_input_buffer();
    
    int index = find_teacher_by_id(id);
    if (index == -1) {
        printf("Teacher with ID %d not found.\n", id);
        return;
    }
    
    int count = 0;
    Teacher* teachers = load_teachers_from_file(&count);
    
    printf("\n===== CONFIRM DELETION =====\n");
    display_teacher_details(teachers[index]);
    
    printf("\nAre you sure you want to delete this teacher? (y/N): ");
    char confirm = getchar();
    clear_input_buffer();
    
    if (confirm == 'y' || confirm == 'Y') {
        FILE* file = fopen("data/teachers.txt", "w");
        if (file) {
            for (int i = 0; i < count; i++) {
                if (i != index) {
                    fprintf(file, "%d|%s|%s|%s|%s|%s|%s|%s|%s|%.2f|%s|%s|%d\n",
                            teachers[i].teacher_id, teachers[i].first_name, teachers[i].last_name,
                            teachers[i].email, teachers[i].phone, teachers[i].address,
                            teachers[i].qualification, teachers[i].specialization,
                            teachers[i].hire_date, teachers[i].salary, teachers[i].subjects,
                            teachers[i].status, teachers[i].experience_years);
                }
            }
            fclose(file);
            printf("\n✓ Teacher deleted successfully!\n");
        } else {
            printf("Error deleting teacher.\n");
        }
    } else {
        printf("Deletion cancelled.\n");
    }
    
    free(teachers);
}

void assign_subjects_to_teacher() {
    int id;
    printf("\nEnter Teacher ID to assign subjects: ");
    scanf("%d", &id);
    clear_input_buffer();
    
    int index = find_teacher_by_id(id);
    if (index == -1) {
        printf("Teacher with ID %d not found.\n", id);
        return;
    }
    
    int count = 0;
    Teacher* teachers = load_teachers_from_file(&count);
    
    printf("\n===== ASSIGN SUBJECTS =====\n");
    printf("Teacher: %s %s\n", teachers[index].first_name, teachers[index].last_name);
    printf("Current subjects: %s\n", teachers[index].subjects);
    
    printf("Enter new subjects (comma-separated): ");
    fgets(teachers[index].subjects, sizeof(teachers[index].subjects), stdin);
    remove_newline(teachers[index].subjects);
    
    // Save updated data
    FILE* file = fopen("data/teachers.txt", "w");
    if (file) {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%d|%s|%s|%s|%s|%s|%s|%s|%s|%.2f|%s|%s|%d\n",
                    teachers[i].teacher_id, teachers[i].first_name, teachers[i].last_name,
                    teachers[i].email, teachers[i].phone, teachers[i].address,
                    teachers[i].qualification, teachers[i].specialization,
                    teachers[i].hire_date, teachers[i].salary, teachers[i].subjects,
                    teachers[i].status, teachers[i].experience_years);
        }
        fclose(file);
        printf("\n✓ Subjects assigned successfully!\n");
    } else {
        printf("Error assigning subjects.\n");
    }
    
    free(teachers);
}

int get_next_teacher_id() {
    FILE* file = fopen("data/teachers.txt", "r");
    int max_id = 2000; // Starting ID for teachers
    
    if (file) {
        char line[500];
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

void save_teacher_to_file(Teacher teacher) {
    FILE* file = fopen("data/teachers.txt", "a");
    if (file) {
        fprintf(file, "%d|%s|%s|%s|%s|%s|%s|%s|%s|%.2f|%s|%s|%d\n",
                teacher.teacher_id, teacher.first_name, teacher.last_name,
                teacher.email, teacher.phone, teacher.address,
                teacher.qualification, teacher.specialization,
                teacher.hire_date, teacher.salary, teacher.subjects,
                teacher.status, teacher.experience_years);
        fclose(file);
    } else {
        printf("Error: Could not save teacher data.\n");
    }
}

Teacher* load_teachers_from_file(int* count) {
    FILE* file = fopen("data/teachers.txt", "r");
    Teacher* teachers = NULL;
    *count = 0;
    
    if (!file) {
        return NULL;
    }
    
    char line[600];
    int capacity = 10;
    teachers = malloc(capacity * sizeof(Teacher));
    
    while (fgets(line, sizeof(line), file)) {
        if (*count >= capacity) {
            capacity *= 2;
            teachers = realloc(teachers, capacity * sizeof(Teacher));
        }
        
        sscanf(line, "%d|%49[^|]|%49[^|]|%99[^|]|%19[^|]|%199[^|]|%99[^|]|%99[^|]|%14[^|]|%f|%199[^|]|%19[^|]|%d",
               &teachers[*count].teacher_id,
               teachers[*count].first_name,
               teachers[*count].last_name,
               teachers[*count].email,
               teachers[*count].phone,
               teachers[*count].address,
               teachers[*count].qualification,
               teachers[*count].specialization,
               teachers[*count].hire_date,
               &teachers[*count].salary,
               teachers[*count].subjects,
               teachers[*count].status,
               &teachers[*count].experience_years);
        
        (*count)++;
    }
    
    fclose(file);
    return teachers;
}

int find_teacher_by_id(int id) {
    int count = 0;
    Teacher* teachers = load_teachers_from_file(&count);
    
    if (!teachers) return -1;
    
    for (int i = 0; i < count; i++) {
        if (teachers[i].teacher_id == id) {
            free(teachers);
            return i;
        }
    }
    
    free(teachers);
    return -1;
}

void display_teacher_details(Teacher teacher) {
    printf("\n===== TEACHER DETAILS =====\n");
    printf("Teacher ID: %d\n", teacher.teacher_id);
    printf("Name: %s %s\n", teacher.first_name, teacher.last_name);
    printf("Email: %s\n", teacher.email);
    printf("Phone: %s\n", teacher.phone);
    printf("Address: %s\n", teacher.address);
    printf("Qualification: %s\n", teacher.qualification);
    printf("Specialization: %s\n", teacher.specialization);
    printf("Experience: %d years\n", teacher.experience_years);
    printf("Hire Date: %s\n", teacher.hire_date);
    printf("Salary: %.2f\n", teacher.salary);
    printf("Subjects: %s\n", teacher.subjects);
    printf("Status: %s\n", teacher.status);
    printf("===========================\n");
}