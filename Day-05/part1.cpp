#include "../get_input.cpp"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <string>

std::string test{"dabAcCaCBAcCcaDA"};

int main(){
	std::string input = get_input(2018, 5);

	input.erase(std::remove_if(input.begin(), input.end(), isspace),input.end());

	int start_size = input.size();
	int rem_size = start_size;
	for(int i = 0;i<start_size-1;i++){
		if(abs(input[i] - input[i+1]) == 'a' - 'A'){
			input[i] = input[i+1] = 0;
			rem_size -= 2;
			int pre = i;
			while(pre > -1 && input[pre] == 0)
				pre--;
			int post = i + 2;
			while(pre > -1 && post < start_size && abs(input[pre] - input[post]) == 'a' - 'A'){
				input[pre] = input[post] = 0;
				rem_size -= 2;
				while(pre > -1 && input[pre] == 0)
					pre--;
				post++;
			}
			i = post-1;
		}
	}
	std::cout << "Remaining size: " << rem_size << std::endl;
}
