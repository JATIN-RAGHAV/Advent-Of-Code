import fs from 'fs';

const data = fs.readFileSync('./text.txt', 'utf-8');

const testData = `Time:      7  15   30
Distance:  9  40  200`

const findPossibleWays = (time, dist) =>{
    let count = 0;
    for(let t = 1; t<=time;t++){
        let winsRace = ((time-t)*t) > dist;
        if(winsRace) {
            count++
        };
    }
    return count;
}

const formatData = (data) =>{
     return data.split('\n').map(row => {
        return row.split(':')[1].trim().split(/ +/g).map(string => parseInt(string));
     });

}

const justDoIt = (data) =>{
    const [times, distances] = formatData(data);
    const racesNum = times.length;
    let errorMargin = 1;
    for(let i = 0;i<racesNum;i++){
        const possibleWays = findPossibleWays(times[i], distances[i]);
        errorMargin *= possibleWays;

    }
    return errorMargin;
}

console.log(justDoIt(data));