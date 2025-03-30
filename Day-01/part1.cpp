#include "iostream" 
#include <cstdlib>
#include <fstream>
#include <string>

int matoi(std::string line);

int main(){
	std::ifstream file("./text.txt",std::ios::in);
	
	if(file.is_open()){
		std::string line;
		auto max = 0;
		auto current = 0;
		while(std::getline(file, line)){
			if(line.compare("") == 0){
				if(current > max)
					max = current;
				current = 0;
			}
			else{
				int num = matoi(line);
				current += num;
			}
		}
		std::cout << "The answer is: " << max << std::endl;
	}
	file.close();
}
int matoi(std::string line){
	auto size = line.size();
	auto num  = 0;
	for(int i = 0;i<size; i++){
		num = (num*10) + line[i] - '0';
	}
	return num;
}
