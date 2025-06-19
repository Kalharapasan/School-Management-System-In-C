#include "exam.h"
#include "utils.h"

void create_exam() {
    Exam new_exam;
    
    printf("\n===== CREATE NEW EXAM =====\n");
    
    new_exam.exam_id = get_next_exam_id();
    printf("Exam ID (Auto-generated): %d\n", new_exam.exam_id);
    
    printf("Enter Exam Name: ");
    fgets(new_exam.exam_name, sizeof(new_exam.exam_name), stdin);
    remove_newline(new_exam.exam_name);
    
    printf("Enter Exam Type (Midterm/Final/Quiz/Assignment): ");
    fgets(new_exam.exam_type, sizeof(new_exam.exam_type), stdin);
    remove_newline(new_exam.exam_type);
    
    printf("Enter Subject ID: ");
    scanf("%d", &new_exam.subject_id);
    clear_input_buffer();
    
    printf("Enter Subject Name: ");
    fgets(new_exam.subject_name, sizeof(new_exam.subject_name), stdin);
    remove_newline(new_exam.subject_name);
    
    printf("Enter Class ID: ");
    scanf("%d", &new_exam.class_id);
    clear_input_buffer();
    
    printf("Enter Class Name: ");
    fgets(new_exam.class_name, sizeof(new_exam.class_name), stdin);
    remove_newline(new_exam.class_name);
    
    printf("Enter Exam Date (DD/MM/YYYY): ");
    fgets(new_exam.exam_date, sizeof(new_exam.exam_date), stdin);
    remove_newline(new_exam.exam_date);
    
    printf("Enter Start Time (HH:MM): ");
    fgets(new_exam.start_time, sizeof(new_exam.start_time), stdin);
    remove_newline(new_exam.start_time);
    
    printf("Enter End Time (HH:MM): ");
    fgets(new_exam.end_time, sizeof(new_exam.end_time), stdin);
    remove_newline(new_exam.end_time);
    
    printf("Enter Total Marks: ");
    scanf("%d", &new_exam.total_marks);
    clear_input_buffer();
    
    strcpy(new_exam.status, "Scheduled");
    
    save_exam_to_file(new_exam);
    
    printf("\n✓ Exam created successfully!\n");
    printf("Exam ID: %d\n", new_exam.exam_id);
    printf("Exam: %s (%s)\n", new_exam.exam_name, new_exam.exam_type);
    printf("Date: %s | Time: %s - %s\n", new_exam.exam_date, new_exam.start_time, new_exam.end_time);
}

void display_all_exams() {
    int count = 0;
    Exam* exams = load_exams_from_file(&count);
    
    if (count == 0) {
        printf("\nNo exams found in database.\n");
        return;
    }
    
    printf("\n===== ALL EXAMS =====\n");
    printf("%-5s %-20s %-12s %-15s %-15s %-12s %-8s %-10s\n", 
           "ID", "Exam Name", "Type", "Subject", "Class", "Date", "Marks", "Status");
    printf("============================================================================================\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-12s %-15s %-15s %-12s %-8d %-10s\n",
               exams[i].exam_id,
               exams[i].exam_name,
               exams[i].exam_type,
               exams[i].subject_name,
               exams[i].class_name,
               exams[i].exam_date,
               exams[i].total_marks,
               exams[i].status);
    }
    
    printf("\nTotal Exams: %d\n", count);
    free(exams);
}

