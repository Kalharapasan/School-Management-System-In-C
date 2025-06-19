#include "admin.h"
#include "utils.h"

void add_admin() {
    Admin new_admin;
    
    printf("\n===== ADD NEW ADMIN =====\n");
    
    new_admin.admin_id = get_next_admin_id();
    printf("Admin ID (Auto-generated): %d\n", new_admin.admin_id);
    
    printf("Enter Username: ");
    fgets(new_admin.username, sizeof(new_admin.username), stdin);
    remove_newline(new_admin.username);
    
    printf("Enter Password: ");
    fgets(new_admin.password, sizeof(new_admin.password), stdin);
    remove_newline(new_admin.password);
    
    printf("Enter First Name: ");
    fgets(new_admin.first_name, sizeof(new_admin.first_name), stdin);
    remove_newline(new_admin.first_name);
    
    printf("Enter Last Name: ");
    fgets(new_admin.last_name, sizeof(new_admin.last_name), stdin);
    remove_newline(new_admin.last_name);
    
    printf("Enter Email: ");
    fgets(new_admin.email, sizeof(new_admin.email), stdin);
    remove_newline(new_admin.email);
    
    printf("Enter Phone Number: ");
    fgets(new_admin.phone, sizeof(new_admin.phone), stdin);
    remove_newline(new_admin.phone);
    
    printf("Enter Role (Super Admin/Admin/Assistant): ");
    fgets(new_admin.role, sizeof(new_admin.role), stdin);
    remove_newline(new_admin.role);
    
    get_current_date(new_admin.created_date);
    strcpy(new_admin.last_login, "Never");
    strcpy(new_admin.status, "Active");
    
    save_admin_to_file(new_admin);
    
    printf("\n✓ Admin added successfully!\n");
    printf("Admin ID: %d\n", new_admin.admin_id);
    printf("Username: %s\n", new_admin.username);
}

void display_all_admins() {
    int count = 0;
    Admin* admins = load_admins_from_file(&count);
    
    if (count == 0) {
        printf("\nNo admins found in database.\n");
        return;
    }
    
    printf("\n===== ALL ADMINS =====\n");
    printf("%-5s %-15s %-15s %-15s %-25s %-15s %-15s %-10s\n", 
           "ID", "Username", "First Name", "Last Name", "Email", "Phone", "Role", "Status");
    printf("=================================================================================================\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-5d %-15s %-15s %-15s %-25s %-15s %-15s %-10s\n",
               admins[i].admin_id,
               admins[i].username,
               admins[i].first_name,
               admins[i].last_name,
               admins[i].email,
               admins[i].phone,
               admins[i].role,
               admins[i].status);
    }
    
    printf("\nTotal Admins: %d\n", count);
    free(admins);
}

void update_admin() {
    int id;
    printf("\nEnter Admin ID to update: ");
    scanf("%d", &id);
    clear_input_buffer();
    
    int index = find_admin_by_id(id);
    if (index == -1) {
        printf("Admin with ID %d not found.\n", id);
        return;
    }
    
    int count = 0;
    Admin* admins = load_admins_from_file(&count);
    
    printf("\n===== UPDATE ADMIN (ID: %d) =====\n", id);
    display_admin_details(admins[index]);
    
    printf("\nWhat do you want to update?\n");
    printf("1. Personal Information\n");
    printf("2. Contact Information\n");
    printf("3. Role\n");
    printf("4. Status\n");
    printf("5. Password\n");
    printf("Enter choice: ");
    
    int choice;
    scanf("%d", &choice);
    clear_input_buffer();
    
    switch(choice) {
        case 1:
            printf("Enter new First Name (current: %s): ", admins[index].first_name);
            fgets(admins[index].first_name, sizeof(admins[index].first_name), stdin);
            remove_newline(admins[index].first_name);
            
            printf("Enter new Last Name (current: %s): ", admins[index].last_name);
            fgets(admins[index].last_name, sizeof(admins[index].last_name), stdin);
            remove_newline(admins[index].last_name);
            break;
            
        case 2:
            printf("Enter new Email (current: %s): ", admins[index].email);
            fgets(admins[index].email, sizeof(admins[index].email), stdin);
            remove_newline(admins[index].email);
            
            printf("Enter new Phone (current: %s): ", admins[index].phone);
            fgets(admins[index].phone, sizeof(admins[index].phone), stdin);
            remove_newline(admins[index].phone);
            break;
            
        case 3:
            printf("Enter new Role (current: %s): ", admins[index].role);
            fgets(admins[index].role, sizeof(admins[index].role), stdin);
            remove_newline(admins[index].role);
            break;
            
        case 4:
            printf("Enter new Status (current: %s): ", admins[index].status);
            fgets(admins[index].status, sizeof(admins[index].status), stdin);
            remove_newline(admins[index].status);
            break;
            
        case 5:
            printf("Enter new Password: ");
            fgets(admins[index].password, sizeof(admins[index].password), stdin);
            remove_newline(admins[index].password);
            break;
            
        default:
            printf("Invalid choice!\n");
            free(admins);
            return;
    }
    
    // Save updated data
    FILE* file = fopen("data/admins.txt", "w");
    if (file) {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%d|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s\n",
                    admins[i].admin_id, admins[i].username, admins[i].password,
                    admins[i].first_name, admins[i].last_name, admins[i].email,
                    admins[i].phone, admins[i].role, admins[i].created_date,
                    admins[i].last_login, admins[i].status);
        }
        fclose(file);
        printf("\n✓ Admin information updated successfully!\n");
    } else {
        printf("Error updating admin information.\n");
    }
    
    free(admins);
}

