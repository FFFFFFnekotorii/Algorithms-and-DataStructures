#![allow(unused_imports)]
#![allow(unused_parens)]
#![allow(dead_code)]


use std::clone::Clone;
use std::cmp::{Ord, Ordering, PartialOrd, min, max};
use std::collections::{BTreeMap, HashMap, HashSet, VecDeque};
use std::io;
use std::mem::swap;
use std::ops::*;
use std::str::{FromStr};
use std::fmt::{
    Debug,
    Display,
    Formatter
};

const MOD: i32 = 998_244_353;
const INF: i32 = 1_000_000_007;
const IAM: u64 = 0x8c433d971212bf42;

fn type_of<T>(_: &T) -> String {
    return format!("{}", std::any::type_name::<T>());
}

fn get_line() -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();

    return input.trim().to_string();
}

fn load_args(args: &mut Vec<String>) {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();

    args.clear();
    args.extend(input.trim().split_whitespace().map(|s| s.to_string()));
}

#[derive(Debug, Clone, Copy, Default)]
struct Point<T> {
    x: T,
    y: T,
    z: T,
}

#[derive(Debug, PartialEq, Eq)]
struct ParsePointError;

impl<T> Point<T> {
    fn new(x: T, y: T, z: T) -> Self {
        Self { x, y, z }
    }

    fn map<U>(self) -> Point<U>
    where
        T: Into<U>
    {
        Point::new(self.x.into(), self.y.into(), self.z.into())
    }
}

impl<T: Add<Output = T>> Add for Point<T> {
    type Output = Point<T>;
    fn add(self, oth: Point<T>) -> Self::Output {
        Point::new(self.x + oth.x, self.y + oth.y, self.z + oth.z)
    }
}

impl<T: Sub<Output = T>> Sub for Point<T> {
    type Output = Point<T>;
    fn sub(self, oth: Point<T>) -> Self::Output {
        Point::new(self.x - oth.x, self.y - oth.y, self.z - oth.z)
    }
}

impl<T: Mul<Output = T> + Add<Output = T>> Mul for Point<T> {
    type Output = T;
    fn mul(self, oth: Point<T>) -> Self::Output {
        self.x * oth.x + self.y * oth.y + self.z * oth.z
    }
}

impl<T: Mul<Output = T> + Sub<Output = T> + Copy> BitXor for Point<T> {
    type Output = Point<T>;
    fn bitxor(self, oth: Point<T>) -> Self::Output {
        Point::new(
            self.y * oth.z - oth.y * self.z,
            self.x * oth.z - oth.x * self.z,
            self.x * oth.y - oth.x * self.y
        )
    }
}

impl<T: FromStr> FromStr for Point<T> {
    type Err = ParsePointError;

    fn from_str(line: &str) -> Result<Self, Self::Err> {
        let words: Vec<&str> = line.trim().split_whitespace().collect::<_>();

        Ok(Point {
            x: words[0].parse().map_err(|_| ParsePointError)?,
            y: words[1].parse().map_err(|_| ParsePointError)?,
            z: words[2].parse().map_err(|_| ParsePointError)?
        })
    }
}

impl Point<f64> {
    fn length(&self) -> f64 {
        (*self * *self).powf(0.5)
    }

    fn times(&self, k: f64) -> Self {
        Point::new(self.x * k, self.y * k, self.z * k)
    }
}

struct CuteXorShift {
    state: u32,
}

impl CuteXorShift {
    pub fn new(seed: u32) -> Self {
        CuteXorShift { state: seed }
    }

    pub fn next_u32(&mut self) -> u32 {
        self.state ^= self.state << 13;
        self.state ^= self.state >> 17;
        self.state ^= self.state << 5;
        self.state
    }

    pub fn next_f64(&mut self) -> f64 {
        self.next_u32() as f64 / 4294967295.0
    }
}

fn min_f64(a: f64, b: f64) -> f64 {
    if a < b {
        a
    } else {
        b
    }
}

fn sign_f64(x: f64) -> i32 {
    if x > 0.0 {
        return 1;
    }
    return -1;
}

fn solve() {
    let mut args: Vec<String> = Vec::new();
    
    let a = get_line().parse::<Point<f64>>().unwrap();
    let b = get_line().parse::<Point<f64>>().unwrap();
    let c = get_line().parse::<Point<f64>>().unwrap();

    const ITERS: usize = 1e7 as usize;
    let mut count: usize = 0;
    let mut rnd = CuteXorShift::new(1337);
    for i in 0 .. ITERS {
        let mut l1 = rnd.next_f64();
        let mut l2 = rnd.next_f64();

        if l1 + l2 > 1.0 {
            l1 = 1.0 - l1;
            l2 = 1.0 - l2;
        }

        let pt = a + (b - a).times(l1) + (c - a).times(l2);
        if pt.length() < 100.0 {
            count += 1;
        }
    }
    let s = ((b - a) ^ (c - a)).length() / 2.0;

    println!("{}", (count as f64 / ITERS as f64) * s);
}

fn main() {
    solve();
}
