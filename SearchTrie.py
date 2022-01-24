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

def bin64(n):
    res = []
    while(n > 0):
        res.append(n % 2)
        n //= 2
    while(len(res) < 64):
        res.append(0)
    res.reverse()
    return res

class Node:
    def __init__(self):
        self.term = 0
        self.to = [None, None]
        self.cnt = 0

class Trie:
    def __init__(self):
        self.root = Node()
    def insert(self, val):
        cur = self.root
        binary = bin64(val)
        for i in binary:
            if(cur.to[i] == None):
                cur.to[i] = Node()
            cur = cur.to[i]
            cur.cnt += 1
    def lower_bound(self, val):
        cur = self.root
        binary = bin64(val)

    def _lower_bound(self, val)

def main():
    t = Trie()
main()
