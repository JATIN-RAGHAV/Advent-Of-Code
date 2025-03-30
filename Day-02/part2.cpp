#include "iostream"
#include <fstream>
#include <ostream>
#include <string>

int main(){
	std::fstream file("text.txt",std::ios::in);
	if(file.is_open()){
		std::string line;
		int score, current, other = 0;
		while(std::getline(file, line)){
			other = line[0] - 'A' + 1;
			switch (line[2]) {
				case 'X':
					if(other >= 2)
						current += other - 1;
					else
						current = 3;
					break;
				case 'Y':
					current += 3 + other;
					break;
				case 'Z':
					current += 6;
					if(other <= 2)
						current += other + 1;
					else
						current += 1;
			}
			score += current;
			current = 0;
		}
		std::cout << "The answer is: " << score << std::endl;
		file.close();
	}
}
