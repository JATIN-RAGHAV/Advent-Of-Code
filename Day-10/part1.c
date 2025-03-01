#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>

#define RUNS 50

char *initial = "1113222113";
char *load_and_say(char*s);

int main(){

	char *num = (char *)malloc(20);
	int i;
	for(i = 0;initial[i] != '\0';i++)
		num[i] = initial[i];
	num[i] = '\0';

	for(i = 0;i<RUNS;i++){
		num = load_and_say(num);
	}
	for(i = 0;num[i] != '\0';i++)
		;
	printf("Length: %d\n",i);
}

char *load_and_say(char*s){
	int i;
	for(i = 0;s[i] != '\0';i++)
		;
	char* returnStr = (char*)malloc(i*2);
	int index = 0;
	char current = s[0];
	int currentCount = 1;
	if(i == 1){
		returnStr[index++] = '1';
		returnStr[index++] = current ;
	}else{
		for(int j = 1;j<i;j++){
			if(s[j] == current)
				currentCount++;
			else{
				returnStr[index++] = currentCount + '0';
				returnStr[index++] = current;
				current = s[j];
				currentCount = 1;
			}
		}
		returnStr[index++] = currentCount + '0';
		returnStr[index++] = current;
	}
	
	returnStr[index++] = '\0';
	free(s);
	return returnStr;
}
