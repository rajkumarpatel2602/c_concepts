#include <stdio.h>
#include <stdlib.h>

//sorts data while adding to the __gnuc_va_list
//and then remove the duplicate entries 
//
//output of the program 
//node data : 0
//node data : 5
//node data : 10
//node data : 20
//node data : 30
//node data : 120
//After removing duplicates
//
//node data : 5
//node data : 10
//node data : 30
//node data : 120


typedef struct node{
	int data;
	struct node *next;
}node_t;

void print_ll(node_t *head){
	node_t *temp = head;
	while(temp){
		printf("\nnode data : %d\n", temp->data);
		temp = temp->next;
	}
}

void add_ll(node_t **head, int data){
	node_t *Node = (node_t *)malloc(sizeof(struct node));
	if(Node == NULL){
		printf("Allocation failed\n");
	}
	Node->data = data;
	Node->next = NULL;
	if(*head == NULL || (*head)->data > data){
		Node->next = *head;
		*head = Node;
	}
	else{
		node_t *temp = *head;
		while ((temp->next != NULL) && (temp->next->data < data) ){
			temp = temp->next;
		}
		Node->next = temp->next;
		temp->next = Node;
	}
}

void remove_duplicates(node_t **head){
	node_t *temp = *head;
	node_t *p_follow = NULL;
	if (temp == NULL) return;
	while(temp->next != NULL){
		if(temp->data == temp->next->data){
			node_t *node_ptr = temp->next->next;
			free(temp->next);
			temp->next = node_ptr;
		}else{
			temp = temp->next;
		}
	}
}


node_t *head= NULL;

int main(int argc, char* argv[]){
	add_ll(&head, 10);
	add_ll(&head, 30);
	add_ll(&head, 30);
	add_ll(&head, 120);
	add_ll(&head, 5);
	add_ll(&head, 5);
	add_ll(&head, 30);
	add_ll(&head, 30);
	add_ll(&head, 120);
	add_ll(&head, 10);
	add_ll(&head, 120);
	print_ll(head);
	remove_duplicates(&head);
	printf("\nAfter removing duplicates\n");
	print_ll(head);
}