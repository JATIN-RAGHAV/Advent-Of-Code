#include "stdio.h"
#include "stdlib.h"
#include <stdio.h>
#include <stdlib.h>

int findFirstNegative(char* s,int len);

int main(){
	FILE* pfile = fopen("text.txt", "r");

	if(pfile == NULL){
		perror("Could not read file\n");
		return 1;
	}

	fseek(pfile, 1, SEEK_END);
	int length = ftell(pfile);
	rewind(pfile);

	char *buffer = malloc(length);
	if(buffer == NULL){
		perror("Don't have enough space\n");
		return 2;
	}

	fread(buffer, 1, length+1, pfile);

	int ans = findFirstNegative(buffer, length);
	printf("Ans: %d\n",ans);

	free(buffer);
	fclose(pfile);
}

int findFirstNegative(char* s,int len){
	int floor = 0;
	for(int i = 0;i<len;i++){
		if(s[i] == ')')
			floor--;
		else
			floor++;
		if(floor<0)
			return i+1;

	}
	return -1;
}
