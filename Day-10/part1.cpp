#include "../get_input.cpp"
#include <cstdio>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <unistd.h>

typedef struct{
	int X;
	int Y;
	int Vx;
	int Vy;
}point;

std::string test{"position=< 9,  1> velocity=< 0,  2>\nposition=< 7,  0> velocity=<-1,  0>\nposition=< 3, -2> velocity=<-1,  1>\nposition=< 6, 10> velocity=<-2, -1>\nposition=< 2, -4> velocity=< 2,  2>\nposition=<-6, 10> velocity=< 2, -2>\nposition=< 1,  8> velocity=< 1, -1>\nposition=< 1,  7> velocity=< 1,  0>\nposition=<-3, 11> velocity=< 1, -2>\nposition=< 7,  6> velocity=<-1, -1>\nposition=<-2,  3> velocity=< 1,  0>\nposition=<-4,  3> velocity=< 2,  0>\nposition=<10, -3> velocity=<-1,  1>\nposition=< 5, 11> velocity=< 1, -2>\nposition=< 4,  7> velocity=< 0, -1>\nposition=< 8, -2> velocity=< 0,  1>\nposition=<15,  0> velocity=<-2,  0>\nposition=< 1,  6> velocity=< 1,  0>\nposition=< 8,  9> velocity=< 0, -1>\nposition=< 3,  3> velocity=<-1,  1>\nposition=< 0,  5> velocity=< 0, -1>\nposition=<-2,  2> velocity=< 2,  0>\nposition=< 5, -2> velocity=< 1,  2>\nposition=< 1,  4> velocity=< 2,  1>\nposition=<-2,  7> velocity=< 2, -2>\nposition=< 3,  6> velocity=<-1, -1>\nposition=< 5,  0> velocity=< 1,  0>\nposition=<-6,  0> velocity=< 2,  0>\nposition=< 5,  9> velocity=< 1, -2>\nposition=<14,  7> velocity=<-2,  0>\nposition=<-3,  6> velocity=< 2, -1>"};

void print_grid(bool** grid, int row, int col);

int main(){
	std::string input = get_input(2018, 10);
	std::string line;
	std::stringstream lines{input};
	std::vector<point*> points;
	std::regex pattern(R"((-*\d+), +(-*\d+)[^\d-]+(-*\d+), +(-*\d+))");
	std::smatch match;
	int max_x, max_y, min_x, min_y, min_y_vel, max_y_vel;
	max_x = max_y = min_x = min_y = 0;
	while(std::getline(lines, line)){
		if(std::regex_search(line, match, pattern)){
			int X = std::stoi(match[1].str());
			int Y = std::stoi(match[2].str());
			int Vx = std::stoi(match[3].str());
			int Vy = std::stoi(match[4].str());
			point* this_point = new point;
			this_point->X = X + (Vx);
			this_point->Y = Y + (Vy);
			this_point->Vx = Vx;
			this_point->Vy = Vy;
			if(this_point->X > max_x)
				max_x = this_point->X;
			if(this_point->Y > max_y){
				max_y = this_point->Y;
				max_y_vel = this_point->Vy;
			}

			if(this_point->X < min_x)
				min_x = this_point->X;
			if(this_point->Y < min_y){
				min_y = this_point->Y;
				min_y_vel = this_point->Vy;
			}
			points.push_back(this_point);
		}
	}
	int time = 0;
	while(max_y - min_y > 30){
		max_y += max_y_vel;
		min_y += min_y_vel;
		time++;
	}

	min_y = min_x = 10000;
	for(auto p : points){
		p->X += p->Vx*time;
		p->Y += p->Vy*time;
		if(min_y > p->Y)
			min_y = p->Y;
		if(min_x > p->X)
			min_x = p->X;
	}

	max_x = max_y = 0;
	for(auto p : points){
		p->X -= min_x;
		p->Y -= min_y;
		if(p->X > max_x)
			max_x = p->X;
		if(p->Y > max_y)
			max_y = p->Y;
	}


	bool** grid = new bool*[max_x+2];
	for(int i = 0; i <= max_x; i++)
		grid[i] = new bool[max_y+2];

	// Initializing Grid
	for(int x = 0; x <= max_x; x++){
		for(int y = 0; y <= max_y; y++){
			grid[x][y] = false;
		}
	}

	for(auto p : points) grid[p->X][p->Y] = true;

	while(true){
		for(auto p : points){
			grid[p->X][p->Y] = false;
			p->X += p->Vx;
			p->Y += p->Vy;
			grid[p->X][p->Y] = true;
		}
		std::cout << "Time: " << ++time << '\n';
		print_grid(grid,max_x , max_y);
		sleep(1);
	}


}

void print_grid(bool** grid, int x_len, int y_len){
	for(int y = 0; y <= y_len ; y++){
		for(int x = 0; x <= x_len ; x++){
			if(grid[x][y])
				printf("# ");
			else
				printf(". ");
		}
		putchar(10);
	}
}
