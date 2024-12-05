import fs from 'fs'

const data = fs.readFileSync('text.txt', 'utf8').split('\n').map(row => {
	return row.split('   ').map(num => parseInt(num));
})

let firstList = [];
let secondList = [];

for (let i = 0; i < 1000; i++) {
	firstList.push(data[i][0]);
	secondList.push(data[i][1]);
}

firstList.sort();
secondList.sort();

let totalDiff = 0;

for (let i = 0; i < 1000; i++) {
	totalDiff += Math.abs(firstList[i] - secondList[i])
}

console.log(totalDiff);

