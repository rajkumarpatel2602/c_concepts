#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// This program will store size-1 members in circular queue
// one place will always be empty as this algo makes sure
// that tail pointer always point to an empty location.
// and empty list condition is when head==tail.
// One can change make use of empty place as well,
// but then our is_full and is_empty conditions would be same
// in this case, one has to make sure to pad UNUSUAL number
// e.g. -1 while emptying fields.
// this will allow us to bifurcate in filled and empty condition

// Circular queue data structure
int arr[10] = {0};
unsigned int head = 0;
unsigned int tail = 0;
unsigned int size_arr = sizeof(arr)/sizeof(int);

// forward declaration
int filled_count(int arr[]);

void print_all(int arr[]){
	int temp = head;
	printf("filled count : %d\n", filled_count(arr));
	while(temp  != tail){
		printf("%d ->", arr[temp]);
		temp = (temp + 1)%size_arr;
	}
	printf("\n");
}

bool is_full(int arr[]){
	if (head == (1 + tail) % size_arr){
		printf("List is full!\n");
		return true;
	}
	else{
		return false;
	}
}

bool is_empty(int arr[]){
	if (head == tail % size_arr){
		printf("List is empty!\n");
		return true;
	}
	else{
		return false;
	}
}

int filled_count(int arr[]){
	int cnt = 0;
	int temp = head;
	while(temp != tail){
		temp++;
		if(temp >= size_arr)
			temp = temp % size_arr;	
		cnt++;
	}
	return cnt;
}

bool push_queue(int arr[], int data){
	if (is_full(arr)){
		return false;
	}
	arr[tail] = data;
	tail = (tail+1)%size_arr;
	print_all(arr);
	return true;
}

int pop_queue(int arr[]){
	if (is_empty(arr)){
		return false;
	}
	int ret = arr[head];
	head = head+1;
	print_all(arr);
	return ret;
}


int main(int argc, char* argv[]){
	printf("is list empty ? : %s\n", (is_empty(arr) ? "true" : "false"));
	push_queue(arr, 101);
	push_queue(arr, 102);
	push_queue(arr, 103);
	push_queue(arr, 104);
	push_queue(arr, 105);
	push_queue(arr, 106);
	push_queue(arr, 107);
	push_queue(arr, 108);
	push_queue(arr, 109);
	push_queue(arr, 110);
	pop_queue(arr);
	pop_queue(arr);
	pop_queue(arr);
	pop_queue(arr);
	pop_queue(arr);
	pop_queue(arr);
	push_queue(arr, 6);
	push_queue(arr, 7);
	push_queue(arr, 8);
	push_queue(arr, 9);
	push_queue(arr, 10);
}