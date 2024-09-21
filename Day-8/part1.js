import fs from 'fs';

const data = fs.readFileSync('text.txt', 'utf-8');

const testData1 = `RL

AAA = (BBB, CCC)
BBB = (DDD, EEE)
CCC = (ZZZ, GGG)
DDD = (DDD, DDD)
EEE = (EEE, EEE)
GGG = (GGG, GGG)
ZZZ = (ZZZ, ZZZ)`

const testData2 = `LLR

AAA = (BBB, BBB)
BBB = (AAA, ZZZ)
ZZZ = (ZZZ, ZZZ)`

const formatData = (data) =>{
    const splittedData =  data.split('\n');
    const sequence = splittedData.shift();
    splittedData.shift();
    let returnObj = {};
    for(let i of splittedData){
        const [nameString, directions] = i.split(' = ');
        returnObj[nameString] = [directions.slice(1,4), directions.slice(6,9)];
    }
    return [sequence,returnObj]
}

const makeAMove = (move, currentPlace, data)=>{
    const [L, R] = data[currentPlace];
    if(move == 'L')
    return L;
    return R;
}

const justDoIt = (data)=>{
    const [sequence, newData] = formatData(data);
    let moves = 0;
    let currentPlace = 'AAA';
    let currentMove = 0;
    while(currentPlace != 'ZZZ'){
        if(currentMove == sequence.length){
            currentMove = 0;
        }
        currentPlace = makeAMove(sequence[currentMove], currentPlace, newData);
        currentMove++;
        moves++;
    }
    return moves;
}
console.log(justDoIt(data));

// 20659
