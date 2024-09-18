import fs from "fs";

let data = fs.readFileSync("./day3.txt", "utf-8").split("\n");

const testData = `467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..`.split("\n");

// Finds the numbers in a give string
const findGear = (s) => {
    const regex = /\*/g;
    return [...s.matchAll(regex)].map((n) => {
      return n.index;
    });
};

// Find number at a given index given a string
const findNum = (s, index)=>{
    let beforeString = '';
    let afterString = '';
    if(!isNaN(s[index-1])){
        if(isNaN(s[index-2])){
            beforeString = s[index-1];
        }else{
            beforeString = s[index-2]+s[index-1];
        }
    }
    if(!isNaN(s[index+1])){
        if(isNaN(s[index+2])){
            afterString = s[index+1];
        }else{
            afterString = s[index+1]+s[index+2];
        }
    }
    return parseInt(beforeString+s[index]+afterString);
}

// Tells how many numbers the given string contains
const numberCount = (s, start,m) => {
    let nums = [false, false, false];
    // When is the row containing the gear
    if(m){
        if(!isNaN(s[start])){
            nums[0] = true;
        }
        if(!isNaN(s[start+2])){
            nums[2] = true;
        }
    }
    else{
        if(isNaN(s[start])){
            nums[2] = !isNaN(s[start+1]+s[start+2])
        }else{
            nums[0] = true;
            if(isNaN(s[start+1])){
                nums[2] = !isNaN(s[start+2]);
            }else{
                nums[1] = true;
            }
        }
    }

    // Finding the final return value
    let returnValue = {
        nums:0,
        product:1
    }
    if(nums[1]){
        let num = findNum(s,start+1);
        returnValue.nums = 1;
        returnValue.product *= num;
    //     console.log(s)
    // console.log(start)
    // console.log(nums)
        return returnValue;
    }
    if(nums[0]){
        let num = findNum(s,start);
        returnValue.nums++;
        returnValue.product *= num;
    }
    if(nums[2]){
        returnValue.nums++;
        let num = findNum(s,start+2);
        returnValue.product *= num;
    }
    // console.log(s)
    // console.log(start)
    // console.log(nums)
    return returnValue;
};

// Tells if the current symbols is gear or not
const isGear = (data, i, index)=>{
    const ownCount = numberCount(data[i],index-1,true);
    console.log(`from here ${ownCount.nums}`)
    if(i == 0){
        const nextCount = numberCount(data[i+1],index-1,false);
        const returnValue = {
            isGear:ownCount.nums+nextCount.nums==2,
            product:ownCount.product*nextCount.product
        }
        // console.log('hi')
        // console.log(returnValue)
        return returnValue;
    }
    if(i<data.length-1){
        const beforeCount = numberCount(data[i-1],index-1,false);
        const nextCount = numberCount(data[i+1],index-1,false);
        const returnValue = {
            isGear:beforeCount.nums+ownCount.nums+nextCount.nums==2,
            product:beforeCount.product*ownCount.product*nextCount.product
        }
        console.log()
        console.log('hiasdf')
        console.log(beforeCount)
        console.log(ownCount)
        console.log(nextCount);
        return returnValue;
    }
    
    const returnValue = {
        isGear:ownCount.nums+beforeCount.nums==2,
        product:ownCount.product*beforeCount.product
    }
    // console.log('hhi')
    //     console.log(returnValue)
    return returnValue;
}

// Finds the final solution
const findGearRatioSum = (data)=>{
    let sum = 0;
    for(let i = 0; i<data.length;i++){
        const currentGears = findGear(data[i]);
        console.log(currentGears);
        for(let j = 0;j<currentGears.length;j++){
            const currentGear = isGear(data, i, currentGears[j]);
            console.log(currentGear);
            if(currentGear.isGear){
                sum += currentGear.product;
            }
        }
        // console.log();
    }
    return sum;
}

console.log(findGearRatioSum(data))

// console.log(isGear(data,138,18))

// console.log(numberCount(data[137],20,false))

// 79741868