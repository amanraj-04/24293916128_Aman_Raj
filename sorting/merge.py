import matplotlib.pyplot as plt

n_values = [50, 100, 500, 1000, 3000, 5000, 6000, 7000, 8000]
time_values = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.000665, 0.000764, 0.000863]

plt.plot(n_values, time_values, marker='o', linestyle='-', color='b', label="Merge Sort")
plt.title("Merge Sort Time Complexity")
plt.xlabel("Input Size (n)")
plt.ylabel("Time Taken (seconds)")
plt.grid(True)
plt.legend()
plt.show()