void delete_admin() {
    int id;
    printf("\nEnter Admin ID to delete: ");
    scanf("%d", &id);
    clear_input_buffer();
    
    int index = find_admin_by_id(id);
    if (index == -1) {
        printf("Admin with ID %d not found.\n", id);
        return;
    }
    
    int count = 0;
    Admin* admins = load_admins_from_file(&count);
    
    printf("\n===== CONFIRM DELETION =====\n");
    display_admin_details(admins[index]);
    
    printf("\nAre you sure you want to delete this admin? (y/N): ");
    char confirm = getchar();
    clear_input_buffer();
    
    if (confirm == 'y' || confirm == 'Y') {
        FILE* file = fopen("data/admins.txt", "w");
        if (file) {
            for (int i = 0; i < count; i++) {
                if (i != index) {
                    fprintf(file, "%d|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s\n",
                            admins[i].admin_id, admins[i].username, admins[i].password,
                            admins[i].first_name, admins[i].last_name, admins[i].email,
                            admins[i].phone, admins[i].role, admins[i].created_date,
                            admins[i].last_login, admins[i].status);
                }
            }
            fclose(file);
            printf("\n✓ Admin deleted successfully!\n");
        } else {
            printf("Error deleting admin.\n");
        }
    } else {
        printf("Deletion cancelled.\n");
    }
    
    free(admins);
}

void create_system_backup() {
    printf("\n===== SYSTEM BACKUP =====\n");
    printf("Creating backup of all system data...\n");
    
    char backup_dir[100];
    sprintf(backup_dir, "backup_%s", get_current_timestamp());
    
    char command[200];
    sprintf(command, "mkdir -p %s", backup_dir);
    system(command);
    
    sprintf(command, "cp data/*.txt %s/", backup_dir);
    system(command);
    
    printf("✓ Backup created successfully in directory: %s\n", backup_dir);
    printf("Backup includes:\n");
    printf("- Students data\n");
    printf("- Teachers data\n");
    printf("- Admins data\n");
    printf("- Subjects data\n");
    printf("- Exams data\n");
    printf("- Marks data\n");
}

int get_next_admin_id() {
    FILE* file = fopen("data/admins.txt", "r");
    int max_id = 9000; // Starting ID for admins
    
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

void save_admin_to_file(Admin admin) {
    FILE* file = fopen("data/admins.txt", "a");
    if (file) {
        fprintf(file, "%d|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s\n",
                admin.admin_id, admin.username, admin.password,
                admin.first_name, admin.last_name, admin.email,
                admin.phone, admin.role, admin.created_date,
                admin.last_login, admin.status);
        fclose(file);
    } else {
        printf("Error: Could not save admin data.\n");
    }
}

Admin* load_admins_from_file(int* count) {
    FILE* file = fopen("data/admins.txt", "r");
    Admin* admins = NULL;
    *count = 0;
    
    if (!file) {
        return NULL;
    }
    
    char line[400];
    int capacity = 10;
    admins = malloc(capacity * sizeof(Admin));
    
    while (fgets(line, sizeof(line), file)) {
        if (*count >= capacity) {
            capacity *= 2;
            admins = realloc(admins, capacity * sizeof(Admin));
        }
        
        sscanf(line, "%d|%49[^|]|%99[^|]|%49[^|]|%49[^|]|%99[^|]|%19[^|]|%49[^|]|%14[^|]|%19[^|]|%19[^|\n]",
               &admins[*count].admin_id,
               admins[*count].username,
               admins[*count].password,
               admins[*count].first_name,
               admins[*count].last_name,
               admins[*count].email,
               admins[*count].phone,
               admins[*count].role,
               admins[*count].created_date,
               admins[*count].last_login,
               admins[*count].status);
        
        (*count)++;
    }
    
    fclose(file);
    return admins;
}

int find_admin_by_id(int id) {
    int count = 0;
    Admin* admins = load_admins_from_file(&count);
    
    if (!admins) return -1;
    
    for (int i = 0; i < count; i++) {
        if (admins[i].admin_id == id) {
            free(admins);
            return i;
        }
    }
    
    free(admins);
    return -1;
}

void display_admin_details(Admin admin) {
    printf("\n===== ADMIN DETAILS =====\n");
    printf("Admin ID: %d\n", admin.admin_id);
    printf("Username: %s\n", admin.username);
    printf("Name: %s %s\n", admin.first_name, admin.last_name);
    printf("Email: %s\n", admin.email);
    printf("Phone: %s\n", admin.phone);
    printf("Role: %s\n", admin.role);
    printf("Created Date: %s\n", admin.created_date);
    printf("Last Login: %s\n", admin.last_login);
    printf("Status: %s\n", admin.status);
    printf("=========================\n");
}