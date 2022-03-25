use std::io;

fn main() {
    let mut cal_number = 0;
    let mut input_line = String::new();
    io::stdin()
        .read_line(&mut input_line)
        .expect("Failed to Read");
    
    let mut a = min(10, 5)
    println!("{}", a);
}

/*
loop {
        if x == 1 { break; }
        else if x 
        else if x % 3 == 0 { x /= 3; cal_number += 1; }
        else if x % 2 == 0 { x /= 2; cal_number += 1; }
        else { x -= 1; cal_number += 1; }
    }
    let x: i32 = get_num
        .trim()
        .parse()
        .expect("");
    */
