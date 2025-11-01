import matplotlib.pyplot as plt

n_values = [50, 100, 500, 1000, 3000, 5000, 6000, 7000, 8000]
time_values = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.000490, 0.000572, 0.000663]

plt.plot(n_values, time_values, marker='o', linestyle='-', color='r', label="QuickSort")
plt.title("QuickSort Time Complexity")
plt.xlabel("Input Size (n)")
plt.ylabel("Time Taken (seconds)")
plt.grid(True)
plt.legend()
plt.show()
