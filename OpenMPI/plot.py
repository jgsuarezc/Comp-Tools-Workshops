import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def f(x):
    return x
data = pd.read_csv('data_cores.txt',sep='\s+',header=None)
data = pd.DataFrame(data)

#xtheo = np.linspace(0,6,6)
x = data[0]
y = 0.013582818/(data[0]*data[1])
plt.xlabel("n cores or process")
plt.ylabel("Parallel Efficiency")
plt.title("Efficiency vs number of process")

plt.plot(x, y,'r*')
plt.plot(x, y,'r')
#plt.plot(xtheo,f(xtheo))
plt.legend(["Total Rects =12000"])
plt.show()
