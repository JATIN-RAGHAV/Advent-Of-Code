#include "iostream"
#include <fstream>
#include <string>

int main(){
	std::ifstream file("./text.txt",std::ios::in);
	
	if(file.is_open()){
		int other, current,score = 0;
		std::string line;
		while(std::getline(file,line)){
			current += line[2] - 'W';
			other = line[0] - 'A' + 1;
			if(other == current){
				current += 3;
			}
			else if(other - current == -1 | other - current == 2){
				current += 6;
			}
			score += current;
			current = 0;
		}
		std::cout << "The answer is: " << score << std::endl;
		file.close();
	}
}
