import fs from "fs";

let data = fs.readFileSync("./day4.txt", "utf-8").split("\n");

let testData = `Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1
Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
Card 6: 31 18 13  5 72 | 74 77 10 23  5 67 36 11`.split("\n");

const getNumsArray = (s) => {
  s = s.trim();
  let numsArray = s.split(/\s+/);
  return numsArray;
};

const findMatchesNumber = (have, winning) => {
  let matches = 0;
  for (let i = 0; i < have.length; i++) {
    if (winning.indexOf(have[i]) != -1) matches++;
  }
  return matches;
};

const findMatch = (s) => {
  const [winN, haveN] = s.split("|");
  const winningNums = getNumsArray(winN);
  const havingNums = getNumsArray(haveN);
  const matches = findMatchesNumber(havingNums, winningNums);
  return matches;
};

const increaseCardCount = (array, winningNum, index, count)=>{
    // count => points of the current card
    // index => index of the current card
    for(let i = index+1;(i<=index+winningNum && i<array.length);i++){
        array[i] += count;
    }
}

const justDoIt = (data) => {
    let cardsCountArray = new Array(data.length).fill(1);
  for (let i = 0; i < data.length; i++) {
    let [cardNum, nums] = data[i].split(":");
    cardNum = parseInt(cardNum.split(/\s+/)[1]);
    const matches = findMatch(nums);
    increaseCardCount(cardsCountArray, matches, cardNum-1,cardsCountArray[cardNum-1]);
  }
  const cardsCount = cardsCountArray.reduce((prev, current) => prev+current,0)
  return cardsCount;

};

console.log(justDoIt(data));

// 12648035