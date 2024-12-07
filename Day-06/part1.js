import fs from 'fs'

const map = fs.readFileSync('text.txt', 'utf8').split('\n').map(row => {
	return row.split('');
})

const possibleStarts = ['<', '^', '>', 'v'];

let start = [];

for (let i = 0; i < map.length; i++) {
	for (let j = 0; j < map[0].length; j++) {
		if (possibleStarts.indexOf(map[i][j]) != -1) {
			start = [i, j];
		}
	}
}

let placesVisited = {};

const makeMove = (currentPos, map) => {
	const [i, j] = currentPos;
	let agent = map[i][j];
	let move;

	switch (agent) {
		case '<':
			move = [0, -1]
			break;
		case '^':
			move = [-1, 0];
			break;
		case '>':
			move = [0, 1];
			break;
		case 'v':
			move = [1, 0]
	}

	const iMove = i + move[0];
	const jMove = j + move[1];

	if (map[iMove] == undefined || map[iMove][jMove] == undefined) return false;

	if (map[iMove][jMove] == '#') {
		switch (agent) {
			case '<':
				agent = '^'
				break;
			case '^':
				agent = '>'
				break;
			case '>':
				agent = 'v'
				break;
			case 'v':
				agent = '<'
		}

		map[i][j] = agent;
		return [i, j];
	}

	map[i][j] = '.';
	map[iMove][jMove] = agent;
	if (!placesVisited[iMove + ',' + jMove]) {
		placesVisited[iMove + ',' + jMove] = true;
	}
	return [iMove, jMove];
}

while (true) {
	const move = makeMove(start, map);
	if (!move) break;

	start = move;
}


const placesVisitedCount = Object.keys(placesVisited).length;

console.log(placesVisitedCount)
