#!/usr/bin/env python3
import random

tests = 50
print(tests)

for test in range(0, tests):
    dig = []
    sym = []

    n = random.randint(1,10)
    o = random.randint(1,4)
    m = random.randint(4,20)
    print(n, o, m)

    i = n
    while(i != 0):
        i = i - 1
        d = random.randint(0,9)
        if (d in dig):
            i = i + 1
        else:
            print(d, end=' ')
            dig.append(d)
    print()

    i = o
    while(i != 0):
        i = i - 1
        s = random.randint(1,4)
        if (s in sym):
            i = i + 1
        else:
            print(s, end=' ')
            sym.append(s)
    print()

    w = random.randint(0,999)
    print(w)
