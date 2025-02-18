#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct point{
	int x;
	int y;
} point;
#define MAXLENGTH 10000

void printMemo(point *s,int len);
int giveUniqueHouses(char *s);
int hasVisited(int x,int y, point arr[],int len);

int main(){
	FILE* pfile = fopen("text.txt", "r");
	fseek(pfile, 1, SEEK_END);
	int length = ftell(pfile);
	rewind(pfile);

	char *buffer = (char*)malloc(length+1);
	fread(buffer, 1, length, pfile);
	buffer[length] = '\0';
	printf("%s",buffer);

	int uniqueVisits = giveUniqueHouses(buffer);
	printf("Unique Visits: %d\n",uniqueVisits);

	free(buffer);
	fclose(pfile);
}

int giveUniqueHouses(char *s){
	int index = 0;
	point memo[MAXLENGTH];
	memo[index].x = 0;
	memo[index++].y = 0;
	point current = {0,0};
	int uniqueVisits = 1;


	for(int i = 0;s[i] != '\n' && s[i] != '\0';i++){
		point direction;
		switch (s[i]) {
			case '<':
				direction.x = -1;
				direction.y = 0;
				break;
			case '>':
				direction.x = 1;
				direction.y = 0;
				break;
			case '^':
				direction.x = 0;
				direction.y = 1;
				break;
			case 'v':
				direction.x = 0;
				direction.y = -1;
				break;
		}
		// printf("Symbol: %c, Direction: [%d,%d]\n",s[i],direction.x,direction.y);
		if(!hasVisited(current.x + direction.x, current.y + direction.y, memo,index)){
			// printf("CurrentLocation: [%d,%d]\n",current.x,current.y);
			current.x += direction.x;
			current.y += direction.y;
			memo[index].x = current.x;
			memo[index++].y = current.y;
			uniqueVisits++;
		}else{
			current.x += direction.x;
			current.y += direction.y;
		}
			// printf("UpdatedLocation: [%d,%d]\n\n",current.x,current.y);
		// printMemo(memo,index);
	}



	return uniqueVisits;
}

void printMemo(point *s,int len){
	printf("[");
	for(int i = 0; i<len;i++){
		printf("[%d,%d]\n",s[i].x,s[i].y);
	}
	printf("]\n\n");
}

int hasVisited(int x,int y, point arr[],int len){
	// printf("location given to hasVisited: [%d,%d]\n",x,y);
	for(int i = 0;i<=len;i++){
		if(x == arr[i].x && y == arr[i].y)
			return 1;
	}
	return 0;
}
