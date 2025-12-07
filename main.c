#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Patient Structure (Node of SLL)
struct Patient {
    char id[20];          // CHANGED from int to string
    char name[50];
    char disease[50];
    int priority;         // 1 = Emergency, 0 = Normal
    struct Patient *next;
};

struct Patient *head = NULL;

// Create a new patient
struct Patient* createPatient(char id[], char name[], char disease[], int priority) {
    struct Patient *newNode = (struct Patient*)malloc(sizeof(struct Patient));
    strcpy(newNode->id, id);
    strcpy(newNode->name, name);
    strcpy(newNode->disease, disease);
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

// Add patient (Emergency → beginning, Normal → end)
void addPatient(char id[], char name[], char disease[], int priority) {
    struct Patient *newNode = createPatient(id, name, disease, priority);

    if (priority == 1) {
        newNode->next = head;
        head = newNode;
        printf("Emergency patient added at beginning!\n");
    } else {
        if (head == NULL) head = newNode;
        else {
            struct Patient *temp = head;
            while (temp->next != NULL) temp = temp->next;
            temp->next = newNode;
        }
        printf("Normal patient added at end!\n");
    }
}

// Display all patients
void displayPatients() {
    if (head == NULL) {
        printf("No patients in the list.\n");
        return;
    }

    struct Patient *temp = head;
    printf("\n--- Patient List ---\n");
    while (temp != NULL) {
        printf("ID: %s | Name: %s | Disease: %s | Priority: %s\n",
               temp->id, temp->name, temp->disease,
               temp->priority ? "Emergency" : "Normal");
        temp = temp->next;
    }
}

// Search patient
void searchPatient(char id[]) {
    struct Patient *temp = head;

    while (temp != NULL) {
        if (strcmp(temp->id, id) == 0) {
            printf("\nPatient Found!\n");
            printf("ID: %s | Name: %s | Disease: %s | Priority: %s\n",
                   temp->id, temp->name, temp->disease,
                   temp->priority ? "Emergency" : "Normal");
            return;
        }
        temp = temp->next;
    }
    printf("Patient with ID %s not found.\n", id);
}

// Delete patient
void deletePatient(char id[]) {
    if (head == NULL) {
        printf("No patients to delete.\n");
        return;
    }

    struct Patient *temp = head, *prev = NULL;

    if (strcmp(temp->id, id) == 0) {
        head = temp->next;
        free(temp);
        printf("Patient with ID %s d1eleted.\n", id);
        return;
    }

    while (temp != NULL && strcmp(temp->id, id) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Patient not found.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Patient with ID %s deleted.\n", id);
}

void countPatients() {
    int count = 0;
    struct Patient *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    printf("Total number of patients: %d\n", count);
}

int main() {
    int choice, priority;
    char id[20], name[50], disease[50];

    while (1) {
        printf("\n--- Hospital Patient Management (SLL) ---\n");
        printf("1. Add Patient\n");
        printf("2. Display Patients\n");
        printf("3. Search Patient\n");
        printf("4. Delete Patient\n");
        printf("5. Count Patients\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Patient ID: ");
                scanf("%s", id);
                printf("Enter Name: ");
                scanf("%s", name);
                printf("Enter Disease: ");
                scanf("%s", disease);
                printf("Priority (1 = Emergency, 0 = Normal): ");
                scanf("%d", &priority);
                addPatient(id, name, disease, priority);
                break;

            case 2:
                displayPatients();
                break;

            case 3:
                printf("Enter ID to search: ");
                scanf("%s", id);
                searchPatient(id);
                break;

            case 4:
                printf("Enter ID to delete: ");
                scanf("%s", id);
                deletePatient(id);
                break;

            case 5:
                countPatients();
                break;

            case 6:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
