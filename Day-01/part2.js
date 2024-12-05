import fs from 'fs'

const data = fs.readFileSync('text.txt', 'utf8').split('\n').map(row => {
	return row.split(/ +/).map(num => parseInt(num));
})

let firstList = [];
let secondList = [];

for (let i = 0; i < data.length - 1; i++) {
	firstList.push(data[i][0]);
	secondList.push(data[i][1]);
}

const findOccurances = (num, list) => {
	let count = 0;
	let isThere = false;

	for (let i = 0; i < list.length; i++) {
		if (list[i] === num) {
			isThere = true;
			count++;
		} else if (isThere) {
			return count;
		}
	}
	return count;
}

let memo = {};

secondList.sort();

let similarityScore = 0;

for (let i = 0; i < firstList.length; i++) {
	if (memo[firstList[i]]) {
		similarityScore += (memo[firstList[i]] * firstList[i])
	} else {
		let occurances = findOccurances(firstList[i], secondList);
		memo[firstList[i]] = occurances;
		similarityScore += (occurances * firstList[i]);
	}
}

console.log(similarityScore);
