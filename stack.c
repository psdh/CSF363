// FILE TO BE REMOVED
// BEING USED TO TEMP TEST CASE

#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node node;

struct node
{
    int data;
    node* next;
};

node* insert(node* head, int val)
{
    // Allocate new space
    node* new = (node*) malloc(sizeof(node));
    new->data = val;
    new->next = head;
    head = new;

    return head;
}

int print(node* head)
{
    node* temp = head;

    printf("\n");
    while (temp->next != NULL)
    {
        printf("  %d  -->", temp->data);
        temp = temp->next;
    }
    printf("%d\n", temp->data);

    return 0;
}

int main()
{
    printf("Hello, world \nAll over again! :D");

    node* head = NULL;

    head = insert(head, 2);
    head = insert(head, 3);

    print(head);
}

/*
#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node node;

struct node
{
    int data;
    node* next;
};

node* insert(node* head, int val)
{
    // Allocate new space
    node* new = (node*) malloc(sizeof(node));
    new->data = val;
    new->next = head;
    head = new;

    return head;
}

int print(node* head)
{
    node* temp = head;

    printf("\n");
    while (temp->next != NULL)
    {
        printf("  %d  -->", temp->data);
        temp = temp->next;
    }
    printf("  %d\n", temp->data);

    return 0;
}

int main()
{
    printf("Hello, world \nAll over again! :D");

    node* head = NULL;

    head = insert(head, 2);
    head = insert(head, 3);

    print(head);
}

#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node node;

struct node
{
    int data;
    node* next;
};

node* insert(node* head, int val)
{
    // Allocate new space
    node* new = (node*) malloc(sizeof(node));
    new->data = val;
    new->next = head;
    head = new;

    return head;
}

int print(node* head)
{
    node* temp = head;

    printf("\n");
    while (temp->next != NULL)
    {
        printf("  %d  -->", temp->data);
        temp = temp->next;
    }
    printf("  %d\n", temp->data);

    return 0;
}

int main()
{
    printf("Hello, world \nAll over again! :D");

    node* head = NULL;

    head = insert(head, 2);
    head = insert(head, 3);

    print(head);
}

#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node node;

struct node
{
    int data;
    node* next;
};

node* insert(node* head, int val)
{
    // Allocate new space
    node* new = (node*) malloc(sizeof(node));
    new->data = val;
    new->next = head;
    head = new;

    return head;
}

int print(node* head)
{
    node* temp = head;

    printf("\n");
    while (temp->next != NULL)
    {
        printf("  %d  -->", temp->data);
        temp = temp->next;
    }
    printf("  %d\n", temp->data);

    return 0;
}

int main()
{
    printf("Hello, world \nAll over again! :D");

    node* head = NULL;

    head = insert(head, 2);
    head = insert(head, 3);

    print(head);
}

#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node node;

struct node
{
    int data;
    node* next;
};

node* insert(node* head, int val)
{
    // Allocate new space
    node* new = (node*) malloc(sizeof(node));
    new->data = val;
    new->next = head;
    head = new;

    return head;
}

int print(node* head)
{
    node* temp = head;

    printf("\n");
    while (temp->next != NULL)
    {
        printf("  %d  -->", temp->data);
        temp = temp->next;
    }
    printf("  %d\n", temp->data);

    return 0;
}

int main()
{
    printf("Hello, world \nAll over again! :D");

    node* head = NULL;

    head = insert(head, 2);
    head = insert(head, 3);

    print(head);
}

*/
