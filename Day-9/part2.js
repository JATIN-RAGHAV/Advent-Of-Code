import fs from "fs";

const data = fs.readFileSync("text.txt", "utf-8");

const dataFormatter = (data) => {
  return data.split("\n").map((row) => {
    return row.split(" ").map((number) => parseInt(number));
  });
};

const testData = `0 3 6 9 12 15
1 3 6 10 15 21
10 13 16 21 30 45`;

const reduceRow = (row) => {
  let returnArray = [];
  for (let i = 0; i < row.length - 1; i++) {
    returnArray.push(row[i + 1] - row[i]);
  }
  return returnArray;
};

const predVal = (row) => {
  let firstElementArray = [];
  const len = row.length;
  firstElementArray.push(row[0]);
  for (let i = 0; i < len - 1; i++) {
    row = reduceRow(row);
    firstElementArray.push(row[0]);
  }
  firstElementArray.reverse();
  return firstElementArray.reduce((prev, current) => current-prev,0);
};

const justDoIt = (data) => {
  const newData = dataFormatter(data);
  let sum = 0;
  for (let i = 0; i < newData.length; i++) {
    sum += predVal(newData[i]);
  }
  return sum;
};

console.log(justDoIt(data));

// 1038