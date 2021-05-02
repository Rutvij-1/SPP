from matplotlib import pyplot as plt

files1 = ["0.txt", "5.txt", "10.txt", "15.txt", "20.txt",
          "30.txt", "40.txt", "50.txt", "55.txt", "60.txt",
          "70.txt", "75.txt", "80.txt", "85.txt", "90.txt"]
files2 = ["t6", "t19", "t29", "t31", "t43", "t49", "t75", "t77",
          "t78", "t91"]
time1o = [0.008515585, 0.019653597, 0.015463830, 0.020043642,
          0.352398048, 0.100993559, 1.125018476, 0.057257166,
          0.771221822, 0.144838158, 4.389843584, 2.993409156,
          1.585746356, 1.661027184, 8.526596750]
time1u = [0.018180014, 0.044525745, 0.034943607, 0.044617234,
          0.847854777, 0.589578988, 10.639992278, 0.063972803,
          7.654112832, 0.157762324, 28.329546915, 23.487757354,
          12.094196424, 12.121997897, 74.111655268]
time2o = [0.093261194, 23.486831558, 34.476143466, 0.029922887,
          0.153811950, 0.076883681, 0.128191855, 22.153771591,
          0.089074441, 0.112954690]
time2u = [0.235298608, 61.990595090, 91.608344280, 0.094304077,
          0.396301783, 0.198945531, 0.327734577, 58.446569704,
          0.226341573, 0.294993977]
plt.plot(files1, time1o, label='Optimized')
plt.plot(files1, time1u, label='Un-Optimized')
plt.xlabel('Test Case Files')
plt.ylabel('Time taken (in sec)')
plt.title(
    'Time Comparison between Optimized and Unoptimized code for Sequential Matrix Multiplication')
plt.legend()
plt.show()
plt.plot(files2, time2o, label='Optimized')
plt.plot(files2, time2u, label='Un-Optimized')
plt.xlabel('Test Case Files')
plt.ylabel('Time taken (in sec)')
plt.title(
    'Time Comparison between Optimized and Unoptimized code for Floyd Warshall Algorithm')
plt.legend()
plt.show()
