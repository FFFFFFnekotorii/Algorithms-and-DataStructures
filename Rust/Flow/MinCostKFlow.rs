#![allow(unused_imports)]
#![allow(unused_parens)]
#![allow(dead_code)]


use std::clone::Clone;
use std::cmp::{Ord, Ordering, PartialOrd, min, max};
use std::collections::{
    BTreeMap, HashMap, 
    BTreeSet, HashSet,
    VecDeque
};
use std::io;
use std::mem::swap;
use std::ops::*;
use std::str::{FromStr};
use std::fmt::{
    Debug,
    Display,
    Formatter
};
use std::cell::{
    Cell
};

const MOD: i32 = 998_244_353;
const INF: i32 = 1_000_000_007;
const IAM: u64 = 0x8c433d971212bf42;

fn type_of<T>(_: &T) -> String {
    format!("{}", std::any::type_name::<T>())
}

fn get_line() -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();

    input.trim().to_string()
}

fn load_args(args: &mut Vec<String>) {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();

    args.clear();
    args.extend(input.trim().split_whitespace().map(|w| w.to_string()));
}

struct Edge {
    to: usize,
    cap: i32,
    a: i32,
    flow: i32
}

impl Edge {
    fn new(to: usize, cap: i32, a: i32) -> Self {
        let flow = 0i32;
        Self { to, cap, a, flow }
    }
}

struct Network {
    adj: Vec<Vec<usize>>,
    eds: Vec<Edge>,
}

impl Network {
    fn new(n: usize) -> Self {
        let adj = vec![vec![]; n];
        let eds = vec![];
        Self { adj, eds }
    }

    fn src(&self) -> usize {
        self.adj.len() - 2
    }

    fn trg(&self) -> usize {
        self.adj.len() - 1
    }

    fn connect(&mut self, v: usize, u: usize, cap: i32, a: i32) {
        let idx = self.eds.len();

        self.adj[v].push(idx);
        self.adj[u].push(idx ^ 1);
        self.eds.push(Edge::new(u, cap, a));
        self.eds.push(Edge::new(v, 0, -a));
    }

    fn dijkstra(&self) -> Vec<Option<usize>> {
        let mut dist: Vec<Option<i64>> = vec![None; self.adj.len()];
        let mut prev: Vec<Option<usize>> = vec![None; self.adj.len()];
        let mut h: BTreeSet<(i64, usize)> = BTreeSet::new();

        dist[self.src()] = Some(0);
        h.insert((0, self.src()));
        while let Some((d, v)) = h.pop_first() {
            for idx in &self.adj[v] {
                let Edge { to, cap, a, flow } = self.eds[*idx];
                if flow < cap && (dist[to].is_none() || dist[to].unwrap() > d + a as i64) {
                    dist[to] = Some(d + a as i64);
                    prev[to] = Some(idx ^ 1);
                    h.insert((d + a as i64, to));
                }
            }
        }

        prev
    }

    fn mincost_kflow(&mut self, k: usize) -> (i64, i64) {
        let mut cost: i64 = 0;
        let mut flow: i64 = 0;

        for _ in 0 .. k {
            let prev = self.dijkstra();

            if prev[self.trg()].is_none() {
                break;
            }
            let mut cur = self.trg();
            while cur != self.src() {
                let idx1 = prev[cur].unwrap();

                self.eds[idx1 ^ 1].flow += 1;
                self.eds[idx1].flow -= 1;

                cost += self.eds[idx1 ^ 1].a as i64;
                
                cur = self.eds[idx1].to;
            }
            flow += 1;
        }

        (cost, flow)
    }
}

fn solve() {
    let mut args: Vec<String> = Vec::new();

    load_args(&mut args);
    let n = args[0].parse::<usize>().unwrap();
    let m = args[1].parse::<usize>().unwrap();

    let mut col: Vec<Vec<usize>> = vec![vec![0; m]; n];
    let mut cnt: Vec<usize> = vec![0; 26];

    for i in 0 .. n {
        let s = get_line().chars().collect::<Vec<_>>();
        for j in 0 .. m {
            col[i][j] = s[j] as usize - 'a' as usize;
            cnt[col[i][j]] += 1;
        }
    }

    let mut groups: Vec<Vec<(usize, usize)>> = Vec::new();
    for i in 0 .. (n + 1) / 2 {
        for j in 0 .. (m + 1) / 2 {
            let mut group = vec![];

            group.push((i, j));
            group.push((n - i - 1, j));
            group.push((i, m - j - 1));
            group.push((n - i - 1, m - j - 1));

            group.sort();
            group.dedup();
            groups.push(group);
        }
    }

    // println!("{:?}", &groups);

    let mut net = Network::new(groups.len() + 26 + 2);

    for i in 0 .. 26 {
        net.connect(net.src(), i, cnt[i] as i32, 0);
        for j in 0 .. cnt[i] {
            for g in 0 .. groups.len() {
                if cnt[i] < groups[g].len() {
                    continue;
                }
                let mut cost = 0;
                for (x, y) in groups[g].clone() {
                    if col[x][y] != i {
                        cost += 1;
                    }
                }
                net.connect(i, 26 + g, groups[g].len() as i32, cost * (4 / groups[g].len()) as i32);
            }
        }
    }

    for g in 0 .. groups.len() {
        net.connect(26 + g, net.trg(), groups[g].len() as i32, 0);
    }

    println!("{}", net.mincost_kflow(n * m).0 / 4);
}

fn main() {
    solve();
}
