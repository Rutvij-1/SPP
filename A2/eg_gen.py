import random

# n = random.randint(1, 5)
n = 5
print(n)
# dim = [random.randint(1, 1000) for _ in range(n+1)]
dim = [1000 for _ in range(n+1)]
for i in range(n):
    print(dim[i], dim[i+1])
    for _ in range(dim[i]):
        for __ in range(dim[i+1]):
            print(random.randint(-10, 10), end=" ")
        print('')
