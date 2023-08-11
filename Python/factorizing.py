def gcd(a, b):
    if(b == 0):
        return a
    return gcd(b, a % b)

def prob_prime(n):
    b = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41]
    for d in b:
        if(n == d):
            return True
        if(n % d == 0):
            return False
        r = pow(d, n - 1, n)
        if(abs(r) != 1):
            return False
        r = pow(d + 1, n, n) - (pow(d, n, n) + 1)
        if(r > 0):
            return False
    return True

def isqrt(n):
    if(n < 0):
        n *= -1
    k = int(pow(n, 0.5))
    return k

def is_square(n):
    k = isqrt(n)
    return k * k == n 

def rho_alg(n, c):
    
    def f(x):
        return (x * x + c) % n

    x = f(1)
    y = f(x)
    lmt = 10 ** 3
    #lmt <= 10 ** 4.5
    for _ in range(lmt):
        x = f(x)
        y = f(f(y))
        g = gcd(x*x - y*y, n)
        if(1 < g < n):
            return g
    return n

def squfof(n, k):
    P = [isqrt(k * n)]
    Q = [1, k * n - P[0] ** 2]
    i = 1
    while(is_square(Q[i]) == False):
        b_i = (P[0] + P[i - 1]) // Q[i]
        P += [b_i * Q[i] - P[i - 1]]
        Q += [Q[i - 1] + b_i * (P[i - 1] - P[i])]
        i += 1
    b_0 = (P[0] - P[i - 1]) // isqrt(Q[i])
    P = [b_0 * isqrt(Q[i]) + P[i - 1]]
    Q = [isqrt(Q[i])]
    Q += [(k * n - P[0] ** 2) // Q[0]]
    i = 0
    while(i > 0 and P[i] != P[i - 1]):
        b_i = (P[0] + P[i - 1]) // Q[i]
        P += [b_i * Q[i] - P[i - 1]]
        Q += [Q[i - 1] + b_i * (P[i - 1] - P[i])]
        i += 1
    return gcd(n, P[i])

def fact(n):
    i = 2
    F = []
    while(i * i * i <= n):
        if(n % i == 0):
            while(n % i == 0):
                n //= i
                F += [i]
        i += 1
    
    if(n == 1):
        return F
    if(prob_prime(n)):
        return F + [n]
    s = isqrt(n)
    if(s * s == n):
        return F + [s, s]

    base = [1, 3, 5, 7]
    for k in base:
        d = rho_alg(n, k)
        #d = squfof(n, k)
        if(1 < d < n):
            return F + [d, n // d]

    return F + [n]

def main():
    n = int(input())
    f = fact(n)
    print(f)
main()
