#include "stdio.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef  unsigned char uchar ;
typedef struct {
	uchar *string;
	unsigned int len;
	unsigned int originalBitCount;
} hash;


char* addNum(char* s, int n);
char *secret = "pqrstuv";
int power(int base, int power);
hash addPadding(char* s);
uchar *addLength(hash h);
void fillSinTable();
void ROUND1(uint32_t *a, uint32_t b, uint32_t c, uint32_t d, int k, int s, int i, uint32_t X[]);
void ROUND2(uint32_t *a, uint32_t b, uint32_t c, uint32_t d, int k, int s, int i, uint32_t X[]);
void ROUND3(uint32_t *a, uint32_t b, uint32_t c, uint32_t d, int k, int s, int i, uint32_t X[]);
void ROUND4(uint32_t *a, uint32_t b, uint32_t c, uint32_t d, int k, int s, int i, uint32_t X[]);
void solveBlock(uchar* s);

uint32_t sinTable[64];
uint32_t A = 0x67452301;
uint32_t B = 0xefcdab89;
uint32_t C = 0x98badcfe;
uint32_t D = 0x10325476;

int main(){
	char* numberedString = addNum(secret, 1048970);
	hash padded = addPadding(numberedString);
	uchar *finalStr = addLength(padded);
	fillSinTable();

	int word16Count = (padded.len + 8) / 64;

	for(int i = 0; i<word16Count;i++){
		uchar *blockBase = &finalStr[i+64];
		solveBlock(blockBase);
	}

	printf("%08x%08x%08x%08x\n",A,B,C,D);
}

