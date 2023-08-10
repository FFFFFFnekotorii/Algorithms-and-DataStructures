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

def dfs(g, s, d, sz):
    n = len(g)
    par1 = [-1] * n
    par2 = [-1] * n
    st = [s]

    sz[s] = 1
    d[s] = 0

    do = 0
    while(st):
        v = st[-1]
        f = False
        while(g[v]):
            u, w = g[v].pop()
            if(par1[v] == u):
                continue
            st += [u]
            d[u] = 0
            sz[u] = 1
            par1[u] = v
            par2[u] = w
            f = True
        
        if(f == False):
            if(par1[v] != -1):
                sz[par1[v]] += sz[v]
                d[par1[v]] += d[v] + par2[v] * sz[v]
            st.pop()
        do += 1

def dfs1(g, s, d, sz, dp):
    n = len(g)
    par1 = [-1] * n
    par2 = [-1] * n
    st = [s]

    dp[s] = d[s]

    do = 0
    while(st):
        v = st[-1]
        f = False
        while(g[v]):
            u, w = g[v].pop()
            if(par1[v] == u):
                continue
            st += [u]
            d[v] -= (d[u] + w * sz[u])
            d[u] += (d[v] + w * (n - sz[u]))
            dp[u] = d[u]
            par1[u] = v
            par2[u] = w
            f = True
            break
        
        if(f == False):
            if(par1[v] != -1):
                d[v] -= (d[par1[v]] + par2[v] * (n - sz[v]))
                d[par1[v]] += (d[v] + par2[v] * sz[v])
            st.pop()
        do += 1

def copy(a):
    if(type(a) != list):
        return a
    return [copy(x) for x in a]

def main():

    n = int(get())

    g = [[] for i in range(n)]

    for i in range(n - 1):
        v, u, w = getf()
        v -= 1
        u -= 1

        g[v] += [(u, w)]
        g[u] += [(v, w)]

    g1 = copy(g)

    d = [-1] * n
    sz = [-1] * n
    dp = [-1] * n
    dfs(g, 0, d, sz)

    dfs1(g1, 0, d, sz, dp)
    
    #print(d, dp)

    put("%.4f" % (sum(dp) / (n * (n - 1))))
    
main()
