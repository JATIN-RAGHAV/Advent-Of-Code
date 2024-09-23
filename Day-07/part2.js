import fs from "fs";

const data = fs.readFileSync("./text.txt", "utf-8");

let valueArrMe = [];

const testData = `2345A 1
J345A 2
2345J 3
32T3K 5
KK677 7
T3Q33 11
Q2KJJ 13
T3T3J 17
Q2Q2Q 19
2AAAA 23
T55J5 29
QQQJA 31
KTJJT 34
JJJJJ 37
JJJJ2 41
JAAAA 43
2JJJJ 53
AAAAJ 59
AAAAA 61`;

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
  
    const switchTypeWithoutJ = (characterCount) => {
      switch (characterCount) {
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
  
    let characterCount = characters.length;
    if (characterObject.J == undefined) {
      return switchTypeWithoutJ(characterCount);
    }
  
    if (characters.length == 1) return 7; // Handle five of a kind with a Joker

  let maxAppearanceChar = characters[0];
  let maxAppearanceValue = characterObject[characters[0]];
  for (let i = 0; i < characterCount; i++) {
    const character = characters[i];
    if (character != 'J') {
      const currentCharacterValue = characterObject[character];
      if (currentCharacterValue > maxAppearanceValue) {
        maxAppearanceChar = character;
        maxAppearanceValue = currentCharacterValue;
      }
    }
  }

  characterObject[maxAppearanceChar] += characterObject.J;
  delete characterObject.J;
    const indexOfJ = characters.indexOf('J');
      characters.splice(indexOfJ,1)
    const type = switchTypeWithoutJ(characterCount-1);
    return type;
  };

let characterValues = {
    A: 13,
    K: 12,
    Q: 11,
    T: 10,
    J: 1,
  };
  for (let i = 2; i <= 9; i++) {
    characterValues[i] = i;
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
      if(rank > 690){
          console.log(rank);
          console.log(typeValue[i]);
          console.log()
      }
      valueArrMe.push(currentValue);
      sum += currentValue;
      rank++;
    }
  }
  return sum;
};
console.log(justDoIt(data));

// 250088022
// 249996449
// 249965517
// 249952712
// 249965517
// 250057090