void solveBlock(uchar* s){
	uint32_t X[16];
	for(int i = 0;i<16;i++){
		for(int j = 3;j>=0;j--){
			uchar c = s[i+j];
			X[i] += c;
			X[i] = X[i] << 8;
		}
	}

	uint32_t AA = A;
	uint32_t BB = B;
	uint32_t CC = C;
	uint32_t DD = D;

	// [ABCD  0  7  1]  [DABC  1 12  2]  [CDAB  2 17  3]  [BCDA  3 22  4]
	// [ABCD  4  7  5]  [DABC  5 12  6]  [CDAB  6 17  7]  [BCDA  7 22  8]
	// [ABCD  8  7  9]  [DABC  9 12 10]  [CDAB 10 17 11]  [BCDA 11 22 12]
	// [ABCD 12  7 13]  [DABC 13 12 14]  [CDAB 14 17 15]  [BCDA 15 22 16]

	// ROUND 1 BEGINS
	for(int i = 0;i<16;i++){
		int second;
		uint32_t d,c,b, *a;
		switch (i/4) {
			case 0:
				second = 7;
				a = &A;
				b = B;
				c = C;
				d = D;
				break;
			case 1:
				second = 12;
				a = &D;
				b = A;
				c = B;
				d = C;
				break;
			case 2:
				second = 17;
				a = &C;
				b = D;
				c = A;
				d = B;
				break;
			case 3:
				second = 22;
				a = &B;
				b = C;
				c = D;
				d = A;
				break;
		}

		ROUND1(a, b, c, d, i, second, i+1, X);
	}
	
		// [ABCD  1  5 17]  [DABC  6  9 18]  [CDAB 11 14 19]  [BCDA  0 20 20]
		// [ABCD  5  5 21]  [DABC 10  9 22]  [CDAB 15 14 23]  [BCDA  4 20 24]
		// [ABCD  9  5 25]  [DABC 14  9 26]  [CDAB  3 14 27]  [BCDA  8 20 28]
		// [ABCD 13  5 29]  [DABC  2  9 30]  [CDAB  7 14 31]  [BCDA 12 20 32]

	// ROUND 2 BEGINS
	for(int i = 0;i<16;i++){
		int second;
		int first = ((i*5+1) % 16) ;
		uint32_t d,c,b, *a;
		switch (i/4) {
			case 0:
				second = 5;
				a = &A;
				b = B;
				c = C;
				d = D;
				break;
			case 1:
				second = 9;
				a = &D;
				b = A;
				c = B;
				d = C;
				break;
			case 2:
				second = 14;
				a = &C;
				b = D;
				c = A;
				d = B;
				break;
			case 3:
				second = 20;
				a = &B;
				b = C;
				c = D;
				d = A;
				break;
		}

		ROUND2(a, b, c, d, first, second, i+17, X);
	}
		// [ABCD  5  4 33]  [DABC  8 11 34]  [CDAB 11 16 35]  [BCDA 14 23 36]
		// [ABCD  1  4 37]  [DABC  4 11 38]  [CDAB  7 16 39]  [BCDA 10 23 40]
		// [ABCD 13  4 41]  [DABC  0 11 42]  [CDAB  3 16 43]  [BCDA  6 23 44]
		// [ABCD  9  4 45]  [DABC 12 11 46]  [CDAB 15 16 47]  [BCDA  2 23 48]

	// ROUND 3 BEGINS
	for(int i = 0;i<16;i++){
		int second;
		int first = ((i*3+5) % 16);
		uint32_t d,c,b, *a;
		switch (i/4) {
			case 0:
				second = 4;
				a = &A;
				b = B;
				c = C;
				d = D;
				break;
			case 1:
				second = 11;
				a = &D;
				b = A;
				c = B;
				d = C;
				break;
			case 2:
				second = 16;
				a = &C;
				b = D;
				c = A;
				d = B;
				break;
			case 3:
				second = 23;
				a = &B;
				b = C;
				c = D;
				d = A;
				break;
		}

		ROUND3(a, b, c, d, first, second, i+33, X);
	}

		// [ABCD  0  6 49]  [DABC  7 10 50]  [CDAB 14 15 51]  [BCDA  5 21 52]
		// [ABCD 12  6 53]  [DABC  3 10 54]  [CDAB 10 15 55]  [BCDA  1 21 56]
		// [ABCD  8  6 57]  [DABC 15 10 58]  [CDAB  6 15 59]  [BCDA 13 21 60]
		// [ABCD  4  6 61]  [DABC 11 10 62]  [CDAB  2 15 63]  [BCDA  9 21 64]

	// ROUND 4 BEGINS
	for(int i = 0;i<16;i++){
		int second;
		int first = ((i*7) % 16);
		uint32_t d,c,b, *a;
		switch (i/4) {
			case 0:
				second = 6;
				a = &A;
				b = B;
				c = C;
				d = D;
				break;
			case 1:
				second = 10;
				a = &D;
				b = A;
				c = B;
				d = C;
				break;
			case 2:
				second = 15;
				a = &C;
				b = D;
				c = A;
				d = B;
				break;
			case 3:
				second = 21;
				a = &B;
				b = C;
				c = D;
				d = A;
				break;
		}

		ROUND4(a, b, c, d, first, second, i+49, X);
	}

	printf("%08x\n",A);
	printf("%08x\n",AA);
	A += AA;
	B += BB;
	C += CC;
	D += DD;
}



uchar *addLength(hash h){
	unsigned long bits = h.originalBitCount;
	
	uchar *lengthed = (uchar*)malloc(h.len+8);
	int index = 0;
	for(int i = 0;i<h.len;i++)
		lengthed[index++] = h.string[i];
	
	for(int i = 0;i<8;i++){
		uchar lsb = bits & 0xff;
		lengthed[index++] = lsb;
		bits = bits >> 8;
	}

	return lengthed;

}

// F(X,Y,Z) = XY v not(X) Z
// G(X,Y,Z) = XZ v Y not(Z)
// H(X,Y,Z) = X xor Y xor Z
// I(X,Y,Z) = Y xor (X v not(Z))

uint32_t func1(uint32_t X, uint32_t Y, uint32_t Z){
	return (X&Y) | ((!X) &Z);
}

