#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

typedef struct node{
	int sum;
	struct node* children[10];
	int hasRed;
	int childrenCount;
}node;


int findSum(char *s,int);
int sumObject(char *s, int len);
int findTotalSum(char *s);
int sumNode(node *node);
int findRedSum(char *s);
void printStruct(node *node, int indent);

int main(){
	FILE* file = fopen("text.txt", "r");

	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	rewind(file);

	char*buffer = (char*)malloc(length+1);
	fread(buffer,1,length,file);

	int sum = findRedSum(buffer);
	printf("Sum: %d\n",sum);

	free(buffer);
	fclose(file);
}

int findRedSum(char *s){
	node* nodeStack[20];
	int top = 0;
	char num[10];
	node* root = NULL;
	int numIndex = 0;
	int inArray = FALSE;
	int wasArray = FALSE;
	node* cNode = NULL;

	for(int i = 0;s[i] != '\0';i++){
		if(s[i] == '{' || s[i] == '['){
			node *nNode = (node *)malloc(sizeof(node));
			nNode->sum = 0;
			nNode->hasRed = FALSE;
			nNode->childrenCount = 0;
			if(cNode != NULL){
				cNode->children[cNode->childrenCount++] = nNode;
			}
			inArray = FALSE;
			nodeStack[top++] = nNode;
			cNode = nNode;
			if(root == NULL)
				root = cNode;
			if(s[i] == '['){
				inArray = TRUE;
				wasArray = TRUE;
			}
		}else if(s[i] == '}' || s[i] == ']'){
			if(wasArray)
				inArray = TRUE;
			top--;
			cNode = nodeStack[top];
			if(s[i] == ']'){
				inArray = FALSE;
				wasArray = FALSE;
			}
		}
		else if(s[i] == '-' || (s[i] >= '0' && s[i] <= '9')){
			num[numIndex++] = s[i];
			i++;
			for(;s[i] >= '0' && s[i] <= '9';i++){
				num[numIndex++] = s[i];
			}
			num[numIndex] = 0;
			cNode->sum += atoi(num);
			numIndex = 0;
			i--;
		}
		else if(i>=2 && inArray == FALSE){
			if(s[i-2] == 'r' && s[i-1] == 'e' && s[i] == 'd')
			cNode->hasRed = TRUE;
		}

	}

	int sum = sumNode(root);
	printStruct(root, 0);
	return sum;
}

void printStruct(node *node, int indent){
	for(int i = 0;i<indent;i++)
		putchar('\t');
	printf("Sum: %d, childrenCount: %d, hasRed: %d\n",node->sum, node->childrenCount, node->hasRed);
	for(int i = 0;i<node->childrenCount;i++){
		printStruct(node->children[i], indent+1);
	}

}

int sumNode(node *node){
	printf("Sum: %d, childrenCount: %d, hasRed: %d\n",node->sum, node->childrenCount, node->hasRed);
	if(node->hasRed == TRUE)
		return 0;
	int sum = node->sum;
	for(int i = 0;i<node->childrenCount;i++){
		sum += sumNode(node->children[i]);
	}

	return sum;
}

int findTotalSum(char *s){
	int sum = 0;
	char num[10];
	int index = 0;
	for(int i = 0;s[i] != 0;i++){
		if((s[i] >= '0' && s[i] <= '9') || s[i] == '-')
			num[index++] = s[i];
		else{
			num[index] = 0;
			sum += atoi(num);
			index = 0;
		}
	}

	return sum;
}
int sumObject(char *s, int len){
	int sum = 0;
	char num[10];
	int index = 0;

	for(int i = 0;i<len;i++){
		if(((s[i] >= '0' && s[i] <= '9') || s[i] == '-'))
			num[index++] = s[i];
		else{
			num[index] = 0;
			sum += atoi(num);
			index = 0;
		}
	}
	return sum;
}
