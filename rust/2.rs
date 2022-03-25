use std::io;

fn main() {
    let mut get_num = String::new();
    io::stdin()
        .read_line(&mut get_num)
        .expect("");
    let x: i32 = get_num
        .trim()
        .parse()
        .expect("");
    
    let mut num_array:[i32; 1000];
    
    for i in 0..x {
        let mut get = String::new();
        io::stdin()
            .read_line(&mut get_num)
            .expect("");
        let y: i32 = get_num
            .trim()
            .parse()
            .expect("");
        num_array[i] = y;
    }

    println!("{}", num_array[0]);
}