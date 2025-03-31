#include "../get_input.cpp"
#include <iostream>
#include <sstream>
#include <string>

int main(){
	std::string input = get_input(2018, 1);
	std::istringstream lines(input);

	int sum = 0;
	std::string number;
	while(lines >> number){
		sum += std::stoi(number);
	}

	std::cout << "The sum is: " << sum << '\n';
}
