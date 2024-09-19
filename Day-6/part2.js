import fs from 'fs';

const data = fs.readFileSync('./text.txt', 'utf-8');

const testData = `Time:      7  15   30
Distance:  9  40  200`

const findPossibleWays = (time, dist) =>{
    for(let t = 1; t<=time;t++){
        let winsRace = ((time-t)*t) > dist;
        if(winsRace) {
            const lowestTime = t;
            const highestTime = time-t;
            const possibleWays = (highestTime-lowestTime)+1;
            return possibleWays
        };
    }
    return 0;
}

const formatData = (data) =>{
     return data.split('\n').map(row => {
        return parseInt(row.split(':')[1].trim().split(/ +/g).join(''))
     });

}

const justDoIt = (data) =>{
    const [time, distance] = formatData(data);
    return findPossibleWays(time, distance);
}

console.log(justDoIt(data));