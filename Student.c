#include "student.h"
#include "utils.h"

void register_student() {
    Student new_student;
    
    printf("\n===== STUDENT REGISTRATION =====\n");
    
    new_student.student_id = get_next_student_id();
    printf("Student ID (Auto-generated): %d\n", new_student.student_id);
    
    printf("Enter First Name: ");
    fgets(new_student.first_name, sizeof(new_student.first_name), stdin);
    remove_newline(new_student.first_name);
    
    printf("Enter Last Name: ");
    fgets(new_student.last_name, sizeof(new_student.last_name), stdin);
    remove_newline(new_student.last_name);
    
    printf("Enter Email: ");
    fgets(new_student.email, sizeof(new_student.email), stdin);
    remove_newline(new_student.email);
    
    printf("Enter Phone Number: ");
    fgets(new_student.phone, sizeof(new_student.phone), stdin);
    remove_newline(new_student.phone);
    
    printf("Enter Address: ");
    fgets(new_student.address, sizeof(new_student.address), stdin);
    remove_newline(new_student.address);
    
    printf("Enter Date of Birth (DD/MM/YYYY): ");
    fgets(new_student.date_of_birth, sizeof(new_student.date_of_birth), stdin);
    remove_newline(new_student.date_of_birth);
    
    get_current_date(new_student.enrollment_date);
    
    printf("Enter Class ID: ");
    scanf("%d", &new_student.class_id);
    clear_input_buffer();
    
    printf("Enter Class Name: ");
    fgets(new_student.class_name, sizeof(new_student.class_name), stdin);
    remove_newline(new_student.class_name);
    
    printf("Enter Guardian Name: ");
    fgets(new_student.guardian_name, sizeof(new_student.guardian_name), stdin);
    remove_newline(new_student.guardian_name);
    
    printf("Enter Guardian Phone: ");
    fgets(new_student.guardian_phone, sizeof(new_student.guardian_phone), stdin);
    remove_newline(new_student.guardian_phone);
    
    printf("Enter Total Fees: ");
    scanf("%f", &new_student.total_fees);
    
    printf("Enter Fees Paid: ");
    scanf("%f", &new_student.fees_paid);
    clear_input_buffer();
    
    strcpy(new_student.status, "Active");
    
    save_student_to_file(new_student);
    
    printf("\n✓ Student registered successfully!\n");
    printf("Student ID: %d\n", new_student.student_id);
    printf("Name: %s %s\n", new_student.first_name, new_student.last_name);
}

void display_all_students() {
    int count = 0;
    Student* students = load_students_from_file(&count);
    
    if (count == 0) {
        printf("\nNo students found in database.\n");
        return;
    }
    
    printf("\n===== ALL STUDENTS =====\n");
    printf("%-5s %-15s %-15s %-25s %-15s %-10s %-10s\n", 
           "ID", "First Name", "Last Name", "Email", "Phone", "Class", "Status");
    printf("=================================================================================\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-5d %-15s %-15s %-25s %-15s %-10s %-10s\n",
               students[i].student_id,
               students[i].first_name,
               students[i].last_name,
               students[i].email,
               students[i].phone,
               students[i].class_name,
               students[i].status);
    }
    
    printf("\nTotal Students: %d\n", count);
    free(students);
}

