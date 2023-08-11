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

def phi(n):
    ans = n
    i = 2
    while(i * i <= n):
        if(n % i == 0):
            ans -= ans // i
            while(n % i == 0):
                n //= i
        i += 1
    if(n > 1):
        ans -= ans // n
    return ans

def main():
    n = int(get())
    phi_a = [i for i in range(n + 1)]
    i = 2
    cnt = 0
    while(i <= n):
        if(phi_a[i] == i):
            #(phi_a[i] == i) => (i is prime)
            phi_a[i] -= 1
            #phi(prime) = prime - 1
            j = i * 2
            while(j <= n):
                phi_a[j] -= phi_a[j]//i
                j += i
        i += 1
    #phi_a[i] = phi(i)
main()
