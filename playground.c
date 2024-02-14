#include<stdio.h>

int main(){
	int a = 0x12345678;
	char *c = &a;
	printf("%x\n",*c);
	return 0;
}
