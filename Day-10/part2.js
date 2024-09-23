import fs from "fs";

const data = fs.readFileSync("text.txt", "utf-8");

const testData1 = `OF----7F7F7F7F-7OOOO
O|F--7||||||||FJOOOO
O||OFJ||||||||L7OOOO
FJL7L7LJLJ||LJIL-7OO
L--JOL7IIILJS7F-7L7O
OOOOF-JIIF7FJ|L7L7L7
OOOOL7IF7||L7|IL7L7|
OOOOO|FJLJ|FJ|F7|OLJ
OOOOFJL-7O||O||||OOO
OOOOL---JOLJOLJLJOOO`;

const testData2 = `...........
.S-------7.
.|F-----7|.
.||.....||.
.||.....||.
.|L-7.F-J|.
.|..|.|..|.
.L--J.L--J.
...........`;

const testData3 = `FF7FSF7F7F7F7F7F---7
L|LJ||||||||||||F--J
FL-7LJLJ||||||LJL-77
F--JF--7||LJLJ7F7FJ-
L---JF-JLJ.||-FJLJJ7
|F|F-JF---7F7-L7L|7|
|FFJF7L7F-JF7|JL---7
7-L-JL7||F7|L7F-7F7|
L.L7LFJ|||||FJL7||LJ
L7JLJL-JLJLJL--JLJ.L`;

const dataFormatter = (data) => {
  let returnData = data.split("\n");
  for (let i = 0; i < returnData.length; i++) {
    returnData[i] = returnData[i].split("");
  }
  return returnData;
};

const findS = (data) => {
  for (let i = 0; i < data.length; i++) {
    for (let j = 0; j < data[0].length; j++) {
      if (data[i][j] == "S") return [i, j];
    }
  }
};

const pipes = ["|", "-", "L", "J", "7", "F", "S"];

const possibleMoves = {
  "|": [
    [-1, 0],
    [1, 0],
  ],
  "-": [
    [0, 1],
    [0, -1],
  ],
  L: [
    [-1, 0],
    [0, 1],
  ],
  J: [
    [-1, 0],
    [0, -1],
  ],
  7: [
    [0, -1],
    [1, 0],
  ],
  F: [
    [1, 0],
    [0, 1],
  ],
};

const possibleApproaches = {
  "|": [
    [-1, 0],
    [1, 0],
  ],
  "-": [
    [0, 1],
    [0, -1],
  ],
  L: [
    [1, 0],
    [0, -1],
  ],
  J: [
    [1, 0],
    [0, 1],
  ],
  7: [
    [0, 1],
    [-1, 0],
  ],
  F: [
    [-1, 0],
    [0, -1],
  ],
};

const arrayEquals = (arr1, arr2) => {
  if (arr1.length != arr2.length) return false;
  return arr1.every((value, index) => value == arr2[index]);
};

const makeAMove = ([x, y], [xm, ym], data) => {
  if (data[x + xm] == undefined) return false;
  if (data[x + xm][y + ym] == undefined) return false;
  const newPosition = data[x + xm][y + ym];
  if (newPosition == "S") return "S";
  if (pipes.indexOf(newPosition) != -1) {
    const possibleApproache = possibleApproaches[newPosition];
    if (possibleApproache.some((value) => arrayEquals(value, [xm, ym]))) {
      const possibleMove = possibleMoves[newPosition];
      const nextMove = possibleMove.find(
        (move) => !(move[0] + xm == 0 && move[1] + ym == 0)
      );
      return nextMove;
    }
  }
  return false;
};

const givePipeForS = ([xIn, yIn], [xOut, yOut]) => {
  let possibleEntries = [];
  let possibleExits = [];
  for (let pipe of Object.keys(possibleApproaches)) {
    if (
      possibleApproaches[pipe].find((move) => move[0] == xIn && move[1] == yIn)
    ) {
      possibleEntries.push(pipe);
    }
    if (
      possibleMoves[pipe].find((move) => move[0] == xOut && move[1] == yOut)
    ) {
      possibleExits.push(pipe);
    }
  }
  return possibleEntries.find((pipe) => possibleExits.indexOf(pipe) != -1);
};

const getLoopTilesArray = (data) => {
  const startingMoves = [
    [0, 1],
    [1, 0],
    [-1, 0],
    [0, -1],
  ];
  let x, y;
  let xIn, yIn, xOut, yOut;
  let loopTiles = [];
  let done = false;
  let steps = 0;
  for (let move of startingMoves) {
    [x, y] = findS(data);
    let currentMove = move;
    // console.log(loopTiles);
    if (done) break;
    [xOut, yOut] = move;
    steps = 0;
    loopTiles = [];
    while (true) {
      // console.log(loopTiles);
      loopTiles.push(`${x},${y}`);
      currentMove = makeAMove([x, y], move, data);
      steps++;
      x += move[0];
      y += move[1];
      [xIn, yIn] = move;
      move = currentMove;
      if (data[x][y] == "S") {
        done = true;
        break;
      }
      if (!move) break;
    }
  }
  const sPipe = givePipeForS([xIn, yIn], [xOut, yOut]);
  [x, y] = findS(data);
  data[x][y] = sPipe;
  //   console.log(loopTiles);
  return loopTiles;
};

const cornerPipe = ["F", "7", "L", "J"];

const findNextCorner = ([x, y], data) => {
  y++;
  let currentPosition = data[x][y];
  while (cornerPipe.indexOf(currentPosition) == -1) {
    y++;
    currentPosition = data[x][y];
  }
  return y;
};

const crossedRegion = (start, end) => {
  if (start == "F") {
    return end == "J";
  }
  if (start == "7") {
    return end == "L";
  }
  if (start == "J") {
    return end == "F";
  }
  if (start == "L") {
    return end == "7";
  }
};

const isInLoop = (data, [x, y], loopTiles) => {
  if (pipes.indexOf(data[x][y]) != -1) {
    return loopTiles.indexOf(`${x},${y}`) == -1;
  }
  let count = 0;
  let currentPosition = data[x][y];
  while (currentPosition != undefined) {
    if (pipes.indexOf(currentPosition) != -1) {
      if (cornerPipe.indexOf(currentPosition) != -1) {
        const yNext = findNextCorner([x, y], data);
        if (crossedRegion(data[x][y], data[x][yNext])) count++;
        y = yNext;
        y++;
        currentPosition = data[x][y];
      } else {
        count++;
        y++;
        currentPosition = data[x][y];
      }
    } else {
      y++;
      currentPosition = data[x][y];
    }
  }
  return count % 2 != 0;
};

const changeJunkPipesToTiles = (data, loopTiles) => {
  for (let x = 0; x < data.length; x++) {
    for (let y = 0; y < data[0].length; y++) {
      if (loopTiles.indexOf(`${x},${y}`) == -1) {
        data[x][y] = ".";
      }
    }
  }
};

const justDoIt = (data) => {
  data = dataFormatter(data);
  const loopTiles = getLoopTilesArray(data);
  changeJunkPipesToTiles(data, loopTiles);
  let count = 0;
  for (let i = 0; i < data.length; i++) {
    for (let j = 0; j < data[0].length; j++) {
      if (isInLoop(data, [i, j], loopTiles)) {
        count++;
      }
    }
  }
  return count;
};
console.log(justDoIt(data));

// 335