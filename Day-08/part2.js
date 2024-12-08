import fs from 'fs';

const data = fs.readFileSync('text.txt', 'utf8').trim().split('\n').map(row => {
	return row.trim().split('');
})

let locations = {};

const height = data.length;
const width = data[0].length;

for (let i = 0; i < height; i++) {
	for (let j = 0; j < width; j++) {
		const element = data[i][j];
		if (element != '.') {
			if (locations[element])
				locations[element].push([i, j])
			else
				locations[element] = [[i, j]]
		}
	}
}

let antiNodes = new Set();

for (let element in locations) {
	const array = locations[element];
	for (let first = 0; first < array.length - 1; first++) {
		for (let second = first + 1; second < array.length; second++) {
			const iDist = array[first][0] - array[second][0]
			const jDist = array[first][1] - array[second][1];
			let antiNode1 = [array[second][0], array[second][1]]
			let antiNode2 = [array[first][0], array[first][1]]
			let broken = 0;
			while (true) {
				if ((antiNode1[0] >= 0 && antiNode1[0] < height) && (antiNode1[1] >= 0 && antiNode1[1] < width))
					antiNodes.add(`${antiNode1[0]},${antiNode1[1]}`)
				else broken = 1;
				if ((antiNode2[0] >= 0 && antiNode2[0] < height) && (antiNode2[1] >= 0 && antiNode2[1] < width))
					antiNodes.add(`${antiNode2[0]},${antiNode2[1]}`)
				else if (broken == 1) broken++;
				antiNode1 = [antiNode1[0] - iDist, antiNode1[1] - jDist]
				antiNode2 = [antiNode2[0] + iDist, antiNode2[1] + jDist]
				if (broken == 2) break;
			}
		}
	}
}

console.log(antiNodes.size);
