import numpy as np
import matplotlib.pyplot as plt

# Create a new figure of size 8x6 points, using 100 dots per inch
plt.figure(figsize=(8,6), dpi=100)

x, y = np.loadtxt('OutputFiles/Density10by3.dat', unpack=True)
plt.plot(x,y, color='blue', linewidth=1.0, linestyle='-', label='Height$=4$, Width$=4$, Step Size$=.01$')

plt.xlabel('Valid Space Density', fontsize=15)
plt.ylabel('Solution Density', fontsize=15)

plt.legend(loc='upper left', fontsize=15)



plt.savefig('DensityPlot10by3.pdf')

plt.show()