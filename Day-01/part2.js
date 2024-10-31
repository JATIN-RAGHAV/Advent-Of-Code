const fs = require('fs')

const data = fs.readFileSync('./text.txt', 'utf8').split('\n').map(e => parseInt(e))

let count = 0;

for (let i = 1; i < data.length - 2; i++) {
	if (data[i + 2] > data[i - 1]) count++;
}

console.log(count)
