import fs from "fs";

const data = fs.readFileSync("./text.txt", "utf-8");

/* This function formats the data from a single string to a block format {
    [source-to-destination map:]:{
        '
    }
} */

const testData = `seeds: 79 14 55 13

seed-to-soil map:
50 98 2
52 50 48

soil-to-fertilizer map:
0 15 37
37 52 2
39 0 15

fertilizer-to-water map:
49 53 8
0 11 42
42 0 7
57 7 4

water-to-light map:
88 18 7
18 25 70

light-to-temperature map:
45 77 23
81 45 19
68 64 13

temperature-to-humidity map:
0 69 1
1 0 69

humidity-to-location map:
60 56 37
56 93 4`;

const formatNumberString = (s) => {
  return s
    .trim()
    .split(" ")
    .map((s) => parseInt(s));
};

const formatData = (data) => {
  data = data.split(/\n/g);
  let newData = {};
  let currentMap = "";
  let i = 1;
  while (i < data.length) {
    if (data[i] == "") {
      currentMap = data[i + 1];
      i++;
    } else {
      if (newData[currentMap] == undefined) {
        newData[currentMap] = [formatNumberString(data[i])];
      } else {
        newData[currentMap].push(formatNumberString(data[i]));
      }
    }
    i++;
  }
  return newData;
};

// Function that returns tha value using source destination and range;
const mapValue = (value, mapBlock) => {
  for (let i = 0; i < mapBlock.length; i++) {
    const source = mapBlock[i][1];
    const range = mapBlock[i][2];
    if (value >= source && value < source + range) {
      const destination = mapBlock[i][0];
      const mappedValue = destination - source + value;
      return mappedValue;
    }
  }
  return value;
};

// Function that returns the seed numbers as arrays
const getSeeds = (data) => {
  let seeds = data
    .split("\n")[0]
    .split(":")[1]
    .split(/ /)
    .map((s) => parseInt(s));
  seeds.shift();
  return seeds;
};

const justDoIt = (data) => {
  const newData = formatData(data);
  const seeds = getSeeds(data);
  const keys = Object.keys(newData);
  let lowestLocation = Infinity;
  for (let i = 0; i < seeds.length / 2; i++) {
    const startValue = seeds[i * 2];
    const range = seeds[i * 2 + 1];
    console.log(`StartValue => ${startValue}`);
    console.log(`Range => ${range}`)
    console.log()
    const startTime = new Date();
    for (let j = startValue; j < startValue + range; j++) {
      let value = j;
      for (let map of keys) {
        value = mapValue(value, newData[map]);
      }
      if (value < lowestLocation) lowestLocation = value;
    }
    console.log(i)
    console.log(`${(new Date() - startTime)/1000} seconds`)
  }
  return lowestLocation;
};

const startTime = new Date();

console.log(justDoIt(data));

const endTime = new Date();

console.log(`Time took => ${(endTime-startTime)/100} secs`)

// 69323689
// 52631801
// 69323689
// 69323688