import fs from 'fs';
import { convertToObject } from 'typescript';

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

const findGalaxies = (data) =>{
    let galaxies = [];
    for(let i = 0;i<data.length;i++){
        for(let j = 0;j<data[0].length;j++){
            if(data[i][j] == '#') galaxies.push([i,j]);
        }
    }
    return galaxies;
}

const findEmptyRowsColumnsBetweenGalaxies = (emptyRows, emptyColumns, galaxy1, galaxy2)=>{
    const rows = galaxy1[0]<galaxy2[0]? [galaxy1[0],galaxy2[0]]:[galaxy2[0],galaxy1[0]];
    const columns = galaxy1[1]<galaxy2[1]?[galaxy1[1],galaxy2[1]]:[galaxy2[1],galaxy1[1]];
    const emptyRowsCount = emptyRows.filter(row => row>rows[0] && row<rows[1]).length;
    const emptyColumnsCount = emptyColumns.filter(column => column>columns[0] && column<columns[1]).length;
    return emptyColumnsCount + emptyRowsCount;
}

const justDoIt = (data) => {
    const newData = dataFormatter(data);
    const emptyRows = findEmptyRows(newData);
    const emptyColumns = findEmptyColumns(newData);
    const galaxies = findGalaxies(newData);
    let totalDist = 0;
    for(let i = 0;i<galaxies.length-1;i++){
        for(let j = i+1;j<galaxies.length;j++){
            const currentShortestDist = Math.abs(galaxies[i][0]-galaxies[j][0]) + Math.abs(galaxies[i][1] - galaxies[j][1]);
            const intermediateEmptyRowsColumns = findEmptyRowsColumnsBetweenGalaxies(emptyRows, emptyColumns, galaxies[i],galaxies[j])
            const currentShortestDistExpanded = (currentShortestDist-intermediateEmptyRowsColumns) + (intermediateEmptyRowsColumns*1000000)
            totalDist += currentShortestDistExpanded;
        }
    }
    return totalDist;
}

console.log(justDoIt(data))

// 62618006
// 543018317006