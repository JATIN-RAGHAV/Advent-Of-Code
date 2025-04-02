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

	int min_len = start_size;

	for(char c = 'a'; c<='z'; c++){

		std::string current{""};
		for(int i = 0;i < start_size; i++){
			if(input[i] != c && input[i] != c + 'A' - 'a')
				current.push_back(input[i]);
		}
		
		int current_size = current.size();
		int rem_size = current_size;

		for(int i = 0;i<current_size-1;i++){
			if(abs(current[i] - current[i+1]) == 'a' - 'A'){
				current[i] = current[i+1] = 0;
				rem_size -= 2;
				int pre = i;
				while(pre > -1 && current[pre] == 0)
					pre--;
				int post = i + 2;
				while(pre > -1 && post < start_size && abs(current[pre] - current[post]) == 'a' - 'A'){
					current[pre] = current[post] = 0;
					rem_size -= 2;
					while(pre > -1 && current[pre] == 0)
						pre--;
					post++;
				}
				i = post-1;
			}
		}

		if(rem_size < min_len)
			min_len = rem_size;
	}

	std::cout << "Remaining size: " << min_len<< std::endl;
}