void enter_student_marks() {
    ExamMark new_mark;
    
    printf("\n===== ENTER STUDENT MARKS =====\n");
    
    new_mark.mark_id = get_next_mark_id();
    printf("Mark ID (Auto-generated): %d\n", new_mark.mark_id);
    
    printf("Enter Student ID: ");
    scanf("%d", &new_mark.student_id);
    clear_input_buffer();
    
    printf("Enter Student Name: ");
    fgets(new_mark.student_name, sizeof(new_mark.student_name), stdin);
    remove_newline(new_mark.student_name);
    
    printf("Enter Exam ID: ");
    scanf("%d", &new_mark.exam_id);
    clear_input_buffer();
    
    printf("Enter Exam Name: ");
    fgets(new_mark.exam_name, sizeof(new_mark.exam_name), stdin);
    remove_newline(new_mark.exam_name);
    
    printf("Enter Subject ID: ");
    scanf("%d", &new_mark.subject_id);
    clear_input_buffer();
    
    printf("Enter Subject Name: ");
    fgets(new_mark.subject_name, sizeof(new_mark.subject_name), stdin);
    remove_newline(new_mark.subject_name);
    
    printf("Enter Total Marks: ");
    scanf("%f", &new_mark.total_marks);
    
    printf("Enter Marks Obtained: ");
    scanf("%f", &new_mark.marks_obtained);
    clear_input_buffer();
    
    // Calculate percentage
    new_mark.percentage = (new_mark.marks_obtained / new_mark.total_marks) * 100;
    
    // Calculate grade
    strcpy(new_mark.grade, calculate_grade(new_mark.percentage));
    
    printf("Enter Remarks (optional): ");
    fgets(new_mark.remarks, sizeof(new_mark.remarks), stdin);
    remove_newline(new_mark.remarks);
    
    get_current_date(new_mark.entry_date);
    
    save_mark_to_file(new_mark);
    
    printf("\n✓ Student marks entered successfully!\n");
    printf("Student: %s\n", new_mark.student_name);
    printf("Exam: %s\n", new_mark.exam_name);
    printf("Marks: %.2f/%.2f (%.2f%%)\n", new_mark.marks_obtained, new_mark.total_marks, new_mark.percentage);
    printf("Grade: %s\n", new_mark.grade);
}

void update_student_marks() {
    int mark_id;
    printf("\nEnter Mark ID to update: ");
    scanf("%d", &mark_id);
    clear_input_buffer();
    
    int count = 0;
    ExamMark* marks = load_marks_from_file(&count);
    
    int found = -1;
    for (int i = 0; i < count; i++) {
        if (marks[i].mark_id == mark_id) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("Mark record with ID %d not found.\n", mark_id);
        if (marks) free(marks);
        return;
    }
    
    printf("\n===== UPDATE STUDENT MARKS =====\n");
    printf("Current Record:\n");
    printf("Student: %s\n", marks[found].student_name);
    printf("Exam: %s\n", marks[found].exam_name);
    printf("Current Marks: %.2f/%.2f (%.2f%%)\n", 
           marks[found].marks_obtained, marks[found].total_marks, marks[found].percentage);
    printf("Current Grade: %s\n", marks[found].grade);
    
    printf("\nEnter new marks obtained: ");
    scanf("%f", &marks[found].marks_obtained);
    clear_input_buffer();
    
    // Recalculate percentage and grade
    marks[found].percentage = (marks[found].marks_obtained / marks[found].total_marks) * 100;
    strcpy(marks[found].grade, calculate_grade(marks[found].percentage));
    
    printf("Enter new remarks: ");
    fgets(marks[found].remarks, sizeof(marks[found].remarks), stdin);
    remove_newline(marks[found].remarks);
    
    // Save updated data
    FILE* file = fopen("data/marks.txt", "w");
    if (file) {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%d|%d|%s|%d|%s|%d|%s|%.2f|%.2f|%.2f|%s|%s|%s\n",
                    marks[i].mark_id, marks[i].student_id, marks[i].student_name,
                    marks[i].exam_id, marks[i].exam_name, marks[i].subject_id,
                    marks[i].subject_name, marks[i].marks_obtained, marks[i].total_marks,
                    marks[i].percentage, marks[i].grade, marks[i].remarks, marks[i].entry_date);
        }
        fclose(file);
        printf("\n✓ Student marks updated successfully!\n");
        printf("New Marks: %.2f/%.2f (%.2f%%)\n", 
               marks[found].marks_obtained, marks[found].total_marks, marks[found].percentage);
        printf("New Grade: %s\n", marks[found].grade);
    } else {
        printf("Error updating marks.\n");
    }
    
    free(marks);
}

void view_student_results() {
    int student_id;
    printf("\nEnter Student ID to view results: ");
    scanf("%d", &student_id);
    clear_input_buffer();
    
    int count = 0;
    ExamMark* marks = load_marks_from_file(&count);
    
    if (count == 0) {
        printf("\nNo marks found in database.\n");
        return;
    }
    
    int found = 0;
    printf("\n===== STUDENT RESULTS =====\n");
    
    for (int i = 0; i < count; i++) {
        if (marks[i].student_id == student_id) {
            if (!found) {
                printf("Student: %s (ID: %d)\n", marks[i].student_name, marks[i].student_id);
                printf("===========================================\n");
                printf("%-20s %-15s %-8s %-8s %-6s %-5s\n", 
                       "Exam", "Subject", "Obtained", "Total", "%%", "Grade");
                printf("===========================================\n");
                found = 1;
            }
            printf("%-20s %-15s %-8.2f %-8.2f %-6.2f %-5s\n",
                   marks[i].exam_name,
                   marks[i].subject_name,
                   marks[i].marks_obtained,
                   marks[i].total_marks,
                   marks[i].percentage,
                   marks[i].grade);
        }
    }
    
    if (!found) {
        printf("No results found for student ID %d.\n", student_id);
    } else {
        // Calculate overall statistics
        float total_percentage = 0;
        int exam_count = 0;
        
        for (int i = 0; i < count; i++) {
            if (marks[i].student_id == student_id) {
                total_percentage += marks[i].percentage;
                exam_count++;
            }
        }
        
        float average = total_percentage / exam_count;
        printf("===========================================\n");
        printf("Overall Average: %.2f%% | Grade: %s\n", average, calculate_grade(average));
    }
    
    free(marks);
}

