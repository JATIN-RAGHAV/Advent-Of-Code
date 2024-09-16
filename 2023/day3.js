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
const findNum = (s) => {
  const regex = /\d+/g;
  return [...s.matchAll(regex)].map((n) => {
    return {
        num:parseInt(n[0]),
      index: n.index,
      len: n[0].length,
    };
  });
};


// Tells whether the given string contains symbol or not
const isSymbol = (s, start, end) => {
  for (let i = start; i < end; i++) {
    if (s[i] != "." && isNaN(s[i]) && s[i] != undefined) {
      return true;
    }
  }
  return false;
};

// Tells whether the current number is part number or not
const isPartNumber = (data, i, index, len) => {
    const ownRow = isSymbol(data[i], index - 1, index + len + 1);
  if (i == 0) {
    const nextRow = isSymbol(data[i+1], index - 1, index + len + 1);
    return ownRow || nextRow;
  }
  if( i < data.length-1){
    const prevRow = isSymbol(data[i-1], index - 1, index + len + 1);
    const nextRow = isSymbol(data[i+1], index - 1, index + len + 1);
    return prevRow || ownRow || nextRow;
  }
  const prevRow = isSymbol(data[i-1], index - 1, index + len + 1);
  return prevRow || ownRow;
};

// Finds the final solution
const findPartNumberSum = (data)=>{
    let sum = 0;
    for(let i = 0; i<data.length;i++){
        const currentNums = findNum(data[i]);
        for(let j = 0;j<currentNums.length;j++){
            const {index, len, num} = currentNums[j];
            if(isPartNumber(data,i,index,len)) sum+=num;
        }
    }
    return sum;
}

console.log(findPartNumberSum(data));
