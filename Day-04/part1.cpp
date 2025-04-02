#include "../get_input.cpp"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>

// [1518-11-01 00:00] Guard #10 begins shift
// [1518-11-01 00:05] falls asleep
// [1518-11-01 00:25] wakes up
// [1518-11-01 00:30] falls asleep
// [1518-11-01 00:55] wakes up
// [1518-11-01 23:58] Guard #99 begins shift
// [1518-11-02 00:40] falls asleep
// [1518-11-02 00:50] wakes up
// [1518-11-03 00:05] Guard #10 begins shift
// [1518-11-03 00:24] falls asleep
// [1518-11-03 00:29] wakes up
// [1518-11-04 00:02] Guard #99 begins shift
// [1518-11-04 00:36] falls asleep
// [1518-11-04 00:46] wakes up
// [1518-11-05 00:03] Guard #99 begins shift
// [1518-11-05 00:45] falls asleep
// [1518-11-05 00:55] wakes up

char test[] = "[1518-11-01 00:00] Guard #10 begins shift\n[1518-11-01 00:05] falls asleep\n[1518-11-01 00:25] wakes up\n[1518-11-01 00:30] falls asleep\n[1518-11-01 00:55] wakes up\n[1518-11-01 23:58] Guard #99 begins shift\n[1518-11-02 00:40] falls asleep\n[1518-11-02 00:50] wakes up\n[1518-11-03 00:05] Guard #10 begins shift\n[1518-11-03 00:24] falls asleep\n[1518-11-03 00:29] wakes up\n[1518-11-04 00:02] Guard #99 begins shift\n[1518-11-04 00:36] falls asleep\n[1518-11-04 00:46] wakes up\n[1518-11-05 00:03] Guard #99 begins shift\n[1518-11-05 00:45] falls asleep\n[1518-11-05 00:55] wakes up";

int main(){
	std::string input = get_input(2018, 4);
	std::istringstream lines(input);
	std::vector<std::string> entries;
	std::string line;
	int cout = 0;
	while(std::getline(lines, line)){
		entries.push_back(line);
	}
	std::sort(entries.begin(), entries.end(), [](std::string first, std::string second){
		return strcmp(first.substr(0,19).c_str(), second.substr(0,19).c_str()) < 0;
	});
	int size = entries.size();
	std::regex pattern_full(R"(\[\d+-(\d+)-(\d+) (\d+):(\d+)\])");
	std::regex pattern_id(R"(#(\d+))");
	std::smatch match;
	int current_guard, prev_guard = 0;
	int prevHr, prevMin, Hr, Min = 0;
	std::unordered_map<int, int*> guard_map;
	bool is_sleeping = false;
	for(int i = 0;i<size;i++){
		if(std::regex_search(entries[i], match, pattern_full)){
			prevHr = Hr;
			prevMin = Min;
			Hr = std::stoi(match[3]);
			Min = std::stoi(match[4]);
			if(entries[i].find("Gua") != -1){
				std::regex_search(entries[i], match,pattern_id);
				prev_guard = current_guard;
				current_guard = std::stoi(match[1].str());
				if(guard_map.count(current_guard) == 0){
					int* mins = new int[60];
					for(int j = 0;j<60;j++)
						mins[j] = 0;
					guard_map.insert({current_guard, mins});
				}
				if(is_sleeping){
					int sleep_time = 60 - prevMin;
					for(int j = prevMin-1;j<60;j++)
						guard_map[prev_guard][j]++;
				}
				is_sleeping = false;
			}
			else if(entries[i].find("wa") != -1){
				printf("PrevHr:%d, Hr:%d, PrevMin:%d, Min:%d, is_sleeping:%d, current_guard:%d\n",prevHr, Hr,prevMin,Min, is_sleeping,current_guard);
				if(prevHr == 23)
					for(int j = 0;i<Min-1; i++)
						guard_map[current_guard][j]++;
				else
					for(int j = prevMin - 1;j<Min-1; j++)
						guard_map[current_guard][j]++;
				is_sleeping = false;
			}else{
				is_sleeping = true;
			}
		}
	}

	int max_sleep_id = 0;
	int max_sleep_time = 0;

	for(const auto& pair : guard_map){
		int id = pair.first;
		int* sleeps = pair.second;

		int current_sleep = 0;
		for(int i = 0;i<60; i++)
			current_sleep += sleeps[i];

		if(current_sleep > max_sleep_time){
			max_sleep_time = current_sleep;
			max_sleep_id = id;
		}
	}
	int max_min = 0;
	for(int i = 0;i<60;i++){
		if(guard_map[max_sleep_id][i] > guard_map[max_sleep_id][max_min])
			max_min = i;
	}
	
	max_min++;

	std::cout << "ID: " << max_sleep_id << ", TIME: " << max_min << ", ANS: " << max_sleep_id* max_min << std::endl;
}
