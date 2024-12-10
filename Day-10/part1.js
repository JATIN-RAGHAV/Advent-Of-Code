import fs from 'fs';

const data = fs.readFileSync('text.txt', 'utf8').trim().split('\n').map(row => {
	return row.split('').map(num => parseInt(num));
})

let zeros = [];

for (let i = 0; i < data.length; i++) {
	for (let j = 0; j < data[0].length; j++) {
		if (data[i][j] == '0') zeros.push([i, j])
	}
}

const moves = [
	[-1, 0],
	[1, 0],
	[0, -1],
	[0, 1]
];

const getTillEnd = ([i, j], nineIndices) => {
	let current = data[i][j];
	if (current == 9) {
		nineIndices.add(i + ',' + j)
		return;
	}
	while (true) {
		for (let move = 0; move < moves.length; move++) {
			const [iMove, jMove] = moves[move];
			const next = data[i + iMove] && data[i + iMove][j + jMove];
			if (next) {
				if (next - current == 1) {
					getTillEnd([i + iMove, j + jMove], nineIndices);
				}
			}
		}
		return
	}
}

let totalScore = 0;

for (let head = 0; head < zeros.length; head++) {
	let nineIndices = new Set();
	getTillEnd(zeros[head], nineIndices);
	totalScore += nineIndices.size;
}


console.log(totalScore);
