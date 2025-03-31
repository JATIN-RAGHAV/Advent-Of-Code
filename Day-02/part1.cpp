#include "../get_input.cpp"
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

bool check_frequency(std::string w,int freq);

int main(){
	std::string input = get_input(2018, 2);
	std::istringstream lines(input);
	std::string line;
	int count2, count3 = 0;
	while(lines >> line){
		if(check_frequency(line, 2))
			count2++;
		if(check_frequency(line, 3))
			count3++;
	}
	std::cout <<  ", The checksum returns: " << count2 * count3 << std::endl;
}

bool check_frequency(std::string w,int freq){
	int size = w.size();
	for(int i = 0;i < size - 1;i++){
		int count = 1;
		if(w[i]){
			for(int j = i+1;j < size;j++){
				if(w[j] == w[i]){
					w[j] = 0;
					count++;
				}
			}
			if(count == freq)
				return true;
		}
	}
	return false;
}