void search_student() {
    int search_choice;
    int count = 0;
    Student* students = load_students_from_file(&count);
    
    if (count == 0) {
        printf("\nNo students found in database.\n");
        return;
    }
    
    printf("\n===== SEARCH STUDENT =====\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("3. Search by Class\n");
    printf("Enter choice: ");
    scanf("%d", &search_choice);
    clear_input_buffer();
    
    switch(search_choice) {
        case 1: {
            int id;
            printf("Enter Student ID: ");
            scanf("%d", &id);
            clear_input_buffer();
            
            for (int i = 0; i < count; i++) {
                if (students[i].student_id == id) {
                    display_student_details(students[i]);
                    free(students);
                    return;
                }
            }
            printf("Student with ID %d not found.\n", id);
            break;
        }
        case 2: {
            char name[50];
            printf("Enter student name (first or last): ");
            fgets(name, sizeof(name), stdin);
            remove_newline(name);
            
            int found = 0;
            for (int i = 0; i < count; i++) {
                if (strstr(students[i].first_name, name) || strstr(students[i].last_name, name)) {
                    if (!found) {
                        printf("\n===== SEARCH RESULTS =====\n");
                        found = 1;
                    }
                    display_student_details(students[i]);
                    printf("----------------------------\n");
                }
            }
            if (!found) {
                printf("No students found with name containing '%s'.\n", name);
            }
            break;
        }
        case 3: {
            char class_name[50];
            printf("Enter class name: ");
            fgets(class_name, sizeof(class_name), stdin);
            remove_newline(class_name);
            
            int found = 0;
            for (int i = 0; i < count; i++) {
                if (strstr(students[i].class_name, class_name)) {
                    if (!found) {
                        printf("\n===== STUDENTS IN CLASS '%s' =====\n", class_name);
                        found = 1;
                    }
                    printf("ID: %d | Name: %s %s | Phone: %s\n",
                           students[i].student_id,
                           students[i].first_name,
                           students[i].last_name,
                           students[i].phone);
                }
            }
            if (!found) {
                printf("No students found in class '%s'.\n", class_name);
            }
            break;
        }
        default:
            printf("Invalid choice!\n");
    }
    
    free(students);
}

void update_student() {
    int id;
    printf("\nEnter Student ID to update: ");
    scanf("%d", &id);
    clear_input_buffer();
    
    int index = find_student_by_id(id);
    if (index == -1) {
        printf("Student with ID %d not found.\n", id);
        return;
    }
    
    int count = 0;
    Student* students = load_students_from_file(&count);
    
    printf("\n===== UPDATE STUDENT (ID: %d) =====\n", id);
    display_student_details(students[index]);
    
    printf("\nWhat do you want to update?\n");
    printf("1. Personal Information\n");
    printf("2. Contact Information\n");
    printf("3. Academic Information\n");
    printf("4. Fee Information\n");
    printf("5. Status\n");
    printf("Enter choice: ");
    
    int choice;
    scanf("%d", &choice);
    clear_input_buffer();
    
    switch(choice) {
        case 1:
            printf("Enter new First Name (current: %s): ", students[index].first_name);
            fgets(students[index].first_name, sizeof(students[index].first_name), stdin);
            remove_newline(students[index].first_name);
            
            printf("Enter new Last Name (current: %s): ", students[index].last_name);
            fgets(students[index].last_name, sizeof(students[index].last_name), stdin);
            remove_newline(students[index].last_name);
            break;
            
        case 2:
            printf("Enter new Email (current: %s): ", students[index].email);
            fgets(students[index].email, sizeof(students[index].email), stdin);
            remove_newline(students[index].email);
            
            printf("Enter new Phone (current: %s): ", students[index].phone);
            fgets(students[index].phone, sizeof(students[index].phone), stdin);
            remove_newline(students[index].phone);
            break;
            
        case 3:
            printf("Enter new Class ID (current: %d): ", students[index].class_id);
            scanf("%d", &students[index].class_id);
            clear_input_buffer();
            
            printf("Enter new Class Name (current: %s): ", students[index].class_name);
            fgets(students[index].class_name, sizeof(students[index].class_name), stdin);
            remove_newline(students[index].class_name);
            break;
            
        case 4:
            printf("Enter new Total Fees (current: %.2f): ", students[index].total_fees);
            scanf("%f", &students[index].total_fees);
            
            printf("Enter new Fees Paid (current: %.2f): ", students[index].fees_paid);
            scanf("%f", &students[index].fees_paid);
            clear_input_buffer();
            break;
            
        case 5:
            printf("Enter new Status (Active/Inactive/Suspended) (current: %s): ", students[index].status);
            fgets(students[index].status, sizeof(students[index].status), stdin);
            remove_newline(students[index].status);
            break;
            
        default:
            printf("Invalid choice!\n");
            free(students);
            return;
    }
    
    // Save updated data
    FILE* file = fopen("data/students.txt", "w");
    if (file) {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%d|%s|%s|%s|%s|%s|%s|%s|%d|%s|%s|%s|%.2f|%.2f|%s\n",
                    students[i].student_id, students[i].first_name, students[i].last_name,
                    students[i].email, students[i].phone, students[i].address,
                    students[i].date_of_birth, students[i].enrollment_date,
                    students[i].class_id, students[i].class_name,
                    students[i].guardian_name, students[i].guardian_phone,
                    students[i].fees_paid, students[i].total_fees, students[i].status);
        }
        fclose(file);
        printf("\n✓ Student information updated successfully!\n");
    } else {
        printf("Error updating student information.\n");
    }
    
    free(students);
}

