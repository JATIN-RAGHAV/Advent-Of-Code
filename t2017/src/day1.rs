use std::fs;

pub fn part2(){
    let input = fs::read_to_string("./1.txt").expect("Cant' read");
    let input:Vec<&str> = input.trim().split("").collect();
    let mut num_input:Vec<i32> = Vec::new();

    for i in 1..input.len()-1{
        num_input.push(input[i].trim().parse().unwrap());
    }

    let half = num_input.len()>>1;
    let full = num_input.len();
    let mut res = 0;

    for i in 0..num_input.len(){
        if num_input[i] == num_input[(i+half)%full]{
            res += num_input[i];
        }
    }

    println!("Answer is {res}");
}

pub fn part1(){
    let input = fs::read_to_string("./1.txt").expect("Error in reading");
    let input:Vec<&str> = input.trim().split("").collect();
    let mut num_input:Vec<i32>=Vec::new();
    for i in 1..input.len()-1{
        num_input.push(input[i].trim().parse().expect("Can't prase."));
    }

    let mut lst = -1;
    let mut res = 0;
    for n in &num_input{
        if *n == lst {
            res += lst;
        }
        lst = *n;
    }
    if num_input.len() > 1 && num_input[0] == *num_input.last().expect(""){
        res += num_input[0];
    }

    println!("Answer is {res}");
}
