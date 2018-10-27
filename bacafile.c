#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	FILE *fs;
	char ch;
	int num;
	fs = fopen("test.txt", "r");
	ch = fgetc(fs);
	num = atoi(&ch);
	num = num + 10;
	printf("The added number is: %d\n", num);
}
