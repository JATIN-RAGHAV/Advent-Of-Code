import fs from 'fs'

const data = fs.readFileSync('text.txt', 'utf8').replace('\n', '');

const regex = /(mul\(\d{1,3},\d{1,3}\)|do\(\)|don't\(\))/g;

const mulCalls = data.match(regex)

const solveMul = (call) => {
	call = call.replace('mul(', '').replace(')', '');
	const nums = call.split(',');
	return parseInt(nums[0]) * parseInt(nums[1]);
}

let sum = 0;
let solve = true;

for (let i = 0; i < mulCalls.length; i++) {
	if (mulCalls[i] === "don't()")
		solve = false;
	else if (mulCalls[i] == "do()")
		solve = true;
	else {
		if (solve)
			sum += solveMul(mulCalls[i])
	}
}

console.log(sum);
