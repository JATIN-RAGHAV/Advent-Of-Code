#include "stdio.h"

#define SUM 2020

int main () {
	FILE *fileptr;
	fileptr = fopen("text.txt", "r");
	if(fileptr != NULL){
		int c;
		int nums[201];
		for(int i = 0; i<201;i++)
			nums[i] = 0;
		int index = 0;

		while(( c = fgetc(fileptr)) != EOF){
			if(c == '\n')
				index++;
			else
				nums[index] = (nums[index] * 10) + c - '0';
		}

		for(int i = 0; i<index-1;i++){
			for(int j = i+i; j<index;j++){
				if(nums[i] + nums[j] == SUM){
					printf("%d\n",nums[i] * nums[j]);
					return 0;
				}
			}
		}
	}
};
