#include <stdio.h>
#include <stdlib.h>

// Program to read singly linkedList backward
// recursion method
//
//output
//Reading the list forward
//10 -> 20 -> 30 -> 40 -> 50 -> 60 ->
//
//Reading the list backward
//60 <- 50 <- 40 <- 30 <- 20 <- 10 <-

typedef struct node{
	int data;
	struct node *next;
}node_t;

void print_ll(node_t *head){
	node_t *temp = head;
	while(temp){
		printf(" %d ->", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

void add_ll(node_t **head, int data){
	node_t *Node = (node_t *)malloc(sizeof(struct node));
	if(Node == NULL){
		printf("Allocation failed\n");
	}
	Node->data = data;
	Node->next = NULL;
	if (*head == NULL){
		*head = Node; 
	}
	else{
		node_t *temp = *head;
		while(temp->next){
			temp = temp->next;
		}
		temp->next = Node;
	}
}

void read_ll_backwards(node_t *head){
	if(head){
		read_ll_backwards(head->next);
		printf("%d <- ", head->data);
	}
	return; 
}

node_t *head= NULL;

int main(int argc, char* argv[]){
	add_ll(&head, 10);
	add_ll(&head, 20);
	add_ll(&head, 30);
	add_ll(&head, 40);
	add_ll(&head, 50);
	add_ll(&head, 60);
	print_ll(head);
	printf("\nReading the list backward\n");
	read_ll_backwards(head);
}