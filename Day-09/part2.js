import fs from 'fs';

const data = fs.readFileSync('text.txt', 'utf8').trim().split('').map(n => parseInt(n));

const spaces = data.filter((_, index) => index % 2 === 1);
const values = data.filter((_, index) => index % 2 === 0);

let valuesIDArray = [];
for (let i = 0; i < values.length; i++) {
}

let interMediateArray = [];

for (let i = 0; i < values.length; i++) {
	let tempArray = [];
	for (let j = 0; j < values[i]; j++) {
		tempArray.push(i);
	}
	interMediateArray.push(tempArray)
	interMediateArray.push([])
}

for (let i = values.length - 1; i >= 0; i--) {
	for (let j = 0; j < i; j++) {
		if (spaces[j] >= values[i]) {
			spaces[j] -= values[i];
			for (let k = 0; k < values[i]; k++) {
				interMediateArray[(j * 2) + 1].push(i)
			}
			interMediateArray.splice(i * 2, 1, []);
			spaces[i - 1] += values[i];
			break;
		}
	}
}

for (let i = 0; i < spaces.length; i++) {
	const spaceCount = spaces[i]
	if (spaceCount > 0) {
		for (let j = 0; j < spaceCount; j++) {
			interMediateArray[(i * 2) + 1].push(0);
		}
	}
}

let finalArray = [];

for (let i = 0; i < interMediateArray.length; i++) {
	finalArray.push(...interMediateArray[i]);
}
const checkSum = finalArray.reduce((prev, current, index) => prev + (current * index));

console.log(checkSum);
