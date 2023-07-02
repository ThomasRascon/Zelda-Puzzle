# TODO: allow user to generate data by linking to cpp file
#       color code based on expected nonzero neighbors per space

import numpy as np
import matplotlib.pyplot as plt
import sys
import os.path


if(len(sys.argv)!=5):
    print('Enter width, height, sample size, and step size.')
    exit()

width = sys.argv[1]
height = sys.argv[2]
sampleSize = sys.argv[3]
stepSize = sys.argv[4]

inputFile = "Densities"+width+"by"+height+"Sampling"+sampleSize

if not os.path.isfile('OutputFiles/'+inputFile):
    print('File with specified parameters not found. Generate data with given parameters?')
    

# Create a new figure of size 8x6 points, using 100 dots per inch
plt.figure(figsize=(8,6), dpi=100)

plt.title('Solution Density VS Space Density for Width'+width+ 
             ', Height '+height+', Sample Size '+sampleSize+
             ', and Step Size '+stepSize)

x, y = np.loadtxt('OutputFiles/'+inputFile+'.dat', unpack=True)
plt.plot(x,y, color='blue', linewidth=1.0, linestyle='-')

plt.xticks(np.arange(0,1,.1))
plt.yticks(np.arange(0,1,.1))

plt.xlabel('Space Density', fontsize=15)
plt.ylabel('Solution Density', fontsize=15)


plt.savefig('OutputFiles/'+inputFile+'.pdf')

plt.show()