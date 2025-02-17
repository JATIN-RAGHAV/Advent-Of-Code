#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>

int findRibbonLength(char* s,int len);

int main(){
	FILE* fptr = fopen("text.txt","r");

	fseek(fptr, 1,SEEK_END);
	int length = ftell(fptr);
	rewind(fptr);

	char* buffer = (char *) malloc(length+1);
	fread(buffer, 1, length, fptr);

	int totalRibbon = findRibbonLength(buffer, length);
	printf("Total Ribbon: %d\n",totalRibbon);

	free(buffer);
	fclose(fptr);
}


int findRibbonLength(char* s,int len){
	char line[50];
	int index = 0;
	int totalRibbon = 0;
	for(int i =0; i<len;i++){
		if(s[i] != '\n')
			line[index++] = s[i];
		else{
			int length,breath,height;
			length = breath = height = 0;
			int state = 0;
			for(int j = 0;j<index;j++){
				if(line[j] == 'x')
					state++;
				else{
					switch (state) {
						case 0:
							length = length*10 + (line[j]-'0');
							break;
						case 1:
							breath = breath*10 + (line[j] - '0');
							break;
						case 2:
							height = height*10 + (line[j] - '0');
					}
				}
			}

			int wrappingRibbon;
			int bowRibbon = length * breath * height;
			if(length > height){
				if(length>breath)
					wrappingRibbon = 2*(height+breath);
				else
					wrappingRibbon = 2*(height+length);
			}else{
				if(height>breath)
					wrappingRibbon = 2*(length+breath);
				else
					wrappingRibbon = 2*(height+length);
			}
			totalRibbon += bowRibbon + wrappingRibbon;
			index = 0;
		}
	}
	return totalRibbon;
}
