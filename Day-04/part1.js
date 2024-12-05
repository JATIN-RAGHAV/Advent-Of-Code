import fs from 'fs'

const data = fs.readFileSync('text.txt', 'utf8').split('\n').map((row) => {
	return row.split('');
})

const directionUpdates = [];
for (let i = -1; i < 2; i++) {
	for (let j = -1; j < 2; j++) {
		if (!(i == 0 && j == 0))
			directionUpdates.push([i, j])
	}
}
const searchPhrase = ['X', 'M', 'A', 'S'];

const isXMAS = (data, i, j) => {
	let XMAXCount = 0;
	for (let move = 0; move < directionUpdates.length; move++) {
		let currenti = i;
		let currentj = j;
		for (let char = 1; char < searchPhrase.length; char++) {
			currenti += directionUpdates[move][0]
			currentj += directionUpdates[move][1]
			if (!data[currenti] || !data[currenti][currentj]) break;
			if (data[currenti][currentj] != searchPhrase[char])
				break;
			if (char == searchPhrase.length - 1) {
				XMAXCount++;
			}
		}
	}
	return XMAXCount;
}

let XMAXCount = 0;

for (let i = 0; i < data.length; i++) {
	for (let j = 0; j < data[0].length; j++) {
		if (data[i][j] == 'X') {
			XMAXCount += isXMAS(data, i, j);
		}
	}
}

console.log(XMAXCount);
