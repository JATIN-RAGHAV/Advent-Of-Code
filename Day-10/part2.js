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

const getTillEnd = ([i, j]) => {
	let current = data[i][j];
	let trailCount = 0;
	if (current == 9) {
		return 1;
	}
	while (true) {
		for (let move = 0; move < moves.length; move++) {
			const [iMove, jMove] = moves[move];
			const next = data[i + iMove] && data[i + iMove][j + jMove];
			if (next) {
				if (next - current == 1) {
					trailCount += getTillEnd([i + iMove, j + jMove], trailCount);
				}
			}
		}
		return trailCount
	}
}

let totalRating = 0;

for (let head = 0; head < zeros.length; head++) {
	totalRating += getTillEnd(zeros[head]);
}


console.log(totalRating);