uint32_t func2(uint32_t X, uint32_t Y, uint32_t Z){
	return (X&Z) | (Y & (!Z));
}

uint32_t func3(uint32_t X, uint32_t Y, uint32_t Z){
	return X ^ Y ^ Z;
}

uint32_t func4(uint32_t X, uint32_t Y, uint32_t Z){
	return Y ^ (X | (!Z));
}

     /* Let [abcd k s i] denote the operation
          a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s). */

void ROUND1(uint32_t *a, uint32_t b, uint32_t c, uint32_t d, int k, int s, int i, uint32_t X[]){
	uint32_t func1Out = func1(b,c,d);
	uint32_t sum = (*a + func1Out + X[k] + sinTable[i]);
	uint32_t shiftedSum = (sum << s) | (sum >> (32-s));
	*a = b + (shiftedSum);
}
     /* Let [abcd k s i] denote the operation
          a = b + ((a + G(b,c,d) + X[k] + T[i]) <<< s). */

void ROUND2(uint32_t *a, uint32_t b, uint32_t c, uint32_t d, int k, int s, int i, uint32_t X[]){
	uint32_t func2Out = func2(b,c,d);
	uint32_t sum = (*a + func2Out + X[k] + sinTable[i]);
	uint32_t shiftedSum = (sum << s) | (sum >> (32-s));
	*a = b + (shiftedSum);
}

void ROUND3(uint32_t *a, uint32_t b, uint32_t c, uint32_t d, int k, int s, int i, uint32_t X[]){
	uint32_t func3Out = func3(b,c,d);
	uint32_t sum = (*a + func3Out + X[k] + sinTable[i]);
	uint32_t shiftedSum = (sum << s) | (sum >> (32-s));
	*a = b + (shiftedSum);
}

void ROUND4(uint32_t *a, uint32_t b, uint32_t c, uint32_t d, int k, int s, int i, uint32_t X[]){
	uint32_t func4Out = func4(b,c,d);
	uint32_t sum = (*a + func4Out + X[k] + sinTable[i]);
	uint32_t shiftedSum = (sum << s) | (sum >> (32-s));
	*a = b + (shiftedSum);
}

char* addNum(char* s, int n){
	int i;
	for(i = 0;s[i] != '\0';i++)
		;
	int j;
	int temp = n;
	for(j = 0;temp>0;j++)
		temp /= 10;

	char *fullString = (char *)malloc(i+j+1);
	int index = 0;
	for(i = 0;s[i] != '\0';i++)
		fullString[index++] = s[i];

	for(;j>0;j--){
		char digit = (n / (power(10,j-1))) + '0';
		n = n % power(10, j-1);
		fullString[index++] = digit;
	}

	fullString[index] = '\0';
	return fullString;
}

int power(int base, int power){
	int ans = 1;
	for(;power>0;power--)
		ans *= base;

	return ans;
}

hash addPadding(char* s){
	int len;
	for(len = 0;s[len] != '\0';len++)
		;

	int bits = len * 8;
	int remainder = bits % 512;
	int bitsToAdd;
	if(remainder < 448)
		bitsToAdd = 448 - remainder;
	else
		bitsToAdd = (512 - remainder) + 448;

	int bytesToAdd = bitsToAdd / 8;
	uchar *paddedStr = (uchar *)malloc(len+bytesToAdd);

	int index = 0;
	for(int i = 0;s[i] != '\0';i++)
		paddedStr[index++] = s[i];
	paddedStr[index++] = 0x80;
	for(int i = 0;index<len+bytesToAdd;)
		paddedStr[index++] = 0;

	hash ans = {paddedStr,len+bytesToAdd,bits};

	return ans;
}

void fillSinTable(){
	for(int i = 0;i<64;i++){
		double sinn = sin(i+1);
		sinn = sinn > 0 ? sinn : -sinn;
		sinTable[i] = 4294967296 * sinn;
	}
}
