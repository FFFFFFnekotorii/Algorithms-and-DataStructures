from sys import stdout
from sys import stdin
def get():
    return stdin.readline().strip()
def getf(sp = " "):
    return [int(i) for i in get().split(sp)]
def put(a, end = "\n"):
    stdout.write(str(a) + end)
def putf(a, sep = " ", end = "\n"):
    stdout.write(sep.join([str(i) for i in a]) + end)
      
#from collections import defaultdict as dd, deque
#from random import randint, shuffle, sample
#from functools import cmp_to_key, reduce
#from math import factorial as fac, acos, asin, atan2, gcd, log, e
#from bisect import bisect_right as br, bisect_left as bl, insort
 
def gcd(a, b):
    if(b == 0):
        return a
    return gcd(b, a % b)
 
class SegTree:
     
    def __init__(self, n):
        self.t = [0] * (4 * n)
        self.zero = 0
        self.func = lambda x, y: gcd(x, y)
 
    def build(self, v, l, r, a):
        if(r - l == 1):
            self.t[v] = a[l]
        else:
            m = (l + r) // 2
            self.build(2 * v, l, m, a)
            self.build(2 * v + 1, m, r, a)
            self.t[v] = self.func(self.t[2 * v], self.t[2 * v + 1])
 
    def get(self, v, l, r, ql, qr):
        if(ql <= l and r <= qr):
            return self.t[v]
        if(r <= ql or qr <= l):
            return self.zero
        m = (l + r) // 2
        return self.func(self.get(2 * v, l, m, ql, qr), self.get(2 * v + 1, m, r, ql, qr))
 
    def upd(self, v, l, r, ind, val):
        if(r - l == 1):
            if(l == ind):
                self.t[v] = val
        else:
            m = (l + r) // 2
            if(ind < m):
                self.upd(2 * v, l, m, ind, val)
            else:
                self.upd(2 * v + 1, m, r, ind, val)
            self.t[v] = self.func(self.t[2 * v], self.t[2 * v + 1])
 
def main():
    n = int(get())
    a = getf()
    t = SegTree(n)
    t.build(1, 0, n, a)
    q = int(get())
    ans = []
    for i in range(q):
        c, x, y = get().split()
        if(c == "g"):
            l, r = int(x), int(y)
            l -= 1
            res = t.get(1, 0, n, l, r)
            ans.append(res)
        else:
            ind, val = int(x), int(y)
            ind -= 1
            t.upd(1, 0, n, ind, val)
    putf(ans)
main()
