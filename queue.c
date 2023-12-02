#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

// Structure to create a node with data, name, and the next pointer
struct node {
    double spending;
    double percentage;
    char name[20];
    struct node *next;
};

struct node *front = NULL;
struct node *rear = NULL;

// Enqueue() operation on a queue
void push(double percentage, double value, const char *name) {
    struct node *ptr;
    ptr = (struct node *)malloc(sizeof(struct node));
    ptr->spending = value;
    ptr->percentage = percentage;
    strncpy(ptr->name, name, sizeof(ptr->name) - 1);
    ptr->name[sizeof(ptr->name) - 1] = '\0';  // Ensure null-terminated string
    ptr->next = NULL;

    if ((front == NULL) && (rear == NULL)) {
        front = rear = ptr;
    } else {
        rear->next = ptr;
        rear = ptr;
    }
}

// Dequeue() operation on a queue
double pop(char *name) {
    if (front == NULL) {
        printf("\nAll customers are served\n");
        return -1.0;
    } else {
        struct node *temp = front;
        double temp_data = front->spending;
        double amount = temp_data * front->percentage;
        strncpy(name, front->name, sizeof(front->name) - 1);
        name[sizeof(front->name) - 1] = '\0';  // Ensure null-terminated string
        front = front->next;
        free(temp);
        return amount;
    }
}
