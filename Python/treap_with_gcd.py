from sys import stdout
from sys import stdin

def get():
    return stdin.readline().strip()
def getf():
    return [int(i) for i in get().split()]
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
from math import gcd

class treap:
    
    def __init__(self, maxn):
        self.l = [None] * maxn
        self.r = [None] * maxn
        
        self.prior = [None] * maxn
        self.key = [None] * maxn
        self.gcd = [None] * maxn
        
        self.free_ind = 1
        self.root = 0

        self.gcd[0] = 0
        self.prior[0] = randint(0, 10 ** 18)
        self.key[0] = 0

    def new_node(self, key):
        self.key[self.free_ind] = key
        self.gcd[self.free_ind] = key
        self.prior[self.free_ind] = randint(0, 10 ** 18)
        
        self.free_ind += 1
        
        return self.free_ind - 1

    def upd_gcd(self, t):
        if(t == None):
            return None

        self.gcd[t] = self.key[t]
        if(self.l[t] != None):
            self.gcd[t] = gcd(self.gcd[t], self.gcd[self.l[t]])
        if(self.r[t] != None):
            self.gcd[t] = gcd(self.gcd[t], self.gcd[self.r[t]])

    def merge(self, lt, rt):
        if(lt == None):
            return rt
        if(rt == None):
            return lt
        
        if(self.prior[lt] < self.prior[rt]):
            self.l[rt] = self.merge(lt, self.l[rt])
            self.upd_gcd(rt)
            
            return rt
        else:
            self.r[lt] = self.merge(self.r[lt], rt)
            self.upd_gcd(lt)
            
            return lt

    def split(self, t, val):
        if(t == None):
            return (None, None)
        
        if(self.key[t] < val):
            lt, rt = self.split(self.r[t], val)
            self.r[t] = lt
            self.upd_gcd(t)
            
            return (t, rt)
        else:
            lt, rt = self.split(self.l[t], val)
            self.l[t] = rt
            self.upd_gcd(t)
            
            return (lt, t)

    def insert(self, val):
        lt, rt = self.split(self.root, val)
        node = self.new_node(val)
        
        self.root = self.merge(self.merge(lt, node), rt)

    def erase(self, val):
        lt, mt = self.split(self.root, val)
        _, rt = self.split(mt, val + 1)

        self.root = self.merge(lt, rt)

def main():

    pass
    
main()
