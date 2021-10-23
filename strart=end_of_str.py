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

p = 31
q = 1000000007
 
class hstr:
    def __init__(self, s):
        self.h = [0]
        self.pq = [1]
        n = len(s)
        for i in range(n):
            self.h += [(self.h[i] * p + ord(s[i])) % q]
            self.pq += [(self.pq[i] * p) % q]
    def get(self, l, r):
        return ((self.h[r] - self.h[l] * self.pq[r - l]) % q + q) % q

def main():
    s = get()
    h = hstr(s)
    n = len(s)
    ans = 0
    for i in range(n // 2 + 1):
        if(h.get(0, i) == h.get(n - i, n)):
            ans = i
    put(ans)
    #max k: s[0 : k] = s[n - k : n]
main()
