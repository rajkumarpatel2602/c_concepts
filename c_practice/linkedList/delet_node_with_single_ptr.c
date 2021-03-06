#include <stdio.h>
#include <stdlib.h>

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


// with a single pointer
// this won't work for last node.
void delete_node(node_t **head, int data){
	//if node is headnode
	if (*head == NULL){
		printf("List is empty!\n");
	}
	node_t *temp = *head;// temp is holding address of head
	// modifying temp will also make change in head.
	for( ; temp->data != data; temp = temp->next);
	if(temp->next != NULL){
		printf("tmep is :%p\n", temp);
		printf("head is :%p\n", *head);
		node_t *p_del = temp->next;
		temp->data = temp->next->data;
		temp->next = temp->next->next;
		free(p_del);
	}
	else{
		printf("No such element found!\n");
	}
}


// code with slow and fast pointers
//void delete_node(node_t **head, int data){
//	//if node is headnode
//	node_t *slow = NULL, *fast = *head;
//	for(; fast && (fast->data != data); slow = fast, fast = fast->next);
//	if(fast != NULL){
//		if (fast == *head){
//			*head = fast->next;
//		}
//		else{
//			slow->next = fast->next;
//			free(fast);
//		}
//	}else{
//		printf("No such node found\n");
//	}
//}

int main(int argc, char* argv[]){
	node_t *head= NULL;
	add_ll(&head, 10);
	add_ll(&head, 20);
	add_ll(&head, 30);
	add_ll(&head, 40);
	add_ll(&head, 50);
	add_ll(&head, 60);
	int num=0;
	printf("Enter number to delete!\n");
	scanf("%d", &num);
	printf("Before deletion of %d\n", num);
	print_ll(head);
	delete_node(&head, num);
	printf("After deletion of %d\n", num);
	print_ll(head);
}