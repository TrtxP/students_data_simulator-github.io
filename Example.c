#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int age;
} Student;

void creating_new_file(const char* filename, Student* students, int studentCount);
void sorting_by_name(Student* students, int studentCount);
void swap_students(Student *a, Student *b);

int main() {
    Student* students = NULL; 
    int studentCount = 0; 

    while (1) {
        int newCount; 
        printf("Enter the new number of students: ");
        if (scanf("%d", &newCount) != 1 || newCount < 1) {
            printf("Error: please enter a valid number greater than 0!\n");
            while (getchar() != '\n'); // Очищаем буфер ввода
            continue; 
        }
        if (newCount < studentCount) {
            for (int i = newCount; i < studentCount; i++) {
                free(students[i].name);
            }
        }

        Student* temp = realloc(students, newCount * sizeof(Student));  

        if (temp == NULL) {
            printf("Error reallocating memory!\n");
            for (int i = 0; i < studentCount; i++) {
                free(students[i].name);
            }
            free(students);
            return 1;
        }

        students = temp; /* Присваиваем значение структуры данных Student students 
        * к структуре данных Student temp, чтобы туда сохрнанять данные про каждого студента */ 

        for (int i = studentCount; i < newCount; i++) {
            char buffer[100];

            printf("Enter the name of student %d: ", i + 1);
            scanf("%99s", &buffer);
            students[i].name = malloc(strlen(buffer) + 1);
            strcpy(students[i].name, buffer);

            printf("Enter the age of student %d: ", i + 1);
            if (scanf("%d", &students[i].age) != 1 || students[i].age < 17 || students[i].age > 50) {
                printf("Error: age must be between 17 and 50.\n");
                free(students[i].name);
                i--; 
                while (getchar() != '\n'); /* Очищаем буфер ввода, пока уменьшаем 
                * инкремент один раз на единицу для записи данных следующего студента */ 
                continue;
            }
        }

        studentCount = newCount; // Присваиваем studentCount к newCount для вывода списка всех студентов 

        printf("\nList of students:\n");
        for (int i = 0; i < studentCount; i++) {
            printf("Student %d: %s, %d years old\n", i + 1, students[i].name, students[i].age);
        }

        int choice;
        printf("\nDo you want to change the number of students? (1 - yes, 2 - no): ");
        scanf("%d", &choice);
        if (choice == 2) {
            break;
        }
    }

    sorting_by_name(students, studentCount);

    creating_new_file("Students.txt", students, studentCount);

    for (int i = 0; i < studentCount; i++) {
        free(students[i].name);
    }
    free(students);

    printf("Program finished.\n");
    return 0;
}

void creating_new_file(const char* filename, Student* students, int studentCount) 
{
    char filepath[256];

    printf("Where do you want to save the new file?\n");
    printf("1 - C:/Temp/Students.txt\n");
    printf("2 - D:/VS Code/C/Students.txt\n");

    int choice;
    scanf("%d", & choice);

    if (choice == 1) strcpy(filepath, "C:/Temp/Students.txt"); 
    else if (choice == 2) strcpy(filepath, "D:/VS Code/C/Students.txt");
    else {
        printf("Invalid choice, using default: C:/Temp/Students.txt\n");
        strcpy(filepath, "C:/Temp/Students.txt");
    }

    FILE* file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Error opening file for writing students data\n");
        return;
    }

    fprintf(file, "List of students:\n");
    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "Student %d: %s, %d years old\n", i+1, students[i].name, students[i].age);
    }

    fclose(file);
}

// Основная функция сортировки студентов по имени
void sorting_by_name(Student* students, int studentCount) {
    printf("Would do want to sort students by name in alphabetical order?\n");
    printf("1 - Yes\n");
    printf("2 - No\n");

    int select_choice;
    scanf("%d", &select_choice);
    if (select_choice == 1) {
        for (int i = 0; i < studentCount - 1; i++) {
            for (int j = 0; j < studentCount - i - 1; j++) {
                if (strcmp(students[j].name, students[j+1].name) > 0) swap_students(&students[j], &students[j+1]);
        }
    }
    printf("List of students:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("Student %d: %s, %d years old\n", i+1, students[i].name, students[i].age);
    }
    printf("Sorting students by name in alphabetical order has finished succeesfully!\n");
    }
    else if (select_choice == 2) {
        return;
    }
}

// Функция обмена студентов 
void swap_students(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}