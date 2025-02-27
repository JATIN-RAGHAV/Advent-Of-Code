#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>

int solve(char *s,int len);
int findDiff(char *s);

int main(){
	FILE* file = fopen("text.txt", "r");

	fseek(file, 0,SEEK_END);
	int length = ftell(file);
	rewind(file);

	char *buffer = (char *)malloc(length+1);

	fread(buffer, 1, length, file);
	
	int ans = solve(buffer,length);
	printf("Ans: %d\n",ans);

	free(buffer);
	fclose(file);
}

int solve(char *s,int len){
	char line[500];
	int index = 0;
	int diff = 0;

	for(int i = 0;i<len;i++){
		if(s[i] != '\n')
			line[index++] = s[i];
		else{
			line[index] = '\0';
			diff += findDiff(line);
			index = 0;
		}
	}


	return diff;
}

int findDiff(char *s){
	int diff = 4;

	for(int i = 0;s[i] != '\0';i++){
		if(s[i] == '\\'){
			if(s[i+1] == '\\' || s[i+1] == '"'){
				diff += 2;
				i += 1;
			}else if(s[i+1] == 'x'){
				diff += 1;
				i += 3;
			}
		}
	}

	return  diff;
}
