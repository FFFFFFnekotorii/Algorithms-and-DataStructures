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

from random import randint
from math import e

def cost(n, p, dist):
    res = 0
    for i in range(n - 1):
        res += dist[p[i]][p[i + 1]]
    res += dist[p[n - 1]][p[0]]
    return res

def rnd():
    n = randint(2, 200)
    a = randint(1, n // 2)
    return a / n

def psi(n):
    i = randint(0, n - 1)
    j = randint(0, n - 1)
    if(i == j):
        return psi(n)
    return (i, j)

def exp(n):
    return pow(e, n)

def solve(n, d):
    dist = [[(abs(d[i][0] - d[j][0]) + abs(d[i][1] - d[j][1])) for j in range(n)] for i in range(n)]
    p = [i for i in range(n)]
    t = 1.0
    gamma = 0.95
    for k in range(500):
        t *= gamma
        tmp = p.copy()
        change = psi(n)
        a, b = change
        tmp[a], tmp[b] = tmp[b], tmp[a]
        #print(tmp)
        f1 = cost(n, p, dist)
        f2 = cost(n, tmp, dist)
        if(f2 < f1):
            r = exp((f1 - f2) / t)
            if(r > rnd()):
                p = tmp.copy()
    #print(p)
    return cost(n, p, dist)

def main():
    t = int(get())
    for _ in range(t):
        _ = getf()
        d = [getf()]
        n = int(get())
        for i in range(n):
            d.append(getf())
        ans = solve(n + 1, d)
        put("The shortest path has length %d" % (ans))
main()
