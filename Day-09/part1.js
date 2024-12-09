import fs from 'fs';

const data = fs.readFileSync('text.txt', 'utf8').trim().split('').map(n => parseInt(n));

const spaces = data.filter((_, index) => index % 2 === 1);
const values = data.filter((_, index) => index % 2 === 0);

let valuesIDArray = [];
for (let i = 0; i < values.length; i++) {
	for (let j = 0; j < values[i]; j++) {
		valuesIDArray.push(i);
	}
}

const totalLength = valuesIDArray.length
let finalArray = [];

for (let i = 0; i < spaces.length; i++) {
	for (let j = 0; j < values[i]; j++) {
		if (finalArray.length == totalLength) break;
		finalArray.push(i);
	}
	for (let j = 0; j < spaces[i]; j++) {
		if (finalArray.length == totalLength) break;
		finalArray.push(valuesIDArray.pop())
	}
}

const checkSum = finalArray.reduce((prev, current, index) => prev + (current * index))

console.log(checkSum);
