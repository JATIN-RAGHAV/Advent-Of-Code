#include "stdio.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

char *wire = "a";

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef struct {
	char op;
	uint desHash;
	uchar isOp1Imm;
	uchar isOp2Imm;
	uint op1Hash;
	uint op2Hash;
}move;
typedef struct{
	uchar lenght;
	uint *hash;
} createTreeReturnType;
typedef struct node{
	move move;
	char parentNum;
	uint *parents;
	char childNum;
	uint *children;
}node;

node *nodesHashTable[800];
ushort globalState[800] = {0};
uchar initialisedState[800] = {0};

void makeMove(move move);

uint findA(char *s,int len);
move findMove(char *s);
uint hashName(char *s);
ushort atos(char *s);
void initializeNode(move move);
createTreeReturnType createTree();
void printTree(char indent, uint hash);
ushort executeNode(uint hash);

int main(){
	FILE* file = fopen("text.txt", "r");

	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	rewind(file);

	char *buffer = (char *)malloc(length+1);

	fread(buffer, 1, length, file);

	findA(buffer, length);

	free(buffer);
	fclose(file);
}

// ASSIGN => 0
// AND    => 1
// OR     => 2
// LSHIFT => 3
// RSHIFT => 4
// NOT    => 5

uint findA(char *s,int len){

	char line[100];
	int index = 0;

	for(int i = 0;i<len;i++){
		if(s[i] != '\n')
			line[index++] = s[i];
		else{
			line[index++] = '\0';
			move move = findMove(line);
			initializeNode(move);
			// printf("%s\n",line);
			index = 0;
			if(move.desHash == 336)
				printf("OP: %x, Destination:%d,isOp1Imm: %x, operand1: %d, isOp2Imm: %x, operand2: %d\n ",move.op,move.desHash,move.isOp1Imm, move.op1Hash, move.isOp2Imm, move.op2Hash);

		}
	}

	createTreeReturnType roots = createTree();
	
	uint value = executeNode(hashName(wire));
	printf("Value: %d\n",value);
	return 0;
}

ushort executeNode(uint hash){
	node *cnode = nodesHashTable[hash];
	uint op1Has, op2Hash;
	ushort op1,op2;
	// printf("got node pointer\t");
	if(cnode->move.isOp1Imm)
		op1 = cnode->move.op1Hash;
	else{
		if(initialisedState[cnode->move.op1Hash])
			op1 = globalState[cnode->move.op1Hash];
		else
			op1 = executeNode(cnode->move.op1Hash);
	}
	// printf("Got op1\t");
	if(cnode->move.op > 0 || cnode->move.op < 5){
		if(cnode->move.isOp2Imm)
			op2 = cnode->move.op2Hash;
		else{
			if(initialisedState[cnode->move.op2Hash])
				op2 = globalState[cnode->move.op2Hash];
			else
				op2 = executeNode(cnode->move.op2Hash);
		}
	}
	// printf("got op2\t");

	switch (cnode->move.op) {
		case 0:
			globalState[hash] = op1;
			break;
		case 1:
			globalState[hash] = op1 & op2;
			break;
		case 2:
			globalState[hash] = op1 | op2;
			break;
		case 3:
			globalState[hash] = op1 << op2;
			break;
		case 4:
			globalState[hash] = op1 >> op2;
			break;
		case 5:
			globalState[hash] = ~op1;
	}
	initialisedState[hash] = 1;

	move move = cnode->move;
	printf("OP: %x, Destination:%d,isOp1Imm: %x, operand1: %d, isOp2Imm: %x, operand2: %d\n ",move.op,move.desHash,move.isOp1Imm, move.op1Hash, move.isOp2Imm, move.op2Hash);
	printf("desHash: %d, op1: %d, op2: %d, opcode: %x, result: %d\n",hash,op1,op2,cnode->move.op,globalState[hash]);
	// putchar(10);
	return globalState[hash];

}

// ASSIGN => 0
// AND    => 1
// OR     => 2
// LSHIFT => 3
// RSHIFT => 4
// NOT    => 5
void printTree(char indent, uint hash){
	if(initialisedState[hash] == 0){
		for(int i = 0;i<=indent;i++)
			putchar('\t');
		printf("Hash: %d\n",hash);
		initialisedState[hash] = 1;
		node *node = nodesHashTable[hash];
		if(node->childNum > 0){
			for(int i = 0;i<node->childNum;i++)
				printTree(indent+1,node->children[i]);
		}
	}
}

// ASSIGN => 0
// AND    => 1
// OR     => 2
// LSHIFT => 3
// RSHIFT => 4
// NOT    => 5
		
