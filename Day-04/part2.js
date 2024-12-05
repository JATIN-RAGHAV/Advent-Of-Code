import { match } from 'assert';
import fs from 'fs'

const data = fs.readFileSync('text.txt', 'utf8').split('\n').map((row) => {
	return row.split('');
})

const possibleConfigs = [
	[['M', 'M'],
	['S', 'S']],

	[['S', 'M'],
	['S', 'M']],

	[['S', 'S'],
	['M', 'M']],

	[['M', 'S'],
	['M', 'S']]
]

const isXMAS = (data, i, j) => {
	if (data[i - 1] && data[i + 1] && data[i][j - 1] && data[i][j + 1]) {
		const currentConfig = [
			[data[i - 1][j - 1], data[i - 1][j + 1]],
			[data[i + 1][j - 1], data[i + 1][j + 1]]
		]
		return matchConfig(currentConfig);
	} else {
		return false;
	}
}

const matchConfig = (config) => {
	for (let i = 0; i < possibleConfigs.length; i++) {
		const arrayToMatch = possibleConfigs[i];
		if (arrayToMatch[0][0] == config[0][0] && arrayToMatch[0][1] == config[0][1] && arrayToMatch[1][0] == config[1][0] && arrayToMatch[1][1] == config[1][1])
			return true;
	}
	return false;
}

let XMAXCount = 0;

for (let i = 0; i < data.length; i++) {
	for (let j = 0; j < data[0].length; j++) {
		if (data[i][j] == 'A') {
			XMAXCount += isXMAS(data, i, j);
		}
	}
}

console.log(XMAXCount);
