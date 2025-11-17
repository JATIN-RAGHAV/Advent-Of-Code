package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

func negate(x int)int{
	if x >= 0{
		return 2*x
	}else{
		return -(2*x) - 1
	}
}

func Szudzik(x,y int)int{
	if x > y{
		return (x*x) + x + y
	}else{
		return (y*y) + x + y
	}
}

func main(){
	data, err := os.ReadFile("./text.txt")
	if err != nil {
		panic(err)
	}
	my_arr := strings.Split(strings.TrimSpace(string(data)),",")
	var places [1000][1000]bool
	current :=0
	X,Y:= 500,500
	places[X][Y] = true
	done := false
	for i := range my_arr{
		my_arr[i] = strings.Trim(my_arr[i]," ")
		s := strings.Trim(my_arr[i],"RL")
		steps,err := strconv.Atoi(s)
		if err != nil{
			panic(err)
		}
		if my_arr[i][0] == 'R'{
			current++;
		}else{
			current--;
		}
		current = (current+4)%4
		switch current{
		case 0:
		for i:=0;i<steps;i++{
			Y++
			if places[X][Y] {
				done=true;break
			}
			places[X][Y]=true
		}
		case 1:
		for i:=0;i<steps;i++{
			X++
			if places[X][Y] {
				done=true;break
			}
			places[X][Y]=true
		}
		case 2:
		for i:=0;i<steps;i++{
			Y--
			if places[X][Y] {
				done=true;break
			}
			places[X][Y]=true
		}
		case 3:
		for i:=0;i<steps;i++{
			X--
			if places[X][Y] {
				done=true;break
			}
			places[X][Y]=true
		}
		}
		if done {
			break
		}
	}
	ans := AbsInt(X-500) + AbsInt(Y-500)
	fmt.Println("Answer if finally as it turns out to be",ans)
}

func AbsInt(x int)int{
	if x<0{
		return -x
	}else{
		return x
	}
}
