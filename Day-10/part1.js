import fs from 'fs';

const data = fs.readFileSync('text.txt','utf-8');

const testData1 = `7-F7-
.FJ|7
SJLL7
|F--J
LJ.LJ`

const testData2 = `-L|F7
7S-7|
L|7||
-L-J|
L|-JF`

const dataFormatter = (data) =>{
    let returnData = data.split('\n');
    for(let i = 0;i<returnData.length;i++){
        returnData[i] = returnData[i].split('');
    }
    return returnData;
}

const findS = (data) =>{
    for(let i = 0; i<data.length; i++){
        for(let j = 0;j<data[0].length;j++){
            if(data[i][j] == 'S') return [i,j];
        }
    }
}

const pipes = ['|','-','L','J','7','F','S'];

const possibleMoves = {
    '|':[[-1,0],[1,0]],
    '-':[[0,1],[0,-1]],
    'L':[[-1,0],[0,1]],
    'J':[[-1,0],[0,-1]],
    '7':[[0,-1],[1,0]],
    'F':[[1,0],[0,1]]
}

const possibleApproaches = {
    '|':[[-1,0],[1,0]],
    '-':[[0,1],[0,-1]],
    'L':[[1,0],[0,-1]],
    'J':[[1,0],[0,1]],
    '7':[[0,1],[-1,0]],
    'F':[[-1,0],[0,-1]],
}

const arrayEquals = (arr1, arr2) =>{
    if(arr1.length != arr2.length) return false;
    return arr1.every((value, index) => value == arr2[index]);
}

const makeAMove = ([x,y], [xm,ym], data)=>{
    if(data[x+xm] == undefined)return false; 
    if(data[x+xm][y+ym] == undefined) return false;
    const newPosition = data[x+xm][y+ym];
    if(newPosition == 'S') return 'S';
    if(pipes.indexOf(newPosition) != -1){
        const possibleApproache = possibleApproaches[newPosition];
        if(possibleApproache.some(value => arrayEquals(value, [xm,ym]))){
            const possibleMove = possibleMoves[newPosition];
            const nextMove = possibleMove.find(move => !((move[0]+xm == 0) && (move[1]+ym == 0)));
            return nextMove;
        }
    }
    return false;
}

const justDoIt = (data) =>{
    data = dataFormatter(data);
    const startingMoves = [[0,1],[1,0],[-1,0],[0,-1]];
    for(let move of startingMoves){
        let [x,y] = findS(data);
        let steps = 0;
        let currentMove = move;
        while(true){
            currentMove = makeAMove([x,y],move,data);
            steps++;
            x += move[0];
            y += move[1];
            move = currentMove;
            if(data[x][y] == 'S') return steps/2;
            if(!move)break;
        }
    }

}

console.log(justDoIt(data))

// 7097