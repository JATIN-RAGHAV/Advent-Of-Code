package main


import (
	"fmt"
	"os"
	"strings"
)

func check(e error){
	if e!=nil{panic(e)}
}

func main(){
	data,e := os.ReadFile("./text.txt")
	check(e)
	lines := strings.Split(strings.TrimSpace(string(data)),"\n")

	curr := '5'
	res := ""
	for _,x := range lines{
		for _,c := range x{
			switch c{
			case 'L':
				if !strings.ContainsRune("125AD",curr){
					curr -= 1
				}
			case 'R':
				if !strings.ContainsRune("149CD",curr){
					curr += 1
				}
			case 'U':
				if !strings.ContainsRune("12549",curr){
					if curr == '3'{
						curr = '1'
					}else if strings.ContainsRune("678",curr){
						curr -= 4
					}else if strings.ContainsRune("ABC",curr){
						curr = '6' + curr - 'A'
					}else{
						curr = 'B'
					}
				}
			case 'D':
				if !strings.ContainsRune("5ADC9",curr){
					if curr == '1'{
						curr = '3'
					}else if strings.ContainsRune("234",curr){
						curr += 4
					}else if strings.ContainsRune("678",curr){
						curr = 'A' + curr - '6'
					}else{
						curr = 'D'
					}
				}
			}
		}
		res += string(curr)
	}
	fmt.Println(res)
}
/*    1
  2 3 4
5 6 7 8 9
  A B C
    D
*/
