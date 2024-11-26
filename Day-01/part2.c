#include "stdio.h"

int main(){
	int c,i,n;
	int nums[203];

	i = n = 0;
	FILE* fileptr = fopen("text.txt", "r");
	while((c = fgetc(fileptr)) != EOF){
		if(c != '\n')
			n = (n * 10) + (c - '0');
		else{
			nums[i] = n;
			n = 0;
			i++;
		}
	};

	int brek = 0;
	for(n = 0;n < i-2; n++){
		for(int j = 0; j<i-1;j++){
			for(int k = 0; k<i;k++){
				if(nums[n] + nums[j] + nums[k] == 2020){
					printf("%d\n",nums[n]*nums[j]*nums[k]);
					brek = 1;
					break;
				}
			}
			if(brek == 1)
				break;
		}
		if(brek == 1)
			break;
	}
}
