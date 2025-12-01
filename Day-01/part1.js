import fs from 'fs'
let data= fs.readFileSync("./test.txt",'utf-8')
//data = "L68\nL30\nR48\nL5\nR60\nL55\nL1\nL99\nR14\nL82"

data = data.trim().split('\n').map(e => {
        return [e[0],parseInt(e.substring(1))]
})

let curr = 50
let ans = 0
for(let i = 0;i<data.length;i++){
        let [dir,steps] = data[i]
        if(dir == 'L'){
                curr = (curr - steps+100)%100
        }
        else{
                curr = (curr + steps+100)%100
        }
        if(curr == 0){
                ans++
        }
}

console.log("answer is ",ans)
