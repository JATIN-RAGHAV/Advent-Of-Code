import fs from 'fs'

const map = fs.readFileSync('text.txt', 'utf8').trim().split('\n').map(row => {
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

const isLoop = (map, start) => {
	let [i, j] = start;
	let agent;
	let placesVisited = {};
	while (true) {
		const move = makeMove([i, j], map);
		if (!move) return false;

		[i, j, agent] = move;

		if (placesVisited[i + ',' + j]) {
			if (placesVisited[i + ',' + j].indexOf(agent) != -1) return true;
			placesVisited[i + ',' + j].push(agent);
		}
		else {
			placesVisited[i + ',' + j] = [agent];
		}
	}
}

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
		return [i, j, agent];
	}

	map[i][j] = '.';
	map[iMove][jMove] = agent;
	return [iMove, jMove, agent];
}

let loop = 0;

for (let i = 0; i < map.length; i++) {
	for (let j = 0; j < map[0].length; j++) {
		if (!(i == start[0] && j == start[1]) && map[i][j] == '.') {
			let newArray = [];
			for (let row = 0; row < map.length; row++) {
				newArray.push([...(map[row])])
			}
			newArray[i][j] = '#';
			if (isLoop(newArray, [...start])) {
				loop++;
				console.log(`i=> ${i}, j=> ${j}`)
			}
		}
	}
}

console.log(loop)
