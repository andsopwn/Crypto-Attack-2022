fn main() {
    let mut val = String::new();
    std::io::stdin()
        .read_line (&mut val)
        .expect("");
    let mut space = val.split_whitespace();
    let mut next_num = || -> usize {
        space.next().expect("")
                   .parse().expect("")
    };
    let val1 = next_num();
    let val2 = next_num();

    println!("{}", val1 * val2);
  }