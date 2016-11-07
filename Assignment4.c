#include<stdio.h>
#include<stdlib.h>

struct Node  {
	int size;
    char id;
	struct Node* next;
	struct Node* prev;
};

struct Node* head;
struct Node* temp;

struct Node* GetNewNode(char id, int size) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->size = size;
    newNode->id = id;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

void InsertAtTail(char id, int size) {
	struct Node* temp = head;
	struct Node* newNode = GetNewNode(id, size);
	if(head == NULL) {
		head = newNode;
		return;
	}
	while(temp->next != NULL) temp = temp->next;
	temp->next = newNode;
	newNode->prev = temp;
}

void releaseNode(char x)
{
    struct Node* temp = head;
    while (temp->id != x)
    {
        temp = temp->next;
    }
    temp->id = '*';
}

void combineNodes()
{
    int storedmem, onemem, twomem;
    struct Node* temp = head;
    struct Node* one;
    struct Node* two;
    while (temp->id != '*')
    {
        temp = temp->next;
    }
    one = temp;
    two = temp->prev;
    temp = temp->next;
    if (temp->id == '*')
    {
        onemem = one->size;
        twomem = temp->size;
        storedmem = onemem + twomem;
        InsertAtTail('*', storedmem);
        if (head == one)
        {
            head = one->next;
        }
        if(head == temp)
        {
            head = temp->next;
        }
        temp = temp->next;
        one->next = temp;
        //two->next = temp;
    }

}

void FirstFit(char id, int size)
{
    int extramem, currentmem;
    struct Node* temp = head;
    while (temp->size < size || temp->id != '*')
    {
        temp = temp->next;
    }

    if (temp->size >= size)
    {
        currentmem = temp->size;
        extramem = currentmem - size;
        if (extramem > 0)
        {
            InsertAtTail('*', extramem);
        }
    }

    temp->id = id;
    temp->size = size;
}

void BestFit(char id, int size)
{
    int extramem, currentmem;
    struct Node* temp = head;
    while (temp->size < size || temp->id != '*')
    {
        temp = temp->next;
    }

    if (temp->size == size )
    {
        temp->id = id;
        temp->size = size;
    }

    if (temp->size == size + 1)
    {
        currentmem = temp->size;
        extramem = currentmem - size;
        if (extramem > 0)
        {
            InsertAtTail('*', extramem);
        }
        temp->id = id;
        temp->size = size;
    }

    if (temp->size == size + 2)
    {
        currentmem = temp->size;
        extramem = currentmem - size;
        if (extramem > 0)
        {
            InsertAtTail('*', extramem);
        }
        temp->id = id;
        temp->size = size;
    }
}

void NextFit(char id, int size)
{
    int extramem, currentmem;
    struct Node* temp = head;
    while (temp->size < size || temp->id != '*')
    {
        temp = temp->next;
    }

    if (temp->size >= size)
    {
        currentmem = temp->size;
        extramem = currentmem - size;
        if (extramem > 0)
        {
            InsertAtTail('*', extramem);
        }
    }

    temp->id = id;
    temp->size = size;
}

void Print() {
	struct Node* temp = head;
	while(temp != NULL) {
          printf("(%c ",temp->id);
		printf("%d)",temp->size);
		temp = temp->next;
	}
	printf("\n");
}

int main() {

	head = NULL;

    InsertAtTail('*',1);
    InsertAtTail('A',4);
    InsertAtTail('*',2);
    InsertAtTail('B',1);
    InsertAtTail('*',2);
    InsertAtTail('C',5);
    InsertAtTail('*',1);
    InsertAtTail('D',8);
    InsertAtTail('*',2);
    InsertAtTail('E',2);
    InsertAtTail('*',1);
    InsertAtTail('F',4);
    InsertAtTail('*',2);
    InsertAtTail('G',3);
    InsertAtTail('*',5);

    printf("Initial List: \n");
    Print();
    printf("\n");
    releaseNode('A');
    printf("Relased A: \n");
    Print();
    printf("\n");
    combineNodes();
    printf("Combined adjacent free spaces: \n");
    Print();
    printf("\n");
    FirstFit('Z', 5);
    printf("Placed Z as a 5m size: \n");
    Print();
    printf("\n");
    FirstFit('Y', 2);
    printf("Placed Y as a 2m size: \n");
    Print();
    printf("\n");
    printf("Released C: \n");
    releaseNode('C');
    Print();
    printf("\n");
    printf("Combinging adjacent free spaces: \n");
    combineNodes();
    Print();
    printf("\n");
    printf("Placing X as a 6m size: \n");
    BestFit('X', 6);
    combineNodes();
    Print();
    printf("\n");
    printf("Placing W as a 4m size \n");
    NextFit('W', 4);
    Print();
    printf("\n");

    return 0;

}
