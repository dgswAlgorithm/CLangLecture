#include <stdio.h>

typedef struct {
    int x;
    int y;
}point;

int main()
{
    point p1;
    p1.x = 2;
    p1.y = 3;
    printf("%d %d\n", p1.x, p1.y);
    return 0;
}


////////////////////////////////////////////////


#define _CRT_SECURE_NO_WARNINGS   
#include <stdio.h>
#include <string.h>  
#include <stdlib.h>  

typedef struct {
    char name[20];
    int age;
    char address[100];
}Person;

int main()
{
    Person* kim = malloc(sizeof(Person));
    strcpy(kim->name, "동균");
    kim->age = 20;
    strcpy(kim->address, "김해시 외동");

    printf("이름: %s\n", kim->name);
    printf("나이: %d\n", kim->age);
    printf("주소: %s\n", kim->address);

    free(kim);

    return 0;
}


////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[20];
    int* age;
}Person;

int main()
{
    int myAge = 20;
    Person kimA;
    Person* kimB = malloc(sizeof(Person));

    kimA.age = &myAge;
    kimB->age = &myAge; //(*kimB).age = &myAge;

    printf("나이 : %d\n", *kimA.age);
    printf("나이 : %d\n\n", *kimB->age);

    strcpy(kimB->name, "KimDongGyun");
    printf("이름 : %s\n", (*kimB).name);
    printf("나이 : %d\n", *(*kimB).age);

    //printf("이름 : %s\n", *kimB->name); 퀴즈 : 에러가 발생하는 이유는? 
    //printf("나이 : %d\n", kimB->age); 퀴즈 : 실행 결과가 10484812가 나왔다면 그 이유는?


    free(kimB);

    return 0;
}

//////////////////////////////////


#include <stdio.h> 
#include <stdlib.h> 


struct QNode {
	int key;
	struct QNode* next;
};

struct Queue {
	struct QNode* front, * rear;
};

// A utility function to create a new linked list node. 
struct QNode* newNode(int k)
{
	struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
	temp->key = k;
	temp->next = NULL;
	return temp;
}

// A utility function to create an empty queue 
struct Queue* createQueue()
{
	struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
	q->front = q->rear = NULL;
	return q;
}

// The function to add a key k to q 
void enQueue(struct Queue* q, int k)
{
	// Create a new LL node 
	struct QNode* temp = newNode(k);

	// If queue is empty, then new node is front and rear both 
	if (q->rear == NULL) {
		q->front = q->rear = temp;
		return;
	}

	// Add the new node at the end of queue and change rear 
	q->rear->next = temp;
	q->rear = temp;
}

// Function to remove a key from given queue q 
void deQueue(struct Queue* q)
{
	// If queue is empty, return NULL. 
	if (q->front == NULL)
		return;

	// Store previous front and move front one node ahead 
	struct QNode* temp = q->front;

	q->front = q->front->next;

	// If front becomes NULL, then change rear also as NULL 
	if (q->front == NULL)
		q->rear = NULL;

	free(temp);
}

// Driver Program to test anove functions 
int main()
{
	struct Queue* q = createQueue();
	enQueue(q, 10);
	enQueue(q, 20);
	deQueue(q);
	deQueue(q);
	enQueue(q, 30);
	enQueue(q, 40);
	enQueue(q, 50);
	deQueue(q);
	printf("Queue Front : %d \n", q->front->key);
	printf("Queue Rear : %d\n", q->rear->key);
	return 0;
}

////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

typedef struct _polyNode {
	int coef;
	int expon;
	struct polyNode* link;
} polyNode;


typedef struct _sList {
	int size;
	polyNode* head;
	polyNode* tail;
} sList;

void error(char* str)
{
	fprintf(stderr, "%s\n", str);
	exit(1);
}

//  리스트 헤더 생성 함수
sList* create()
{
	sList* node = (sList*)malloc(sizeof(sList));
	node->size = 0;
	node->head = node->tail = NULL;
	return node;
}

void insertNode(sList* node, int c, int e)
{
	polyNode* temp = (polyNode*)malloc(sizeof(polyNode));
	if (temp == NULL) error("메모리 할당 에러");
	temp->coef = c;
	temp->expon = e;
	temp->link = NULL;
	if (node->tail == NULL) {
		node->head = node->tail = temp;
	}
	else {
		node->tail->link = temp;
		node->tail = temp;
	}
	node->size++;
}

// d = a + b
void poly_add(sList* aPoly, sList* bPoly, sList* dPoly)
{
	polyNode* a = aPoly->head;
	polyNode* b = bPoly->head;
	int sum;

	while (a && b) {
		if (a->expon == b->expon) {
			sum = a->coef + b->coef;
			if (sum != 0) insertNode(dPoly, sum, a->expon);
			a = a->link; b = b->link;
		}
		else if (a->expon > b->expon) {
			insertNode(dPoly, a->coef, a->expon);
			a = a->link;
		}
		else {
			insertNode(dPoly, b->coef, b->expon);
			b = b->link;
		}
	}

	for (; a != NULL; a = a->link)
		insertNode(dPoly, a->coef, a->expon);
	for (; b != NULL; b = b->link)
		insertNode(dPoly, b->coef, b->expon);
}


