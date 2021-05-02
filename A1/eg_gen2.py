import random

v = random.randint(1, 2500)
e = random.randint(1, int(1e5))
print(v, e)
for _ in range(e):
    print(random.randint(1, v), random.randint(
        1, v), random.randint(1, int(1e5)))
