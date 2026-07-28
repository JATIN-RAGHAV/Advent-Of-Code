use std::{cmp::max, fs,cmp::min};


pub fn part1(){
    let input = fs::read_to_string("./2.txt").unwrap();
    let input:Vec<&str> = input.trim().split("\n").collect();

    let mut res = 0;

    for ln in &input{
        let rn:Vec<&str> = ln.trim().split_whitespace().collect();
        let mut bg = i32::MIN;
        let mut sm = i32::MAX;
        for c in rn{
            let nm = c.trim().parse().unwrap();
            bg = max(bg,nm);
            sm = min(sm,nm);
        }

        res += bg - sm;
    }

    println!("Answer is {res}");
}



pub fn part2(){
    let input = fs::read_to_string("./2.txt").unwrap();
    let input:Vec<&str> = input.trim().split("\n").collect();

    let mut res = 0;

    for ln in input{
        let rn:Vec<&str> = ln.trim().split_whitespace().collect();
        let rn:Vec<i32> = rn.iter().map(|s|{
            s.trim().parse().unwrap()
        }).collect();

        'outer: for i in 0..rn.len(){
            for j in i+1..rn.len(){
                if rn[i] % rn[j] == 0{
                    res += rn[i] / rn[j];
                    break 'outer;
                }
                if rn[j] % rn[i] == 0 {
                    res += rn[j] / rn[i];
                    break 'outer;
                }
            }
        }
    }

    println!("Answer is {res}");
}
