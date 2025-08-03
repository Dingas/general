use std::fmt;
use std::ops;
use std::cmp;

/*

fn main(){
    let cList1 = CauchyList { p: 8, content: vec![1, 2, 3, 4, 5] };
    let cList2 = CauchyList { p: 8, content: vec![1, 2, 3, 4, 5, 6, 7] };
}
*/

fn main(){
    let cList1 = CauchyList { p: 8, content: vec![1, 2, 3, 4, 5] };
    let cList2 = CauchyList { p: 8, content: vec![1, 2, 3, 4, 5, 6, 7] };
    
    let x = cList1 * cList2;
    println!("{}", x);
}


fn multi(a: Vec<i32>, b: Vec<i32>, c: i32) -> std::vec::Vec<i32>{
    
    
    let len = a.len() + b.len() -1;
    
    let mut new_vec: Vec<i32> = Vec::new();
    let mut temp_int: i32 = 0;
    for x in 0..len {
        //println!("x = {}", x);
        for i in 0..x{
            //println!("i = {}", x);
            if (x-i) < (b.len()) && i < a.len() {
                //println!("a[i] = {}, b[x-i] = {}", a[i], b[x-i]);
                temp_int+=a[i] * b[x-i];
                
            }

        }
        //println!("int ={}", temp_int);
        new_vec.push(temp_int);
        temp_int=0;
    }
    //println!("{}", new_vec.len());
    for x in 0..(len){
        new_vec[x] = new_vec[x]%c;
    }
   return new_vec;
}





fn multi_int(a: Vec<i32>, b: i32, c: i32) -> std::vec::Vec<i32>{
    let mut new_vec = Vec::new();
    
    for x in 0..a.len(){
        new_vec.push((a[x]*b)%c);
    }
    return new_vec;
    
}
/*

multiplier:
------
get length of both lists

new array length = cList1 length + cList2 length - 1

c[i] = a[0] * b[i] + a[1] * b[i - 1] + a[2] * b[i - 2] + · · · + a[i] * b[0] 


fn helper(list: Vec<i32>, x: i32) -> i32{
    if ( x < (list.len()-1)){
        return list[x];
    }
    else{
        return 0;
    }
}


*/


pub fn adder(a: Vec<i32>, b: Vec<i32>, c: i32) -> std::vec::Vec<i32>{
    let mut new_list = Vec::new();
    if a.len()>b.len() {
        for x in 0..(a.len() - 1){
            if x<=(b.len()-1){
                new_list.push((a[x] + b[x])%c);
            }
            else{
                new_list.push(0);
            }
        }  
    }
    else{
        for x in 0..(b.len() - 1){
            if x<=(a.len()-1){
                new_list.push((a[x] + b[x])%c);
            }
            else{
                new_list.push(0);
            } 
        }
    }
    return new_list;
}

pub fn subber(a: Vec<i32>, b: Vec<i32>, c: i32) -> std::vec::Vec<i32>{
    let mut new_list = Vec::new();
    if a.len()>b.len() {
        for x in 0..(a.len() - 1){
            if x<=(b.len()-1){
                new_list.push((a[x] - b[x])%c);
            }
            else{
                new_list.push(0);
            }
        }  
    }
    else{
        for x in 0..(b.len() - 1){
            if x<=(a.len()-1){
                new_list.push((a[x] - b[x])%c);
            }
            else{
                new_list.push(0);
            } 
        }
    }
    return new_list;
}


pub struct CauchyList {
    pub p: i32,
    pub content: Vec<i32>
}

impl CauchyList {
    // methods here
}

impl cmp::PartialEq for CauchyList {
    fn eq(&self, other: &Self) -> bool {    
        self.p == other.p && self.content == other.content
    }
}

impl ops::Add<CauchyList> for CauchyList {
    type Output = CauchyList;
    fn add(self, other: CauchyList) -> CauchyList {
        return CauchyList {p: self.p, content: adder(self.content, other.content, self.p)};
    }
}

impl ops::Sub<CauchyList> for CauchyList {
    type Output = CauchyList;
    fn sub(self, other: CauchyList) -> CauchyList {
        return CauchyList {p: self.p, content: subber(self.content, other.content, self.p)};
    }
}

impl ops::Mul<CauchyList> for CauchyList {
    type Output = CauchyList;
    fn mul(self, other: CauchyList) -> CauchyList {
        return CauchyList {p: self.p, content: multi(self.content, other.content, self.p)};
    }
}

impl ops::Mul<i32> for CauchyList {
    type Output = CauchyList;
    fn mul(self, other: i32) -> CauchyList {
        // for multiplying with regular integers
        return CauchyList {p: self.p, content: multi_int(self.content, other, self.p)};
    }
}

impl fmt::Display for CauchyList {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {    
		write!(f, "p:{}\nlength:{}\ncontent:{:?}", self.p, self.content.len(), self.content)
    }
}