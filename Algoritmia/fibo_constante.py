import math

def fibo(t_n):
    n = t_n + 1
    return math.trunc(1/(5**0.5)*abs((((1+(5**0.5))/2)**n)-(((1-(5**0.5))/2)**n)))

for i in range(11):
    print(fibo(i))