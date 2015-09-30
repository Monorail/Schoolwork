
typedef struct node
{
    // each node holds a single character
    char data;

    // pointer to next node in linked list
    struct node *next;
} node;
node *insert(node *head, int data)
{
    node *temp;
    for(temp=head; temp->next!=NULL; temp=temp->next);
    temp->next=malloc(sizeof(node));
    temp->data;
    temp->next.next=NULL;
    return head;
}
node *createNode(int data)
{
    //prof's code
    node *ptr = malloc(sizeof(node));
    ptr->data = data;
    ptr->next = NULL;
    return ptr;
}

int main(void)
{
    node *herp = createNode(5);
    herp = insert(5);



    return 0;
}
