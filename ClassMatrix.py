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

MOD = 10 ** 9 + 7

class Matrix:
    def __init__(self, n, m):
        self.M = [[0 for j in range(m)] for i in range(n)]
        self.size = (n, m)
 
    def __repr__(self):
        return "\n".join(["[" + " ".join([str(j) for j in i]) + "]" for i in self.M])
 
    def fill(self, arr):
        n, m = self.size
        for i in range(n):
            for j in range(m):
                self.M[i][j] = arr[i][j] % MOD
 
    def __add__(self, other):
        if(self.size != other.size):
            put("---error---")
            put("cant size(%d, %d) add to size(%d, %d)" % (self.size[0], self.size[1], other.size[0], other.size[1]))
            put("-----------")
        else:
            n, m = self.size
            for i in range(n):
                for j in range(m):
                    self.M[i][j] += other.M[i][j]
                    self.M[i][j] %= MOD
        return self
 
    def __mul__(self, other):
        n, k1 = self.size
        k2, m = other.size
        if(k1 != k2):
            put("---error---")
            put("cant size(%d, %d) multiply by size(%d, %d)" % (self.size[0], self.size[1], other.size[0], other.size[1]))
            put("-----------")
        else:
            c = Matrix(n, m)
            for i in range(n):
                for j in range(m):
                    for k in range(k1):
                        c.M[i][j] += self.M[i][k] * other.M[k][j]
                        c.M[i][j] %= MOD
            return c

    def __pow__(self, n):
        if(n == 1):
            return self
        if(n % 2 == 0):
            a = pow(self, n // 2)
            return a * a
        return self * pow(self, n - 1)

def main():
    p = Matrix(2, 2)
    p.fill([[0, 1], [1, 1]])
    #print(p)
    #print(pow(p, 2))
    a = Matrix(1, 2)
    a.fill([[0, 1]])
    print(a)
    print(a * pow(p, 5))
main()
