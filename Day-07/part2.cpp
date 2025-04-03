#include "../get_input.cpp"
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
	int time_taken = 0;
	int completed[26]{0};
	int* current_tasks[5];
	for( int i = 0; i<5;i++){
		current_tasks[i] = new int[2];
		current_tasks[i][0] = -1;
	}
	int current_tasks_count = 0;

	while(true){
		for(int i = 0;i<26 and current_tasks_count < 5; i++){
			if(frontier[i] == 1){
				for(int j = 0; j<5;j++){
					if(current_tasks[j][0] == -1){
						current_tasks_count++;
						current_tasks[j][0] = i;
						current_tasks[j][1] = i+1 + 60;
						break;
					}
				}
				frontier[i] = 0;
			}
		}
		if(current_tasks_count == 0)
			break;

		int shortest_task{0};
		int shortest_time = 60 + 26;

		for(int i = 0;i<5;i++)
			if(current_tasks[i][0] != -1 and current_tasks[i][1] < shortest_time){
				shortest_task = i;
				shortest_time = current_tasks[i][1];
			}
		time_taken += shortest_time;
		for(int i = 0; i<5; i++)
				current_tasks[i][1] -= shortest_time;

		int current_task = current_tasks[shortest_task][0];
		current_tasks[shortest_task][0] = -1;
		current_tasks_count--;
		task_order.push_back(current_task+'A');
		completed[current_task] = 1;

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
	std::cout << "Time Taken: " << time_taken << std::endl;
}
