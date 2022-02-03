from sys import stdout
from sys import stdin
def get():
    return stdin.readline().strip()
def getf(sep = " "):
    return [int(i) for i in get().split(sep)]
def put(a, end = "\n"):
    stdout.write(str(a) + end)
def putf(a, sep = " ", end = "\n"):
    stdout.write(sep.join([str(i) for i in a]) + end)
 
#from collections import defaultdict as dd, deque
#from random import randint, shuffle, sample
#from functools import cmp_to_key, reduce
#from math import factorial as fac, acos, asin, atan2, gcd, log, e
#from bisect import bisect_right as br, bisect_left as bl, insort
 
def calc(a0, d, n):
    return (n * (2 * a0 + d * (n - 1))) // 2
 
class SegTree:
    
    def __init__(self, n):
        self.tree = [0 for i in range(4 * n)]
        self.mod = [0 for i in range(4 * n)]
        #mod[v] = 0 => nothing to do
        #mov[v] = -val < 0 => set val
        #mov[v] = val > 0 => add val
    
    def build(self, v, l, r, a):
        if(r - l == 1):
            self.tree[v] = a[l]
            return 0
        m = (l + r) // 2
        self.build(2 * v, l, m, a)
        self.build(2 * v + 1, m, r, a)
        self.tree[v] = self.tree[2 * v] + self.tree[2 * v + 1]
 
    def push(self, v, l, r):
        if(r - l == 1):
            self.mod[v] = 0
            return 0
        if(self.mod[v] == 0):
            return 0
        m = (l + r) // 2
        if(self.mod[v] > 0):
            if(self.mod[2 * v] == 0):
                self.mod[2 * v] = self.mod[v]
                self.tree[2 * v] += self.mod[v] * (m - l)
            elif(self.mod[2 * v] > 0):
                self.mod[2 * v] += self.mod[v]
                self.tree[2 * v] += self.mod[v] * (m - l)
            else:
                self.tree[2 * v] = (-self.mod[2 * v] + self.mod[v]) * (m - l)
                self.mod[2 * v] = self.mod[2 * v] - self.mod[v]
            
            if(self.mod[2 * v + 1] == 0):
                self.mod[2 * v + 1] = self.mod[v]
                self.tree[2 * v + 1] += self.mod[v] * (r - m)
            elif(self.mod[2 * v + 1] > 0):
                self.mod[2 * v + 1] += self.mod[v]
                self.tree[2 * v + 1] += self.mod[v] * (r - m)
            else:
                self.tree[2 * v + 1] = (-self.mod[2 * v + 1] + self.mod[v]) * (r - m)
                self.mod[2 * v + 1] = self.mod[2 * v + 1] - self.mod[v]
        else:
            self.mod[2 * v] = self.mod[v]
            self.mod[2 * v + 1] = self.mod[v]
            self.tree[2 * v] = -self.mod[2 * v] * (m - l)
            self.tree[2 * v + 1] = -self.mod[2 * v + 1] * (r - m)
        self.mod[v] = 0
 
    def get(self, v, l, r, ql, qr):
        if(r <= ql or qr <= l):
            return 0
        self.push(v, l, r)
        if(ql <= l and r <= qr):
            return self.tree[v]
        m = (l + r) // 2
        res = self.get(2 * v, l, m, ql, qr) + self.get(2 * v + 1, m, r, ql, qr)
        return res
 
    def upd(self, v, l, r, ql, qr, val):
        if(r <= ql or qr <= l):
            return 0
        self.push(v, l, r)
        if(ql <= l and r <= qr):
            self.mod[v] = -val
            self.tree[v] = val * (r - l)
            return 0
        m = (l + r) // 2
        self.upd(2 * v, l, m, ql, qr, val)
        self.upd(2 * v + 1, m, r, ql, qr, val)
        self.tree[v] = self.tree[2 * v] + self.tree[2 * v + 1]
 
    def add(self, v, l, r, ql, qr, val):
        if(r <= ql or qr <= l):
            return 0
        self.push(v, l, r)
        if(ql <= l and r <= qr):
            self.mod[v] = val
            self.tree[v] += val * (r - l)
            return 0
        m = (l + r) // 2
        self.add(2 * v, l, m, ql, qr, val)
        self.add(2 * v + 1, m, r, ql, qr, val)
        self.tree[v] = self.tree[2 * v] + self.tree[2 * v + 1]
 
def main():
    n, q = getf()
    a = getf()
    t = SegTree(n)
    t.build(1, 0, n, a)
    for i in range(q):
        inp = get().split()
        qtype = int(inp[0])
        l = int(inp[1]) - 1
        r = int(inp[2])
        if(qtype == 1):
            x = int(inp[3])
            t.add(1, 0, n, l, r, x)
        elif(qtype == 2):
            x = int(inp[3])
            t.upd(1, 0, n, l, r, x)
        else:
            put(t.get(1, 0, n, l, r))
main()
