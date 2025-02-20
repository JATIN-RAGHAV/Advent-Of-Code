#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char act;
	unsigned int range[2][2];
} move;

unsigned char lights[1000][1000];

int tellTotalBrightness(char *s);
move findMove(char *ins, int len);
void makeMove(move move);
int findTotalBrightness();


int main(){
	FILE* file = fopen("text.txt", "r");

	fseek(file,0, SEEK_END);
	int length = ftell(file);
	rewind(file);

	char *buffer = (char*)malloc(length+1);
	fread(buffer, 1, length, file);

	int totalBrightness= tellTotalBrightness(buffer);
	printf("Total Brightness: %d\n",totalBrightness);

	free(buffer);
	fclose(file);
}

// 0 => turn on
// 1 => turn off
// 2 => toggle

int tellTotalBrightness(char *s){
	char instruction[100];
	int index = 0;

	for(int i = 0;s[i] != '\0';i++){
		if(s[i] != '\n')
			instruction[index++] = s[i];
		else{
			instruction[index] = '\0';
			move currentMove = findMove(instruction, index);
			// printf("ACT: %x   ",currentMove.act);
			// printf("Range: [%d,%d] - [%d,%d]\n",currentMove.range[0][0],currentMove.range[0][1], currentMove.range[1][0], currentMove.range[1][1]);
			makeMove(currentMove);
			index = 0;
		}
	}
	int totalBrithness= findTotalBrightness();
	return totalBrithness;
}

int findTotalBrightness(){
	int totalBrightness = 0;
	for(int i = 0;i<1000;i++){
		for(int j =0; j<1000; j++)
			totalBrightness += lights[i][j];
	}
	return totalBrightness;
}

void makeMove(move move){
	for(int i = move.range[0][0];i<= move.range[1][0];i++){
		for(int j = move.range[0][1]; j<= move.range[1][1]; j++){
			switch (move.act) {
				case 0:
					lights[i][j] += 1;
					break;
				case 1:
					lights[i][j] = lights[i][j] -1 <0? 0: lights[i][j] - 1;
					break;
				case 2:
					lights[i][j] += 2;
			}
		}
	}
}

move findMove(char *ins, int len){
	char act = 3;
	unsigned int range[2][2];
	range[0][0] = 0;
	range[0][1] = 0;
	range[1][0] = 0;
	range[1][1] = 0;
	char number = 0;

	for(int i = 0;i<len;i++){
		if(ins[i] >= '0' && ins[i] <= '9'){
				switch (ins[i-2]) {
					case 'n':
						act = 0;
						break;
					case 'f':
						act = 1;
						break;
					case 'e':
						act = 2;
						break;
				}
			for(;i<len;i++){
				if(ins[i] >= '0' && ins[i] <= '9'){
					switch (number) {
						case 0:
							range[0][0] = range[0][0] * 10 + (ins[i] - '0');
							break;
						case 1:
							range[0][1] = range[0][1] * 10 + (ins[i] - '0');
							break;
						case 2:
							range[1][0] = range[1][0] * 10 + (ins[i] - '0');
							break;
						case 3: range[1][1] = range[1][1] * 10 + (ins[i] - '0');
					}
				}
				else if(ins[i] == ',' || ins[i] == 'r')
					number++;
			}
			
		}

	}
	move ans;
	ans.act = act;
	ans.range[0][0] = range[0][0];
	ans.range[0][1] = range[0][1];
	ans.range[1][0] = range[1][0];
	ans.range[1][1] = range[1][1];
	return ans;
}
