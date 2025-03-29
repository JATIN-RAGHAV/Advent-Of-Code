#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uchar;
typedef unsigned int uint;
typedef struct node{
	int connections[10];
}node;

typedef struct{
	int num;
	int start;
	int end;
} move;


int NODES[10][10] = {0};
int nodeCount;
char *strings[10];
int maxHash = 0;

int getHash(char *s);
int findMaxHappyness(char *s);
move* getMove(char *s);
void executeMove(move*m);
uint findLongestPath(int start, int end, uchar visited[],int remainingCount);

int main(){
	FILE* file = fopen("text.txt","r");

	fseek(file,0,SEEK_END);
	int length = ftell(file);
	rewind(file);

	char *buffer = (char*)malloc(length+1);

	fread(buffer, 1, length, file);

	int maxHappiness = findMaxHappyness(buffer);
	printf("Max Happiness: %d\n",maxHappiness);

	free(buffer);
	fclose(file);
}

int findMaxHappyness(char *s){
	char line[200];
	int index = 0;

	for(int i = 0; s[i] != 0;i++){
		if(s[i] != 10)
			line[index++] = s[i];
		else{
			line[index] = 0;
			move * cmove = getMove(line);
			index = 0;
			executeMove(cmove);
			free(cmove);
		}
	}

	nodeCount = 1;
	for(;NODES[nodeCount][0] != 0;nodeCount++)
		;

	for(int i = 0;i<nodeCount;i++){
		printf("\t[");
		for(int j = 0;j<nodeCount;j++)
			printf("%5d,",NODES[i][j]);
		printf("]\n");
	}

	int maxHappiness = 0;
	for(int i = 0;i<nodeCount;i++){
		for(int j = 0;j<nodeCount; j++){
			uchar *visited = (uchar*)malloc(nodeCount);
			for(int k = 0;k<nodeCount;k++)
				visited[k] = 0;
			visited[i] = 1;
			visited[j] = 1;
			int cHappiness = findLongestPath(i, j,visited , nodeCount-2);
			free(visited);
			if(cHappiness > maxHappiness)
				maxHappiness = cHappiness;
		}
	}

	return maxHappiness;
}
uint findLongestPath(int start, int end, uchar visited[],int remainingCount){
	printf("Visited: ");
	for(int i = 0;i<nodeCount;i++)
		printf("%d,",visited[i]);
	printf("]\n");
	printf("Remaining Cound: %d\n",remainingCount);
	if(remainingCount <= 1){
		uint sum = 0;
		int middleNode;
		for(int i = 0;i<nodeCount;i++){
			if(visited[i] == 0 && i!=end)
				middleNode = i;
		}
		return NODES[start][middleNode] + NODES[middleNode][end];
	}

	uint LargestSum = 0;

	for(int i = 0;i<nodeCount;i++){
		if(visited[i] == 0 && i!= end){
			uchar* visitedCopy = (uchar*)malloc(nodeCount*(sizeof(uchar)));
			for(int j = 0;j<nodeCount; j++)
				visitedCopy[j] = visited[j];
			visitedCopy[end] = 1;

			uint currentSum = findLongestPath(start, i, visitedCopy, remainingCount-1);
			currentSum += NODES[i][end];
			if(currentSum > LargestSum){
				LargestSum = currentSum;
			}

			free(visitedCopy);
		}
	}

		
	return LargestSum;
}

void executeMove(move*m){
	NODES[m->start][m->end] += m->num;
	NODES[m->end][m->start] += m->num;
}

move* getMove(char *s){
	move* cmove = (move *)malloc(sizeof(move));
	int firstHash, secondHash, sign;
	char num[10];
	int numIndex = 0;
	int weight = 0;

	int spaces = 0;
	for(int i = 0;s[i] != 0;i++){
		if(s[i] == ' '){
			spaces++;
			if(spaces == 1){
				s[i] = 0;
				firstHash = getHash(s);
			}
			else if(spaces == 2){
				sign = s[++i] == 'g' ? +1 : -1;
			}
			else if(spaces == 3){
				i++;
				for(;s[i] != ' ';i++)
					num[numIndex++] = s[i];
				num[numIndex] = 0;
				weight = atoi(num);
			}
			else if(i>3 && s[i-2] == 't' && s[i-1] == 'o' && s[i] == ' '){
				char* firstLetter = &s[++i];
				for(;s[i] != '.';i++)
					;
				s[i] = 0;
				secondHash = getHash(firstLetter);
			}
		}
	}
	cmove->num = weight * sign;
	cmove->start = firstHash;
	cmove->end = secondHash;

	return cmove;
}

int getHash(char *s){
	int i;
	for(i = 0;i<maxHash;i++){
		if(strcmp(s, strings[i]) == 0)
			return i;
	}
	int size;
	for(size = 0;s[size] != 0; size++)
		;
	char *newString = (char *)malloc(size);
	for(i = 0;s[i] != 0;i++)
		newString[i] = s[i];
	newString[i] = 0;
	strings[maxHash++] = newString;
	return maxHash -1;
	
}
