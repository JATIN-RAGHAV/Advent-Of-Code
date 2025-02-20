#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>

int hasVowels(char *s);
int hasDouble(char *s);
int donestContainBadStuff(char *s);
int countNice(char *s);

int main(){
	FILE *pfile = fopen("text.txt","r");
	
	fseek(pfile, 0, SEEK_END);
	int length = ftell(pfile);
	rewind(pfile);

	char *buffer = (char *)malloc(length+1);

	fread(buffer, 1, length, pfile);

	int niceWords = countNice(buffer);
	printf("Ans: %d\n",niceWords);

	free(buffer);
	fclose(pfile);
}

int countNice(char *s){
	int niceWords = 0;
	char word[20];
	int index = 0;
	for(int i = 0;s[i] != '\0';i++){
		if(s[i] != '\n')
			word[index++] = s[i];
		else{
			word[index++] = '\0';
			index = 0;
			if(hasVowels(word) && hasDouble(word) && donestContainBadStuff(word))
				niceWords++;
		}
	}

	return niceWords;
}
// It contains at least three vowels (aeiou only), like aei, xazegov, or aeiouaeiouaeiou.
// It contains at least one letter that appears twice in a row, like xx, abcdde (dd), or aabbccdd (aa, bb, cc, or dd).
// It does not contain the strings ab, cd, pq, or xy, even if they are part of one of the other requirements.

int hasVowels(char *s){
	int vowels = 0;
	for(int i = 0;s[i] != '\0';i++){
		switch (s[i]) {
			case 'a': case 'e': case 'i': case 'o': case 'u':
				vowels++;
		}
	}

	return vowels>=3;
}

int hasDouble(char *s){
	for(int i = 0; s[i] != '\0'; i++)
		if(s[i] == s[i+1])
			return 1;

	return 0;
}

int donestContainBadStuff(char *s){
	for(int i = 0; s[i] != '\0';i++){
		if((s[i] == 'a' && s[i+1] == 'b') || (s[i] == 'c' && s[i+1] == 'd') || (s[i] == 'p' && s[i+1] == 'q') || (s[i] == 'x' && s[i+1] == 'y'))
			return 0;
	}
	return 1;
}
