#include "set"
#include "../get_input.cpp"
#include <sstream>
#include <string>


int main(){
	std::string input = get_input(2018, 1);

	std::stringstream lines(input);
	std::string line;
	int frequency = 0;
	std::set<int> frequencies{};
	while(true){
		while(lines >> line){
			frequency += std::stoi(line);
			if(frequencies.count(frequency)){
				std::cout << "The answer is: " << frequency << '\n';
				exit(0);
			}
			else
				frequencies.insert(frequency);
		}
		lines.clear();
		lines.seekg(0);
	}
}
