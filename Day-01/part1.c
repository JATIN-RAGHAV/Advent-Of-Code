#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>

int findFloor(char* s);

int main(){
	FILE* file = fopen("text.txt","r"); 

	if(file == NULL){
		perror("Could not open file");
		return 1;
	}

	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	rewind(file);

	char* buffer = malloc(length+1);

	fread(buffer, 1, length,file);

	printf("The floor is %d\n",findFloor(buffer));

	fclose(file);
}

int findFloor(char* s){
	int floor = 0;
	for(int i = 0;s[i] != '\0';i++){
		if(s[i] == '(')
			floor++;
		else if (s[i] == ')')
			floor--;
	}

	return floor;
}
