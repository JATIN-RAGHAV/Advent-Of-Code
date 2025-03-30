#include "iostream"
#include "fstream"

int atoi(std::string line);

int main(){
	std::ifstream file("./text.txt",std::ios::in);

	if(!file.is_open())
		exit(1);

	std::string line;
	int first, second, third,current = 0;
	while(std::getline(file, line)){
		if(line.compare("") == 0){
			if(current > first){
				third = second;
				second = first;
				first = current;
			}
			else if(current > second){
				third = second;
				second = current;
			}
			else if(current > third)
				third = current;
			current = 0;
		}else{
			current += atoi(line);
		}
	}
	std::cout << "The answer is: " << first + second + third << '\n';
}

int atoi(std::string line){
	int size = line.size();
	int num = 0;
	for(int i = 0; i < size; i++)
		num = (num*10) + line[i] - '0';
	return num;
}
