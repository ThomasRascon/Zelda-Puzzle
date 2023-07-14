# TODO: allow user to generate data by linking to cpp file (1st priority)
#       color code based on expected nonzero neighbors per space
#       add tag for saving or not saving data

import numpy as np
import matplotlib.pyplot as plt
import sys
import os.path


SOLN_DENSITY = 1

if(SOLN_DENSITY):
    place = 'SolutionDensity/'
    y_value = 'Solution Density'
else: 
    place = 'Solutionness/'
    y_value = 'Solutionness'


if(len(sys.argv)!=4):
    print('Enter width, height, sample size.')
    exit()

width = sys.argv[1]
height = sys.argv[2]
sampleSize = sys.argv[3]

inputFile = width+"by"+height+"Sampling"+sampleSize

if not os.path.isfile('OutputFiles/'+place+inputFile+'.dat'):
    print('File with specified parameters not found. Generate data with given parameters?')
    

def expected_neighbors(k):
    return (2*k/(height*width))(2-(1/height)-(1/width))

# Create a new figure of size 8x6 points, using 100 dots per inch
plt.figure(figsize=(8,6), dpi=100)

plt.title(y_value+' VS Space Density for Width '+width+ 
             ', Height '+height+', Sample Size '+sampleSize)

x, y = np.loadtxt('OutputFiles/'+place+inputFile+'.dat', unpack=True)
plt.plot(x,y, color='blue', linewidth=1.0, linestyle='-')

x, y = np.loadtxt('OutputFiles/'+place+'AllPointsOf'+inputFile+'.dat', unpack=True)
plt.scatter(x, y, alpha=0.2, s=20)

plt.xticks(np.arange(0,1,.1))
plt.yticks(np.arange(0,1,.1))

plt.xlabel('Space Density', fontsize=15)
plt.ylabel(y_value, fontsize=15)


plt.savefig('OutputFiles/'+place+inputFile+'.pdf')

plt.show()