move findMove(char *s){
	char *destination = (char *)malloc(5);
	char dIndex = 0;
	char op = -1;
	move move;

	for(int i = 0;s[i] != '\0';i++){
		switch (s[i]) {
			case 'A':
				op = 1;
				break;
			case 'O':
				op = 2;
				break;
			case 'L':
				op = 3;
				break;
			case 'R':
				op = 4;
				break;
			case 'N':
				op = 5;
				break;
		}
		if(op != -1)
			break;
	}
	if(op == -1)
		op = 0;

	if(op == 5){
		char operand[50];
		char OpIndex = 0;
		op = 5;
		int i;
		for(i = 4;s[i] != ' ';i++){
			operand[OpIndex++] = s[i];
		}
		operand[OpIndex] = '\0';
		int target = 0;
		for(;s[i] != '\0';i++){
			if(s[i] == '>'){
				target = 1;
				i++;
			}else if(s[i] >= 'a' && s[i] <= 'z' && target)
				destination[dIndex++] = s[i];

		}
		destination[dIndex] = '\0';
		move.op = op;
		move.desHash= hashName(destination);
		operand[OpIndex++] = '\0';
		if(operand[0] >= '0' && operand[0] <= '9'){
			move.isOp1Imm = 1;
			move.op1Hash = atos(operand);
		}else{
			move.isOp1Imm = 0;
			move.op1Hash = hashName(operand);
		}
		free(destination);
		return move;

	}

	else if(op < 5 && op >0){
		int inOpe = 1;
		char operand1[50];
		char operand2[50];
		char op1Index= 0;
		char op2Index = 0;
		char null = 0;
		for(int i = 0;s[i] != '\0';i++){
			if(((s[i] >= 'a' && s[i] <= 'z') | (s[i] >= '0' && s[i] <= '9') ) && inOpe){
				if(null == 0)
					operand1[op1Index++] = s[i];
				else
					operand2[op2Index++] = s[i];
			}
			else if(s[i] >= 'A' && s[i] <= 'Z' && null == 0){
				null = 1;
			}
			else if(s[i] == '>'){
				i++;
				inOpe = 0;
			}
			else if(inOpe == 0 && s[i] >= 'a' && s[i] <= 'z'){
				destination[dIndex++] = s[i];
			}
		}
		destination[dIndex] = '\0';
		operand1[op1Index] = '\0';
		operand2[op2Index] = '\0';

		move.desHash= hashName(destination);
		
		if(operand1[0] >= 'a' && operand1[0] <= 'z'){
			move.isOp1Imm = 0;
			move.op1Hash = hashName(operand1);
		}else{
			move.isOp1Imm = 1;
			move.op1Hash = atos(operand1);
		}

		if(operand2[0] >= 'a' && operand2[0] <= 'z'){
			move.isOp2Imm = 0;
			move.op2Hash = hashName(operand2);
		}else{
			move.isOp2Imm = 1;
			move.op2Hash = atos(operand2);
		}

		move.op = op;
	}

	else if(op == 0){
		char operand[50];
		char opIndex = 0;
		char inOp = 1;
		for(int i = 0;s[i] != '\0';i++){
			if((s[i] >= 'a' && s[i] <= 'z' ) || (s[i] >= '0' && s[i] <= '9'))
				if(inOp)
					operand[opIndex++] = s[i];
				else
					destination[dIndex++] = s[i];
			else if(s[i] == '>')
					inOp = 0;
		}
		destination[dIndex] = '\0';
		operand[opIndex] = '\0';
		move.desHash = hashName(destination);
		move.op = op;
		
		if(operand[0] >= 'a' && operand[0] <= 'z'){
			move.isOp1Imm = 0;
			move.op1Hash = hashName(operand);
		}else{
			move.isOp1Imm = 1;
			move.op1Hash = atos(operand);
		}
	}
	return move;
}

void initializeNode(move move){
	node *cnode = (node *)malloc(sizeof(node));
	if(cnode == NULL){
		printf("Memory Full\n");
		return;
	}
	uint *parents = (uint *)malloc(2*(sizeof(uint)));
	if(move.isOp2Imm == 0)
		cnode->parentNum = 2;
	else
		cnode->parentNum = 1;
	parents[0] = move.op1Hash;
	parents[1] = move.op2Hash;
	cnode->move = move;
	cnode->childNum = 0;
	cnode->parents = parents;
	cnode->children = 0;
	nodesHashTable[move.desHash] = cnode;
}

createTreeReturnType createTree(){
	uint *roots = (uint*)calloc(10, sizeof(uint));
	uchar rootIndex = 0;
	for(int i = 0;i<800;i++){
		if(nodesHashTable[i]){
			node *cnode = nodesHashTable[i];
			
			if(cnode->move.op == 0 && cnode->move.isOp1Imm)
				roots[rootIndex++] = cnode->move.desHash;
			else{
				node* parent1;
				node* parent2;
				parent1 = nodesHashTable[cnode->parents[0]];
				if(parent1->childNum == 0){
					uint *child = (uint *)malloc(sizeof(uint));
					parent1->childNum = 1;
					*child = cnode->move.desHash;
					parent1->children = child;
				}else{
					uint* children = (uint *)calloc(parent1->childNum+1, sizeof(uint));
					for(int j = 0;j<parent1->childNum;j++)
							children[j] = parent1->children[j];
					children[parent1->childNum] = cnode->move.desHash;
					parent1->childNum++;
					free(parent1->children);
					parent1->children = children;
				}

				if(cnode->parentNum == 2){
					parent2 = nodesHashTable[cnode->parents[1]];
					if(parent2->childNum == 0){
						uint *child = (uint *)malloc(sizeof(uint));
						parent2->childNum = 1;
						*child = cnode->move.desHash;
						parent2->children = child;
					}else{
						uint* children = (uint *)calloc(parent2->childNum+1, sizeof(uint));
						for(int j = 0;j<parent2->childNum;j++)
							children[j] = parent2->children[j];
						children[parent2->childNum] = cnode->move.desHash;
						parent2->childNum++;
						free(parent2->children);
						parent2->children = children;
					}
				}
			}
		}
	}
	createTreeReturnType returnType;
	returnType.lenght = rootIndex;
	returnType.hash = roots;
	return returnType;
}

uint hashName(char *s){
	int base26 = 0;
	int i;
	for(i = 0;s[i] != '\0';i++)
		;
	for(int j = 0;s[j] != '\0';j++)
		base26 += (s[j] - 'a' + 1)*(pow(26, i-j-1));
	return base26;
}

ushort atos(char *s){
	ushort num = 0;
	for(int i = 0; s[i] != '\0';i++)
		num = (num*10) + s[i] - '0';
	return num;
}

