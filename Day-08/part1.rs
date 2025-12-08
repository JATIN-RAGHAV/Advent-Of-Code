use std::fs;
use std::io;

struct Point{
    x:i64,
    y:i64,
    z:i64
}

struct Dist{
    dist:i64,
    i:usize,
    j:usize,
}

fn dfs(i:usize, j:usize, adj:&Vec<Vec<usize>>,visited:&mut Vec<bool>)->bool{
    if i == j{
        return true;
    }
    for x in adj[i].iter(){
        if !visited[*x]{
            visited[*x] = true;
            if dfs(*x,j,adj,visited){
                return true;
            }
        }
    }
    false
}

fn dfs_cnt(i:usize, adj:&Vec<Vec<usize>>, visited:&mut Vec<bool>) -> i32{
    visited[i] = true;
    let mut res:i32 = 0;
    for x in adj[i].iter(){
        if !visited[*x]{
            res += dfs_cnt(*x,&adj,visited);
        }
    }
    res+1
}

fn main() -> io::Result<()>{
    let data = fs::read_to_string("./text.txt")?;
    let data = data.trim();
    let data:Vec<&str> = data.split("\n").collect();
    let mut cordinates:Vec<Point> = Vec::new();
    for s in data.iter() {
        let nums:Vec<&str> = s.split(",").collect();
        let pt = Point{
            x:nums[0].parse().expect("Can't parse x"),
            y:nums[1].parse().expect("Can't parse y"),
            z:nums[2].parse().expect("Can't parse z"),
        };
        cordinates.push(pt);
    }
    let mut dist:Vec<Dist> = Vec::new();
    for i in 0..data.len(){
        for j in 0..data.len(){
            if i<j {
                let d:i64 = (cordinates[i].x - cordinates[j].x)*(cordinates[i].x - cordinates[j].x) +
                            (cordinates[i].y - cordinates[j].y)*(cordinates[i].y - cordinates[j].y) + 
                            (cordinates[i].z - cordinates[j].z)*(cordinates[i].z - cordinates[j].z);
                let dis = Dist{
                    dist:d,
                    i:i,
                    j:j
                };
                dist.push(dis);
            }
        }
    }
    dist.sort_by(|a,b| a.dist.cmp(&b.dist));
    let mut rem = 1000; 
    let mut adj:Vec<Vec<usize>>= vec![Vec::new();data.len()];
    for d in dist{
        let mut visited:Vec<bool> = vec![false;data.len()];
        visited[d.i] = true;
        if !dfs(d.i,d.j,&adj,&mut visited){
            adj[d.i].push(d.j);
            adj[d.j].push(d.i);
        }
        rem -= 1;
        if rem == 0{
            break;
        }
    }
    let mut visited = vec![false;data.len()];
    let mut res:Vec<i32> = Vec::new();
    for i in 0..data.len(){
        if !visited[i]{
            let cnt = dfs_cnt(i,&adj,&mut visited);
            res.push(cnt);
        }
    }
    res.sort();
    res.reverse();
    println!("Answer is {}",res[0]*res[1]*res[2]);
    Ok(())
}
