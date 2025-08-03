fn main(){

    let mut v1 = vec![1,2,3,4,5,6,7,8,9];
    let mut v2 = vec![1,2,3,4,5,6,7];
    let len = v1.len() + v2.len() - 1;

    let mut new_vec = Vec::new();
    for x in 0..len-1 {
        for i in 0..x{
            let mut val = x-i;
            if (val) < v2.len() || i < v1.len() {
                new_vec.push(v1[i] * v2[val]);
            }
            else{ new_vec.push(0)}
        }
    }
   println!("{:?}", new_vec);
}