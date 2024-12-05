import fs from 'fs';

const data = fs.readFileSync('text.txt', 'utf8').split('\n').map(row => {
	return row.split(' ').map(num => parseInt(num))
})
data.pop();

const isSafe = (row) => {
	let isIncreasing = (row[1] - row[0]) > 0;
	for (let i = 0; i < row.length - 1; i++) {
		let diff = row[i + 1] - row[i];
		let hasIncreased = diff > 0;
		diff = Math.abs(diff);
		if (diff < 1 || diff > 3) {
			return false
		}
		if (hasIncreased != isIncreasing) {
			return false;
		}
	}
	return true;
}

let safeCount = 0;

for (let i = 0; i < data.length; i++) {
	if (isSafe(data[i]))
		safeCount++;
}

console.log(safeCount);
