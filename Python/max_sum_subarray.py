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

def main():
    n, m = getf()
    a = [getf() for i in range(n)]
    pr = [[0] * (m + 1) for i in range(n + 1)]
    pr[1][1] = a[0][0]
    for i in range(2, n + 1):
        pr[i][1] = pr[i - 1][1] + a[i - 1][0]
    for j in range(2, m + 1):
        pr[1][j] = pr[1][j - 1] + a[0][j - 1]
    ans = pr[1][1]
    for i in range(2, n + 1):
        for j in range(2, m + 1):
            pr[i][j] = pr[i - 1][j] + pr[i][j - 1] + a[i - 1][j - 1] - pr[i - 1][j - 1]
    for i1 in range(0, n):
        for i2 in range(i1 + 1, n + 1):
            res = 0
            for j in range(1, m + 1):
                res += pr[i2][j] + pr[i1][j - 1] - pr[i1][j] - pr[i2][j - 1]
                if(res > ans):
                    ans = res
                if(res < 0):
                    res = 0
    put(ans)
main()
