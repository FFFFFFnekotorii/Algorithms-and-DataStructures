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

def getbit(m, pos):
    return m & (1 << pos)

def setbit(m, pos):
    return m | (1 << pos)
 
class pt0:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    def __repr__(self):
        return "(" + str(self.x) + ", " + str(self.y) + ")"
    
    def dist(self, other):
        return abs(self.x - other.x) + abs(self.y - other.y)

def dp(pos, m, dist, n, dp_calc):
    if(m == pow(2, n) - 1):
        return dist[pos][0]
    
    if(dp_calc[m][pos] != -1):
        return dp_calc[m][pos]
    
    res = 10 ** 9 + 7
    for i in range(n):
        if(getbit(m, i) == 0):
            m1 = setbit(m, i)
            cost = dist[pos][i]
            res = min(res, cost + dp(i, m1, dist, n, dp_calc))
    dp_calc[m][pos] = res
    return res
 
def main():
    n = int(get())
    dist = [[0] * n for i in range(n)]
    m = 0
    p = []
    for i in range(n):
        xi, yi = getf()
        p += [pt0(xi, yi)]
    for i in range(n):
        for j in range(n):
            dist[i][j] = p[i].dist(p[j])
    dp_calc = [[-1] * n for i in range(1 << n)]
    res = dp(0, m, dist, n, dp_calc)
    put("The shortest path has length %d" % (res))
main()
