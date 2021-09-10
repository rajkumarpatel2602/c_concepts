#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
	int data;
	struct node *next;
}node_t;

node_t *top = NULL;

void print_ll(node_t *top){
	node_t *temp = top;
	while(temp){
		printf("node data : %d\n", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

bool is_empty(node_t *top){
	if(top == NULL){
		return true;
	}
	else{
		return false;
	}
}

int pop_ll(node_t **top){
	int ret = -1;
	if (!is_empty(*top)){
		ret = (*top)->data;
		node_t *temp = *top;
		*top = (*top)->next;
		free(temp);
	}
	return ret;
}

void push_ll(node_t **top, int data){
	node_t *Node = (node_t *)malloc(sizeof(struct node));
	if(Node == NULL){
		printf("Allocation failed\n");
	}
	Node->data = data;
	Node->next = NULL;
	if(*top == NULL){
		*top = Node;
		return;
	}
	Node->next  = *top;
	*top = Node;
	return;
}

int main(int argc, char* argv[]){	
	push_ll(&top, 10);
	push_ll(&top, 20);
	push_ll(&top, 30);
	push_ll(&top, 40);
	push_ll(&top, 50);
	push_ll(&top, 60);
	printf("\nAfter Push\n");
	print_ll(top);
	printf("poped value is : %d\n", pop_ll(&top));
	printf("poped value is : %d\n", pop_ll(&top));
	printf("poped value is : %d\n", pop_ll(&top));
	printf("\nAfter Pop\n");
	print_ll(top);
}