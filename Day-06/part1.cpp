#include "../get_input.cpp"
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

std::string test = "1, 1\n1, 6\n8, 3\n3, 4\n5, 5\n8, 9";

int main(){
	std::string input = get_input(2018, 6);

	std::vector<std::vector<int>> list;

	std::regex pattern(R"((\d+), (\d+))");
	std::string line;
	std::stringstream lines{input};
	std::smatch match;
	while(std::getline(lines, line)){
		if(std::regex_search(line, match, pattern)){
			list.push_back({std::stoi(match[1].str()),std::stoi(match[2].str())});
		}
	}

	std::vector<std::vector<int>> bounded;
	int xBoundMax , yBoundMax, xBoundMin, yBoundMin;
	xBoundMax = yBoundMax = 0;
	xBoundMin = yBoundMin = std::numeric_limits<int>::max();

	for(int i = 0;i<list.size(); i++){
		bool posX, posY, negX, negY;
		posX = posY = negX = negY = false;
		for(int j = 0; j<list.size(); j++){
			if(i != j){
				int relX = list[j][0] - list[i][0];
				int relY = list[j][1] - list[i][1];
				if(relX >= 0){
					if(relY >= 0){
						if(relX == relY)
							posX = posY = true;
						else if(relX > relY)
							posX = true;
						else
							posY = true;
					}
					else{
						if(relX == -relY)
							negY = posX = true;
						else if(relX > -relY)
							posX = true;
						else
							negY = true;
					}
				}else{
					if(relY >= 0){
						if(-relX == relY)
							negX = posY = true;
						else if(-relX > relY)
							negX = true;
						else
							posY = true;
					}else{
						if(relX == relY)
							negX = negY = true;
						else if(relX < relY)
							negX = true;
						else
							negY = true;
					}
				}
			}
		}
		if(posX and posY and negX and negY){
			bounded.push_back(list[i]);
		}
		else{
			if(list[i][0] < xBoundMin)
				xBoundMin = list[i][0];
			else if(list[i][0] > xBoundMax)
				xBoundMax = list[i][0];
			if(list[i][1] < yBoundMin)
				yBoundMin = list[i][1];
			else if(list[i][1] > yBoundMax)
				yBoundMax = list[i][1];
		}
	}

	int* areas= new int[bounded.size()];

	for(int x = xBoundMin; x<=xBoundMax; x++){
		for(int y = yBoundMin; y<=yBoundMax; y++){
			int min_dist = std::numeric_limits<int>::max();
			int closest_coordinate_x, closest_coordinate_y;
			for(int i = 0;i < list.size(); i++){
				int dist = abs(list[i][0] - x) + abs(list[i][1] - y);
				if(dist < min_dist){
					min_dist = dist;
					closest_coordinate_x = list[i][0];
					closest_coordinate_y = list[i][1];
				}
			}
			int min_dist_count = 0;
			for(int i = 0;i < list.size(); i++){
				int dist = abs(list[i][0] - x) + abs(list[i][1] - y);
				if(dist == min_dist){
					min_dist_count++;
				}
			}
			if(min_dist_count == 1)
				for(int i = 0;i<bounded.size();i++){
					if(bounded[i][0] == closest_coordinate_x and bounded[i][1] == closest_coordinate_y){
						areas[i]++;
					}
				}
		}
	}

	int max_coordinate_x, max_coordinate_y;
	int max_area = 0;
	for(int i = 0;i < bounded.size(); i++){
		if(areas[i] > max_area){
			max_area = areas[i];
			max_coordinate_x = bounded[i][0];
			max_coordinate_y = bounded[i][1];
		}
	}

	printf("Max Area Coordinate: [%d,%d], Area: %d\n",max_coordinate_x, max_coordinate_y, max_area);
}
