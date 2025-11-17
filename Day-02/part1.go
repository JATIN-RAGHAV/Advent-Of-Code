
import (
	"fmt"
	"os"
	"strings"
)

func check(e error){
	if e != nil{
		panic("error check")
	}
}

func main(){
	data,err := os.ReadFile("./text.txt")
	check(err)
	lines := strings.Split(strings.TrimSpace(string(data)), "\n")

	curr := '5'
	res := ""
	for _,x := range lines{
		for _,c := range x{
			switch c {
			case 'L':
				if(!strings.ContainsRune("147",curr)){
					curr -= 1
				}
			case 'R':
				if(!strings.ContainsRune("369",curr)){
					curr += 1
				}
			case 'U':
				if(!strings.ContainsRune("123",curr)){
					curr -= 3
				}
			case 'D':
				if(!strings.ContainsRune("789",curr)){
					curr += 3
				}
			}
		}
		res += string(curr)
	}
	fmt.Println(res)
}
