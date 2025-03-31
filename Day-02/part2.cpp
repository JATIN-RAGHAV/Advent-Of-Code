#include "../get_input.cpp"
#include <iostream>
#include <string>
#include <vector>

bool is_correct_pair(std::string str1, std::string str2);

int main(){
	std::string input = get_input(2018, 2);
	std::vector<std::string> ids;
	std::stringstream lines(input);
	std::string line;

	while(lines >> line){
		ids.push_back(line);
	}
	
	std::sort(ids.begin(), ids.end());

	std::string ans{""};

	for(int i = 0;i < ids.size()-1; i++){
		if(is_correct_pair(ids[i], ids[i+1])){
			std::cout << "pair: " << ids[i] << ':' << ids[i+1] << std::endl;
			for(int j = 0;j<ids[i].size();j++)
				if(ids[i][j] == ids[i+1][j])
					ans+=ids[i][j];
			std::cout << "Ans is: " << ans << std::endl;
			exit(0);
		}
	}
}

bool is_correct_pair(std::string str1, std::string str2){
	int size = str1.size();
	int diff = 0;
	for(int i = 0;i<size; i++){
		if(str1[i] != str2[i])
			diff++;
	}
	return diff == 1;
}
