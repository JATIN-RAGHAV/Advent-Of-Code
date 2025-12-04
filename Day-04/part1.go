package main

import (
	"fmt"
	"os"
	"strings"
)

func main1(){
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

	data_bytes,_ := os.ReadFile("text.txt")
	data := strings.Split(strings.Trim(string(data_bytes),"\n "), "\n");

	rows := len(data);
	cols := len(data[0]);
	var grid[][]bool = make([][]bool,rows);
	for i,_ := range grid{
		grid[i] = make([]bool, cols);
		for j,c := range data[i]{
			grid[i][j] = (c == '@');
		}
	}

	res := 0;
	for i,_ := range grid{
		for j,_ := range grid[i]{
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
					res++;
				}
			}
		}
	}
	fmt.Print(res,"\n");
}
