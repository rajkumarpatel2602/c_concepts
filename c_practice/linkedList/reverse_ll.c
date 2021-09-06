#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node *next;
}node_t;

void print_ll(node_t *head){
	node_t *temp = head;
	printf("node data is : \n");
	while(temp){
		printf("%d ->", temp->data);
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

node_t *head= NULL;

//node_t *reverse_ll(node_t *node){
//	node_t *temp = node;
//	if(temp->next != NULL){
//		(reverse_ll(temp->next))->next = temp;
//	}else{
//		head = temp;
//	}
//	return temp;
//}

// without temp variable
node_t *reverse_ll(node_t *root){
	if(root->next != NULL){
		reverse_ll(root->next);
		root->next->next = root;
		return root;
	}else{
		head = root;
	}
}

int main(int argc, char* argv[]){
	add_ll(&head, 10);
	add_ll(&head, 20);
	add_ll(&head, 30);
	add_ll(&head, 40);
	add_ll(&head, 50);
	add_ll(&head, 60);
	printf("After adding all elements!\n");
	print_ll(head);
	(reverse_ll(head))->next = NULL;
	printf("After reversing all elements!\n");
	print_ll(head);
}