#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
    struct Node* prev;
};

typedef struct Node Node;

void add_First(struct Node** headptr, int data);

int main()
{
    printf("Hello world!\n");
    return 0;
}


Node* create_Node(int data)
{
    Node* temp = malloc(sizeof(Node));
    temp->next = NULL;
    temp->prev = NULL;
    temp->data = 0;
    return temp;
}

// Void function adds a node to the DDL
void add_First(struct Node** headptr,int data)
{
    if(*headptr == NULL)
        {
            *headptr = create_Node(data);
        }
    else
        {
            // Get new node becomes new head
            Node* temp = create_Node(data);
            // Old head prev points to temp
            (*headptr)->prev = temp;
            // Temp points to old head
            temp->next = *headptr;
            // Temp becomes the new headpointer
            *headptr = temp;


        }
}
