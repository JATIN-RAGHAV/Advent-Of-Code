#include "stdio.h"

int main() {
	int c,rowsCount,columnCount,columnIndex;

	int mapArray[340][35];

	FILE *filePtr = fopen("text.txt", "r");

	rowsCount = columnIndex = 0;
	
	while((c = fgetc(filePtr)) != EOF){
		if(c == '\n'){
			rowsCount++;
			columnCount = columnIndex;
			columnIndex = 0;
		}else{
			mapArray[rowsCount][columnIndex] = c;
			columnIndex++;
		}
	}

	int currentRow, currentColumn, treesCount;
	currentRow = currentColumn = treesCount = 0;
	while(currentRow <= rowsCount){
		
		if(currentColumn >= columnCount)
			currentColumn = currentColumn - columnCount;

		if(mapArray[currentRow][currentColumn] == '#')
			treesCount++;

		currentRow += 1;
		currentColumn += 3;
	}

	printf("Number of trees encountered: %d\n",treesCount);
}
