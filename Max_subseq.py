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

class multiset:
    def __init__(self):
        self.d = dict()
        self.usd = set()
        self.sz = 0

    def insert(self, x):
        if(x not in self.usd):
            self.usd.add(x)
            self.d[x] = 0
            self.sz += 1
        self.d[x] += 1

    def erase(self, x):
        if(self.d[x] == 1):
            self.usd.remove(x)
            self.sz -= 1
        self.d[x] -= 1

    def min(self):
        return min(self.usd)

    def __len__(self):
        return self.sz

#ans[i] : max sum of k elements in [0 : i]
def main():
    n, k = getf()
    a = getf()
    cnt = multiset()
    ans = [None] * n
    ans[0] = a[0]
    cnt.insert(a[0])
    cur_sum = a[0]
    for i in range(1, k):
        cur_sum += a[i]
        cnt.insert(a[i])
        ans[i] = cur_sum
    putf(ans)
    for i in range(k, n):
        m = cnt.min()
        if(a[i] > m):
            cur_sum += a[i]
            cur_sum -= m
            cnt.insert(a[i])
            cnt.erase(m)
        ans[i] = cur_sum
    putf(ans)
main()
