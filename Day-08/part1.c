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
	int codeCount, stringCount;
	codeCount = stringCount = 0;

	for(int i = 0;s[i] != '\0';i++){
		codeCount++;
		if(s[i] >= 'a' && s[i] <= 'z')
			stringCount++;
		else{
			if(s[i] == '\\'){
				stringCount++;
				if(s[i+1] == '\\' || s[i+1] == '"'){
					codeCount += 1;
					i += 1;
				}else if(s[i+1] == 'x'){
					codeCount += 3;
					i += 3;
				}
			}
		}
	}

	return codeCount - stringCount;
}