void generate_report_cards() {
    printf("\n===== GENERATE REPORT CARDS =====\n");
    printf("This feature will generate comprehensive report cards.\n");
    printf("Features will include:\n");
    printf("- Individual student report cards\n");
    printf("- Subject-wise performance\n");
    printf("- Overall grades and rankings\n");
    printf("- Attendance summary\n");
    printf("- Teacher comments\n");
    printf("- Export to PDF format\n");
}

void class_performance_analysis() {
    int class_id;
    printf("\nEnter Class ID for performance analysis: ");
    scanf("%d", &class_id);
    clear_input_buffer();
    
    int count = 0;
    ExamMark* marks = load_marks_from_file(&count);
    
    if (count == 0) {
        printf("\nNo marks found in database.\n");
        return;
    }
    
    printf("\n===== CLASS PERFORMANCE ANALYSIS =====\n");
    printf("Analysis for Class ID: %d\n", class_id);
    printf("=====================================\n");
    
    // This is a simplified analysis - in a real system, you'd need to 
    // match class_id with student records and then find their marks
    printf("Detailed class performance analysis will be implemented.\n");
    printf("Features will include:\n");
    printf("- Class average calculations\n");
    printf("- Subject-wise performance trends\n");
    printf("- Top performers identification\n");
    printf("- Students needing attention\n");
    printf("- Comparative analysis with other classes\n");
    
    free(marks);
}

