#include "../get_input.cpp"
#include <cstdint>
#include <cstdio>
#include <vector>
#include <regex>

std::string test{"9 players; last marble is worth 25 points"};
std::string test1{"10 players; last marble is worth 1618 points"};
std::string test2{"13 players; last marble is worth 7999 points"};
std::string test3{"17 players; last marble is worth 1104 points"};
std::string test4{"21 players; last marble is worth 6111 points"};
std::string test5{"30 players; last marble is worth 5807 points"};


class Game{
	std::vector<int> marbles;
	int current;
	public:
	Game();
	int play(int marble_number);
};

int main(){
	std::string input = get_input(2018,9);
	std::regex pattern(R"((\d+)[^\d]+(\d+)[^\d])");
	std::smatch match;
	if(std::regex_search(input, match, pattern)){
		int players = std::stoi(match[1].str());
		int max_marble = std::stoi(match[2].str())*100;

		printf("Players: %d, Marbles: %d\n",players, max_marble);
		printf("%d\n",max_marble);

		Game my_game = Game();
		std::int64_t* scores = new std::int64_t[players];

		for(int i = 0;i<players; i++){
			scores[i] = 0;
		}

		for(int i = 1; i<=max_marble; i++){
			int current_player = (i % players) - 1;
			int score = my_game.play(i);
			scores[current_player] += score;
			printf("%d\r",i);
		}

		std::int64_t max_score = 0;
		for(int i = 0; i<players; i++)
			if(max_score < scores[i])
				max_score = scores[i];

		std::cout << "Max Score: " << max_score << std::endl;
		delete[] scores;
	}	

}

Game::Game(): marbles{0}, current{0}{};

int Game::play(int marble_number){
	if(marble_number % 23 == 0){
		int score = marble_number;
		int index_to_remove;
		if(current-7 >=0)
			index_to_remove = current - 7;
		else
			index_to_remove = marbles.size() + (current - 7);
		score += marbles[index_to_remove];
		marbles.erase(marbles.begin()+index_to_remove);
		current = index_to_remove == marbles.size()? 0 : index_to_remove;
		return score;
	}else{
		if(marbles.size() == 1){
			marbles.push_back(marble_number);
			current = 1;
		}
		else if(marbles.size() == 2){
			marbles.insert(marbles.begin()+1, marble_number);
			current = 1;
		}
		else{
			int insert_index;
			if(marbles.size() - current <= 2)
				insert_index = marbles.size() - current == 2 ? 0 : 1;
			else
				insert_index = current + 2;
			marbles.insert(marbles.begin()+insert_index, marble_number);
			current = insert_index;
		}
	}
	return 0;
}
