#include<stdio.h>
#include "Memory.h"
#include "Stack.h"
#define STACK_SIZE 16

Address stack[STACK_SIZE];
int top = -1;

void s_push(Address val){
	if(top == STACK_SIZE-1){
		printf("stack is full!!");
		return;
	}

	top++;
	stack[top] = val;
}

Address s_pop(){
	if(top==-1){
		printf("stack is empty!!");
		return 0;
	}

	Address popped_val = stack[top];
	top--;
	return popped_val;
}

Address get_s_top(){
	if(top == -1){
		printf("stack is empty!!");
		return 0;
	}
	if(top == STACK_SIZE-1){
		printf("stack is full!!");
		return 0;
	}
	return stack[top];
}

void print_s(){
	for(int i=0;i<top;i++) printf("%d --> %d\n",i,stack[i]);
}
 
// int main(){
	// s_push(3);
	// s_push(2);
	// s_push(1);
	// printf("%d\n",get_s_top());
	// s_pop();
	// printf("%d\n",get_s_top());
	// print_s();
	// return 0;
// }
