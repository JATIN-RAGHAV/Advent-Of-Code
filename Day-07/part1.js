import fs from "fs";
import { types } from "util";

const data = fs.readFileSync("./text.txt", "utf-8");

const testData = `32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483`;

/* 
    Five of a kind => 7
    Four of a kind => 6
    Full House     => 5
    Three of a kind=> 4
    Two pair       => 3
    One Pair       => 2
    High Card      => 1
*/

const formatData = (data) => {
  return data
    .split("\n")
    .map((row) => row.split(" "))
    .map((row) => [row[0], parseInt(row[1])]);
};

const findType = (card) => {
  let characterObject = {};
  let characters = [];
  for (let i = 0; i < card.length; i++) {
    if (characterObject[card[i]] == undefined) {
      characters.push(card[i]);
      characterObject[card[i]] = 1;
    } else {
      characterObject[card[i]]++;
    }
  }
  const handleTwo = () => {
    const countOfFirst = characterObject[characters[0]];
    if (countOfFirst == 2 || countOfFirst == 3) return 5;
    return 6;
  };

  const handleThree = () => {
    const countOfFirst = characterObject[characters[0]];
    if (countOfFirst == 3) return 4;
    if (countOfFirst == 2) return 3;
    const countOfSecond = characterObject[characters[1]];
    if (countOfSecond == 2) return 3;
    return 4;
  };

  switch (Object.keys(characterObject).length) {
    case 1:
      return 7;
    case 2:
      return handleTwo();
    case 3:
      return handleThree();
    case 4:
      return 2;
    case 5:
      return 1;
    default:
      return -1;
  }
};

let characterValues = {
  A: 13,
  K: 12,
  Q: 11,
  J: 10,
  T: 9,
};
for (let i = 2; i <= 9; i++) {
  characterValues[i] = i - 1;
}

const comparisonFunction = (first, second) => {
  for (let i = 0; i < 5; i++) {
    const valueOfFirst = characterValues[first[0][i]];
    const valueOfSecond = characterValues[second[0][i]];
    if (valueOfFirst > valueOfSecond) return -1;
    else if (valueOfFirst < valueOfSecond) return 1;
  }
  return 0;
};

const justDoIt = (data) => {
  const formattedData = formatData(data);
  let typeSeperatedData = {};
  for (let i = 1; i <= 7; i++) {
    typeSeperatedData[i] = [];
  }
  for (let i = 0; i < formattedData.length; i++) {
    const card = formattedData[i];
    const type = findType(card[0]);
    typeSeperatedData[type].push(card);
  }

  for (let type = 1; type <= 7; type++) {
    typeSeperatedData[type].sort(comparisonFunction);
  }

  let rank = 1;
  let sum = 0;
  for (let type = 1; type <= 7; type++) {
    const typeValue = typeSeperatedData[type];
    for (let i = typeValue.length - 1; i >= 0; i--) {
      const currentValue = rank * typeValue[i][1];
      sum += currentValue;
      rank++;
    }
    console.log(sum);
    console.log();
  }

  return sum;
};

console.log(justDoIt(data));

// 248812215
