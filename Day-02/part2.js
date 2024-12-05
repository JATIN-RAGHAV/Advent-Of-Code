import fs from 'fs';

const data = fs.readFileSync('text.txt', 'utf8').split('\n').map(row => {
	return row.split(' ').map(num => parseInt(num))
})
data.pop();

const isSafe = (row, dampened) => {
	let firstIncreasing = (row[1] - row[0]) > 0;
	let secondIncreasing = (row[2] - row[1]) > 0;
	let thirdIncreasing = (row[3] - row[2]) > 0;
	let isIncreasing = firstIncreasing != secondIncreasing ? thirdIncreasing : firstIncreasing;

	for (let i = 0; i < row.length - 1; i++) {
		let diff = row[i + 1] - row[i];
		let hasIncreased = diff > 0;
		diff = Math.abs(diff);
		if (diff < 1 || diff > 3) {
			if (dampened) {
				return false;
			}
			let newArray = [...row]
			newArray.splice(i + 1, 1);
			console.log(row)
			row.splice(i, 1);
			console.log(row);
			console.log(newArray)
			console.log()
			return (isSafe(row, true) || isSafe(newArray, true));
		}
		if (hasIncreased != isIncreasing) {
			if (dampened) {
				return false;
			}
			let newArray = [...row]
			console.log(row)
			newArray.splice(i + 1, 1);
			row.splice(i, 1);
			console.log(row);
			console.log(newArray)
			console.log()
			return (isSafe(row, true) || isSafe(newArray, true));
		}
	}
	return true;
}

let safeCount = 0;

for (let i = 0; i < data.length; i++) {
	if (isSafe(data[i], false))
		safeCount++;
}

console.log(safeCount);