void delete_student() {
    int id;
    printf("\nEnter Student ID to delete: ");
    scanf("%d", &id);
    clear_input_buffer();
    
    int index = find_student_by_id(id);
    if (index == -1) {
        printf("Student with ID %d not found.\n", id);
        return;
    }
    
    int count = 0;
    Student* students = load_students_from_file(&count);
    
    printf("\n===== CONFIRM DELETION =====\n");
    display_student_details(students[index]);
    
    printf("\nAre you sure you want to delete this student? (y/N): ");
    char confirm = getchar();
    clear_input_buffer();
    
    if (confirm == 'y' || confirm == 'Y') {
        FILE* file = fopen("data/students.txt", "w");
        if (file) {
            for (int i = 0; i < count; i++) {
                if (i != index) {
                    fprintf(file, "%d|%s|%s|%s|%s|%s|%s|%s|%d|%s|%s|%s|%.2f|%.2f|%s\n",
                            students[i].student_id, students[i].first_name, students[i].last_name,
                            students[i].email, students[i].phone, students[i].address,
                            students[i].date_of_birth, students[i].enrollment_date,
                            students[i].class_id, students[i].class_name,
                            students[i].guardian_name, students[i].guardian_phone,
                            students[i].fees_paid, students[i].total_fees, students[i].status);
                }
            }
            fclose(file);
            printf("\n✓ Student deleted successfully!\n");
        } else {
            printf("Error deleting student.\n");
        }
    } else {
        printf("Deletion cancelled.\n");
    }
    
    free(students);
}

void manage_attendance() {
    printf("\n===== ATTENDANCE MANAGEMENT =====\n");
    printf("This feature will be implemented in the next version.\n");
    printf("Features will include:\n");
    printf("- Mark daily attendance\n");
    printf("- View attendance reports\n");
    printf("- Generate attendance statistics\n");
}

int get_next_student_id() {
    FILE* file = fopen("data/students.txt", "r");
    int max_id = 1000; // Starting ID
    
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

void save_student_to_file(Student student) {
    FILE* file = fopen("data/students.txt", "a");
    if (file) {
        fprintf(file, "%d|%s|%s|%s|%s|%s|%s|%s|%d|%s|%s|%s|%.2f|%.2f|%s\n",
                student.student_id, student.first_name, student.last_name,
                student.email, student.phone, student.address,
                student.date_of_birth, student.enrollment_date,
                student.class_id, student.class_name,
                student.guardian_name, student.guardian_phone,
                student.fees_paid, student.total_fees, student.status);
        fclose(file);
    } else {
        printf("Error: Could not save student data.\n");
    }
}

Student* load_students_from_file(int* count) {
    FILE* file = fopen("data/students.txt", "r");
    Student* students = NULL;
    *count = 0;
    
    if (!file) {
        return NULL;
    }
    
    char line[500];
    int capacity = 10;
    students = malloc(capacity * sizeof(Student));
    
    while (fgets(line, sizeof(line), file)) {
        if (*count >= capacity) {
            capacity *= 2;
            students = realloc(students, capacity * sizeof(Student));
        }
        
        sscanf(line, "%d|%49[^|]|%49[^|]|%99[^|]|%19[^|]|%199[^|]|%14[^|]|%14[^|]|%d|%49[^|]|%99[^|]|%19[^|]|%f|%f|%19[^|\n]",
               &students[*count].student_id,
               students[*count].first_name,
               students[*count].last_name,
               students[*count].email,
               students[*count].phone,
               students[*count].address,
               students[*count].date_of_birth,
               students[*count].enrollment_date,
               &students[*count].class_id,
               students[*count].class_name,
               students[*count].guardian_name,
               students[*count].guardian_phone,
               &students[*count].fees_paid,
               &students[*count].total_fees,
               students[*count].status);
        
        (*count)++;
    }
    
    fclose(file);
    return students;
}

int find_student_by_id(int id) {
    int count = 0;
    Student* students = load_students_from_file(&count);
    
    if (!students) return -1;
    
    for (int i = 0; i < count; i++) {
        if (students[i].student_id == id) {
            free(students);
            return i;
        }
    }
    
    free(students);
    return -1;
}

void display_student_details(Student student) {
    printf("\n===== STUDENT DETAILS =====\n");
    printf("Student ID: %d\n", student.student_id);
    printf("Name: %s %s\n", student.first_name, student.last_name);
    printf("Email: %s\n", student.email);
    printf("Phone: %s\n", student.phone);
    printf("Address: %s\n", student.address);
    printf("Date of Birth: %s\n", student.date_of_birth);
    printf("Enrollment Date: %s\n", student.enrollment_date);
    printf("Class: %s (ID: %d)\n", student.class_name, student.class_id);
    printf("Guardian: %s (%s)\n", student.guardian_name, student.guardian_phone);
    printf("Fees: %.2f / %.2f (Paid/Total)\n", student.fees_paid, student.total_fees);
    printf("Status: %s\n", student.status);
    printf("============================\n");
}