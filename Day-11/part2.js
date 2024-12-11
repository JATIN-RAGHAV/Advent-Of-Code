import fs from 'fs'

const data = fs.readFileSync('text.txt', 'utf8').trim().split(' ').map(num => parseInt(num));


const blink = (number, depth, targetDepth, memo) => {
	const key = `${number},${depth}`;
	const memod = memo.get(key);
	if (memod != undefined) {
		return memod;
	}

	if (depth == targetDepth) {
		return 1;
	}
	stonesCount = 0;
	if (number == 0) {
		stonesCount = blink(1, depth + 1, targetDepth, memo);
	}
	else {
		const leng = number.toString().length;
		if (leng % 2 == 0) {
			stonesCount = blink(Math.floor(number / (10 ** (leng / 2))), depth + 1, targetDepth, memo) + blink(number % (10 ** (leng / 2)), depth + 1, targetDepth, memo)
		} else {
			stonesCount = blink(number * 2024, depth + 1, targetDepth, memo);
		}
	}
	memo.set(key, stonesCount)
	return stonesCount
}
	;
let stonesCount = 0;
let memo = new Map();

for (let number of data) {
	console.log(number);
	stonesCount += blink(number, 0, 25, memo);
}

console.log(memo.size);
