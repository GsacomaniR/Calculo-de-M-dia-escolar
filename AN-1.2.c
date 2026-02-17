#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_STUDENTS 100
#define MIN_APPROVAL 70
#define MIN_RECOVERY 50
#define MIN_FREQUENCY 75

typedef struct {
    char name[100];
    int registration;
    float grades[3];
    float average;
    int absences;
    float frequency;
    char situation[30];
} Student;

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clearScreen() {
    system("cls"); // Windows
    // system("clear"); // Linux/Mac
}

void pause() {
    printf("\nPress Enter to continue...");
    clearBuffer();
    getchar();
}

void header(char *title) {
    clearScreen();
    printf("========================================\n");
    printf("   %s\n", title);
    printf("========================================\n\n");
}

int validateGrade(float grade) {
    return (grade >= 0 && grade <= 100);
}

int validateAbsences(int absences, int total_classes) {
    return (absences >= 0 && absences <= total_classes);
}

void calculateAverage(Student *student) {
    float sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += student->grades[i];
    }
    student->average = sum / 3.0;
}

void calculateFrequency(Student *student, int total_classes) {
    student->frequency = ((float)(total_classes - student->absences) / total_classes) * 100;
}

void determineSituation(Student *student) {
    if (student->frequency < MIN_FREQUENCY) {
        strcpy(student->situation, "FAILED DUE TO ABSENCES");
    } else if (student->average >= MIN_APPROVAL) {
        strcpy(student->situation, "APPROVED");
    } else if (student->average >= MIN_RECOVERY) {
        strcpy(student->situation, "RECOVERY");
    } else {
        strcpy(student->situation, "FAILED DUE TO GRADES");
    }
}

void displayStudent(Student student, int total_classes) {
    printf("Name: %s\n", student.name);
    printf("Registration: %d\n", student.registration);
    printf("Grades: %.1f | %.1f | %.1f\n", 
           student.grades[0], student.grades[1], student.grades[2]);
    printf("Average: %.2f\n", student.average);
    printf("Absences: %d of %d (%.1f%%)\n", 
           student.absences, total_classes, student.frequency);
    printf("Situation: %s\n", student.situation);
}

void registerStudent(Student students[], int *amount, int total_classes) {
    header("REGISTER STUDENT");
    
    if (*amount >= MAX_STUDENTS) {
        printf("Maximum number of students reached!\n");
        pause();
        return;
    }
    
    Student new;
    
    printf("Name of student: ");
    fgets(new.name, sizeof(new.name), stdin);
    new.name[strcspn(new.name, "\n")] = 0; // Remove \n
    
    printf("Registration: ");
    scanf("%d", &new.registration);
    clearBuffer();
    
    printf("\n--- Grades (0 to 100) ---\n");
    for (int i = 0; i < 3; i++) {
        do {
            printf("Grade %d: ", i + 1);
            scanf("%f", &new.grades[i]);
            clearBuffer();
            
            if (!validateGrade(new.grades[i])) {
                printf("Invalid grade! Please enter a value between 0 and 100.\n");
            }
        } while (!validateGrade(new.grades[i]));
    }
    
    do {
        printf("\nNumber of absences (0 to %d): ", total_classes);
        scanf("%d", &new.absences);
        clearBuffer();
        
        if (!validateAbsences(new.absences, total_classes)) {
            printf("Invalid number of absences!\n");
        }
    } while (!validateAbsences(new.absences, total_classes));
    
    // Calculate dados
    calculateAverage(&new);
    calculateFrequency(&new, total_classes);
    determineSituation(&new);
    
    students[*amount] = new;
    (*amount)++;
    
    printf("\nStudent registered successfully!\n");
    printf("\n--- Summary ---\n");
    displayStudent(new, total_classes);
    pause();
}

void listStudents(Student students[], int amount, int total_classes) {
    header("LIST STUDENTS");
    
    if (amount == 0) {
        printf("No students registered.\n");
        pause();
        return;
    }
    
    for (int i = 0; i < amount; i++) {
        printf("\n----- STUDENT %d -----\n", i + 1);
        displayStudent(students[i], total_classes);
    }
    pause();
}

void searchStudent(Student students[], int amount, int total_classes) {
    header("SEARCH STUDENT");
    
    if (amount == 0) {
        printf("No students registered.\n");
        pause();
        return;
    }
    
    int option;
    printf("Search by:\n");
    printf("1. Name\n");
    printf("2. Registration\n");
    printf("Option: ");
    scanf("%d", &option);
    clearBuffer();
    
    if (option == 1) {
        char nameSearch[100];
        printf("Enter the name: ");
        fgets(nameSearch, sizeof(nameSearch), stdin);
        nameSearch[strcspn(nameSearch, "\n")] = 0;
        
        printf("\n--- Results ---\n");
        int found = 0;
        for (int i = 0; i < amount; i++) {
            if (strstr(students[i].name, nameSearch) != NULL) {
                displayStudent(students[i], total_classes);
                printf("\n");
                found++;
            }
        }
        printf("Total found: %d\n", found);
    } 
    else if (option == 2) {
        int matSearch;
        printf("Enter the registration number: ");
        scanf("%d", &matSearch);
        clearBuffer();
        
        for (int i = 0; i < amount; i++) {
            if (students[i].registration == matSearch) {
                displayStudent(students[i], total_classes);
                pause();
                return;
            }
        }
        printf("Student not found!\n");
    }
    pause();
}

