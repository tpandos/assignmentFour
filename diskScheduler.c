#include <stdlib.h> 
#include <time.h> 
#include <stdio.h>

void fcfs(int arr[], int elements, int heads);
void sstf(int arr[], int elements,int heads);

struct Node{
    int data; 
    struct Node *prev; 
    struct Node *next; 
};
void append(struct Node** head_ref, int new_data);
void deleteNode(struct Node** head_ref, struct Node* del);
void printList(struct Node* head);


int main()
{

    int h = 53; // head 

    srand(time(NULL)); 
    int random = rand() % 1000; 
    printf("random number is : %d\n", random); 

    // get a list of 10 random numbers 
    int q[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int s[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int size = 8; 

    //fcfs(q, size, h); 
   
    sstf(s, size, h); 

    return 0; 

}
// first come first serve FCFS
void fcfs(int arr[], int elements, int heads)
{

    int cylinders = 0; 

    //initial cylinders 
    cylinders = abs(heads - arr[0]); 
    printf("Cyclinders: %d\n", abs(heads - arr[0])); 
    
    for(int i = 0; i < elements -1;  i++)  // i < (array length - 1)
    {
        
            cylinders = cylinders + abs(arr[i+1] - arr[i]); 
             printf("Cyclinders: %d\n", abs(arr[i+1] - arr[i] )); 

    }

    printf("Total Cyclinders: %d\n", cylinders); 
}

// SSTF

void sstf(int arr[], int elements,int heads)
{
    struct Node* head = NULL; 

    for(int i = 0; i < elements; i++)
    {
        append(&head, arr[i]); 
    }

    printList(head); 

     for(int i = 0; i < elements; i++)
    {
        deleteNode(&head, head); 
    }

    
}

void append(struct Node** head_ref, int new_data) 
{ 
    /* 1. allocate node */
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node)); 
  
    struct Node* last = *head_ref; /* used in step 5*/
  
    /* 2. put in the data  */
    new_node->data = new_data; 
  
    /* 3. This new node is going to be the last node, so 
          make next of it as NULL*/
    new_node->next = NULL; 
  
    /* 4. If the Linked List is empty, then make the new 
          node as head */
    if (*head_ref == NULL) { 
        new_node->prev = NULL; 
        *head_ref = new_node; 
        return; 
    } 
  
    /* 5. Else traverse till the last node */
    while (last->next != NULL) 
        last = last->next; 
  
    /* 6. Change the next of last node */
    last->next = new_node; 
  
    /* 7. Make last node as previous of new node */
    new_node->prev = last; 
    return; 
}

void deleteNode(struct Node** head_ref, struct Node* del) 
{ 
    /* base case */
    if (*head_ref == NULL || del == NULL) 
        return; 
  
    /* If node to be deleted is head node */
    if (*head_ref == del) 
        *head_ref = del->next; 
  
    /* Change next only if node to be deleted is NOT  
       the last node */
    if (del->next != NULL) 
        del->next->prev = del->prev; 
  
    /* Change prev only if node to be deleted is NOT  
       the first node */
    if (del->prev != NULL) 
        del->prev->next = del->next; 
  
    /* Finally, free the memory occupied by del*/
    free(del); 
} 

void printList(struct Node* head) 
{ 
    int start = 53; 
    
    int distance = 10000; 
    int dif; 
    while (head != NULL) { 
        printf("%d\n", head->data);
        dif = abs(head->data - start); 
        if(dif < distance){
            distance = dif;
            start = head->data;  
        }
        
        
        head = head->next; 

    } 


    printf("distance %d\n", distance); 

} 