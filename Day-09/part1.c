#include "stdio.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uchar;
typedef unsigned int uint ;
typedef struct{
	int place1;
	int place2;
	int weight;
} command;
typedef struct{
	int start;
	int end;
	uint dist;
}pair;


char *globalPlacesString[30];
int currentIndex = 0;
int nodeCount = 0;
int grid[30][30] = {0};
pair *giveShortestParth(char *s, int);
int getHash(char *s);
char * getName(int n);
command* findcommand(char *s);
void executeCommand(command cmd);
uint findShortestPath(int start, int end, uchar [],int remainingCount);

int main(){
	FILE* file = fopen("text.txt", "r");

	fseek(file, 0, SEEK_END);
	int lenght = ftell(file);
	rewind(file);

	char *buffer = (char *)malloc(lenght+1);

	fread(buffer, 1, lenght, file);

	pair *ans = giveShortestParth(buffer,lenght);
	printf("Start: %d, End: %d, Distance: %d\n",ans->start, ans->end, ans->dist);
	
	free(ans);
	free(buffer);
	fclose(file);
}

pair *giveShortestParth(char *s,int len){
	char line[200];
	int index = 0;
	
	for(int i = 0;i<len;i++){
		if(s[i] != '\n')
			line[index++] = s[i];
		else{
			line[index] = '\0';
			command command =  *findcommand(line);
			// printf("Place1 Hash: %d, Place2 Hash: %d, weight: %d\n",command.place1, command.place2, command.weight);
			executeCommand(command);
			index = 0;
		}
	}
	for(nodeCount = 0;globalPlacesString[nodeCount] != 0;nodeCount++)
		;
	
	printf("[\n");
	for(int i = 0;i<nodeCount;i++){
		printf("\t[");
		for(int j = 0;j<nodeCount;j++){
			printf("%4d,",grid[i][j]);
		}
		printf("]\n");
	}
	printf("]\n");

	pair* smallestPair = (pair *)malloc(sizeof(pair));
	smallestPair->dist = INT_MAX;

	for(int i = 0;i<nodeCount;i++){
		for(int j = i+1;j<nodeCount;j++){
			uchar *visited = (uchar*)malloc(nodeCount*sizeof(uchar));
			for(int k = 0;k<nodeCount;k++)
				visited[k] = 0;
			visited[i] = 1;
			visited[j] = 1;
			printf("Visited: ");
			for(int i = 0;i<nodeCount;i++)
				printf("%d,",visited[i]);
			printf("]\n");
			int currentDist= findShortestPath(i, j,visited, nodeCount-2);
			 printf("Start: %d, End: %d, Distance: %d\n",i, j, currentDist);
			if(smallestPair->dist > currentDist){
			// printf("Start: %d, End: %d, Distance: %d\n",i, j, currentDist);
				smallestPair->start = i;
				smallestPair->end = j;
				smallestPair->dist = currentDist;
			}
			free(visited);
		}
	}

	return smallestPair;
}

uint findShortestPath(int start, int end, uchar visited[],int remainingCount){
	// printf("Visited: ");
	// for(int i = 0;i<nodeCount;i++)
	// 	printf("%d,",visited[i]);
	// printf("]\n");
	// printf("Remaining Cound: %d\n",remainingCount);
	if(remainingCount <= 2){
		uint sum = 0;
		int middleNode;
		for(int i = 0;i<nodeCount;i++){
			if(visited[i] == 0 && i!=end)
				middleNode = i;
		}
		return grid[start][middleNode] + grid[middleNode][end];
	}

	uint smallestSum = UINT_MAX;

	for(int i = 0;i<nodeCount;i++){
		if(visited[i] == 0 && i!= end){
			uchar* visitedCopy = (uchar*)malloc(nodeCount*(sizeof(uchar)));
			for(int j = 0;j<nodeCount; j++)
				visitedCopy[j] = visited[j];
			visitedCopy[end] = 1;

			uint currentSum = findShortestPath(start, i, visitedCopy, remainingCount-1);
			currentSum += grid[i][end];
			if(currentSum < smallestSum){
				smallestSum = currentSum;
			}

			free(visitedCopy);
		}
	}

		
	return smallestSum;
}

void executeCommand(command cmd){
	int i = cmd.place1;
	int j = cmd.place2;
	int weight = cmd.weight;
	grid[i][j] = weight;
	grid[j][i] = weight;
}

// state = 0 -> first place
// state = 1 -> second place
// state = 2 -> weight
command* findcommand(char *s){
	command* dis = (command*)malloc(sizeof(command));
	int state = 0;
	for(int i = 0;s[i] != '\0';i++){
		if(s[i] == ' '){
			if(state == 0){
				s[i] = '\0';
				dis->place1 = getHash(s);
				state = 1;
			}
			else if(state == 1){
				char *secondPlace = &s[i+1];
				i++;
				for(;s[i] != ' ';i++)
					;
				s[i] = '\0';
				i++;
				dis->place2 = getHash(secondPlace);
				state = 2;
			}
			else if(state == 2){
				dis->weight = atoi(&s[i+1]);
			}
		}
	}

	return dis;
}


int getHash(char *s){
	int i;
	for(i = 0;i<currentIndex;i++){
		if(strcmp(s,globalPlacesString[i]) == 0)
			break;
	}
	if(i != currentIndex)
		return i;
	
	for(i = 0;s[i] != '\0';i++)
		;
	char *newString = (char *)malloc(i);
	for(i = 0;s[i] != '\0';i++)
		newString[i] = s[i];
	newString[i] = '\0';
	globalPlacesString[currentIndex++] = newString;
	return currentIndex-1;
}

char*getName(int n){
	if(n<currentIndex)
		return globalPlacesString[n];
	char*e = "Err";
	return e;
}
