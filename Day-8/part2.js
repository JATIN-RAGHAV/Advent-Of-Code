import fs from "fs";

const data = fs.readFileSync("text.txt", "utf-8");

const testData = `LR

11A = (11B, XXX)
11B = (XXX, 11Z)
11Z = (11B, XXX)
22A = (22B, XXX)
22B = (22C, 22C)
22C = (22Z, 22Z)
22Z = (22B, 22B)
XXX = (XXX, XXX)`

const formatData = (data) => {
  const splittedData = data.split("\n");
  const sequence = splittedData.shift();
  splittedData.shift();
  let returnObj = {};
  for (let i of splittedData) {
    const [nameString, directions] = i.split(" = ");
    returnObj[nameString] = [directions.slice(1, 4), directions.slice(6, 9)];
  }
  return [sequence, returnObj];
};

const makeAMove = (move, currentPlace, data) => {
  const [L, R] = data[currentPlace];
  if (move == "L") return L;
  return R;
};

const findMoves = (currentPlace, data, sequence)=>{
    let currentMove = 0;
    let moves = 0;
    while(currentPlace[2] != 'Z'){
        if(currentMove == sequence.length){
            currentMove = 0;
        }
        currentPlace = makeAMove(sequence[currentMove], currentPlace, data);
        currentMove++;
        moves++;
    }
    return moves;   
}

function gcd(a, b) { 
    for (let temp = b; b !== 0;) { 
        b = a % b; 
        a = temp; 
        temp = b; 
    } 
    return a; 
} 
  
function lcmFunction(a, b) { 
    const gcdValue = gcd(a, b); 
    return (a * b) / gcdValue; 
} 

const justDoIt = (data) => {
  const [sequence, newData] = formatData(data);
  let currentPlaces = Object.keys(newData).filter((place) => place[2] === "A");
  let moves = [];
    for(let start of currentPlaces){
        moves.push(findMoves(start, newData, sequence))
    }
   return moves.reduce((prev, current) => lcmFunction(prev, current),1)
};
console.log(justDoIt(data));
