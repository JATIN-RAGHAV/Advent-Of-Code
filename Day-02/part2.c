#include "stdio.h"

int main(){
	int c,charNum, validPasswords,lineNum;
	
	char line[30];
	FILE *fileptr = fopen("text.txt", "r");

	charNum = lineNum = validPasswords = 0;
	while((c = fgetc(fileptr)) != EOF){
		if(c != '\n'){
			line[charNum] = c;
			charNum++;
		}else{
			int firstPos, secondPos,chaar,stringStart;
			if(line[1] == '-'){
				firstPos= line[0] - '0';
				if(line[3] == ' '){
					secondPos= line[2] - '0';
					chaar = line[4];
					stringStart = 7;
				}
				else{
					secondPos= (line[2] - '0')*10 + (line[3] - '0');
					chaar = line[5];
					stringStart = 8;
				}
			}else{
				firstPos= (line[0] - '0') * 10 + (line[1] - '0');
				if(line[4] == ' '){
					secondPos= line[3] - '0';
					chaar = line[5];
					stringStart = 8;
				}
				else{
					secondPos = (line [3] - '0') * 10 + (line[4] - '0');
					chaar = line[6];
					stringStart = 9;
				}
			}
			int charCount = 0;
			for(int i = stringStart; i<charNum;i++){
				if(line[i] == chaar)
					charCount++;
			}
			if(((line[firstPos-1+stringStart] == chaar) && (line[secondPos -1+stringStart ] != chaar)) || ((line[firstPos -1+stringStart] != chaar) && (line[secondPos-1+stringStart] == chaar)))
				validPasswords++;
			lineNum++;
			charNum = 0;
		}
	}
	printf("Number of valid passwords: %d\n",validPasswords);
	printf("Number of invalid passwords: %d\n",lineNum - validPasswords);
};
