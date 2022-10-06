#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct node
{
	union
	{
		double Vec[4];
		struct Coordinates
		{
			double xCor;
			double yCor;
			double zCor;
			double tCor;
		};
	} Vector4D;
	struct node* next;
}Node;

Node* addToTail(Node* head, Node* new)
{
	if (!head)
		head = new;
	else {
		Node* temp = head;
		while (temp->next!=NULL) {
			temp = temp->next;
		}
		temp->next = new;

	}
	return head;
}


Node* addToHead(Node* head, Node* new)
{
	if (!head)
		head = new;
	else {
		new->next = head;
		head = new;
	}
	return new;
}


Node* createNode(double xCor, double yCor, double zCor, double tCor)
{
	Node* new = calloc(1, sizeof(Node));
	if (!new) {
		printf("Allocation Failed!");
		exit(1);
	}

	new->Vector4D.xCor = xCor;
	new->Vector4D.yCor = yCor;
	new->Vector4D.zCor = zCor;
	new->Vector4D.tCor = tCor;
	return new;
}

int isCyclic(Node* head)
{
	Node* Fptr = head;
	Node* Sptr = head;
	while (Fptr->next != NULL && Fptr != NULL ) {
			Fptr = Fptr->next->next;
			Sptr = Sptr->next;
			if (Fptr == Sptr)
				return TRUE;
	}
	return FALSE;
}

int repairCyclic(Node* head) {

	Node* Fptr = head;
	Node* Sptr = head;
	do {
		Fptr = Fptr->next->next;
		Sptr = Sptr->next;
	} while (Fptr != Sptr);
	

	Node* ptr1 = Sptr;
	Node* ptr2 = Sptr;
	int k = 1;

	while (ptr1->next != ptr2) {
		ptr1 = ptr1->next;
		k++;
	}

	ptr1 = head;
	ptr2 = head;

	for (int i = 0; i < k; i++)
		ptr2 = ptr2->next;

	k = 1;

	while (ptr2 != ptr1) {
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
		k++;
	}

	while (ptr2->next != ptr1)
		ptr2 = ptr2->next;

		ptr2->next = NULL;
		return k;
}

Node* findCartesianDist(Node* head, double distance, double epsilon)
{

}

void main() {
	Node* a = createNode(1, 2, 3, 4);
	Node* b = createNode(5, 6, 7, 8);
	Node* c = createNode(7, 6, 5, 4);
	Node* d = createNode(1, 2, 3, 1);
	Node* e = createNode(11, 32, 56, 86);

	Node* head = NULL;
	head = addToHead(head, a);
	head = addToHead(head, b);
	head = addToHead(head, c);
	head = addToHead(head, d);
	head = addToTail(head, e);
	head->next->next->next->next = head->next->next;
	if (isCyclic(head))
		printf("There`s a cycle,in %d node",repairCyclic(head));
	else
		printf("There`s no cycle");

}