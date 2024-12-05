import fs from 'fs';

let updates = fs.readFileSync('text.txt', 'utf8').split('\n');
let rules = updates.splice(0, updates.indexOf('') + 1)

rules.pop();
updates.pop();

rules = rules.map(row => {
	return row.split('|').map(num => parseInt(num))
})

updates = updates.map(row => {
	return row.split(',').map(num => parseInt(num))
})

let rulesObject = {};

for (let i = 0; i < rules.length; i++) {
	if (rulesObject[rules[i][1]])
		rulesObject[rules[i][1]].push(rules[i][0]);
	else
		rulesObject[rules[i][1]] = [rules[i][0]];
}

const isCorrectOrder = (update) => {
	for (let i = 0; i < update.length - 1; i++) {
		for (let j = i + 1; j < update.length; j++) {
			if (rulesObject[update[j]] == undefined) {
				let temp = update[i];
				update[i] = update[j];
				update[j] = temp;
				isCorrectOrder(update);
				return false;
			}
			if (rulesObject[update[j]].indexOf(update[i]) == -1) {
				let temp = update[i];
				update[i] = update[j];
				update[j] = temp;
				isCorrectOrder(update);
				return false;
			}
		}
	}
	return true;
}

let sumOfMiddle = 0;

for (let i = 0; i < updates.length; i++) {
	const row = updates[i]
	if (!isCorrectOrder(row))
		sumOfMiddle += row[(row.length - 1) / 2]
}

console.log(sumOfMiddle);
