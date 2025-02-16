#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>

int findWrappingPaper(char *s,int len);

int main(){
	FILE *fptr = fopen("text.txt", "r");
	if(fptr == NULL){
		perror("Could not read file\n");
		return 1;
	}

	fseek(fptr, 1, SEEK_END);
	int length = ftell(fptr);
	rewind(fptr);

	char *buffer = malloc(length+1);
	if(buffer == NULL){
		perror("Don't have enough storage\n");
		return 2;
	}

	fread(buffer, 1, length, fptr);

	int ans = findWrappingPaper(buffer, length);
	printf("Ans: %d\n",ans);

	free(buffer);
	fclose(fptr);
}


int findWrappingPaper(char *s,int len){
	char line[100];
	line[99] = '\0';
	int index = 0;
	int totalAns = 0;
	for(int i =0; i<len;i++){
		if(s[i] != '\n')
			line[index++] = s[i];
		else{
			int length,breath,height;
			length = breath = height = 0;
			int side = 0;
			for(int j = 0;j<index;j++){
				if(line[j] == 'x')
					side++;
				else{
					switch (side) {
						case 0:
							length = length*10 + (line[j] - '0');
							break;
						case 1:
							breath = breath*10 + (line[j] - '0');
							break;
						case 2:
							height = height *10 + (line[j] - '0');
							break;
					}
				}
			}
			int totalSurfaceArea = 2*(length*breath) + 2*(breath*height) + 2*(length*height);
			int additionalArea;
			if(length>height)
				if(length>breath)
					additionalArea = breath*height;
				else
					additionalArea = height*length;
			else
				if(height>breath)
					additionalArea = length*breath;
				else
					additionalArea = length*height;

			totalAns += additionalArea+totalSurfaceArea;
			index = 0;
		}
	}
	return totalAns;
}
