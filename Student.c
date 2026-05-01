#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll;
    char name[50];
    float m1, m2, m3;
    float total;
};

// Add student
void addStudent() {
    FILE *fp = fopen("students.dat", "ab");
    struct Student s;

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter marks (3 subjects): ");
    scanf("%f %f %f", &s.m1, &s.m2, &s.m3);

    s.total = s.m1 + s.m2 + s.m3;

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student added successfully!\n");
}

// Display students
void displayStudents() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("\nRoll: %d", s.roll);
        printf("\nName: %s", s.name);
        printf("\nMarks: %.2f %.2f %.2f", s.m1, s.m2, s.m3);
        printf("\nTotal: %.2f\n", s.total);
    }

    fclose(fp);
}

// Rank list
void rankList() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s[100], temp;
    int i = 0, j, n = 0;

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    while (fread(&s[n], sizeof(struct Student), 1, fp)) {
        n++;
    }
    fclose(fp);

    // Sorting (Descending order)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (s[i].total < s[j].total) {
                temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }

    printf("\n--- Rank List ---\n");
    for (i = 0; i < n; i++) {
        printf("\nRank %d", i + 1);
        printf("\nRoll: %d", s[i].roll);
        printf("\nName: %s", s[i].name);
        printf("\nTotal: %.2f\n", s[i].total);
    }
}

// MAIN MENU (Menu-driven part)
int main() {
    int choice;

    do {
        printf("\n\n===== MENU =====");
        printf("\n1. Add Student");
        printf("\n2. Display Students");
        printf("\n3. Generate Rank List");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                rankList();
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}