void statistics(Student students[], int amount, int total_classes) {
    header("STATISTICS OF THE CLASS");
    
    if (amount == 0) {
        printf("No students registered.\n");
        pause();
        return;
    }
    
    float sum_average = 0;
    float highest_average = students[0].average;
    float lowest_average = students[0].average;
    int approved = 0, recovery = 0, failed = 0;
    
    for (int i = 0; i < amount; i++) {
        sum_average += students[i].average;
        
        if (students[i].average > highest_average) highest_average = students[i].average;
        if (students[i].average < lowest_average) lowest_average = students[i].average;
        
        if (students[i].average >= MIN_APPROVAL && students[i].frequency >= MIN_FREQUENCY)
            approved++;
        else if (students[i].average >= MIN_RECOVERY && students[i].frequency >= MIN_FREQUENCY)
            recovery++;
        else
            failed++;
    }
    
    float average_class = sum_average / amount;
    
    printf("Total of students: %d\n", amount);
    printf("Class average: %.2f\n", average_class);
    printf("Highest average: %.2f\n", highest_average);
    printf("Lowest average: %.2f\n", lowest_average);
    printf("\n--- Situation ---\n");
    printf("Approved: %d (%.1f%%)\n", approved, (float)approved/amount*100);
    printf("Recovery: %d (%.1f%%)\n", recovery, (float)recovery/amount*100);
    printf("Failed: %d (%.1f%%)\n", failed, (float)failed/amount*100);
    
    pause();
}

void saveData(Student students[], int amount) {
    FILE *file = fopen("students_data.txt", "w");
    if (file == NULL) {
        printf("Error saving data!\n");
        return;
    }
    
    fprintf(file, "%d\n", amount);
    for (int i = 0; i < amount; i++) {
        fprintf(file, "%s\n", students[i].name);
        fprintf(file, "%d\n", students[i].registration);
        fprintf(file, "%.1f %.1f %.1f\n", 
                students[i].grades[0], students[i].grades[1], students[i].grades[2]);
        fprintf(file, "%d\n", students[i].absences);
        fprintf(file, "%.2f %.1f\n", students[i].average, students[i].frequency);
        fprintf(file, "%s\n", students[i].situation);
    }
    
    fclose(file);
    printf("Data saved successfully!\n");
    pause();
}

void loadData(Student students[], int *amount) {
    FILE *file = fopen("students_data.txt", "r");
    if (file == NULL) {
        printf("No previous data found.\n");
        return;
    }
    
    fscanf(file, "%d\n", amount);
    for (int i = 0; i < *amount; i++) {
        fgets(students[i].name, sizeof(students[i].name), file);
        students[i].name[strcspn(students[i].name, "\n")] = 0;
        
        fscanf(file, "%d\n", &students[i].registration);
        fscanf(file, "%f %f %f\n", 
               &students[i].grades[0], &students[i].grades[1], &students[i].grades[2]);
        fscanf(file, "%d\n", &students[i].absences);
        fscanf(file, "%f %f\n", &students[i].average, &students[i].frequency);
        fgets(students[i].situation, sizeof(students[i].situation), file);
        students[i].situation[strcspn(students[i].situation, "\n")] = 0;
    }
    
    fclose(file);
    printf("Data loaded successfully!\n");
    pause();
}

int main() {
    setlocale(LC_ALL, "English");
    
    Student students[MAX_STUDENTS];
    int amount = 0;
    int total_classes = 60;
    int option;
    
    // Carregar dados salvos
    loadData(students, &amount);
    
    do {
        header("ACADEMIC MANAGEMENT SYSTEM");
        printf("1. Register Student\n");
        printf("2. List Students\n");
        printf("3. Search Student\n");
        printf("4. Class Statistics\n");
        printf("5. Save Data\n");
        printf("0. Exit\n");
        printf("\nChose a Option: ");
        scanf("%d", &option);
        clearBuffer();
        
        switch(option) {
            case 1:
                registerStudent(students, &amount, total_classes);
                break;
            case 2:
                listStudents(students, amount, total_classes);
                break;
            case 3:
                searchStudent(students, amount, total_classes);
                break;
            case 4:
                statistics(students, amount, total_classes);
                break;
            case 5:
                saveData(students, amount);
                break;
            case 0:
                printf("\nSaving data before exiting...\n");
                saveData(students, amount);
                printf("System closed. See you later!\n");
                break;
            default:
                printf("Invalid option!\n");
                pause();
        }
    } while(option != 0);
    
    return 0;
}
