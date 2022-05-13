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

class Matrix2D:
    def __init__(self, n, m):
        self.matrix = [[0 for j in range(m)] for i in range(n)]
        self.size = (n, m)
 
    def __repr__(self):
        return "\n".join(["|" + " ".join([str(j) for j in i]) + "|" for i in self.matrix])
 
    def fill(self, arr):
        n, m = self.size
        for i in range(min(n, len(arr))):
            for j in range(min(m, len(arr[i]))):
                self.matrix[i][j] = arr[i][j] % MOD

    def unsafe_fill(self, arr):
        n, m = self.size
        for i in range(n):
            for j in range(m):
                self.matrix[i][j] = arr[i][j] % MOD
 
    def __add__(self, other):
        if(self.size != other.size):
            put("---error---")
            put("can not Matrix(%d, %d) add to Matrix(%d, %d)" % (self.size[0], self.size[1], other.size[0], other.size[1]))
            put("-----------")
            return None
        
        n, m = self.size
        for i in range(n):
            for j in range(m):
                self.matrix[i][j] += other.matrix[i][j]
                self.matrix[i][j] %= MOD
        return self
 
    def __mul__(self, other):
        n, k1 = self.size
        k2, m = other.size
        if(k1 != k2):
            put("---error---")
            put("cant Matrix(%d, %d) multiply by Matrix(%d, %d)" % (self.size[0], self.size[1], other.size[0], other.size[1]))
            put("-----------")
            return None
        
        c = Matrix2D(n, m)
        for i in range(n):
            for j in range(m):
                for k in range(k1):
                    c.matrix[i][j] += self.matrix[i][k] * other.matrix[k][j]
                    c.matrix[i][j] %= MOD
        return c

    def __pow__(self, n):
        if(n == 1):
            return self
        if(n % 2 == 0):
            a = pow(self, n // 2)
            return a * a
        return self * pow(self, n - 1)

def main():
    p = Matrix2D(2, 2)
    p.unsafe_fill([[2, 1], [1, 4]])
    a = Matrix2D(1, 2)
    a.unsafe_fill([[1, 1]])
    a1 = a * pow(p, 5)
    put(a1)
main()
