import fs from 'fs'

const data = fs.readFileSync('test.txt', 'utf8').trim().split(' ').map(num => parseInt(num));

const blink = (stones) => {
	let tempArray = [];
	for (let i = 0; i < stones.length; i++) {
		if (stones[i] == 0) tempArray.push(1);

		else if (stones[i].toString().length % 2 == 0) {
			const length = stones[i].toString().length;
			const firstStone = Math.floor(stones[i] / (10 ** (length / 2)))
			const secondStone = stones[i] % (10 ** (length / 2))
			tempArray.push(firstStone);
			tempArray.push(secondStone);
		}
		else tempArray.push(stones[i] * 2024)
	}
	return tempArray;
}

let currentState = data;

for (let i = 0; i < 25; i++) {
	currentState = blink(currentState);
}

console.log(currentState.length);
