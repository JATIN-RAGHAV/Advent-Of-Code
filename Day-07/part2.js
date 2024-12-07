import fs from 'fs'

const data = fs.readFileSync('text.txt', 'utf8').trim().split('\n').map(row => {
	let [testValue, numbers] = row.trim().split(':');
	testValue = parseInt(testValue);
	let numbersArray = numbers.trim().split(' ').map(num => parseInt(num));
	return [testValue, numbersArray]
})

const recursiveCalculator = (target, nums, sums) => {
	if (nums.length == 1) {
		if (nums[0] <= target) sums.push(nums[0])
		return;
	}

	recursiveCalculator(target, nums.slice(0, -1), sums)

	const sumsLeng = sums.length;

	for (let i = 0; i < sumsLeng; i++) {
		const currentNum = sums[i];
		const sum = currentNum + nums.at(-1);
		const mul = currentNum * nums.at(-1);
		const concat = parseInt(`${currentNum}${nums.at(-1)}`);
		if (sum <= target) sums.push(sum);
		if (mul <= target) sums.push(mul);
		if (concat <= target) sums.push(concat);
	}

	sums.splice(0, sumsLeng);

	return;
}

const getsTestValue = (row) => {
	const [target, nums] = row;

	let sums = [];
	recursiveCalculator(target, nums, sums);
	return sums.indexOf(target) != -1
}

let sum = 0;

for (let i = 0; i < data.length; i++) {
	if (getsTestValue(data[i])) {
		sum += data[i][0];
	}
}


console.log(sum);
