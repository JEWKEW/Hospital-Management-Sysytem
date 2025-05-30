#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vari.h"

Patient *createQ(char *fullname, int age, char *sex, char *phone, char *allergies, char *conditions, int pior);
int DeleteByName(Patient **front, const char *name, int *r);
void Enqueue(Patient **front, char *fullname, int age, char *sex, char *phone, char *allergies, char *conditions, int pior, int *r);
void Dequeue(Patient **front, int *r);
void Peek(Patient *front);
void DisplayList(Patient *front);
void Search(Patient *front);
int calculatePriority();

Patient *createQ(char *fullname, int age, char *sex, char *phone, char *allergies, char *conditions, int pior) {
    Patient *newPatient = (Patient *)malloc(sizeof(Patient));
    strcpy(newPatient->fullname, fullname);
    newPatient->age = age;
    strcpy(newPatient->sex, sex);
    strcpy(newPatient->phone, phone);
    strcpy(newPatient->allergies, allergies);
    strcpy(newPatient->conditions, conditions);
    newPatient->pior = pior;
    newPatient->next = NULL;
    return newPatient;
}

int DeleteByName(Patient **front, const char *name, int *r) {
    Patient *temp = *front, *prev = NULL;

    while (temp != NULL && strcmp(temp->fullname, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return 0; 
    }

    if (prev == NULL) {
        *front = temp->next; 
    } else {
        prev->next = temp->next;
    }

    free(temp);
    (*r)--;
    return 1; 
}

void Enqueue(Patient **front, char *fullname, int age, char *sex, char *phone, char *allergies, char *conditions, int pior, int *r) {
    if (*r == MAX - 1) {
        printf("Patient queue is full.\n");
        return;
    }

    Patient *newQ = createQ(fullname, age, sex, phone, allergies, conditions, pior);


    if (*front == NULL || (*front)->pior < pior) {
        newQ->next = *front;
        *front = newQ;
    } else {
        Patient *ptr = *front;

        while (ptr->next != NULL && ptr->next->pior >= pior) {
        ptr = ptr->next;
        }

        newQ->next = ptr->next;
        ptr->next = newQ;
    }

    (*r)++;
}

void Dequeue(Patient **front, int *r) {
    if (*front == NULL) {
        printf("Patient is empty.\n");
        return;
    }

    Patient *temp = *front;
    printf("Cure Patient: Fullname: %s, Priority: %d\n", temp->fullname, temp->pior);
    *front = (*front)->next;
    free(temp);
    (*r)--;
}

void Peek(Patient *front) {
    if (front == NULL) {
        printf("Patient is empty.\n");
        return;
    }
    printf("Next queue is Fullname: %s, Priority: %d\n", front->fullname, front->pior);
}

void DisplayList(Patient *front) {
    if (front == NULL) {
        printf("Patient is empty.\n");
        return;
    }

    Patient *ptr = front;
    int n = 1;
    printf("\nHere are all Patients in the queue:\n");
    printf("%-3s %-20s %-5s %-10s %-10s %-15s %-20s %-20s\n","No", "NAME", "AGE", "SEX", "PRIORITY", "PHONE", "ALLERGIES", "CONDITIONS");
 
    while (ptr != NULL) {
        printf("%-3d %-20s %-5d %-10s %-10d %-15s %-20s %-20s\n", n++, ptr->fullname, ptr->age, ptr->sex, ptr->pior, ptr->phone, ptr->allergies, ptr->conditions);
        ptr = ptr->next;
    }
    printf("\n");
}

void Search(Patient *front) {
    if (front == NULL) {
        printf("Patient is empty.\n");
        return;
    }

    printf("What is your name: ");
    char name[40];
    fgets(name, 40, stdin);
    name[strcspn(name, "\n")] = '\0';

    int n = 0;
    Patient *ptr = front;
    while (ptr != NULL) {
        if (strcmp(ptr->fullname, name) == 0) {
            if (n == 0) {
                printf("Next is your queue\n");
            } else {
                printf("Your queue will arrive in %d queues\n", n);
            }
            return;
        }
        n++;
        ptr = ptr->next;
    }

    printf("Your name is not in the queue\n");
}

int calculatePriority() {
    int responses[4];
    const char *questions[4] = {
        "How would you rate your pain right now?",
        "How would you rate your fatigue level?",
        "Do you feel chest tightness or difficulty breathing?",
        "What is your level of consciousness?"
    };

    printf("\nNow, please answer a few health questions to assess priority:\n");

    int pior = 0;
    int isCritical = 0;
    int isUrgent = 0;
    for (int i = 0; i < 4; i++) {
        int choice;
        do {
            printf("\n%s\n", questions[i]);
            printf("1. No symptoms at all\n");
            printf("2. Mild\n");
            printf("3. Moderate\n");
            printf("4. Severe\n");
            printf("5. Worst imaginable\n");
            printf("Enter choice (1-5): ");
            scanf("%d", &choice);
            getchar(); // consume newline
        } while (choice < 1 || choice > 5);

        if (choice == 5) {
            isCritical = 1;
        }
        if (choice == 4) {
            isUrgent = 1;
        }
        switch (choice) {
            case 1: pior += 0; break;
            case 2: pior += 2; break;
            case 3: pior += 5; break;
            case 4: pior += 8; break;
            case 5: pior += 10; break;
        }
    }

    if (isCritical) {
        printf("\nStatus: CRITICAL\n");
        return 40;
    }
    if (isUrgent) {
        printf("\nStatus: URGENT\n");
        return 32;
    }
    // Determine status
    if (pior <= 8) printf("\nStatus: PREVENTIVE\n");
    else if (pior <= 16) printf("\nStatus: MILD\n");
    else if (pior <= 24) printf("\nStatus: MODERATE\n");
    else if (pior <= 32) printf("\nStatus: URGENT\n");
    else printf("\nStatus: CRITICAL\n");

    return pior;
}