void poly_print(sList* node)
{
	polyNode* p = node->head;

	printf("polynomial = ");
	for (; p; p = p->link) {
		printf("%d^%d + ", p->coef, p->expon);
	}
	printf("\n");
}


int main(void)
{
	sList* a, * b, * d;


	a = create();
	b = create();
	d = create();

	// 다항식 생성 
	insertNode(a, 3, 12);
	insertNode(a, 2, 8);
	insertNode(a, 1, 0);


	insertNode(b, 8, 12);
	insertNode(b, -3, 10);
	insertNode(b, 10, 6);

	poly_print(a);
	poly_print(b);


	poly_add(a, b, d);
	poly_print(d);

	free(a); free(b); free(d);
}


///////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
	int data;
	struct Node* link;
} Node;

void printLinkedList(Node* head)
{
	Node* p;

	if (head == NULL) return;
	p = head->link;
	do {
		printf("%d->", p->data);
		p = p->link;
	} while (p != head);
	printf("%d->", p->data);
}

Node* insertFront(Node* head, int data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;
		head->link = node;
	}
	return head;
}

Node* insertLast(Node* head, int data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;
		head->link = node;
		head = node;
	}
	return head;
}

int main(void)
{
	Node* head = NULL;

	head = insertLast(head, 20);
	head = insertLast(head, 30);
	head = insertLast(head, 40);
	head = insertFront(head, 10);

	printLinkedList(head);
	return 0;
}



///////////////////////////////////////////




#include<stdio.h> 
#include<stdlib.h> 

/* structure for a node */
struct Node
{
	int data;
	struct Node* next;
};

// Function to insert a node at the beginning of a Circular linked list
void insertFront(struct Node** headNode, int data)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	struct Node* temp = *headNode;

	newNode->data = data;
	newNode->next = *headNode;

	/* If linked list is not NULL then set the next of last node */
	if (*headNode != NULL)
	{
		while (temp->next != *headNode)
			temp = temp->next;
		temp->next = newNode;
	}
	else
		newNode->next = newNode; /*For the first node */

	*headNode = newNode;
}

/* Function to print nodes in a given Circular linked list */
void printList(struct Node* head)
{
	struct Node* temp = head;
	if (head != NULL)
	{
		do
		{
			printf("%d ", temp->data);
			temp = temp->next;
		} while (temp != head);
	}
}

int main()
{
	/* Initialize lists as empty */
	struct Node* head = NULL;

	insertFront(&head, 12);
	insertFront(&head, 56);
	insertFront(&head, 2);
	insertFront(&head, 11);

	printf("Contents of Circular Linked List\n ");
	printList(head);

	return 0;
}



/////////////////////////////////////////////


#include<stdio.h> 
#include<stdlib.h> 


struct Node
{
	int data;
	struct Node* next;
};

void splitList(struct Node* head, struct Node** head1_ref, struct Node** head2_ref)
{
	struct Node* slow_ptr = head;
	struct Node* fast_ptr = head;

	if (head == NULL)
		return;

	/* If there are odd nodes in the circular list then
		fast_ptr->next becomes head and for even nodes
		fast_ptr->next->next becomes head */

	while (fast_ptr->next != head && fast_ptr->next->next != head)
	{
		fast_ptr = fast_ptr->next->next;
		slow_ptr = slow_ptr->next;
	}

	/* If there are even elements in list then move fast_ptr */
	if (fast_ptr->next->next == head)
		fast_ptr = fast_ptr->next;

	/* Set the head pointer of first half */
	*head1_ref = head;

	/* Set the head pointer of second half */
	if (head->next != head)
		*head2_ref = slow_ptr->next;

	/* Make second half circular */
	fast_ptr->next = slow_ptr->next;

	/* Make first half circular */
	slow_ptr->next = head;
}

//원형연결리스트의 앞쪽에 노드 삽입
void push(struct Node** head_ref, int data)
{
	struct Node* ptr1 = (struct Node*)malloc(sizeof(struct Node));
	struct Node* temp = *head_ref;
	ptr1->data = data;
	ptr1->next = *head_ref;

	/* If linked list is not NULL then set the next of last node */
	if (*head_ref != NULL)
	{
		while (temp->next != *head_ref)
			temp = temp->next;
		temp->next = ptr1;
	}
	else
		ptr1->next = ptr1; /*For the first node */

	*head_ref = ptr1;
}

/* Function to print nodes in a given Circular linked list */
void printList(struct Node* head)
{
	struct Node* temp = head;
	if (head != NULL)
	{
		printf("\n");
		do {
			printf("%d ", temp->data);
			temp = temp->next;
		} while (temp != head);
	}
}

