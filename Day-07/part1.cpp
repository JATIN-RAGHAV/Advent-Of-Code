#include "../get_input.cpp"
#include <cstdio>
#include <sstream>
#include <string>
#include <regex>
#include <vector>

std::string test{"Step C must be finished before step A can begin.\nStep C must be finished before step F can begin.\nStep A must be finished before step B can begin.\nStep A must be finished before step D can begin.\nStep B must be finished before step E can begin.\nStep D must be finished before step E can begin.\nStep F must be finished before step E can begin."};

int main(){
	std::string input = get_input(2018, 7);
	std::string line;
	std::stringstream lines{input};
	std::regex pattern("[A-Z][^A-Z]*([A-Z])[^A-Z]*([A-Z])[^A-Z]*");
	std::smatch match;
	std::vector<char*> relations;

	std::vector<int>* pointed_by[26];
	for(int i = 0; i<26;i++)
		pointed_by[i] = new std::vector<int>;

	int frontier[26]{0};
	while(std::getline(lines, line)){
		if(std::regex_search(line, match, pattern)){
			char start = match[1].str()[0] - 'A';
			char end = match[2].str()[0] - 'A';
			char* relation = new char[2];
			relation[0] = start;
			relation[1] = end;
			relations.push_back(relation);
			pointed_by[end]->push_back(start);
			if(frontier[start] == 0)
				frontier[start] = 1;
			frontier[end] = -1;
		}
	}

	std::string task_order{""};
	int completed[26]{0};

	while(true){
		int current_task = -1;
		for(int i = 0;i<26; i++){
			if(frontier[i] == 1){
				current_task = i;
				frontier[i] = 0;
				completed[i] = 1;
				break;
			}
		}
		if(current_task == -1)
			break;
		task_order.push_back(current_task+'A');

		for(int i = 0; i<relations.size(); i++){
			if(relations[i][0] == current_task){
				char potential_frontier = relations[i][1];
				bool can_work = true;
				for(char prev : *pointed_by[potential_frontier]){
					if(completed[prev] == 0)
						can_work = false;
				}
				if(can_work)
					frontier[potential_frontier] = 1;
			}
		}
	}

	std::cout << task_order << std::endl;
}
