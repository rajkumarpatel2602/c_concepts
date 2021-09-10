#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node *next;
}node_t;

void print_ll(node_t *head){
	node_t *temp = head;
	while(temp){
		printf("node data : %d\n", temp->data);
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

int find_node(node_t *head, int pos){
	node_t *back = head, *front = head;
	int cnt = 0;
	while(cnt < pos){
		cnt++;
		//front can point to last node at most
		//return in case it reaches to NULL
		if((front = front->next) == NULL) return -1;
	}

	printf("cnt is %d\n", cnt);

	//increament front till the last node
	while(front = front->next){
		//start progressing with back pointer too
	 	back = back->next;
	}
	return back->data;
}

node_t *head= NULL;

int main(int argc, char* argv[]){
	int pos = -1;
	add_ll(&head, 10);
	add_ll(&head, 20);
	add_ll(&head, 30);
	add_ll(&head, 40);
	add_ll(&head, 50);
	add_ll(&head, 60);
	print_ll(head);
	printf("Enter the position from the last to get that node's data :\n");
	scanf("%d", &pos);
	int ret = find_node(head, pos);
	if(-1 == ret){
		printf("given position is not present\n");
	}else{
		printf("Required node-data is : %d\n", ret);
	}
}