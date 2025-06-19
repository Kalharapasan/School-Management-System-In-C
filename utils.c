#include "utils.h"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Clear the input buffer
    }
}

void remove_newline(char* str) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

void get_current_date(char* date_str) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date_str, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

char* get_current_timestamp() {
    static char timestamp[20];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(timestamp, "%d%02d%02d_%02d%02d%02d", 
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
            tm.tm_hour, tm.tm_min, tm.tm_sec);
    return timestamp;
}

void initialize_system() {
    printf("Initializing School Management System...\n");
    
    // Create data directory if it doesn't exist
    if (create_directory("data") == 0) {
        printf("✓ Data directory created/verified\n");
    }
    
    // Create backup directory if it doesn't exist
    if (create_directory("backups") == 0) {
        printf("✓ Backup directory created/verified\n");
    }
    
    // Initialize data files if they don't exist
    FILE* files[] = {
        fopen("data/students.txt", "a"),
        fopen("data/teachers.txt", "a"),
        fopen("data/admins.txt", "a"),
        fopen("data/subjects.txt", "a"),
        fopen("data/exams.txt", "a"),
        fopen("data/marks.txt", "a")
    };
    
    const char* file_names[] = {
        "students.txt", "teachers.txt", "admins.txt",
        "subjects.txt", "exams.txt", "marks.txt"
    };
    
    for (int i = 0; i < 6; i++) {
        if (files[i]) {
            fclose(files[i]);
        }
        printf("✓ %s initialized\n", file_names[i]);
    }
    
    printf("✓ System initialization complete!\n\n");
}

int create_directory(const char* path) {
    char command[100];
    sprintf(command, "mkdir -p %s", path);
    return system(command);
}

void display_loading_animation() {
    printf("Loading");
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        // In a real system, you might use sleep() here
        for (int j = 0; j < 100000000; j++) {
            // Simple delay loop
        }
    }
    printf("\n");
}

void print_header(const char* title) {
    int len = strlen(title);
    int total_width = 50;
    int padding = (total_width - len) / 2;
    
    printf("\n");
    for (int i = 0; i < total_width; i++) printf("=");
    printf("\n");
    
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s", title);
    for (int i = 0; i < padding; i++) printf(" ");
    printf("\n");
    
    for (int i = 0; i < total_width; i++) printf("=");
    printf("\n");
}

void print_separator() {
    for (int i = 0; i < 50; i++) printf("-");
    printf("\n");
}