#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
    int ID;
} node;
int IDCTR = 0;

node* add(node* head, int data);
void printLL(node* head);
node* reallocReverse(node* head);
node* reverse(node* head);

node* add(node* head, int data){
    node* temp = malloc(sizeof(node));
    temp->data = data;
    temp->ID = IDCTR;
    IDCTR++;
    if(head == NULL){
        temp->next = NULL;
        return temp;
    }

    temp->next = head;
    return temp;
}

void printLL(node* head){
    node* temp = head;
    for(;temp != NULL; temp = temp->next){
        printf("%d ", temp->data);
    }
    printf("\n");
}

node* reallocReverse(node* head){
    if(head == NULL){
        return head;
    }
    if(head->next == NULL){
        node* temp = add(temp, head->data);
        printf("(%d, %d) ", temp->data, temp->ID);
        return temp;
    }
    node* temp = reallocReverse(head->next);
    temp = add(temp, head->data);
    printf("(%d, %d) ", temp->data, temp->ID);
    return temp;
}

node* reverse(node* head){
    if(head == NULL){
        return head;
    }
    if(head->next == NULL){
        return head;
    }
    //build up recursive list
    node* ret = reverse(head->next);
    //perform reversal
    node* temp = head->next;
    temp->next = head;
    head->next = NULL;
    //pass through last element b/w return calls
    return ret;
}

int main(){
    node* head = NULL;
    head = add(head, 1);
    head = add(head, 2);
    head = add(head, 3);
    head = add(head, 4);
    head = add(head, 5);
    //head = reallocReverse(head);
    printLL(head);
    head = reverse(head);
    // node* temp = head->next;
    // head->next = NULL;
    // temp->next = head;
    // head = temp;
    printLL(head);
    return 0;
}
