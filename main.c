#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
    struct Node* prev;
};

typedef struct Node Node;
typedef int bool;

void add_First(struct Node** headptr, int data);
void add_Last(struct Node** headptr,int data);
Node* create_Node(int data);
void traverse(Node* cursor);
bool search(Node* cursor, int data);
Node* reverse(Node* cursor,struct Node** headptr);
void insert_Node(int index,int data, struct Node** headptr);
void remove_Node(int index,int* data_Removed,struct Node** headptr);
int size(Node* cursor);
void clear_Buffer();
void free_List(Node** headptr);
void print_Menu();
int main()
{
    int sentienel = 0 ;
    Node* headptr = NULL;
    int character = 0;
    int data = 0;
    int index = 0;

    do{
            print_Menu();
            // Ask for input
            printf("\nSelect an option on the menu\n");
            scanf("%1s",&character); // Ask for 1 character
    switch(character)
    {

        case(49):
                    // Add first node
                    printf("Enter an integer to add to linked list: ");
                    clear_Buffer();
                    scanf("%d",&data);
                    add_First(&headptr,data);
                    break;
        case(50):
                    // Add first node
                    printf("Enter an integer to add to linked list: ");
                    clear_Buffer();
                    scanf("%d",&data);
                    add_Last(&headptr,data);
                    break;
        case(51):   // Traverse
                    traverse(headptr);
                    break;
        case(52):   // Insert index
                    printf("Enter an integer to add to linked list");
                    clear_Buffer();
                    scanf("%d",&data);
                    clear_Buffer();
                    printf("Enter an index");
                    scanf("%d",&index);
                    insert_Node(index,data,&headptr);
                    break;
        case(53):   // Remove insert
                    printf("Index to remove node");
                    clear_Buffer();
                    scanf("%d",&index);
                    remove_Node(index,&data,&headptr);
                    printf("Node removed [%d]",data);
                    break;
        case(54):    // Reverse
                    reverse(headptr,&headptr);
                    printf("Liss reversed");
                    break;
        case(55):   // size of linked list
                    printf("Size of list: %d",size(headptr));
                    break;
        case(56):   // Free linked list
                    free_List(&headptr);
                    break;
        case(57):       // Terminate program
                        sentienel = 1;
                        free_List(&headptr);
            break;
        default:        // Wrong format
                printf("Please enter valid input!\n");

                // clear stream
            break;
        clear_Buffer();
    }
    }while(sentienel == 0);


    return 0;
}

void print_Menu()
{
    printf("\n1.Add first\n2.Add last\n3.Traverse\n4.Insert index\n5.Remove at index\n6.Reverse\n7.Size of list\n8.Free list\n9.Quit");
}

/*void returning function, frees each node and sets head to null*/
void free_List(Node** headptr)
{
    Node* cursor = *headptr;
    Node* doomed = cursor;
    // Traverse and free each node
    while(cursor != NULL)
        {
            // Traverse
            cursor = cursor->next;
            free(doomed);
            doomed = cursor;
        }
        // Set head to null
        *headptr = NULL;
}


/* Void function clears the stream buffer*/
void clear_Buffer()
{
    while(getchar() != '\n'); // clear buffer
}

/*Int returning function, iterates linked list and returns its size*/
int size(Node* cursor)
{
    if(cursor == NULL)
        {
            return 0;
        }
    else
        {
            int count = 0;
            // iterate the list until null
            for(cursor!= NULL; ++count;){cursor = cursor->next;}
            return count;
        }
}

// Void function removes a node at a specific index and returns data to int
void remove_Node(int index, int* data_Removed, struct Node** headptr)
{
    int count = 0;
    count = size(*headptr);
    // IF node removed is first
    if(index == 1)
        {
            data_Removed = (*headptr)->data;
            Node* temp = *headptr;
            (*headptr) = (*headptr)->next;
            free(temp);
            (*headptr)->prev = NULL;
        }
    else if(index == count)
        {
            Node* cursor = *headptr;
            // Get last node in the list
            while(cursor->next != NULL)
                {
                    cursor = cursor->next;
                }
                // Last node rearrange pointers
            Node* temp = cursor;
            data_Removed = temp->data;
            cursor->prev->next = NULL;
            free(temp); // delete node

        }
    else if(index <=0 || index > count)
        {
            // return null
           printf("Invalid index");
           data_Removed = NULL;
        }
        else
        {
            // Iterate and delete node at offset
            Node* cursor = *headptr;
                for(count > 1; --count;)
                    {
                        cursor = cursor->next;
                    }
                    // Have targeted node
            data_Removed = cursor->data;
            Node* temp = cursor;
            cursor->prev->next = temp->next;
            temp->next->prev = temp->prev;
            free(temp);

        }
}

/* void function inserts a node in a specific index */
void insert_Node(int index, int data,struct Node** headptr)
{
    int offset = index;
    int count = size(*headptr);
    if(offset <= 0 || offset > count)
        {
            printf("Invalid index");
        }
    else if(index == 1)
        {
            // Otherwise add node
            add_First( &(*headptr),data);

        }
    else if(index == size )
        {
            add_Last(&(*headptr),data);
        }
        else // Node is in between
            {
                Node* cursor = *headptr;
                for(offset > 1; --offset;)
                    {
                        cursor = cursor->next;
                    }
                // have pointer reassing node's ptr members
                Node* temp = create_Node(data);
                temp->next = cursor->next;
                temp->prev = cursor;
                cursor->next->prev = temp;
                cursor->next= temp;
            }

}

// Recursive node returning function, reverse linked list
Node* reverse(struct Node* cursor, struct Node** headptr)
{
    // If not empty iterate to next head
    if(cursor != NULL)
        {   // Traverse the list until end is reached
            Node* temp = reverse(cursor->next,&(*headptr));
            cursor->next = cursor->prev;
            cursor->prev = temp;
            // Check if temp is null, if so changed head address
            if(temp == NULL){*headptr = cursor; }
        }
        // If empty return null
        return cursor;
}


/* int returning function, searches data in the linked list
    returns a 0 if node not found 1 otherwise*/
bool search( Node* cursor, int data)
{
   while(cursor != NULL)
    {
        cursor = cursor->next;
        if(cursor->data == data){return 1;}
    }
    return 0;
}

/* Void function reassigns headptr to new node if empty otherwise new node is
    added at end of the list */
void add_Last(struct Node ** headptr, int data)
{
    // If list is emnpty
    if(*headptr == NULL)
        {
            *headptr = create_Node(data);
        }
    else
        {
            // The list is not empty find the last node on list
            Node* cursor = *headptr;
            while(cursor->next != NULL)
                {
                    // next node is empty we found the last node
                    cursor = cursor->next;
                }
            // We found the last node now create a new node
            cursor->next = create_Node(data);
            cursor->next->prev = cursor; // point to node prior
        }
}


/* Recursive function Traverses list and prints its data*/
void traverse(Node* cursor)
{
    if(cursor != NULL)
        {
            printf("[%d]--->",cursor->data);
            traverse(cursor->next);
        }
    else
        {
            printf("[NULL]");
        }
}



/* Node* returning function, initializes data members and returns a pointer
    to node allocated on the heap1*/
Node* create_Node(int data)
{
    Node* temp = malloc(sizeof(Node));
    temp->next = NULL;
    temp->prev = NULL;
    temp->data = data;
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
