use std::thread;

fn main() {
    let top = 100 * 1000 * 1000;
    let each = top / 10;

    let mut kids = vec![];

    for tt in 0..10 {
        let local_tt = tt.clone();

        kids.push(thread::spawn(move || {
            let i0 = local_tt * each as i64;
            let i1 = i0 + each as i64;

            let mut sum = 0i64;

            for ii in i0..i1 {
                sum += ii;
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