int main()
{
	int list_size, i;

	/* Initialize lists as empty */
	struct Node* head = NULL;
	struct Node* head1 = NULL;
	struct Node* head2 = NULL;

	/* Created linked list will be 12->56->2->11 */
	push(&head, 12);
	push(&head, 56);
	push(&head, 2);
	push(&head, 11);

	printf("Original Circular Linked List");
	printList(head);

	/* Split the list */
	splitList(head, &head1, &head2);

	printf("\nFirst Circular Linked List");
	printList(head1);

	printf("\nSecond Circular Linked List");
	printList(head2);

	getchar();
	return 0;
}



////////////////////////////////////////

// C implementation to reverse a circular linked list 
#include <stdio.h> 


// Linked list node 
typedef struct _Node Node;
typedef struct _Node {
	int data;
	Node* next;
};

// function to get a new node 
Node* getNode(int data)
{
	// allocate memory for node 
	Node* newNode = (Node*)malloc(sizeof(Node));

	// put in the data 
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

// Function to reverse the circular linked list 
void reverse(Node** head_ref)
{
	// if list is empty 
	if (*head_ref == NULL)
		return;

	// reverse procedure same as reversing a 
	// singly linked list 
	Node* prev = NULL;
	Node* current = *head_ref;
	Node* next;
	do {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	} while (current != (*head_ref));

	// adjutsing the links so as to make the 
	// last node point to the first node 
	(*head_ref)->next = prev;
	*head_ref = prev;
}

// Function to print circular linked list 
void printList(Node* head)
{
	if (head == NULL)
		return;

	Node* temp = head;
	do {
		printf("%d  ", temp->data);
		temp = temp->next;
	} while (temp != head);
}

// Driver program to test above 
int main()
{
	// Create a circular linked list 
	// 1->2->3->4->1 
	Node* head = getNode(1);
	head->next = getNode(2);
	head->next->next = getNode(3);
	head->next->next->next = getNode(4);
	head->next->next->next->next = head;

	printf("Given circular linked list: ");
	printList(head);

	reverse(&head);

	printf("\nReversed circular linked list: ");
	printList(head);

	return 0;
}


///////////////////////////////////////


#include <stdio.h>
#define dim 3 // define dimension of matrix 

typedef struct _Node Node;
struct _Node {
	int data;
	Node* next;
	Node* prev;
	Node* up;
	Node* down;
};


Node* createNode(int data)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	temp->next = NULL;
	temp->prev = NULL;
	temp->up = NULL;
	temp->down = NULL;
	return temp;
}

//constructDoublyListUtil(mtrx, 0, 0, NULL);
Node* constructDoublyListUtil(int mtrx[][dim], int i, int j, Node* curr)
{
	if (i >= dim || j >= dim) {
		return NULL;
	}

	Node* temp = createNode(mtrx[i][j]);

	temp->prev = curr;
	temp->up = curr;

	// Recursive call 
	temp->next = constructDoublyListUtil(mtrx, i, j + 1, temp);
	temp->down = constructDoublyListUtil(mtrx, i + 1, j, temp);

	return temp;
}


Node* constructDoublyList(int mtrx[][dim])
{
	return constructDoublyListUtil(mtrx, 0, 0, NULL);
}

void display(Node* head)
{
	Node* rPtr;       // pointer to move right 
	Node* dPtr = head; // pointer to move down 

	// loop till node->down is not NULL 
	while (dPtr) {
		rPtr = dPtr;
		// loop till node->right is not NULL 
		while (rPtr) {
			printf("%d ", rPtr->data);
			rPtr = rPtr->next;
		}

		printf("\n");
		dPtr = dPtr->down;
	}
}

int main()
{
	int mtrx[dim][dim] = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 }
	};

	Node* list = constructDoublyList(mtrx);
	display(list);

	return 0;
}


//////////////////////////////////////


#include<stdio.h> 
#include<stdlib.h> 
struct node
{
	int data;
	struct node* left;
	struct node* right;
};

struct node* newNode(int data)
{
	struct node* node = (struct node*)malloc(sizeof(struct node));
	node->data = data;

	node->left = NULL;
	node->right = NULL;
	return(node);
}


int main()
{
	struct node* root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	root->left->left = newNode(4);
	return 0;
}



///////////////////////////////////////


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct course Course;
struct course {
	int marks;
	char subject[30];
};

int main() {
	Course* ptr;
	int i, num;
	printf("입력할 과목수는? ");
	scanf("%d", &num);

	ptr = (Course*)malloc(num * sizeof(Course));

	for (i = 0; i < num; ++i) {
		printf("교과목명과 점수를 입력하세요:\n");
		scanf("%s %d", (ptr + i)->subject, &(ptr + i)->marks);
	}

	printf("\n입력한 정보:\n");
	for (i = 0; i < num; ++i)
		printf("%s\t%d\n", (ptr + i)->subject, (ptr + i)->marks);

	return 0;
}


////////////////////////////////////////////////
