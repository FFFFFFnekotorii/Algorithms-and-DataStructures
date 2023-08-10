from sys import stdout
from sys import stdin

def get():
    return stdin.readline().strip()
def getf():
    return [int(i) for i in get().split()]
def put(a, end = "\n"):
    stdout.write(str(a) + end)
def putf(a, sep = " ", end = "\n"):
    stdout.write(sep.join([str(i) for i in a]) + end)

#from collections import defaultdict as dd, deque
#from random import randint, shuffle, sample
#from functools import cmp_to_key, reduce
#from math import factorial as fac, acos, asin, atan2, gcd, log, e
#from bisect import bisect_right as br, bisect_left as bl, insort

class hashtable:
    
    def __init__(self, maxn):
        self.keys = [-1] * maxn
        self.vals = [0] * maxn
        self.maxn = maxn

    def hasher(self, x):
        return x ^ 72727

    def __getitem__(self, key):
        h = self.hasher(key) % self.maxn

        while(self.keys[h] != key and self.keys[h] != -1):
            h += 1
            if(h == self.maxn):
                h = 0

        self.keys[h] = key
        return self.vals[h]

    def __setitem__(self, key, val):
        h = self.hasher(key) % self.maxn

        while(self.keys[h] != key and self.keys[h] != -1):
            h += 1
            if(h == self.maxn):
                h = 0

        self.keys[h] = key
        self.vals[h] = val

def main():

    pass
    
main()
