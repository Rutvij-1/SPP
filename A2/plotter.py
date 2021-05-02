from matplotlib import pyplot as plt
from os import listdir
from os.path import isfile, join


def extract(name):
    return name.split('.')[0]


files = sorted(
    [f for f in listdir("Q1") if isfile(join("Q1", f))], key=extract)
print(files)
timeu = []
with open("time_u.txt", "r") as f:
    lines = f.readlines()
    n = len(lines)
    for i in range(1, n, 2):
        line = lines[i]
        timeu.append(float(line.split()[-2]))
times = []
with open("time_s.txt", "r") as f:
    lines = f.readlines()
    n = len(lines)
    for i in range(1, n, 2):
        line = lines[i]
        times.append(float(line.split()[-2]))
timep = []
with open("time.txt", "r") as f:
    lines = f.readlines()
    n = len(lines)
    for i in range(1, n, 2):
        line = lines[i]
        timep.append(float(line.split()[-2]))
plt.plot(files, timep, label='Parallelly Optimized')
plt.plot(files, times, label='Sequentially Optimized')
plt.plot(files, timeu, label='Un-Optimized')
plt.xlabel('Test Case Files')
plt.ylabel('Time taken (in sec)')
plt.title(
    'Time Comparison between Parallelly Optimized, Sequentially Optimized and Unoptimized code for Chain Matrix Multiplication')
plt.legend()
plt.show()
