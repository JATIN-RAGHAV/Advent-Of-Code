#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>

int findSum(char *s);

int main(){
	FILE* file = fopen("text.txt", "r");

	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	rewind(file);

	char*buffer = (char*)malloc(length+1);
	fread(buffer,1,length,file);

	int sum = findSum(buffer);
	printf("Sum: %d\n",sum);

	free(buffer);
	fclose(file);
}

int findSum(char *s){
	int sum = 0;
	char num[10];
	int index = 0;
	for(int i = 0;s[i] != 0;i++){
		if((s[i] >= '0' && s[i] <= '9') || s[i] == '-')
			num[index++] = s[i];
		else{
			num[index] = 0;
			sum += atoi(num);
			index = 0;
		}
	}

	return sum;
}


