#!/usr/bin/env python3
import random

tests = 100000
print(tests)

for test in range(0, tests):
    n = random.randint(2,25)
    m = random.randint(n,50)
    print(n, m)

    for i in range(0, m):
        print(random.randint(1,100000), end=' ')

    print()

