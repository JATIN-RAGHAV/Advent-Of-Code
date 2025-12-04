package main

import (
	"fmt"
	"os"
	"strings"
)

func solve(grid [][]bool) int{
	directions := [][]int{
		{-1,-1},
		{-1,0},
		{-1,1},
		{0,-1},
		{0,1},
		{1,-1},
		{1,0},
		{1,1},
	}
	rows := len(grid)
	cols := len(grid[0])
	res := 0;
	for i := range grid{
		for j := range grid[i]{
			if grid[i][j]{
				cnts := 0
				for _,dir := range directions{
					ni := dir[0]+i
					nj := dir[1]+j
					if ni < rows && ni >= 0 && nj < cols && nj>=0{
						if grid[ni][nj] {
							cnts++;
						}
					}
				}
				if cnts < 4{
					grid[i][j] = false
					res++;
				}
			}
		}
	}
	return res
}

func main(){

	data_bytes,_ := os.ReadFile("text.txt")
	data := strings.Split(strings.Trim(string(data_bytes),"\n "), "\n");

	rows := len(data);
	cols := len(data[0]);
	var grid[][]bool = make([][]bool,rows);
	for i := range grid{
		grid[i] = make([]bool, cols);
		for j,c := range data[i]{
			grid[i][j] = (c == '@');
		}
	}
	res := 0
	for {
		curr := solve(grid)
		if curr > 0{
			res += curr;
		}else{
			break
		}
	}
	fmt.Print(res,"\n");
}
