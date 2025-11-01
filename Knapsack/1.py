import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
data = pd.read_csv('knapsack_results.txt')
sizes = data['size']
times = data['time']
plt.figure(figsize=(10, 6))
plt.plot(sizes, times,'bo-', linewidth=2, markersize=8, label='knapsack')
plt.xlabel('Input Size (n)', fontsize=12)
plt.ylabel('Time (seconds)', fontsize=12)
plt.title('knapsack Time Complexity Analysis', fontsize=14, fontweight='bold')
plt.grid(True, alpha=0.3)
plt.legend()
for i, (size, time) in enumerate(zip(sizes, times)):
    if i % 2 == 0:
        plt.annotate(f'({size}, {time:.6f})',
(size, time),
xytext=(10, 10),
textcoords='oﬀset points',
fontsize=8,
alpha=0.7)
plt.tight_layout()
plt.savefig('knapsack.png', dpi=300, bbox_inches='tight')
plt.show()