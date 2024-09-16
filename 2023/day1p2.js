import fs from 'fs';

let data = fs.readFileSync('./day1.txt', 'utf-8');

let tryData = `two
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen`;

let testData = `two 
eighthreenine
sevenine
four5seven`;

let dataArray = data.split(/\n/);

const stringToNum = (s) => {
  const numMap = {
    "one":'1', 'two':'2','three':'3','four':'4','five':'5',
    'six':'6','seven':'7','eight':'8','nine':'9'
  }
  return numMap[s] || s;
};

const findCalibirationValue = (s) => {

  const regex = /(?=(one|two|three|four|five|six|seven|eight|nine|\d))/g;
  const matches = [...s.matchAll(regex)].map(match => match[1]);

  const first = stringToNum(matches[0]);
  const last = stringToNum(matches[matches.length-1]);

  let number = parseInt(first + last);

  return number;
};

let sum = 0;

for (let string of dataArray) {
  sum += findCalibirationValue(string);
}

console.log(sum)

// 54135 
// 54175
// 54156
//  CORRECT ANSWER = 54094