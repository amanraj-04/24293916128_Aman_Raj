import matplotlib.pyplot as plt

n_values = [50,100,500,1000,3000,5000,6000, 7000, 8000]
times = [0.0,0.0,0.0,0.0,0.0,0.0,0.053859, 0.065763, 0.077839]

plt.plot(n_values, times, marker='o', linestyle='-', color='b', label="Selection Sort")
plt.xlabel("Number of Elements (n)")
plt.ylabel("Time Taken (seconds)")
plt.title("Selection Sort Time Complexity")
plt.legend()
plt.grid(True)
plt.show()
