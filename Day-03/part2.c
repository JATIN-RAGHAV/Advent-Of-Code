#include "stdio.h"
#include <math.h>

int findTreesEncountered(int map[][35],int rows, int columns,int rowStep, int columnStep);
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

	int columnSteps[] = {1,3,5,7,1};
	int rowStep[] = {1,1,1,1,2};

	double multiply = 1;
	for(int i = 0;i<5;i++){
		multiply *= findTreesEncountered(mapArray, rowsCount, columnCount,rowStep[i],columnSteps[i]);

	}
	printf("Final Multiply answer: %f\n",multiply);
}

int findTreesEncountered(int map[][35],int rows, int columns,int rowStep, int columnStep){
	int currentRow, currentColumn, treesCount;
	currentRow = currentColumn = treesCount = 0;
	while(currentRow <= rows){
		
		if(currentColumn >= columns)
			currentColumn = currentColumn - columns;

		if(map[currentRow][currentColumn] == '#')
			treesCount++;

		currentRow += rowStep;
		currentColumn += columnStep;
	}
	return treesCount;
}
