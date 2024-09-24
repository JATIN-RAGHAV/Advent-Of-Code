import fs from 'fs';

const data = fs.readFileSync('text.txt','utf-8');

const testData = `...#......
.......#..
#.........
..........
......#...
.#........
.........#
..........
.......#..
#...#.....`

const dataFormatter = (data) =>{
    return data.split('\n').map(row => {
        return row.split('')
    })
}

const findEmptyRows = (data) =>{
    let emptyRows = [];
    for(let i= 0;i< data.length;i++){
        const galaxies = data[i].find(point => point=='#');
        if(!galaxies){
            emptyRows.push(i);
        }
    }
    return emptyRows;
}

const findEmptyColumns = (data) =>{
    let emptyColumnsBoolean = new Array(data[0].length).fill(true);
    for(let i = 0;i<data[0].length;i++){
        for(let j = 0;j<data.length;j++){
            if(data[j][i] == '#') emptyColumnsBoolean[i] = false; 
        }
    }
    let emptyColumns = [];
    for(let i = 0;i<emptyColumnsBoolean.length;i++){
        if(emptyColumnsBoolean[i]) emptyColumns.push(i)
    }
    return emptyColumns;
}

const addEmptyRows = (data,rowIndexArray) =>{
    const emptyRow = new Array(data[0].length).fill('.');
    for(let index = rowIndexArray.length-1;index>=0;index--){
        data.splice(rowIndexArray[index],0,emptyRow);
    }
}

const addEmptyColumns = (data, columnIndexArray) =>{
    for(let i = 0; i<columnIndexArray.length;i++){
        for(let j = 0;j<data.length;j++){
            data[j].splice(columnIndexArray[i]+i+1,0,'.');
        }
    }
}

const findGalaxies = (data) =>{
    let galaxies = [];
    for(let i = 0;i<data.length;i++){
        for(let j = 0;j<data[0].length;j++){
            if(data[i][j] == '#') galaxies.push([i,j]);
        }
    }
    return galaxies;
}

const justDoIt = (data) => {
    const newData = dataFormatter(data);
    const emptyRows = findEmptyRows(newData);
    const emptyColumns = findEmptyColumns(newData);
    addEmptyColumns(newData,emptyColumns);
    addEmptyRows(newData,emptyRows);
    const galaxies = findGalaxies(newData);
    let totalDist = 0;
    for(let i = 0;i<galaxies.length-1;i++){
        for(let j = i+1;j<galaxies.length;j++){
            const shortestDistForCurrentPair = Math.abs(galaxies[i][0]-galaxies[j][0]) + Math.abs(galaxies[i][1] - galaxies[j][1]);
            totalDist += shortestDistForCurrentPair;
        }
    }
    return totalDist;
}

console.log(justDoIt(data))

// 9403026