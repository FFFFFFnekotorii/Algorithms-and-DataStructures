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

def solve_mod(a, b, m):
    #a * x = b (mod m)
    a %= m
    b %= m
    if(a == 0):
        return b
    if(b % a == 0):
        return b // a
    return (b + solve_mod(m, -b, a) * m) // a

def main():
    a, b, c = getf()
    #a * x + b * y = c
    g = gcd(a, b)
    if(c % g != 0):
        put("Impossible")
    else:
        a //= g
        b //= g
        c //= g
        x = solve_mod(a, c, b)
        y = (c - a * x) // b
        put("%d %d" % (x, y))
main()
