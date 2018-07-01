#!/usr/bin/python3

import random

tests_num = 1000
MAX_CABS = 20000
MAX_REQS = 20000
MAX_UID = 20000

print(tests_num)
for i in range(tests_num):
    N = random.randint(5, MAX_CABS)
    M = random.randint(5, MAX_REQS)
    ready = [x for x in range(MAX_UID)]
    busy = []
    print("{} {}".format(N, M))
    for j in range(M):
        uid = 0
        dr = 0
        if (len(busy) == 0):
            dr = 1
        elif (len(busy) == N):
            dr = 2
        else:
            dr = random.randint(1, 2)

        if (dr == 1):
            uid = ready.pop(random.randint(0, len(ready)-1))
            busy.append(uid)
        else:
            uid = busy.pop(random.randint(0, len(busy)-1))
            ready.append(uid)
        print("{} {}".format(dr, uid))

