#include "../get_input.cpp"
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

// #1 @ 493,113: 12x14

char grid[1000][1000] = {0};

int main(){
	std::string input = get_input(2018, 3);

	std::stringstream lines(input);
	std::string line;
	std::regex pattern(R"(#(\d+) @ (\d+),(\d+): (\d+)x(\d+))");
	int ans_id;

	while(std::getline(lines,line)){
		std::smatch match;
		if(std::regex_search(line, match, pattern)){
			int id = std::stoi(match[1].str());
			int i = std::stoi(match[2].str());
			int j = std::stoi(match[3].str());
			int width = std::stoi(match[4].str());
			int height = std::stoi(match[5].str());

			for(int x = i;x < i+width; x++){
				for(int y = j;y < j+height; y++){
					grid[x][y]++;
				}
			}
		}
		else
			std::cout << "No match found.";
	}
	lines.clear();
	lines.seekg(0);
	while(std::getline(lines,line)){
		std::smatch match;
		if(std::regex_search(line, match, pattern)){
			int id = std::stoi(match[1].str());
			int i = std::stoi(match[2].str());
			int j = std::stoi(match[3].str());
			int width = std::stoi(match[4].str());
			int height = std::stoi(match[5].str());
			int overlap = 0;

			for(int x = i;x < i+width; x++){
				for(int y = j;y < j+height; y++){
					if(grid[x][y] > 1)
						overlap++;
				}
			}
			if(overlap == 0)
				ans_id = id;
		}
		else
			std::cout << "No match found.";
	}
	std::cout << "Non overlapping id is: " << ans_id << std::endl;
}
