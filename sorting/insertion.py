import matplotlib.pyplot as plt

elements = [50,100,500,1000,3000,5000,6000, 7000, 8000]
times = [0.0,0.0,0.0,0.0,0.0,0.0,0.033490, 0.038369, 0.050250]

plt.figure(figsize=(8, 6))
plt.plot(elements, times, marker='o', linestyle='-', linewidth=2)

plt.xlabel("Number of Elements", fontsize=12)
plt.ylabel("Time Taken (seconds)", fontsize=12)
plt.title("Insertion Sort Performance", fontsize=14)
plt.grid(True)

plt.show()
