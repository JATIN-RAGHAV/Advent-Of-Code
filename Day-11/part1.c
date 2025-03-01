#include "stdio.h"
#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef unsigned char uchar;
char initial[] = "vzbxxyzz";

uchar isValid(char *);
void increment(char *s);

int main(){
	while(TRUE){
		increment(initial);
		if(isValid(initial)){
			break;
		}
	}

	printf("%s\n",initial);
}

// Passwords must include one increasing straight of at least three letters, like abc, bcd, cde, and so on, up to xyz. They cannot skip letters; abd doesn't count.
// Passwords may not contain the letters i, o, or l, as these letters can be mistaken for other characters and are therefore confusing.
// Passwords must contain at least two different, non-overlapping pairs of letters, like aa, bb, or zz.

void increment(char *s){
	for(int i = 0;i<8;i++){
		if(s[i] == 'i' || s[i] == 'o' || s[i] == 'l'){
			s[i]++;
			return;
		}
	}
	for(int i = 7;i>=0;i--){
		if(s[i] < 'z'){
			s[i]++;
			return;
		}else
			s[i] = 'a';
	}
}

uchar isValid(char *s){

	uchar doubles = 0;
	uchar lastMatch = 8;
	uchar continous3Char = FALSE;
	for(int i = 0; i<8;i++){
		if(i<=5){
			if((s[i+2] - s[i+1] == s[i+1] - s[i]) && s[i+2] - s[i+1] == 1)
				continous3Char = TRUE;
		}
		if(s[i] == 'i' || s[i] == 'o' || s[i] == 'l')
			return FALSE;
		if(i<=6 && i != lastMatch){
			if(s[i] == s[i+1]){
				doubles++;
				lastMatch = i+1;
			}
		}
	}
	if(doubles<2 || continous3Char == FALSE)
		return FALSE;

	return TRUE;
}
