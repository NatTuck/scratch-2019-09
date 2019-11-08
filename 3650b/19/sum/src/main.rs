
use std::thread;

fn main() {
    let top = 100 * 1000 * 1000;
    let each = top / 10;

    let mut kids = vec![];

    for tt in 0..10 {
        kids.push(thread::spawn(move || {
            let i0 = tt * each;
            let i1 = i0 + each;

            let mut sum = 0i64;

            for ii in i0..i1 {
                sum += ii as i64;
            }

            sum
        }));
    }

    let mut sum = 0i64;

    for tt in kids {
        sum += tt.join().unwrap();
    }

    println!("sum = {}", sum);
}
