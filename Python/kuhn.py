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

def kuhn(g, v, used, mt):

    if(used[v] == used[-1]):
        return 0

    used[v] = used[-1]

    for u in g[v]:
        if(mt[u] == -1):
            mt[u] = v
            return 1

    for u in g[v]:
        if(kuhn(g, mt[u], used, mt) == 1):
            mt[u] = v
            return 1
    
    return 0
    

def max_match(g, n, m):
    
    mt = [-1] * (n + m)
    uwu = [-1] * (n + m + 1)
    uwu[-1] = 0

    ans = 0

    for i in range(n):
        ans += kuhn(g, i, uwu, mt)
        uwu[-1] += 1

    return ans

def main():

    n, m, k = getf()

    g = [[] for i in range(n + m)]

    for i in range(k):
        v, u = getf()
        v -= 1
        u -= 1

        g[v] += [u + n]
        g[u + n] += [v]

    w = max_match(g, n, m)

    put(n + m - w)
    
main()
