import fs from 'fs';

let testData = `Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green`

let data = fs.readFileSync('day2.txt','utf-8');
data = data.split('\n');

testData = testData.split('\n');

const findMax = (s)=>{
    s = s.split(':')[1].split(/,|;/g);
    let ans = {
        "red":0,
        "blue":0,
        "green":0
    };
    for(let i = 0; i<s.length;i++){
        const [_,count, colour] = s[i].split(' ');
        ans[colour] += parseInt(count);
    }
    return ans;
}

const findMin = (s) =>{
    s = s.split(':')[1].split(/,|;/g);
    let ans = {
        "red":0,
        "blue":0,
        "green":0
    };
    for(let i = 0; i<s.length;i++){
        let [_,count, colour] = s[i].split(' ');
        count = parseInt(count);
        if(ans[colour] < count) {
            ans[colour] = (count)
        };
    }
    return ans;
}

const isPossible = (s)=>{
    let min = findMin(s);
    if(min.red>12 || min.green > 13 || min.blue > 14) {
        console.log(min);
        return false
    };
    return true;
}

const findPower = (s) =>{
    let min = findMin(s);
    return min.red*min.green*min.blue;
}

let sum = 0;

// for(let i = 0;i<data.length;i++){
//     if(isPossible(data[i])){
//         sum += i+1;
//         console.log(`True ${data[i]}`)
//     }
// }

for(let i = 0;i<testData.length;i++){
    sum += findPower(testData[i]);
}
console.log(sum)