void marks_results_menu() {
    int choice;
    do {
        printf("\n===== MARKS & RESULTS =====\n");
        printf("1. Enter Student Marks\n");
        printf("2. Update Student Marks\n");
        printf("3. View Student Results\n");
        printf("4. Subject-wise Results\n");
        printf("5. Class Performance\n");
        printf("6. Generate Report Cards\n");
        printf("0. Back to Main Menu\n");
        printf("===========================\n");
        printf("Enter choice: ");
        
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch(choice) {
            case 1: enter_student_marks(); break;
            case 2: update_student_marks(); break;
            case 3: view_student_results(); break;
            case 4: printf("Subject-wise results feature coming soon...\n"); break;
            case 5: class_performance_analysis(); break;
            case 6: generate_report_cards(); break;
            case 0: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 0);
}

void reports_analytics_menu() {
    printf("\n===== REPORTS & ANALYTICS =====\n");
    printf("Advanced reporting features coming soon:\n");
    printf("- Student performance trends\n");
    printf("- Teacher effectiveness analysis\n");
    printf("- Subject difficulty analysis\n");
    printf("- Attendance patterns\n");
    printf("- Fee collection reports\n");
    printf("- Custom report builder\n");
}

void system_settings_menu() {
    printf("\n===== SYSTEM SETTINGS =====\n");
    printf("System configuration options:\n");
    printf("- Database backup and restore\n");
    printf("- User permissions management\n");
    printf("- Grade scale configuration\n");
    printf("- Academic year settings\n");
    printf("- System maintenance tools\n");
}

int get_next_exam_id() {
    FILE* file = fopen("data/exams.txt", "r");
    int max_id = 4000; // Starting ID for exams
    
    if (file) {
        char line[400];
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

int get_next_mark_id() {
    FILE* file = fopen("data/marks.txt", "r");
    int max_id = 5000; // Starting ID for marks
    
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

void save_exam_to_file(Exam exam) {
    FILE* file = fopen("data/exams.txt", "a");
    if (file) {
        fprintf(file, "%d|%s|%s|%d|%s|%d|%s|%s|%s|%s|%d|%s\n",
                exam.exam_id, exam.exam_name, exam.exam_type,
                exam.subject_id, exam.subject_name, exam.class_id,
                exam.class_name, exam.exam_date, exam.start_time,
                exam.end_time, exam.total_marks, exam.status);
        fclose(file);
    } else {
        printf("Error: Could not save exam data.\n");
    }
}

void save_mark_to_file(ExamMark mark) {
    FILE* file = fopen("data/marks.txt", "a");
    if (file) {
        fprintf(file, "%d|%d|%s|%d|%s|%d|%s|%.2f|%.2f|%.2f|%s|%s|%s\n",
                mark.mark_id, mark.student_id, mark.student_name,
                mark.exam_id, mark.exam_name, mark.subject_id,
                mark.subject_name, mark.marks_obtained, mark.total_marks,
                mark.percentage, mark.grade, mark.remarks, mark.entry_date);
        fclose(file);
    } else {
        printf("Error: Could not save mark data.\n");
    }
}

Exam* load_exams_from_file(int* count) {
    FILE* file = fopen("data/exams.txt", "r");
    Exam* exams = NULL;
    *count = 0;
    
    if (!file) {
        return NULL;
    }
    
    char line[500];
    int capacity = 10;
    exams = malloc(capacity * sizeof(Exam));
    
    while (fgets(line, sizeof(line), file)) {
        if (*count >= capacity) {
            capacity *= 2;
            exams = realloc(exams, capacity * sizeof(Exam));
        }
        
        sscanf(line, "%d|%99[^|]|%49[^|]|%d|%99[^|]|%d|%49[^|]|%14[^|]|%9[^|]|%9[^|]|%d|%19[^|\n]",
               &exams[*count].exam_id,
               exams[*count].exam_name,
               exams[*count].exam_type,
               &exams[*count].subject_id,
               exams[*count].subject_name,
               &exams[*count].class_id,
               exams[*count].class_name,
               exams[*count].exam_date,
               exams[*count].start_time,
               exams[*count].end_time,
               &exams[*count].total_marks,
               exams[*count].status);
        
        (*count)++;
    }
    
    fclose(file);
    return exams;
}

ExamMark* load_marks_from_file(int* count) {
    FILE* file = fopen("data/marks.txt", "r");
    ExamMark* marks = NULL;
    *count = 0;
    
    if (!file) {
        return NULL;
    }
    
    char line[600];
    int capacity = 10;
    marks = malloc(capacity * sizeof(ExamMark));
    
    while (fgets(line, sizeof(line), file)) {
        if (*count >= capacity) {
            capacity *= 2;
            marks = realloc(marks, capacity * sizeof(ExamMark));
        }
        
        sscanf(line, "%d|%d|%99[^|]|%d|%99[^|]|%d|%99[^|]|%f|%f|%f|%4[^|]|%199[^|]|%14[^|\n]",
               &marks[*count].mark_id,
               &marks[*count].student_id,
               marks[*count].student_name,
               &marks[*count].exam_id,
               marks[*count].exam_name,
               &marks[*count].subject_id,
               marks[*count].subject_name,
               &marks[*count].marks_obtained,
               &marks[*count].total_marks,
               &marks[*count].percentage,
               marks[*count].grade,
               marks[*count].remarks,
               marks[*count].entry_date);
        
        (*count)++;
    }
    
    fclose(file);
    return marks;
}

void display_exam_details(Exam exam) {
    printf("\n===== EXAM DETAILS =====\n");
    printf("Exam ID: %d\n", exam.exam_id);
    printf("Exam Name: %s\n", exam.exam_name);
    printf("Type: %s\n", exam.exam_type);
    printf("Subject: %s (ID: %d)\n", exam.subject_name, exam.subject_id);
    printf("Class: %s (ID: %d)\n", exam.class_name, exam.class_id);
    printf("Date: %s\n", exam.exam_date);
    printf("Time: %s - %s\n", exam.start_time, exam.end_time);
    printf("Total Marks: %d\n", exam.total_marks);
    printf("Status: %s\n", exam.status);
    printf("========================\n");
}

char* calculate_grade(float percentage) {
    static char grade[5];
    
    if (percentage >= 90) {
        strcpy(grade, "A+");
    } else if (percentage >= 80) {
        strcpy(grade, "A");
    } else if (percentage >= 70) {
        strcpy(grade, "B+");
    } else if (percentage >= 60) {
        strcpy(grade, "B");
    } else if (percentage >= 50) {
        strcpy(grade, "C+");
    } else if (percentage >= 40) {
        strcpy(grade, "C");
    } else if (percentage >= 35) {
        strcpy(grade, "D");
    } else {
        strcpy(grade, "F");
    }
    
    return grade;
}