#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node *next;
}node_t;

node_t *head= NULL;
node_t *tail = NULL;

void print_ll(node_t *head){
	node_t *temp = head;
	while(temp){
		printf("node data : %d\n", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

int dequeue_ll(node_t **head){
	int ret = -1;
	if(*head){
		ret = (*head)->data;
		node_t *temp = *head;
		*head = (*head)->next;
		free(temp);
	}
	return ret;
}

void enqueue_ll(node_t **head, int data){
	node_t *Node = (node_t *)malloc(sizeof(struct node));
	if(Node == NULL){
		printf("Allocation failed\n");
	}
	Node->data = data;
	Node->next = NULL;
	if(*head == NULL){
		*head = Node;
		tail = Node;
	}
	else{
		tail->next = Node;
		tail = Node;
	}
	return;
}

int main(int argc, char* argv[]){
	
	enqueue_ll(&head, 10);
	enqueue_ll(&head, 20);
	enqueue_ll(&head, 30);
	enqueue_ll(&head, 40);
	enqueue_ll(&head, 50);
	enqueue_ll(&head, 60);
	printf("\nAfter enqueue\n");
	print_ll(head);
	printf("dequeued value is :%d\n", dequeue_ll(&head));
	printf("dequeued value is :%d\n", dequeue_ll(&head));
	printf("dequeued value is :%d\n", dequeue_ll(&head));
	printf("\nAfter dequeue\n");
	print_ll(head);
}