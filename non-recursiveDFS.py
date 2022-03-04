from sys import stdout
from sys import stdin
def get():
    return stdin.readline().strip()
def getf(sep = " "):
    return [int(i) for i in get().split(sep)]
def put(a, end = "\n"):
    stdout.write(str(a) + end)
def putf(a, sep = " ", end = "\n"):
    stdout.write(sep.join([str(i) for i in a]) + end)
 
#from collections import defaultdict as dd, deque
#from random import randint, shuffle, sample
#from math import factorial as fac, acos, asin, atan2, gcd, log, e
#from bisect import bisect_right as br, bisect_left as bl, insort

def main():
    n = int(get())
    g = [[] for i in range(n)]
    for i in range(n - 1):
        a, b = getf()
        a -= 1
        b -= 1
        g[a] += [b]
        g[b] += [a]
    t = 0
    used = [False] * n
    tin = [0] * n
    tout = [0] * n
    color = [0] * n
    stack = [0]
    while(stack):
        v = stack[-1]
        if(color[v] == 0):
            tin[v] = t
            t += 1
            color[v] = 1
            for u in g[v]:
                stack.append(u)
        else:
            color[v] = 2
            tout[v] = t
            t += 1
            stack.pop()
    print(tin)
    print(tout)
main()
