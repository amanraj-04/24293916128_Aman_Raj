import matplotlib.pyplot as plt

# Recorded results (example values, replace with your actual runs)
n_values = [0.0,0.0,0.0,0.0,0.0,0.0,6000, 7000, 8000, 9000, 10000]
time_values = [0.0,0.0,0.0,0.0,0.0,0.0,0.072, 0.095, 0.120, 0.150, 0.185]

plt.plot(n_values, time_values, marker='o', color='red', label="Bubble Sort")
plt.title("Bubble Sort Time Complexity")
plt.xlabel("Number of Elements (n)")
plt.ylabel("Time Taken (seconds)")
plt.legend()
plt.grid(True)
plt.show()
