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

use std::f64::consts::PI;

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

#[derive(Debug, Clone, Copy)]
struct Point<T> {
    x: T,
    y: T,
}

#[derive(Debug, PartialEq, Eq)]
struct ParsePointError;

impl<T> Point<T> {
    fn new(x: T, y: T) -> Self {
        Self { x, y }
    }

    fn map<U>(self) -> Point<U>
    where
        T: Into<U>
    {
        Point::new(self.x.into(), self.y.into())
    }
}

impl<T: Default> Point<T> {
    fn default() -> Self {
        Point::new(T::default(), T::default())
    }
}

impl<T: Add<Output = T>> Add for Point<T> {
    type Output = Point<T>;
    fn add(self, oth: Point<T>) -> Self::Output {
        Point::new(self.x + oth.x, self.y + oth.y)
    }
}

impl<T: Sub<Output = T>> Sub for Point<T> {
    type Output = Point<T>;
    fn sub(self, oth: Point<T>) -> Self::Output {
        Point::new(self.x - oth.x, self.y - oth.y)
    }
}

impl<T: Mul<Output = T> + Add<Output = T>> Mul for Point<T> {
    type Output = T;
    fn mul(self, oth: Point<T>) -> Self::Output {
        self.x * oth.x + self.y * oth.y
    }
}

impl<T: Mul<Output = T> + Sub<Output = T>> BitXor for Point<T> {
    type Output = T;
    fn bitxor(self, oth: Point<T>) -> Self::Output {
        self.x * oth.y - self.y * oth.x
    }
}

impl<T: FromStr> FromStr for Point<T> {
    type Err = ParsePointError;

    fn from_str(line: &str) -> Result<Self, Self::Err> {
        let words: Vec<&str> = line.trim().split_whitespace().collect::<_>();

        Ok(Point {
            x: words[0].parse().map_err(|_| ParsePointError)?,
            y: words[1].parse().map_err(|_| ParsePointError)?
        })
    }
}

impl Point<f64> {
    fn length(&self) -> f64 {
        (*self * *self).powf(0.5)
    }

    fn times(&self, k: f64) -> Self {
        Point::new(self.x * k, self.y * k)
    }

    fn perp(&self) -> Self {
        Point::new(self.y, -self.x)
    }

    fn rotated(&self, phi: f64) -> Self {
        Point::new(
            self.x * phi.cos() - self.y * phi.sin(),
            self.x * phi.sin() + self.y * phi.cos()
        )
    }

}

fn sign<T: Sub<Output = T> + PartialOrd + Copy>(x: T) -> i32 {
    if x > x - x {
        return 1;
    }
    return -1;
}

#[derive(Copy, Clone, Debug)]
struct Line {
    p0: Point<f64>,
    dir: Point<f64>
}

impl Line {
    fn new(p0: Point<f64>, dir: Point<f64>) -> Self {
        Self {
            p0,
            dir
        }
    }

    fn from_2pts(a: Point<f64>, b: Point<f64>) -> Self {
        Self {
            p0: a,
            dir: b - a
        }
    }

    fn intersection(l1: Line, l2: Line) -> Point<f64> {
        let t = ((l2.p0 - l1.p0) ^ l2.dir) / (l1.dir ^ l2.dir);
        l1.p0 + l1.dir.times(t)
    }
}

#[derive(Copy, Clone, Debug)]
struct Circle {
    center: Point<f64>,
    radius: f64
}

impl Circle {
    fn new(center: Point<f64>, radius: f64) -> Self {
        Self {
            center,
            radius
        }
    }

    fn from_3pts(a: Point<f64>, b: Point<f64>, c: Point<f64>) -> Self {
        let l1 = Line::new((a + b).times(0.5), (b - a).perp());
        let l2 = Line::new((a + c).times(0.5), (c - a).perp());

        let center = Line::intersection(l1, l2);
        let radius = (a - center).length();

        Self {
            center,
            radius
        }
    }
}

fn solve() {
    let mut args: Vec<String> = Vec::new();

    let a = get_line().parse::<Point<f64>>().unwrap();

    dbg!(a, sign::<u64>(3), sign::<f32>(-0.0));
}

fn main() {
    solve();
}
