
#include <stdio.h>
#include <stdlib.h>


int countNice(char *buffer);
int hasLetterInBetween(char *word, int len);
int hasPairTwice(char *word, int len);

int main(){
	FILE* file = fopen("text.txt","r");

	fseek(file, 0, SEEK_END);
	int lenght = ftell(file);
	rewind(file);

	char *buffer = (char *)malloc(lenght+1);

	fread(buffer, 1,lenght, file);

	int niceWords = countNice(buffer);
	printf("Ans: %d\n",niceWords);

	free(buffer);
	fclose(file);
}

int countNice(char *s){
	int niceWords = 0;
	char word[20];
	int index = 0;

	for(int i = 0;s[i] != '\0';i++){
		if(s[i] != '\n')
			word[index++] = s[i];
		else{
			word[index] = '\0';
			if(hasPairTwice(word, index) && hasLetterInBetween(word,index))
				niceWords++;
			index = 0;
		}
	}

	return niceWords;
}

// It contains a pair of any two letters that appears at least twice in the string without overlapping, like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
// It contains at least one letter which repeats with exactly one letter between them, like xyx, abcdefeghi (efe), or even aaa.

int hasPairTwice(char *word, int len){
	for(int i = 0;i<len-1;i++){
		char first = word[i];
		char second = word[i+1];

		for(int j = i+2;j<len-1;j++){
			if(word[j] == first && word[j+1] == second)
				return 1;
		}
	}

	return 0;
}

int hasLetterInBetween(char *word, int len){
	for(int i = 0; i<len-2;i++){
		if(word[i] == word[i+2])
			return 1;
	}
	return 0;
}
