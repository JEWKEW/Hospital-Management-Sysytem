#ifndef __vari_H_
#define __vari_H_ 1

#define MAX 100

typedef struct Patient {
    char fullname[40];
    int age;
    char sex[10];
    char phone[15];               
    char allergies[100];         
    char conditions[100];         
    int pior;
    struct Patient *next;
} Patient;

typedef struct {
    Patient *front;
    int r;
} Queue;

typedef struct node {
    struct Patient *patient;
    struct node *left;
    struct node *right;
} node;

#endif
